#ifndef AMAZONS_AI__H
#define AMAZONS_AI__H

#include "AmazonsGameController.h"
#include "MoveGenerator.h"
#include "Searchengine.h"
#include <cstdio>
#include <direct.h>
#include <ctime>
#include <string>
#include <iostream>


class CAmazonsAI
{
public:
	int m_nOutMaxValue;//(输硜E计算畜评估值
	int m_nOutDepth;//(输硜E计算甥胰
	int m_nOutNumOfMoves;//(输硜E计算着法数
	int m_nOutNumOfNodes;//(输硜E计算产生的节点数(真正的树的节点数)(调试用)
	int m_nOutNumOfSkippedNodes;//(输硜E计算遍历过的节点数(把扔掉的节点也算进来)

public:
	void AICompute(
	int plate[10][10],			//棋盘数据
	SPosition pieces[],			//8个棋子的位置，长度为9
	bool isPlayer1,				//是否是作为玩家1进行计算，否则作为玩家2进行计藖E
	SPosition& outPosSelected,	//输出着子
	SPosition& outPosMoveTo,	//输出着子
	SPosition& outPosShootAt);	//输出着子

	void StopComputing(){};
};


#endif