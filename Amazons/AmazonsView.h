// AmazonsView.h : interface of the CAmazonsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AMAZONSVIEW_H__8655EBF0_EA24_43CB_A748_4DEA4F7F9150__INCLUDED_)
#define AFX_AMAZONSVIEW_H__8655EBF0_EA24_43CB_A748_4DEA4F7F9150__INCLUDED_
#pragma once
#include "GameSettingDlg.h"
#include "HistoryDlg.h"
#include "AmazonsDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAmazonsView : public CView
{
protected: // create from serialization only
	CAmazonsView();
	~CAmazonsView();
	DECLARE_DYNCREATE(CAmazonsView)

// Attributes
public:
	CAmazonsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmazonsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	//��ͼ
	CDC m_clientMemDC;
	CDC m_bitmapMemDC;
	CBitmap m_bmClient;
	CBitmap m_bmBlackPiece;
	CBitmap m_bmRedPiece;
	CBitmap m_bmSelectMark;
	bool m_bHasInitDCAndBitmap;
	//
	CPoint m_ptTopLeft1;//���Ͻ�1����ע��ͼ��ʼλ��
	CPoint m_ptTopLeft2;//���Ͻ�2����ע����λ��
	CRect m_rectLeft;//
	CRect m_rectRight;
	//
	int m_nCellWidth;//С����ĳߴ�
	int m_nRightMinWidth;//�ұ��������С���
	COLORREF m_clrPlateBg;
	COLORREF m_clrViewBg;
	COLORREF m_clrDark;
	COLORREF m_clrLight;
	COLORREF m_clrArrow;

	//��Ϸ���̿���
	int m_nGameState;
	//���ӿ�����ʵ��
	bool m_bMarkMove;
	bool m_bComputerThinking;//�����Ƿ��ڼ��㣬�ӿ�ʼ���㣬һֱ��������ɲ���˼������
	bool m_bComputerMoving;
	int m_nComputerMoveTimer;
	int m_nCurState;//0δѡ�����ӣ�2��ѡ�����ӣ�3ѡ�����Ӳ�����һ�����ȴ��ż�
	SPosition m_posSelected;//ѡ�ӣ����û�У�ֵΪ(-1,-1)
	SPosition m_posMoveTo;//����λ�ã����û�У�ֵΪ(-1,-1)
	SPosition m_posShootAt;//�ż�λ�ã����û�У�ֵΪ(-1,-1)
	//

	//״̬��ʾ
	CString m_strPlayer1TotalTime;
	CString m_strPlayer2TotalTime;
	CString m_strPlayer1Timer;
	CString m_strPlayer2Timer;
	CString m_strTotalTimer;
	CString m_strGameState;
	CString m_strDepth;
	CString m_strMoves;
	CString m_strNodes;
	int m_nPlayerTimer;
	int m_nTotalTimer;//������
	//�����������ֵĿ���
	CGameSettingDlg m_dlgSettings;
	CHistoryDlg* m_pDlgHistory;
	bool m_bHistoryDlgOpened;//�Ƿ������ʷ����
	bool m_bSetTimer;
	bool m_bThreadStart;
	CWinThread *m_pThread;
	/////////////////////////

	CString m_strFilePathName;//�浵�ļ�·������ֻ���ڴ򿪻򱣴��ļ�����


private:
	void Select(SPosition posSelected);//ѡ������(ֻ��ͼ)
	void Move(SPosition posSelected, SPosition posMoveTo);//����(��ͼ����������)
	void Shoot(SPosition posShootAt);//�ż�(��ͼ����������)
	void MarkTheAction(SPosition posActBgn,SPosition posActEnd, bool isShoot);//��־ĳһ�ŷ�
	void HumanMoveFinished();
	void ComputerMoveFinished();//��������

	void UpdateHistoryDlg();//������ʷ����Ի���
	void ForwardOrBackwardHistoryEnd();//��ִ�к��ˡ�ǰ������ʱ����˸�������
	void ResetVariables();//��ʼ��һЩ�����Կ�ʼ��һ����Ϸ
	void GetTimeString(int nTime,CString& strTime);//��nTime��������������ʱ�䣬��strTime����
	void UpdateTimeCounter();
	void UpdateComputerMove();//�������Ӻͷż�����һ��ʱ����
	void UpdateRightInfo();
	void UpdateAppTitle();
	TCHAR * GetPlayerName(int playerType);
	TCHAR * GetPlayer1Color();
	TCHAR * GetPlayer2Color();
	int GetCurPlayerType();

	void StartAIComputing();//�����߲�
	void Suggest();
	void OpponentTurn(bool isStartGame = false);//�Է���֮�������������֮���л�
	bool IsOpponentNetplayer();
	bool IsCurPlayerPiece(int piece);
	bool IsGameOver();//��Ϸ�Ƿ����,�����Ļ�������m_nGameStateΪOVER

	static UINT Thread_AICompute(LPVOID pParam);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void StartGame(bool sendMsgToNetPlayer);

// Generated message map functions
protected:
	//{{AFX_MSG(CAmazonsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCmdFileOpen();
	afx_msg void OnCmdFileSave();
	afx_msg void OnCmdFileSaveAs();

	afx_msg void OnCmdNewGame();
	afx_msg void OnCmdNewGameUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdGameStart();
	afx_msg void OnCmdGameStartUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdGameSuspend();
	afx_msg void OnCmdGamesuspendUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdBackwardOne();
	afx_msg void OnCmdBackwardOneUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdBackwardTwo();
	afx_msg void OnCmdBackwardTwoUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdBackwardToStart();
	afx_msg void OnCmdBackwardToStartUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdForwardOne();
	afx_msg void OnCmdForwardOneUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdForwardTwo();
	afx_msg void OnCmdForwardTwoUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdForwardToEnd();
	afx_msg void OnCmdForwardToEndUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdSettings();
	afx_msg void OnCmdSettingsUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdShowHistoryDlg();
	afx_msg void OnCmdShowHistoryDlgUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdMark();
	afx_msg void OnCmdMarkUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdSuggest();
	afx_msg void OnCmdSuggestUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdStopComputing();
	afx_msg void OnCmdStopComputingUpdate(CCmdUI* pCmdUI);
	afx_msg void OnCmdNetwork();
	afx_msg void OnCmdNetworkUpdate(CCmdUI* pCmdUI);

	//}}AFX_MSG
	afx_msg LRESULT OnAIComputingFinished(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnNetworkConnectedToServer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkGetPlayerList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkConnectedToOpponent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkDisConnectToOpponent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNetworkGameControl(WPARAM wParam, LPARAM lParam);//wparam��Ҫ���еĲ�������SNetMsgCsGameControl
	DECLARE_MESSAGE_MAP()

public:
	void HistoryDlgClosed();
};

#ifndef _DEBUG  // debug version in AmazonsView.cpp
inline CAmazonsDoc* CAmazonsView::GetDocument()
   { return (CAmazonsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMAZONSVIEW_H__8655EBF0_EA24_43CB_A748_4DEA4F7F9150__INCLUDED_)
