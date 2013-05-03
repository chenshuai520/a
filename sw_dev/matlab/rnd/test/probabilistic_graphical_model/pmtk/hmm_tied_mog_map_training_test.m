%----------------------------------------------------------
% MAP estimates for HMM w/ tied mixture-of-Gaussians observations
% [ref] ${PMTK_HOME}/demos/hmmMixGaussTiedTest.m

%----------------------------------------------------------

% [Caution]
%	${PMTK_HOME}/initPmtk3.m ���� ��, run�� ����Ͽ� M file�� �����ϸ� ���������� ������� ����.
%	PMTK library�� run �Լ��� �����ϰ� �־, Matlab���� �����ϴ� �⺻ run �Լ��� ���������� �������� ����.
%		${PMTK_HOME}/projects/Emt/FA/BXPCA/run.m

% at desire.kaist.ac.kr
%run('D:\work_center\sw_dev\matlab\rnd\src\probabilistic_graphical_model\pmtk\pmtk3-1nov12\initPmtk3.m');
%cd('D:\work_center\sw_dev\matlab\rnd\test\probabilistic_graphical_model\pmtk');

%----------------------------------------------------------
loadData('speechDataDigits4And5');
data = [train4'; train5'];
d = 13;
nstates = 2;
nmix = 3;  % must specify nmix

model = hmmFit(data, nstates, 'mixGaussTied', 'verbose', true, ...
    'nRandomRestarts', 2, 'maxiter', 5, 'nmix', nmix); 

if 0
    localev = hmmObs2LocalEv(data);
    localev(1:3:end) = nan;  % use dgmTrain for arbitrarily missing local ev
    Tmax = 131;  % maximum length of the sequences.
    dgm = hmmToDgm(model, Tmax);

    dgm2 = dgmTrain(dgm, 'localev', localev, 'verbose', true);
end

% This doesn't actually test anything!
