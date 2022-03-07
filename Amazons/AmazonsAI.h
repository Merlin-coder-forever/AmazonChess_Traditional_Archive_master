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
	int m_nOutMaxValue;//(�䳁E������������ֵ
	int m_nOutDepth;//(�䳁E��������
	int m_nOutNumOfMoves;//(�䳁E�����ŷ���
	int m_nOutNumOfNodes;//(�䳁E��������Ľڵ���(���������Ľڵ���)(������)
	int m_nOutNumOfSkippedNodes;//(�䳁E����������Ľڵ���(���ӵ��Ľڵ�Ҳ�����)

public:
	void AICompute(
	int plate[10][10],			//��������
	SPosition pieces[],			//8�����ӵ�λ�ã�����Ϊ9
	bool isPlayer1,				//�Ƿ�����Ϊ���1���м��㣬������Ϊ���2���м�ˁE
	SPosition& outPosSelected,	//�������
	SPosition& outPosMoveTo,	//�������
	SPosition& outPosShootAt);	//�������

	void StopComputing(){};
};


#endif