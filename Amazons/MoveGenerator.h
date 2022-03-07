#if !defined(AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_)
#define AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Move
{
	BYTE x;
	BYTE y;
	BYTE priviousX;
	BYTE priviousY;
	BYTE barX;
	BYTE barY;
	double score;
 

};

class MoveGenerator
{
public:
	MoveGenerator();
    virtual ~MoveGenerator();

	int CreatePossibleMove(BYTE position[][12],int side,int nply);
	int CreatePossibleBar(BYTE position[][12],int x,int y,int lx,int ly,int nply);



public:
	Move moveLine[10][2500];
	int moveCount;

};

#endif // !defined(AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_)
