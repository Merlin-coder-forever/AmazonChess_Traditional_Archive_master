// AmazonsView.cpp : implementation of the CAmazonsView class
//

#include "stdafx.h"
#include "AmazonsApp.h"
#include "math.h"
#include "MainFrm.h"

#include "AmazonsDoc.h"
#include "AmazonsView.h"
#include "AmazonsGameController.h"
#include "AmazonsAI.h"
#include "GlobalFunctions.h"

#include "name.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STATE_UNSELECT 0	//�ȴ�ѡ������
#define STATE_SELECTED 1	//�ȴ����ӣ���ȡ������
#define STATE_MOVED 2		//�ȴ��ż�
#define STATE_SHOOTED 3		//�����

#define GAME_STATE_NOT_START 0
#define GAME_STATE_PLAYING 1
#define GAME_STATE_SUSPEND 2
#define GAME_STATE_OVER 3

#define  TIMER_INTERVAL 200//UIʱ�Ӽ������λms

#define TEMP_FILE_NAME _T("$Amazons_temp.amz")


//��Ϸ����
CAmazonsGameController *g_pGameController = new CAmazonsGameController;


//����AI
CAmazonsAI *g_pAI = new CAmazonsAI;

/////////////////////////
//�߳�ͨ��
SPosition g_posSelected, g_posMoveTo, g_posShootAt;
CEvent g_eventContinue(FALSE, FALSE);
bool g_bPlayAsPlayer1 = false;
/////////////////////////////////////////////////////////////////////////////
// CAmazonsView

IMPLEMENT_DYNCREATE(CAmazonsView, CView)

BEGIN_MESSAGE_MAP(CAmazonsView, CView)
	//{{AFX_MSG_MAP(CAmazonsView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()

	ON_COMMAND(ID_FILE_OPEN, OnCmdFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnCmdFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnCmdFileSaveAs)

	ON_COMMAND(ID_GAME_START, OnCmdGameStart)
	ON_UPDATE_COMMAND_UI(ID_GAME_START, OnCmdGameStartUpdate)
	ON_COMMAND(ID_NEW_GAME, OnCmdNewGame)
	ON_UPDATE_COMMAND_UI(ID_NEW_GAME, OnCmdNewGameUpdate)
	ON_COMMAND(ID_GAMESUSPEND, OnCmdGameSuspend)
	ON_UPDATE_COMMAND_UI(ID_GAMESUSPEND, OnCmdGamesuspendUpdate)
	ON_COMMAND(ID_BACKWARD_ONE, OnCmdBackwardOne)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_ONE, OnCmdBackwardOneUpdate)
	ON_COMMAND(ID_BACKWARD_TWO, OnCmdBackwardTwo)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_TWO, OnCmdBackwardTwoUpdate)
	ON_COMMAND(ID_BACKWARD_TO_START, OnCmdBackwardToStart)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_TO_START, OnCmdBackwardToStartUpdate)
	ON_COMMAND(ID_FORWARD_ONE, OnCmdForwardOne)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_ONE, OnCmdForwardOneUpdate)
	ON_COMMAND(ID_FORWARD_TWO, OnCmdForwardTwo)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_TWO, OnCmdForwardTwoUpdate)
	ON_COMMAND(ID_FORWARD_TO_END, OnCmdForwardToEnd)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_TO_END, OnCmdForwardToEndUpdate)
	ON_COMMAND(ID_SETTINGS, OnCmdSettings)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS, OnCmdSettingsUpdate)
	ON_COMMAND(ID_SHOW_HISTORY_DLG, OnCmdShowHistoryDlg)
	ON_UPDATE_COMMAND_UI(ID_SHOW_HISTORY_DLG, OnCmdShowHistoryDlgUpdate)
	ON_COMMAND(ID_MARK, OnCmdMark)
	ON_UPDATE_COMMAND_UI(ID_MARK, OnCmdMarkUpdate)
	ON_COMMAND(ID_SUGGEST_A_MOVE, OnCmdSuggest)
	ON_UPDATE_COMMAND_UI(ID_SUGGEST_A_MOVE, OnCmdSuggestUpdate)
	ON_COMMAND(ID_STOP_COMPUTING, OnCmdStopComputing)
	ON_UPDATE_COMMAND_UI(ID_STOP_COMPUTING, OnCmdStopComputingUpdate)

	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmazonsView construction/destruction

CAmazonsView::CAmazonsView()
{
	//��ͼ�ñ���
	m_ptTopLeft1 = CPoint(20, 20);
	m_ptTopLeft2 = m_ptTopLeft1 + CPoint(30, 30);
	m_nRightMinWidth = 270;
	m_clrDark = RGB(39, 78, 19);
	m_clrLight = RGB(106, 168, 79);
	m_clrArrow = RGB(230, 145, 56);
	m_clrViewBg = RGB(0, 0, 0);
	m_clrPlateBg = RGB(255, 255, 255);
	///////
	ResetVariables();
	m_bMarkMove = true;
	m_pDlgHistory = new CHistoryDlg(this);
	m_pDlgHistory->Create();//CDialog(CHistoryDlg::IDD, pParent)
	m_bThreadStart = false;
	m_bHistoryDlgOpened = false;
	m_pThread = NULL;
	m_bSetTimer = false;
	m_bHasInitDCAndBitmap = false;

	m_strMoves = "�÷�: ";
	m_strDepth = "���: ";
	m_strNodes = "�ڵ�: ";
}

void CAmazonsView::ResetVariables()
{
	m_nGameState = GAME_STATE_NOT_START;
	m_bComputerMoving = false;
	m_bComputerThinking = false;
	//
	m_nCurState = STATE_UNSELECT;
	m_posSelected = m_posMoveTo = m_posShootAt = SPosition(-1, -1);

	m_strPlayer1TotalTime = _T("00:00:00");
	m_strPlayer2TotalTime = _T("00:00:00");
	m_strPlayer1Timer = _T("00:00:00");
	m_strPlayer2Timer = _T("00:00:00");
	m_strTotalTimer = _T("00:00:00");
	m_strGameState = _T("");
	m_strDepth.Format(_T("���:"));
	m_strNodes.Format(_T("�ڵ�:"));
	m_strMoves.Format(_T("�÷�:"));
	m_nPlayerTimer = 0;
	m_nTotalTimer = 0;
}

CAmazonsView::~CAmazonsView()
{	
}

#ifdef _DEBUG
void CAmazonsView::AssertValid() const
{
	CView::AssertValid();
}

void CAmazonsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAmazonsDoc* CAmazonsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAmazonsDoc)));
	return (CAmazonsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAmazonsView message handlers

#pragma region Thread

UINT CAmazonsView::Thread_AICompute(LPVOID pParam)
{
	TRACE("ComputingThreadStarted\n");
	HWND  hWnd = (HWND)pParam;
	int plate[10][10];
	SPosition pieces[9];
	while (1)
	{
		::WaitForSingleObject(g_eventContinue, INFINITE);
		g_pGameController->GetPlate(plate);
		g_pGameController->GetPieces(pieces);

		int tmp = 0;
		for (int i=0; i<10; i++)
			for (int j = 0; j < 10; j++) {
				tmp = pieces[j].i;
				tmp = pieces[j].j;
			}
 		g_pAI->AICompute(plate, pieces, g_pGameController->IsPlayer1Turn(), g_posSelected, g_posMoveTo, g_posShootAt);
		::PostMessage(hWnd, WM_AI_COMPUTING_FINISHED, 0, 0);
	}
	return 0;
}

#pragma endregion Thread

#pragma region System Message

BOOL CAmazonsView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CView::OnEraseBkgnd(pDC);
}

int CAmazonsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!m_bHasInitDCAndBitmap)
	{
		CDC *pDC = GetDC();
		m_clientMemDC.CreateCompatibleDC(pDC);
		m_bitmapMemDC.CreateCompatibleDC(pDC);
		m_bmClient.CreateCompatibleBitmap(pDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		m_clientMemDC.SelectObject(m_bmClient);
		m_clientMemDC.SetBkMode(TRANSPARENT);

		m_bmBlackPiece.LoadBitmap(IDB_BLACK);
		m_bmRedPiece.LoadBitmap(IDB_RED);
		m_bmSelectMark.LoadBitmap(IDB_SELECT);

		ReleaseDC(pDC);
		//pDC->DeleteDC();
		m_bHasInitDCAndBitmap = true;
	}
	return 0;
}

void CAmazonsView::OnDestroy()
{
	CView::OnDestroy();
	::DeleteFile(TEMP_FILE_NAME);
	m_clientMemDC.DeleteDC();
	m_bitmapMemDC.DeleteDC();

	delete g_pGameController;
	delete g_pAI;
	delete m_pDlgHistory;
	delete m_pThread;
}

void CAmazonsView::OnInitialUpdate()
{
	if (!m_bThreadStart)
	{
		m_pThread = AfxBeginThread(Thread_AICompute, GetSafeHwnd(), THREAD_PRIORITY_ABOVE_NORMAL);
		m_bThreadStart = true;
	}
	if (!m_bSetTimer){
		SetTimer(1, TIMER_INTERVAL, NULL);
		m_bSetTimer = true;
	}
	
	g_pGameController->Init();

	CView::OnInitialUpdate();
}

void CAmazonsView::OnDraw(CDC* pDC)
{
	int plate[10][10];//��ȡplate���ݽ���չʾ��ֻ��
	g_pGameController->GetPlate(plate);

	// TODO: add draw code for native data here
	double dRatioX, dRatioY;
	int n;

	CRect rectClient;

	//��������
	CPoint ptCellTopLeft(0, 0);
	CBrush bgBrush(m_clrPlateBg);
	CBrush brushDark(m_clrDark);
	CBrush brushLigth(m_clrLight);
	CBrush brushArrow(m_clrArrow);
	int i, j;
	CString str,strX,strY;

	//�������
	int nMargin = 15;
	CPoint ptTemp;
	CFont font, *pOldFont;
	///////////
	//
	//ˢ����
	GetClientRect(rectClient);
	m_clientMemDC.SelectObject(bgBrush);
	m_clientMemDC.FillSolidRect(rectClient, m_clrViewBg);
	//
	//ȷ�����̵Ŀ�ȣ�Ҳ����С���ӵĿ��
	n = (m_ptTopLeft2.x - m_ptTopLeft1.x)*2;
	dRatioX = ((double)rectClient.Width() - 2 * m_ptTopLeft1.x - m_nRightMinWidth - n) / 400;
	dRatioY = ((double)rectClient.Height() - 2 * m_ptTopLeft1.y - n) / 400;
	if (dRatioX > dRatioY)	dRatioX = dRatioY;
	m_nCellWidth = (int)(40 * dRatioX);//�����������ڣ�������ұߺ����������������ߺ��ϱߵĲ�һ��
	if (m_nCellWidth < 10) m_nCellWidth = 10;
	//
	//��������������򣬼����Ӻ����һȦ����һ��ľ�������
	//�ұ�������ʾ����
	m_rectLeft = CRect(m_ptTopLeft1, CSize(m_nCellWidth * 10 + n, m_nCellWidth * 10 + n));
	m_rectRight = CRect(CPoint(m_ptTopLeft1.x + m_rectLeft.Width(), m_ptTopLeft1.y),
		CSize(rectClient.Width() - m_ptTopLeft1.x * 2 - m_rectLeft.Width(), m_rectLeft.Width()));
	m_clientMemDC.SelectObject(&bgBrush);
	m_clientMemDC.Rectangle(m_rectLeft);
	//
	//����ұ�����İ�Χ�򣬵�����
	/*m_clientMemDC.Rectangle(CRect(m_ptTopLeft2, CSize(m_nCellWidth * 10, m_nCellWidth * 10)));
	m_clientMemDC.SelectStockObject(NULL_BRUSH);
	m_clientMemDC.Rectangle(m_rectLeft);
	m_clientMemDC.Rectangle(m_rectRight);*/
	//
	///������
	m_clientMemDC.SetTextColor(RGB(0, 0, 0));
	font.CreatePointFont(130, _T("����"));
	pOldFont = m_clientMemDC.SelectObject(&font);
	for (i = 0; i < 10; i++)//д����
	{
		strX.Format(_T("%c"), i+'A');
		if (i == 0) {
			strY.Format(_T("10"));
		}
		else {
			strY.Format(_T("%c"), '9' - i + 1);
		}
		m_clientMemDC.TextOut(int(m_ptTopLeft2.x + (i + 0.5)*m_nCellWidth), m_ptTopLeft2.y - 26, strX);//����
		m_clientMemDC.TextOut(int(m_ptTopLeft2.x + (i + 0.5)*m_nCellWidth), m_ptTopLeft2.y + 5 + 10 * m_nCellWidth, strX);//����
		m_clientMemDC.TextOut(m_ptTopLeft2.x - 24, int(m_ptTopLeft2.y + (i + 0.3)*m_nCellWidth), strY);//����
		m_clientMemDC.TextOut(m_ptTopLeft2.x + 6 + 10 * m_nCellWidth, int(m_ptTopLeft2.y + (i + 0.3)*m_nCellWidth), strY);//����
	}
	//11������
	CPoint ptLineBegin = m_ptTopLeft2;
	CPoint ptLineEnd = m_ptTopLeft2 + CPoint(m_nCellWidth*10, 0);
	for (i = 0; i < 11; i++)
	{
		m_clientMemDC.MoveTo(ptLineBegin);
		m_clientMemDC.LineTo(ptLineEnd);
		ptLineBegin.y += m_nCellWidth;
		ptLineEnd.y += m_nCellWidth;
	}
	//11������
	ptLineBegin = m_ptTopLeft2;
	ptLineEnd = m_ptTopLeft2 + CPoint(0, m_nCellWidth * 10);
	for (i = 0; i < 11; i++)
	{
		m_clientMemDC.MoveTo(ptLineBegin);
		m_clientMemDC.LineTo(ptLineEnd);
		ptLineBegin.x += m_nCellWidth;
		ptLineEnd.x += m_nCellWidth;
	}
	//
	BITMAP pieceBmpInfo, slectMarkBmpInfo;
	m_bmRedPiece.GetBitmap(&pieceBmpInfo);
	m_bmSelectMark.GetBitmap(&slectMarkBmpInfo);
	//
	//���С����
	int nCellValue = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			nCellValue = plate[i][j];
			ptCellTopLeft = CPoint(j*m_nCellWidth + 1, i*m_nCellWidth + 1) + m_ptTopLeft2;

			//�ñ���������
			if ((i + j) % 2 == 0)//ǳɫ����
				m_clientMemDC.SelectObject(&brushLigth);
			else//��ɫ����
				m_clientMemDC.SelectObject(&brushDark);
			m_clientMemDC.SelectStockObject(NULL_PEN);
			m_clientMemDC.Rectangle(CRect(ptCellTopLeft, CSize(m_nCellWidth, m_nCellWidth)));

			//����ͼ��
			if (g_pGameController->IsArrow(nCellValue))//�ż�ͼ��
			{
				m_clientMemDC.SelectObject(&brushArrow);
				m_clientMemDC.Rectangle(CRect(ptCellTopLeft, CSize(m_nCellWidth, m_nCellWidth)));
			}
			else if (g_pGameController->IsPlayer1(nCellValue))//����ͼ��(���1�úڵ�)
			{
				m_bitmapMemDC.SelectObject(&m_bmBlackPiece);
				TransparentBlt(m_clientMemDC.m_hDC, ptCellTopLeft.x, ptCellTopLeft.y, m_nCellWidth, m_nCellWidth,
					m_bitmapMemDC.m_hDC, 0, 0, pieceBmpInfo.bmWidth, pieceBmpInfo.bmHeight, RGB(255, 255, 255));
				//TRACE("(%d,%d)\n",i,j);
			}
			else if (g_pGameController->IsPlayer2(nCellValue))//����ͼ��(���2�ú��)
			{
				m_bitmapMemDC.SelectObject(&m_bmRedPiece);
				TransparentBlt(m_clientMemDC.m_hDC, ptCellTopLeft.x, ptCellTopLeft.y, m_nCellWidth, m_nCellWidth,
					m_bitmapMemDC.m_hDC, 0, 0, pieceBmpInfo.bmWidth, pieceBmpInfo.bmHeight, RGB(255, 255, 255));
				//TRACE("(%d,%d)\n",i,j);
			}

			//��ʾѡ�б��
			bool showMark = false;
			if (m_nCurState == STATE_SELECTED)
				showMark = (i == m_posSelected.i && j == m_posSelected.j);
			else if (m_nCurState == STATE_MOVED)
				showMark = (m_posMoveTo.i == i && m_posMoveTo.j == j);
			if (showMark)
			{
				m_bitmapMemDC.SelectObject(&m_bmSelectMark);
				TransparentBlt(m_clientMemDC.m_hDC, ptCellTopLeft.x, ptCellTopLeft.y, m_nCellWidth, m_nCellWidth,
					m_bitmapMemDC.m_hDC, 0, 0, pieceBmpInfo.bmWidth, pieceBmpInfo.bmHeight, RGB(255, 255, 255));
			}
		}
	}
	if (m_bMarkMove)
	{
		MarkTheAction(m_posSelected, m_posMoveTo, false);
		MarkTheAction(m_posMoveTo, m_posShootAt, true);
	}


	//�����ұ�
	//�ұ�(Ӧ����Ϊ�̶��߶ȣ������ػ�ʱ���Ĳ��ֲ�����ȫ�ػ�,70+120+55+100=345)


	m_rectRight.bottom = m_rectRight.top + 900;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!pOldFont = m_clientMemDC.SelectObject(&font);
	m_clientMemDC.SelectStockObject(NULL_BRUSH);
	m_clientMemDC.SelectStockObject(BLACK_PEN);
	m_clientMemDC.SetTextColor(RGB(255, 255, 255));
	//m_clientMemDC.Rectangle(m_rectRight);
	////���ĸ�����
	ptTemp = m_rectRight.TopLeft();
	ptTemp.x = ptTemp.x + nMargin;
	ptTemp.y = ptTemp.y + nMargin + 32;
	/////////////////////��һ���֣�������Ϣ
	m_clientMemDC.SetTextColor(RGB(255, 255, 255));
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y);
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y - 1); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y - 1);
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 15, m_strGameState);
	//
	//���ϡ����1--��/�췽--����/��   ����
	//���¡����1--��/�췽--����/�� 
	ptTemp.y = ptTemp.y + 200;
	CString drawText = _T(" ");
	drawText += g_pGameController->m_bPlayer1Black ? _T("�ڷ���Ӫ��") : _T("�췽��Ӫ��");
	drawText += GetPlayerName(g_pGameController->m_nPlayer1Type);
	
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 10, drawText);
	//
	drawText = _T(" ");
	drawText += g_pGameController->m_bPlayer1Black ? _T("�췽��Ӫ��") : _T("�ڷ���Ӫ��");
	drawText += GetPlayerName(g_pGameController->m_nPlayer2Type);
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 40, drawText);
	//
	drawText = g_pGameController->m_bPlayer1First ? GetPlayer1Color() : GetPlayer2Color();
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 300, ptTemp.y + 24 , drawText + _T("����"));

	/////////////////////�ڶ����֣���ʱ

	ptTemp.y = ptTemp.y + 200;
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y);
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y - 1); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y - 1);
	/*
	//���Ʊ��
	*/
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15, ptTemp.y + 48, "����");			//��2��2
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15, ptTemp.y + 73, "��ǰ");		//��3��3
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 30 + 70, ptTemp.y + 23, g_pGameController->m_bPlayer1Black ? _T("�ڷ�") : _T("�췽"));		//��2��1
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15 + 57, ptTemp.y + 48, m_strPlayer1TotalTime);									//��2��2
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15 + 57, ptTemp.y + 73, m_strPlayer1Timer);										//��2��3
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 30 + 185, ptTemp.y + 23, g_pGameController->m_bPlayer1Black ? _T("�췽") : _T("�ڷ�"));	//��3��1
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15 + 172, ptTemp.y + 48, m_strPlayer2TotalTime);									//��3��2
	m_clientMemDC.TextOut(ptTemp.x + nMargin + 15 + 172, ptTemp.y + 73, m_strPlayer2Timer);										//��3��3
	//m_clientMemDC.Rectangle(m_rectRight2);
	/////////////////////�������֣�˭����
	ptTemp.y = ptTemp.y + 200;
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y);
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y - 1); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y - 1);
	/////////////////////���Ĳ��֣�״̬��ʾ
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y);
	m_clientMemDC.MoveTo(ptTemp.x, ptTemp.y - 1); m_clientMemDC.LineTo(m_rectRight.right, ptTemp.y - 1);
	//
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 15, m_strMoves);
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 40, m_strDepth);
	m_clientMemDC.TextOut(ptTemp.x + nMargin, ptTemp.y + 65, m_strNodes);
	///////////////
	m_clientMemDC.SelectObject(pOldFont);
	m_clientMemDC.SelectStockObject(NULL_BRUSH);
	m_clientMemDC.SelectStockObject(BLACK_PEN);

	pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &m_clientMemDC, 0, 0, SRCCOPY);

	//pDC->GetClipBox(rectClient);//�������������
	//if (rectClient != m_rectRight)
		//m_bThereIsMark = false;//�����ػ����̲�����ǻ���ʧ

}

void CAmazonsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nGameState != GAME_STATE_PLAYING || m_bComputerThinking)
		return;

	if (GetCurPlayerType() == PLAYER_NETWORK)
		return;

	//TRACE("point(%d,%d)\n",point.x,point.y);
	CString str;
	CPoint pointUnit(0, 0);

	//����Ƿ���������
	point = point - m_ptTopLeft2;
	if (point.x < 0 || point.x > m_nCellWidth * 10 || point.y < 0 || pointUnit.y > m_nCellWidth * 10)
		return;

	//������ĸ�������
	int i = point.y / m_nCellWidth;
	int j = point.x / m_nCellWidth;
	int cellValue = g_pGameController->GetPlateCellValue(i, j);
	SPosition pos(i, j);
	//TRACE("Click:(%d,%d)\n", i, j);

	bool redraw = false;
	if (m_nCurState == STATE_UNSELECT)
	{
		if (IsCurPlayerPiece(cellValue))
		{
			//ѡ������
			m_posMoveTo.i = -1;
			m_posMoveTo.j = -1;
			m_posShootAt = m_posMoveTo;
			m_posSelected = pos;
			m_nCurState = STATE_SELECTED;
			redraw = true;
			//TRACE("Selected\n");
		}
	}
	else if (m_nCurState == STATE_SELECTED)
	{
		if (IsCurPlayerPiece(cellValue))
		{
			//ѡ����������
			m_posSelected = pos;
			m_nCurState = STATE_SELECTED;
			redraw = true;
			//TRACE("SelectedLoop\n");
		}
		else if (g_pGameController->IsEmpty(cellValue))
		{
			//����
			if (g_pGameController->CanMoveOrShoot(m_posSelected, pos))
			{
				m_posMoveTo = pos;
				g_pGameController->Move(m_posSelected, pos);
				m_nCurState = STATE_MOVED;
				redraw = true;
			}
		}
	}
	else if (m_nCurState == STATE_MOVED)
	{
		if (m_posMoveTo.i == i && m_posMoveTo.j == j)
		{
			//ȡ������
			g_pGameController->CancelMove(m_posSelected, pos);
			m_posMoveTo.i = -1;
			m_posMoveTo.j = -1;
			m_nCurState = STATE_SELECTED;
			redraw = true;
		}
		else if (g_pGameController->IsEmpty(cellValue))
		{
			//�ż�
			if (g_pGameController->CanMoveOrShoot(m_posMoveTo, pos))
			{
				m_posShootAt = pos;
				g_pGameController->Shoot(pos);
				m_nCurState = STATE_UNSELECT;
				redraw = true;
				HumanMoveFinished();
			}
		}
	}

	if (redraw)
		InvalidateRect(NULL);

	CView::OnLButtonDown(nFlags, point);
}

void CAmazonsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	OnCmdGameStart();
	CView::OnRButtonDown(nFlags, point);
}

void CAmazonsView::OnTimer(UINT nIDEvent)
{
	UpdateComputerMove();
	UpdateRightInfo();
	InvalidateRect(m_rectRight);
	CView::OnTimer(nIDEvent);
}

#pragma endregion

#pragma region Command Message

void CAmazonsView::OnCmdFileOpen()
{
	if (m_bComputerThinking)
	{
		AfxMessageBox(_T("���Լ�����..."));
		return;
	}
	
	CFileDialog dlg(true, _T("amz"), _T("*.amz"), 6, _T("amz files (*.amz)||all(*.*)"));
	if (dlg.DoModal() == IDOK)
	{
		m_strFilePathName = dlg.GetPathName();
		g_pGameController->LoadFromFile(dlg.GetPathName());
		ResetVariables();
		UpdateHistoryDlg();
		IsGameOver();
		UpdateTimeCounter();
		InvalidateRect(NULL);

		UpdateAppTitle();

		//��ȡ��ǰ���裬����mark
		SHistoryRecord record = g_pGameController->GetCurHistoryMove();
		m_posSelected = record.posSelected;
		m_posMoveTo = record.posMoveTo;
		m_posShootAt = record.posShootAt;
	}
}

void CAmazonsView::OnCmdFileSave()
{
	if (m_strFilePathName.IsEmpty())
	{
		CFileDialog dlg(false, _T("amz"), _T("amz.amz"), 6, _T("amz files (*.amz)||all(*.*)"));
		if (dlg.DoModal() == IDOK)
		{
			m_strFilePathName = dlg.GetPathName();
		}
		else
			return;
	}

	g_pGameController->SaveToFile(m_strFilePathName);
	UpdateAppTitle();
}

void CAmazonsView::OnCmdFileSaveAs()
{
	CFileDialog dlg(false, _T("amz"), _T("amz.amz"), 6, _T("amz files (*.amz)||all(*.*)"));
	if (dlg.DoModal() == IDOK)
	{
		m_strFilePathName = dlg.GetPathName();
	}
	else
		return;

	g_pGameController->SaveToFile(m_strFilePathName);
	UpdateAppTitle();
}

void CAmazonsView::OnCmdNewGame()
{
	if (m_nGameState != GAME_STATE_NOT_START)
	{
		if (TipMessage(_T("���Ҫ���¿�ʼ��"), MB_OKCANCEL) != IDOK)
			return;
	}

	g_pGameController->NewGame();
	ResetVariables();
	UpdateHistoryDlg();
	InvalidateRect(NULL);
}

void CAmazonsView::OnCmdNewGameUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bComputerThinking);
}

void CAmazonsView::OnCmdGameStart()
{
	StartGame(TRUE);
}

void CAmazonsView::OnCmdGameStartUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nGameState == GAME_STATE_NOT_START || m_nGameState == GAME_STATE_SUSPEND);
}

void CAmazonsView::OnCmdGameSuspend()
{
	m_nGameState = GAME_STATE_SUSPEND;
}

void CAmazonsView::OnCmdGamesuspendUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nGameState == GAME_STATE_PLAYING && !m_bComputerThinking);
}

void CAmazonsView::OnCmdBackwardOne()
{
	if (g_pGameController->CanBackward(1))
	{
		g_pGameController->Backward(1);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdBackwardOneUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanBackward(1));
}

void CAmazonsView::OnCmdBackwardTwo()
{
	if (g_pGameController->CanBackward(2))
	{
		g_pGameController->Backward(2);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdBackwardTwoUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanBackward(2));
}

void CAmazonsView::OnCmdBackwardToStart()
{
	if (g_pGameController->CanBackward(1))
	{
		g_pGameController->Backward(-1);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdBackwardToStartUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanBackward(1));
}

void CAmazonsView::OnCmdForwardOne()
{
	if (g_pGameController->CanForward(1))
	{
		g_pGameController->Forward(1);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdForwardOneUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanForward(1));
}

void CAmazonsView::OnCmdForwardTwo()
{
	if (g_pGameController->CanForward(2))
	{
		g_pGameController->Forward(2);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdForwardTwoUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanForward(2));
}

void CAmazonsView::OnCmdForwardToEnd()
{
	if (g_pGameController->CanForward(1))
	{
		g_pGameController->Forward(-1);
		ForwardOrBackwardHistoryEnd();
	}
}

void CAmazonsView::OnCmdForwardToEndUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bComputerThinking) && g_pGameController->CanForward(1));
}

void CAmazonsView::OnCmdSettings()
{
	m_dlgSettings.Init(g_pGameController->m_nPlayer1Type,
		g_pGameController->m_nPlayer2Type,
		g_pGameController->m_bPlayer1Black, 
		g_pGameController->m_bPlayer1First);

	if (m_dlgSettings.DoModal() == IDOK)
	{
		g_pGameController->m_nPlayer1Type = m_dlgSettings.m_nPlayer1Type;
		g_pGameController->m_nPlayer2Type = m_dlgSettings.m_nPlayer2Type;
		g_pGameController->m_bPlayer1Black = m_dlgSettings.m_nPlayer1IsBlack==0 ? true : false;
		g_pGameController->m_bPlayer1First = m_dlgSettings.m_nPlayer1IsFirst==0 ? true : false;
		OnCmdNewGame();
	}
}

void CAmazonsView::OnCmdSettingsUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bComputerThinking);
	pCmdUI->SetCheck(m_dlgSettings.m_hWnd != NULL);
}


void CAmazonsView::OnCmdShowHistoryDlg()
{
	if (!m_bHistoryDlgOpened)
	{
		m_bHistoryDlgOpened = true;
		m_pDlgHistory->UpdateHistoryText(g_pGameController);
		m_pDlgHistory->ShowWindow(SW_SHOW);
		m_pDlgHistory->UpdateData(false);
	}
}

void CAmazonsView::OnCmdShowHistoryDlgUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bHistoryDlgOpened);
}

void CAmazonsView::OnCmdMark()
{
	m_bMarkMove = !m_bMarkMove;
	Invalidate(NULL);
}

void CAmazonsView::OnCmdMarkUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bMarkMove);
}

void CAmazonsView::OnCmdSuggest()
{
	Suggest();
}

void CAmazonsView::OnCmdSuggestUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bComputerThinking && m_nGameState == GAME_STATE_PLAYING);
}


void CAmazonsView::OnCmdStopComputing()
{
	g_pAI->StopComputing();
	TipMessage(_T("�޴˹���"));
}

void CAmazonsView::OnCmdStopComputingUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bComputerThinking);
}


#pragma endregion

#pragma region Other Message


LRESULT CAmazonsView::OnAIComputingFinished(WPARAM wParam, LPARAM lParam)
{
	m_posSelected = m_posMoveTo = m_posShootAt = SPosition(-1, -1);
	m_bComputerMoving = true;
	m_nComputerMoveTimer = 0;
	return 0L;
}

#pragma endregion

#pragma region deal things

void CAmazonsView::StartGame(bool sendMsgToNetPlayer)
{
	if (m_nGameState == GAME_STATE_PLAYING) return;

	OpponentTurn(true);
	m_nGameState = GAME_STATE_PLAYING;
}

void CAmazonsView::OpponentTurn(bool isStartGame /*= false*/)
{
	if (IsGameOver())
	{
		AfxMessageBox(m_strGameState, MB_OK);
		return;
	}

	if (GetCurPlayerType() == PLAYER_COMPUTER)
		StartAIComputing();

	m_nPlayerTimer = 0;
}

//�����ǵ��԰�����룬����m_nPlayer1Type��PLAYER_HUMAN
void CAmazonsView::Suggest()
{
	if (m_bComputerThinking || m_nGameState != GAME_STATE_PLAYING) return;

	if (GetCurPlayerType() == PLAYER_HUMAN)
		StartAIComputing();

	m_nPlayerTimer = 0;
}

//bPlayer1 = true���԰������1������������2
void CAmazonsView::StartAIComputing()
{
	g_eventContinue.SetEvent();//�����ź�
	m_bComputerThinking = true;
}

void CAmazonsView::Select(SPosition posSelected)
{
	m_posSelected = posSelected;
	InvalidateRect(m_rectLeft);
}

void CAmazonsView::Move(SPosition posSelected, SPosition posMoveTo)
{
	m_posSelected = posSelected;
	m_posMoveTo = posMoveTo;
	g_pGameController->Move(posSelected, posMoveTo);
	InvalidateRect(m_rectLeft);
}

void CAmazonsView::Shoot(SPosition posShootAt)
{
	m_posShootAt = posShootAt;
	g_pGameController->Shoot(posShootAt);
	InvalidateRect(m_rectLeft);
}

void CAmazonsView::MarkTheAction(SPosition posActBgn, SPosition posActEnd, bool bShoot)
{
	if (posActBgn.i == -1 || posActBgn.j == -1) return;
	if (posActEnd.i == -1 || posActEnd.j == -1) return;

	int i, j;
	CPoint ptBgn, ptEnd;
	CPen penMove(PS_SOLID, 2, RGB(255, 255, 255));
	CPen penShoot(PS_SOLID, 2, RGB(153, 0, 255));
	CBrush brushMove(RGB(153, 255, 255));

	if (bShoot){
		m_clientMemDC.SelectObject(&penShoot);
	}
	else{
		m_clientMemDC.SelectObject(&penMove);
		m_clientMemDC.SelectObject(&brushMove);
	}

	i = posActBgn.i; j = posActBgn.j;
	ptBgn = CPoint(int((j + 0.5)*m_nCellWidth) + 1, int((i + 0.5)*m_nCellWidth) + 1) + m_ptTopLeft2;
	i = posActEnd.i; j = posActEnd.j;
	ptEnd = CPoint(int((j + 0.5)*m_nCellWidth) + 1, int((i + 0.5)*m_nCellWidth) + 1) + m_ptTopLeft2;
	m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	if (!bShoot)
		m_clientMemDC.Ellipse(ptBgn.x - 5, ptBgn.y - 5, ptBgn.x + 5, ptBgn.y + 5);
	//�����ͷ(���¾�ָ��ͷ����)(��ͷһ���������)
	ptBgn = ptEnd;
	if (j == posActBgn.j&&i < posActBgn.i){//��ֱ����
		ptEnd = CPoint(ptBgn.x - 4, ptBgn.y + 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x + 4, ptBgn.y + 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (j == posActBgn.j&&i > posActBgn.i){//��ֱ����
		ptEnd = CPoint(ptBgn.x - 4, ptBgn.y - 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x + 4, ptBgn.y - 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i == posActBgn.i&&j < posActBgn.j){//ˮƽ����
		ptEnd = CPoint(ptBgn.x + 8, ptBgn.y - 4); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x + 8, ptBgn.y + 4); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i == posActBgn.i&&j > posActBgn.j){//ˮƽ����
		ptEnd = CPoint(ptBgn.x - 8, ptBgn.y - 4); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x - 8, ptBgn.y + 4); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i<posActBgn.i&&j < posActBgn.j){//��б����
		ptEnd = CPoint(ptBgn.x + 2, ptBgn.y + 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x + 8, ptBgn.y + 2); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i > posActBgn.i&&j>posActBgn.j){//��б����
		ptEnd = CPoint(ptBgn.x - 8, ptBgn.y - 2); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x - 2, ptBgn.y - 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i<posActBgn.i&&j>posActBgn.j){//��б����
		ptEnd = CPoint(ptBgn.x - 8, ptBgn.y + 2); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x - 2, ptBgn.y + 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}
	if (i > posActBgn.i&&j < posActBgn.j){//��б����
		ptEnd = CPoint(ptBgn.x + 2, ptBgn.y - 8); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
		ptEnd = CPoint(ptBgn.x + 8, ptBgn.y - 2); m_clientMemDC.MoveTo(ptBgn); m_clientMemDC.LineTo(ptEnd);
	}

	m_clientMemDC.SelectStockObject(BLACK_PEN);
	m_clientMemDC.SelectStockObject(NULL_BRUSH);
}

void CAmazonsView::HumanMoveFinished()
{

	g_pGameController->AddToHistory(m_posSelected, m_posMoveTo, m_posShootAt, m_nPlayerTimer);
	g_pGameController->SaveTempFile(TEMP_FILE_NAME);
	UpdateHistoryDlg();
	OpponentTurn();
}

void CAmazonsView::ComputerMoveFinished()
{

	g_pGameController->AddToHistory(m_posSelected, m_posMoveTo, m_posShootAt, m_nPlayerTimer);
	g_pGameController->SaveTempFile(TEMP_FILE_NAME);
	UpdateHistoryDlg();
	OpponentTurn();
}

bool CAmazonsView::IsGameOver()
{
	int nWhoWin = g_pGameController->IsGameOver();

	if (nWhoWin == 1)
	{
		m_strGameState = g_pGameController->m_bPlayer1Black ? _T("�ڷ�Ӯ") : _T("�췽Ӯ");
		m_nGameState = GAME_STATE_OVER;
	}
	else if (nWhoWin == 2)
	{
		m_strGameState = g_pGameController->m_bPlayer1Black ? _T("�췽Ӯ") : _T("�ڷ�Ӯ");
		m_nGameState = GAME_STATE_OVER;
	}
	else if (nWhoWin == 3)
	{
		m_strGameState = _T("ƽ��");
		m_nGameState = GAME_STATE_OVER;
	}

	return nWhoWin >= 1;
}

bool CAmazonsView::IsOpponentNetplayer()
{
	if (g_pGameController->IsPlayer1Turn())
		return g_pGameController->m_nPlayer2Type == PLAYER_NETWORK;
	else
		return g_pGameController->m_nPlayer1Type == PLAYER_NETWORK;
}

bool CAmazonsView::IsCurPlayerPiece(int piece)
{
	//�Ƿ�����Ҷ�Ӧ������
	if (g_pGameController->IsPlayer1Turn())
		return g_pGameController->IsPlayer1(piece);
	else
		return g_pGameController->IsPlayer2(piece);
}

void CAmazonsView::UpdateHistoryDlg()
{
	if (!m_bHistoryDlgOpened) return;

	m_pDlgHistory->UpdateHistoryText(g_pGameController);
	m_pDlgHistory->UpdateData(FALSE);
	m_pDlgHistory->m_editHistory.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void CAmazonsView::UpdateAppTitle()
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	pMainFrame->m_strDocName = GblGetFileNameWithExFromPathName(m_strFilePathName);
	pMainFrame->UpdateApplicationTitle();
}

void CAmazonsView::HistoryDlgClosed()
{
	//������close�ˣ����ܴ���ֱ��������
	m_pDlgHistory->ShowWindow(SW_HIDE);
	m_bHistoryDlgOpened = false;
}

void CAmazonsView::UpdateComputerMove()
{
	//������������
	if (!m_bComputerMoving) return;

	m_nComputerMoveTimer += TIMER_INTERVAL;
	if (m_nCurState == STATE_UNSELECT)
	{
		Select(g_posSelected);
		m_nCurState = STATE_SELECTED;
	}
	if (m_nCurState == STATE_SELECTED && m_nComputerMoveTimer > 300)
	{
		Move(g_posSelected, g_posMoveTo);
		m_nCurState = STATE_MOVED;
		m_nComputerMoveTimer = 0;
	}
	if (m_nCurState == STATE_MOVED && m_nComputerMoveTimer > 300)
	{
		Shoot(g_posShootAt);
		m_nCurState = STATE_SHOOTED;
		m_nComputerMoveTimer = 0;
	}
	if (m_nCurState == STATE_SHOOTED && m_nComputerMoveTimer > 200)
	{
		m_nCurState = STATE_UNSELECT;
		m_bComputerMoving = false;
		m_bComputerThinking = false;
		ComputerMoveFinished();
	}
}

void CAmazonsView::UpdateRightInfo()
{
	if (m_nGameState == GAME_STATE_NOT_START)
	{
		m_strGameState = _T("׼������");
	}
	else if (m_nGameState == GAME_STATE_PLAYING)
	{
		int playerColor = 0;//1Ϊ�ڣ�2Ϊ��
		int playerType = 0;

		if (g_pGameController->IsPlayer1Turn())
		{
			playerColor = g_pGameController->m_bPlayer1Black ? 1 : 2;
			playerType = g_pGameController->m_nPlayer1Type;
		}
		else
		{
			playerColor = g_pGameController->m_bPlayer1Black ? 2 : 1;
			playerType = g_pGameController->m_nPlayer2Type;
		}

		m_strGameState = playerColor == 1 ? _T("�ڷ�") : _T("�췽");
		if      (playerType == PLAYER_HUMAN)    m_strGameState += _T("  ��������");
		else if (playerType == PLAYER_COMPUTER) m_strGameState += _T("  ��������");
		else if (playerType == PLAYER_NETWORK)  m_strGameState += _T("  �����������");

		if (m_bComputerThinking)
		{
			//g_pAI->m_nOutDepth = g_md_;
			//g_pAI->m_nOutMaxValue = g_score_;
			//g_pAI->m_nOutNumOfNodes = g_node_;
			m_strDepth.Format(_T("���: %d"), g_pAI->m_nOutDepth);
			m_strNodes.Format(_T("�ڵ�: %d"),g_pAI->m_nOutNumOfNodes);
			m_strMoves.Format(_T("�÷�: %d"), g_pAI->m_nOutMaxValue);
		}

		UpdateTimeCounter();

	}
	else if (m_nGameState == GAME_STATE_SUSPEND)
	{
		m_strGameState = _T("��Ϸ��ͣ");
	}
	else if (m_nGameState == GAME_STATE_OVER)
	{
		//IsGameOver������״̬������ʲôҲ������
	}
}

void CAmazonsView::UpdateTimeCounter()
{
	m_nTotalTimer += TIMER_INTERVAL;
	m_nPlayerTimer += TIMER_INTERVAL;

	if (g_pGameController->IsPlayer1Turn())
		GetTimeString(m_nPlayerTimer, m_strPlayer1Timer);
	else
		GetTimeString(m_nPlayerTimer, m_strPlayer2Timer);

	GetTimeString(g_pGameController->GetTotalTime(false), m_strPlayer2TotalTime);
	GetTimeString(g_pGameController->GetTotalTime(true), m_strPlayer1TotalTime);
	GetTimeString(m_nTotalTimer, m_strTotalTimer);
}

void CAmazonsView::ForwardOrBackwardHistoryEnd()
{
	m_nCurState = STATE_UNSELECT;
	m_nGameState = GAME_STATE_SUSPEND;

	//��ȡ��ǰ���裬����mark
	SHistoryRecord record = g_pGameController->GetCurHistoryMove();
	m_posSelected = record.posSelected;
	m_posMoveTo = record.posMoveTo;
	m_posShootAt = record.posShootAt;

	IsGameOver();
	UpdateHistoryDlg();
	InvalidateRect(m_rectLeft);
}

TCHAR * CAmazonsView::GetPlayerName(int playerType)
{
	TCHAR *playerNames[3] = {
		_T("��"),
		_T("����"),
		_T("����"),
	};
	return playerNames[playerType];
}

TCHAR * CAmazonsView::GetPlayer1Color()
{
	return g_pGameController->m_bPlayer1Black ? _T("�ڷ�") : _T("�췽");
}

TCHAR * CAmazonsView::GetPlayer2Color()
{
	return g_pGameController->m_bPlayer1Black ? _T("�췽") : _T("�ڷ�");
}

int CAmazonsView::GetCurPlayerType()
{
	if (g_pGameController->IsPlayer1Turn())
		return g_pGameController->m_nPlayer1Type;
	else
		return g_pGameController->m_nPlayer2Type;
}

void CAmazonsView::GetTimeString(int nTime, CString& strTime)
{
	nTime /= 1000;
	int nHour, nMinute, nSecond;
	CString str;
	nHour = nTime / 3600;
	nSecond = nTime % 60;
	nMinute = (nTime - 3600 * nHour - nSecond) / 60;
	strTime.Empty();
	if (nHour < 10)   str.Format(_T("0%d:"), nHour); else str.Format(_T("%d:"), nHour);     strTime += str;
	if (nMinute < 10) str.Format(_T("0%d:"), nMinute); else str.Format(_T("%d:"), nMinute); strTime += str;
	if (nSecond < 10) str.Format(_T("0%d"), nSecond); else str.Format(_T("%d"), nSecond); strTime += str;
}

#pragma endregion







