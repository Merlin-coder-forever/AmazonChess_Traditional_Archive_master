#include "StdAfx.h"
#include "AmazonsGameController.h"
#include "AmazonsAI.h"


void ExChangeInt(BYTE &x, BYTE &y) {
	BYTE tmp = 0;
	tmp = x;
	x = y;
	y = tmp;
}

void CAmazonsAI::AICompute(
	int plate[10][10],			//棋盘数据
	SPosition pieces[],			//8个棋子的位置，长度为9
	bool isPlayer1,				//是否是作为玩家1进行计算，否则作为玩家2进行计算
	SPosition& outPosSelected,	//输出着子
	SPosition& outPosMoveTo,	//输出着子
	SPosition& outPosShootAt)	//输出着子
{
	m_nOutMaxValue = 0;
	m_nOutDepth = 0;
	m_nOutNumOfMoves = 0;
	m_nOutNumOfNodes = 0;
	m_nOutNumOfSkippedNodes = 0;

	bool bFinished = false;


	while (!bFinished)
	{
		BYTE position[12][12];
		for (int i = 0; i<12; i++)
		{
			for (int j = 0; j<12; j++)
			{
				position[i][j] = 1;
			}
		}

		for (int i = 1; i<11; i++)
		{
			for (int j = 1; j<11; j++)
			{
				if (plate[i - 1][j - 1] == -1) {
					position[i][j] = 1;
				}
				else {
					position[i][j] = plate[i - 1][j - 1];
					if (plate[i - 1][j - 1] == 1 || plate[i - 1][j - 1] == 2 || plate[i - 1][j - 1] == 3 || plate[i - 1][j - 1] == 4 ) {
						position[i][j] = 3;
					}
					if (plate[i - 1][j - 1] == 5 || plate[i - 1][j - 1] == 6 || plate[i - 1][j - 1] == 7 || plate[i - 1][j - 1] == 8) {
						position[i][j] = 2;
					}
				}
			}
		}

		for (int i = 1; i < 11; i++)
		{
			for (int j = 1; j < 11; j++)
			{
				if (j <= i)
					ExChangeInt(position[i][j], position[j][i]);
			}
		}

		SearchEngine A;// in file Searchengine.h
		Move bestMove;// in file: movegenerator.h
		////////////计时
		int timecount;
		bestMove = A.searchMove(position, !isPlayer1, m_nOutDepth, m_nOutMaxValue, m_nOutNumOfNodes);
		bestMove.priviousX--;
		bestMove.priviousY--;
		bestMove.x--;
		bestMove.barX--;
		bestMove.y--;
		bestMove.barY--;
		ExChangeInt(bestMove.priviousX, bestMove.priviousY);
		ExChangeInt(bestMove.x, bestMove.y);
		ExChangeInt(bestMove.barX, bestMove.barY);

		//选择棋子
		int piece = 0;
		if (pieces[1].i == bestMove.priviousX && pieces[1].j == bestMove.priviousY) {
			piece = 0;
		}
		if (pieces[2].i == bestMove.priviousX && pieces[2].j == bestMove.priviousY) {
			piece = 1;
		}
		if (pieces[3].i == bestMove.priviousX && pieces[3].j == bestMove.priviousY) {
			piece = 2;
		}
		if (pieces[4].i == bestMove.priviousX && pieces[4].j == bestMove.priviousY) {
			piece = 3;
		}
		if (pieces[5].i == bestMove.priviousX && pieces[5].j == bestMove.priviousY) {
			piece = 4;
		}
		if (pieces[6].i == bestMove.priviousX && pieces[6].j == bestMove.priviousY) {
			piece = 5;
		}
		if (pieces[7].i == bestMove.priviousX && pieces[7].j == bestMove.priviousY) {
			piece = 6;
		}
		if (pieces[8].i == bestMove.priviousX && pieces[8].j == bestMove.priviousY) {
			piece = 7;
		}

		piece++;
		outPosSelected = pieces[piece];

		//走子位置
		SPosition pos;
		pos.i = bestMove.x;
		pos.j = bestMove.y;

		if (CAmazonsGameController::CanMoveOrShoot(plate, pieces, outPosSelected, pos))
		{
			CAmazonsGameController::Move(plate, pieces, outPosSelected, pos);
			outPosMoveTo = pos;
		}
		else
			continue;

		//放箭
		pos.i = bestMove.barX;
		pos.j = bestMove.barY;

		if (CAmazonsGameController::CanMoveOrShoot(plate, pieces, outPosMoveTo, pos))
		{
			outPosShootAt = pos;
			bFinished = true;
		}
		else
		{
			CAmazonsGameController::CancelMove(plate, pieces, outPosSelected, outPosMoveTo);
		}
	}
}
