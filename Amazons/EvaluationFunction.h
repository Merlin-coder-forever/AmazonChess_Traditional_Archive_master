 // evaluationfunction.h: interface for the evaluationfunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_)
#define AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EvaluationFunction  
{
public:
	EvaluationFunction();
	
	void copy(BYTE position[][12]);

    void KingMoveSearch();
	void QueenMoveSearch();
    void MobilitySearch();

	void MobilityCount();
	void t1Count();
	void t2Count();
	void c1Count();
	void c2Count();
	void wCount();
	void aCount();
    double Evaluation(BYTE position[][12],int side);

	virtual ~EvaluationFunction();

	// Generated message map functions

    int nSide;//0-white,1-black;

	BYTE kingMoveWhite[12][12];
	BYTE queenMoveWhite[12][12];

    BYTE kingMoveBlack[12][12];
	BYTE queenMoveBlack[12][12];

	BYTE currentPosition[12][12];
	BYTE mobility[12][12];

	double t1;
	double t2;
	double c1;
	double c2;
	double w;
	int aWhite[4];
	int aBlack[4];

	
	
};



#endif // !defined(AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_)
