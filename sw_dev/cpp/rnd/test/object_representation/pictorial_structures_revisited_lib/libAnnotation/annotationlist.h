
#ifndef ANNOTATIONLIST
#define ANNOTATIONLIST

#include <vector>

#include <libAnnotation/annotation.h>


class AnnotationList
{
public:
  AnnotationList(){};
  AnnotationList(const std::string& file){load(file);};
  ~AnnotationList(){};

  //AnnotationList(const AnnotationList& other);
private:
  Annotation m_emptyAnnotation;//needed when returning const Annotation&
  std::vector<Annotation> m_vAnnotations;

  std::string m_sName;
  std::string m_sPath;

public:
  std::vector<std::string> fileList() const;
  void getFileList(std::vector<std::string>& list) const;

  //--- Content Access ---//
  std::string name() const {return m_sName;};
  std::string path() const {return m_sPath;};

  unsigned size() const {return m_vAnnotations.size();};

  const Annotation& annotation(unsigned i) const {return m_vAnnotations[i];};
  Annotation& annotation(unsigned i) {return m_vAnnotations[i];};
  
  const Annotation& operator[]  (unsigned i) const {return m_vAnnotations[i];};
  Annotation& operator[] (unsigned i) {return m_vAnnotations[i];};
  
  const Annotation& findByName(const std::string&, int frameNr = -1) const;
  Annotation& findByName(const std::string&, int frameNr = -1);
  int getIndexByName(const std::string&, int frameNr = -1) const;

  void addAnnotation(const Annotation& anno) {m_vAnnotations.push_back(anno);};
  void addAnnotationByName(const std::string&, int frameNr = -1);

  void mergeAnnotationList(const AnnotationList&);

  void removeAnnotationByName(const std::string&, int frameNr = -1);
  void clear(){m_vAnnotations.clear();};

  //--- IO ---//
  void printXML() const;
  void printIDL() const;

  void save(const std::string&, bool bSaveRelativeToHome = false) const;
  void saveXML(const std::string&, bool bSaveRelativeToHome = false) const;
  void saveIDL(const std::string&, bool bSaveRelativeToHome = false) const;

  void load(const std::string&);
  void loadXML(const std::string&);
  void loadIDL(const std::string&);
};


#endif
