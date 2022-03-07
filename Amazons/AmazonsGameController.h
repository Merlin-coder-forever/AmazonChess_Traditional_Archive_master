
#pragma once
#ifndef AMAZONS_AI_GAME_CONTROLLER_H
#define AMAZONS_AI_GAME_CONTROLLER_H
#include "StdAfx.h"

//�������
#define PLAYER_HUMAN	0
#define PLAYER_COMPUTER 1
#define PLAYER_NETWORK	2


/*
�������ݱ�ʾ
��1����10*10������洢
��2�����1�����Ӷ�ӦֵΪ1��2��3��4�����2�����Ӷ�ӦֵΪ5��6��7��8
��3���յ�λ��ֵΪ0���ż�λ��Ϊ-1
*/

//λ������
struct SPosition
{
	int i;//��
	int j;//��

	SPosition()
	{
		i = -1;
		j = -1;
	}

	SPosition(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
};

//��ʷ����
struct SHistoryRecord
{
	int spentTime;
	SPosition posSelected;//ѡ��
	SPosition posMoveTo;//����
	SPosition posShootAt;//�ż�
};

class CAmazonsGameController
{
public:
	bool m_bPlayer1Black;//���1�Ƿ��Ǻ��
	bool m_bPlayer1First;//���1�Ƿ�����
	int m_nPlayer1Type;//���1����
	int m_nPlayer2Type;//���2����

private:
	int m_plate[10][10];
	SPosition m_pieces[9];
	//
	SHistoryRecord m_histroy[92];
	int m_nHistoryPtr;//��ʼֵΪ0�����˺�Ϊ93
	int m_nCurHisttoryPtr;//������ǰ�������ʱ������ֵ��仯����m_nHistoryPtr����

public:
	CAmazonsGameController(){};
	~CAmazonsGameController(){};

public:
	void Init();
	void NewGame();
	//
	void GetPlate(int outPlate[10][10]);
	int  GetPlateCellValue(int i, int j);
	void GetPieces(SPosition outPieces[9]);
	//
	void Move(SPosition posFrom, SPosition posTo);
	void Shoot(SPosition posShootAt);
	void CancelMove(SPosition posFrom, SPosition posTo);
	void CancelShoot(SPosition posShootAt);
	bool CanMoveOrShoot(SPosition posFrom, SPosition posTo);
	//
	bool IsPieces(int n);
	bool IsEmpty(int n);
	bool IsArrow(int n);
	bool IsPlayer1(int n);
	bool IsPlayer2(int n);
	int IsGameOver();//����ֵ��0=δ��ʤ����1=���1Ӯ��2=���2Ӯ��3=ƽ��
	bool IsPlayer1Turn();//�Ƿ��ֵ����1���ӣ�����true��ʾ�ֵ����1������false��ʾ�ֵ����2
	bool IsPlayer1Turn(int nHistoryPtr);//�Ƿ��ֵ����1���ӣ�����true��ʾ�ֵ����1������false��ʾ�ֵ����2
	//
	void SaveToFile(CString filePathName);
	void LoadFromFile(CString filePathName);
	void SaveTempFile(CString filePathName);
	//
	int GetTotalTime(bool bPlayer1);
	void GetHistory(SHistoryRecord history[], int &outPtr, int &outCurPtr);
	SHistoryRecord GetCurHistoryMove();
	void AddToHistory(SPosition posSelect, SPosition posMoveTo, SPosition posShootAt, int time);//AddToHistory��ʹָ����ƣ��Ӷ��öԷ���ʼ����
	void Forward(int step);
	void Backward(int step);
	bool CanForward(int step);
	bool CanBackward(int step);

public:
	static void Move(int plate[10][10], SPosition pieces[9], SPosition posFrom, SPosition posTo);
	static void Shoot(int plate[10][10], SPosition pieces[9], SPosition posShootAt);
	static void CancelMove(int plate[10][10], SPosition pieces[9], SPosition posFrom, SPosition posTo);
	static void CancelShoot(int plate[10][10], SPosition pieces[9], SPosition posShootAt);
	static bool CanMoveOrShoot(int plate[10][10], SPosition pieces[9], SPosition posFrom, SPosition posTo);
};

#endif