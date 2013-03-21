#ifndef FSTSEARCHBRANCHANDBOUNDPARTIALPREDICTION_H
#define FSTSEARCHBRANCHANDBOUNDPARTIALPREDICTION_H

/*!======================================================================
   Feature Selection Toolbox 3 source code
   ---------------------------------------
	
   \file    search_branch_and_bound_partial_prediction.hpp
   \brief   Implements Branch and Bound with Partial Prediction (BBPP) method, i.e., with predicted node ordering
   \author  Petr Somol (somol@utia.cas.cz) with collaborators, see Contacts at http://fst.utia.cz
   \date    March 2011
   \version 3.1.0.beta
   \note    FST3 was developed using gcc 4.3 and requires
   \note    \li Boost library (http://www.boost.org/, tested with versions 1.33.1 and 1.44),
   \note    \li (\e optionally) LibSVM (http://www.csie.ntu.edu.tw/~cjlin/libsvm/, 
                tested with version 3.00)
   \note    Note that LibSVM is required for SVM related tools only,
            as demonstrated in demo12t.cpp, demo23.cpp, demo25t.cpp, demo32t.cpp, etc.

*/ /* 
=========================================================================
Copyright:
  * FST3 software (with exception of any externally linked libraries) 
    is copyrighted by Institute of Information Theory and Automation (UTIA), 
    Academy of Sciences of the Czech Republic.
  * FST3 source codes as presented here do not contain code of third parties. 
    FST3 may need linkage to external libraries to exploit its functionality
    in full. For details on obtaining and possible usage restrictions 
    of external libraries follow their original sources (referenced from
    FST3 documentation wherever applicable).
  * FST3 software is availables free of charge for non-commercial use. 
    Please address all inquires concerning possible commercial use 
    of FST3, or if in doubt, to FST3 maintainer (see http://fst.utia.cz).
  * Derivative works based on FST3 are permitted as long as they remain
    non-commercial only.
  * Re-distribution of FST3 software is not allowed without explicit
    consent of the copyright holder.
Disclaimer of Warranty:
  * FST3 software is presented "as is", without warranty of any kind, 
    either expressed or implied, including, but not limited to, the implied 
    warranties of merchantability and fitness for a particular purpose. 
    The entire risk as to the quality and performance of the program 
    is with you. Should the program prove defective, you assume the cost 
    of all necessary servicing, repair or correction.
Limitation of Liability:
  * The copyright holder will in no event be liable to you for damages, 
    including any general, special, incidental or consequential damages 
    arising out of the use or inability to use the code (including but not 
    limited to loss of data or data being rendered inaccurate or losses 
    sustained by you or third parties or a failure of the program to operate 
    with any other programs).
========================================================================== */

#include <boost/smart_ptr.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib> //rand
#include "branch_and_bound_predictor.hpp"
#include "search_branch_and_bound.hpp"
#include "error.hpp"
#include "global.hpp"
#include "result_tracker.hpp"

/*============== Template parameter type naming conventions ==============
--------- Numeric types: -------------------------------------------------
DATATYPE - data sample values - usually real numbers (but may be integers
          in text processing etc.)
REALTYPE - must be real numbers - for representing intermediate results of 
          calculations like mean, covariance etc.
IDXTYPE - index values for enumeration of data samples - (nonnegative) integers, 
          extent depends on numbers of samples in data
DIMTYPE - index values for enumeration of features (dimensions), or classes (not 
          class sizes) - (nonnegative) integers, usually lower extent than IDXTYPE, 
          but be aware of expressions like _classes*_features*_features ! 
          in linearized representations of feature matrices for all classes
BINTYPE - feature selection marker type - represents ca. <10 different feature 
          states (selected, deselected, sel./desel. temporarily 1st nested loop, 2nd...)
RETURNTYPE - criterion value: real value, but may be extended in future to support 
          multiple values 
--------- Class types: ---------------------------------------------------
SUBSET       - class of class type Subset 
CLASSIFIER   - class implementing interface defined in abstract class Classifier 
EVALUATOR    - class implementing interface defined in abstract class Sequential_Step 
DISTANCE     - class implementing interface defined in abstract class Distance 
DATAACCESSOR - class implementing interface defined in abstract class Data_Accessor 
INTERVALCONTAINER - class of class type TIntervaller 
CONTAINER    - STL container of class type TInterval  
========================================================================== */

namespace FST {

/*! \brief Implements Branch and Bound with Partial Prediction (BBPP) method, i.e., with predicted node ordering

	BBPP is generally slower than FBB but faster than IBB. Its principle is
	identical to that of Improved Branch & Bound (IBB), but it replaces
	large amount of criterion evaluations needed for ordering nodes in tree levels
	by quickly predicted values. The optimality of final result is not jeopardized
	but considerable amount of time is saved. See FBB for a more radical but still
	optimality preserving use of value prediction.

	\warning All Branch & Bound feature selection algorithms require the used
	CRITERION to be monotonic with respect to cardinality. More precisely, it must
	hold that removing a feature from a set MUST NOT increase criterion value.
	Otherwise there is no guarantee as of the optimality of obtained results
	with respect to the used criterion.

	\note All Branch & Bound algorithms by definition yield the solution with the 
	same maximum criterion value, therefore the main concern regarding particular
	Branch & Bound algorithm is only its search speed.

	\note Due to possibly high number of subsets to be tested expect
	excessive computational time. 
	
	\note Result tracking in case of Branch & Bound algorithms records only results
	of target cardinality.
*/

template<class RETURNTYPE, typename DIMTYPE, class SUBSET, class CRITERION, class PREDICTOR>
class Search_Branch_And_Bound_Partial_Prediction : public Search_Branch_And_Bound<RETURNTYPE,DIMTYPE,SUBSET,CRITERION>{
public:
	typedef Search_Branch_And_Bound<RETURNTYPE,DIMTYPE,SUBSET,CRITERION> parent;
	typedef typename parent::PCriterion PCriterion;
	typedef typename parent::PSubset PSubset;
	typedef typename parent::PNode PNode;
	typedef typename parent::Node Node;
	typedef typename parent::NodeType NodeType;
	Search_Branch_And_Bound_Partial_Prediction():Search_Branch_And_Bound<RETURNTYPE,DIMTYPE,SUBSET,CRITERION>() {notify("Search_Branch_And_Bound_Partial_Prediction constructor.");}
	virtual ~Search_Branch_And_Bound_Partial_Prediction() {notify("Search_Branch_And_Bound_Partial_Prediction destructor.");}

	// for search() implementation see parent class

	virtual std::ostream& print(std::ostream& os) const {os << "Branch & Bound with Partial Prediction (BBPP)  [Search_Branch_And_Bound_Partial_Prediction() with " << _predictor << "]"; return os;};
protected:
	PREDICTOR _predictor;
	
	// the following may be overriden in descendant Branch and Bound specialization classes
	virtual void initialize(const DIMTYPE d, const DIMTYPE n, const PCriterion crit) {_predictor.initialize(n);} //!< called before search - enables set-up of additional structures in descendants
	virtual void process_leafs();
	virtual void pre_evaluate_availables(); //!< assign values to each feature in availables - to be used for node ordering
	virtual void post_process_tree_level(); //!< enables to substitute missing COMPUTED values in nodes just after level creation, if needed
	virtual bool cut_possible(); //!< tests current node for the possibility to cut its sub-branch
};

template<class RETURNTYPE, typename DIMTYPE, class SUBSET, class CRITERION, class PREDICTOR>
void Search_Branch_And_Bound_Partial_Prediction<RETURNTYPE,DIMTYPE,SUBSET,CRITERION,PREDICTOR>::process_leafs()
{
	assert(parent::get_criterion());
	const PSubset &currentset=parent::get_currentset();
	Node &parentnode=parent::get_parent_node();
	RETURNTYPE value;
	PNode avail;
	for(bool got=getFirstAvailable(avail);got;got=getNextAvailable(avail)) 
	{
		assert(currentset->selected_raw(avail->feature));
		currentset->deselect_raw(avail->feature);
		if(!parent::get_criterion()->evaluate(value,currentset)) throw FST::fst_error("Criterion evaluation failure."); 
		update_bound(value,currentset); //adds to tracker
		// conditionally update prediction info
		if(parentnode.type==parent::COMPUTED) _predictor.learn(avail->feature,parentnode.value-value);
		currentset->select_raw(avail->feature);
	}
}

template<class RETURNTYPE, typename DIMTYPE, class SUBSET, class CRITERION, class PREDICTOR>
void Search_Branch_And_Bound_Partial_Prediction<RETURNTYPE,DIMTYPE,SUBSET,CRITERION,PREDICTOR>::pre_evaluate_availables() 
{
	assert(parent::get_criterion());
	const PSubset &currentset=parent::get_currentset(); assert(currentset);
	Node &parentnode=parent::get_parent_node(); assert(parentnode.type==parent::COMPUTED);

	// pre-evaluate available features before next tree level construction
	PNode avail;
	RETURNTYPE val;
	for(bool got=getFirstAvailable(avail);got;got=getNextAvailable(avail)) 
	{
		if(_predictor.predict(avail->feature,val)) { //value could be predicted
			avail->value=parentnode.value-val;
			avail->type=parent::PREDICTED;
		} else { //value could not be predicted
			assert(currentset->selected_raw(avail->feature));
			currentset->deselect_raw(avail->feature);
			if(!parent::get_criterion()->evaluate(avail->value,currentset)) throw FST::fst_error("Criterion evaluation failure."); 
			avail->type=parent::COMPUTED;
			currentset->select_raw(avail->feature);
			// conditionally update prediction info
			if(parentnode.type==parent::COMPUTED) _predictor.learn(avail->feature,parentnode.value-avail->value);
		}
	}
}

template<class RETURNTYPE, typename DIMTYPE, class SUBSET, class CRITERION, class PREDICTOR>
void Search_Branch_And_Bound_Partial_Prediction<RETURNTYPE,DIMTYPE,SUBSET,CRITERION,PREDICTOR>::post_process_tree_level()
{
	assert(parent::get_criterion());
	const PSubset &currentset=parent::get_currentset();	assert(currentset);
	Node &parentnode=parent::get_parent_node();	assert(parentnode.type==parent::PREDICTED || parentnode.type==parent::COMPUTED);

	// enable to re-evaluate chosen candidate values (e.g., supply missing true criterion values, etc.)
	PNode nod;
	for(bool got=getFirstNode(nod);got;got=getNextNode(nod)) 
	{
		if(nod->type!=parent::COMPUTED) {
			assert(currentset->selected_raw(nod->feature));
			currentset->deselect_raw(nod->feature);
			if(!parent::get_criterion()->evaluate(nod->value,currentset)) throw FST::fst_error("Criterion evaluation failure."); 
			nod->type=parent::COMPUTED;
			currentset->select_raw(nod->feature);
			// conditionally update prediction info
			if(parentnode.type==parent::COMPUTED) _predictor.learn(nod->feature,parentnode.value-nod->value);
		}
	}
}

template<class RETURNTYPE, typename DIMTYPE, class SUBSET, class CRITERION, class PREDICTOR>
bool Search_Branch_And_Bound_Partial_Prediction<RETURNTYPE,DIMTYPE,SUBSET,CRITERION,PREDICTOR>::cut_possible()
{
	if(parent::is_bound_valid()) {
		Node &currentnode=parent::get_current_node(); assert(currentnode.type==parent::COMPUTED);
		if(currentnode.value<=parent::get_bound_value()) { // BBPP ensures that the value must have been COMPUTED by now
			return true;
		}
	}
	return false;
}

} // namespace
#endif // FSTSEARCHBRANCHANDBOUNDPARTIALPREDICTION_H ///:~
