// HistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AmazonsApp.h"
#include "AmazonsGameController.h"
#include "HistoryDlg.h"
#include "AmazonsView.h"
#include "GameSettingDlg.h"

#include<stdlib.h>  
#include<ctime>  
#include<stdio.h>  
#include <iostream>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int count = 0;
int line = 1;
FILE *fp;
char rec[512];
char tmp[30] = { 0 }, tmp2[10] = { 0 };
char name[90] = { 0 };

void WriteIn(int lx, int ly, int x, int y, int bx, int by) {
	fputs(name, fp);
	lx = 10 - lx;
	x = 10 - x;
	bx = 10 - bx;
	if (count % 2 == 1) {
		itoa(line, tmp2, 10);
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		strcat(tmp, " ");
		tmp2[0] = ly + 'a';
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(lx, tmp2, 10);
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		tmp2[0] = y + 'a';
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(x, tmp2, 10);
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		tmp2[0] = by + 'a';
		strcat(tmp, "(");
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(bx, tmp2, 10);
		strcat(tmp, tmp2);
		strcat(tmp, ")");
		strcat(tmp, " ");
		memset(tmp2, 0, 30);
		if (fp)
			fputs(tmp, fp);

		memset(tmp, 0, 30);
	}
	else {
		tmp2[0] = ly + 'a';
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(lx, tmp2, 10);
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		tmp2[0] = y + 'a';
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(x, tmp2, 10);
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		tmp2[0] = by + 'a';
		strcat(tmp, "(");
		strcat(tmp, tmp2);
		memset(tmp2, 0, 30);
		itoa(bx, tmp2, 10);
		strcat(tmp, tmp2);
		strcat(tmp, ")");
		strcat(tmp, "\n");
		memset(tmp2, 0, 30);
		if(fp)
			fputs(tmp, fp);
		line++;
		memset(tmp, 0, 30);
	}
	count++;
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg dialog


CHistoryDlg::CHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistoryDlg)
	m_strHistory = _T("");
	//}}AFX_DATA_INIT
	m_pView=NULL;
}
CHistoryDlg::CHistoryDlg(CView* pView)
{
	m_pView=pView;
}
int CHistoryDlg::Create()
{
	return CDialog::Create(CHistoryDlg::IDD);
}

void CHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistoryDlg)
	DDX_Control(pDX, IDC_HISTORY, m_editHistory);
	DDX_Text(pDX, IDC_HISTORY, m_strHistory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistoryDlg, CDialog)
	//{{AFX_MSG_MAP(CHistoryDlg)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void CHistoryDlg::UpdateHistoryText(CAmazonsGameController *pAmazons)
{
	SHistoryRecord history[92];
	int nPtr = 0;
	int nCurPtr = 0;
	pAmazons->GetHistory(history, nPtr, nCurPtr);
	char timebuf[128] = { 0 };
	char filenamebuf[128] = { 0 };

	_getcwd(name, 90);
	strcat(name, "\\name.txt");
	FILE *fname = fopen(name, "r");

	memset(name, 0, 90);
	if (count == 0) {
		char buffer[512] = { 0 };
		_getcwd(buffer, 512);
		struct tm *newtime;
		char outfile[128] = { 0 };
		time_t t1;
		t1 = time(NULL);
		newtime = localtime(&t1);
		

		strcat(name, "#[AM][");
		fgets(buff20, 20, fname);
		strcat(name, buff20);
		strcat(filenamebuf, "\\AM-");
		strcat(filenamebuf, buff20);

		for (int i = 0; i < 90; i++) {
			if (name[i] == '\n' ) {
				for (int j = i; j < 90 - 1; j++) {
					name[i] = name[i + 1];
				}
				break;
			}
		}


		for (int i = 0; i < 90; i++) {
			if (filenamebuf[i] == '\n') {
				for (int j = i; j < 90 - 1; j++) {
					filenamebuf[i] = filenamebuf[i + 1];
				}
				break;
			}
		}
		strcat(filenamebuf, " B vs ");


		strcat(name, "][");
		fgets(buff20, 20, fname);
		strcat(name, buff20);
		strcat(filenamebuf, buff20);
		strcat(name, "][手胜][");
		strftime(timebuf, 128, "%Y/%m/%d %H:%M:%S", newtime);
		strcat(name, timebuf);
		strcat(name, "  合肥][国赛]; \n");


		strftime(outfile, 128, " W-手胜-%Y%m%d_%H%M%S-合肥-国赛.txt", newtime);

		strcat(buffer, filenamebuf);
		strcat(buffer, outfile);

		fp = fopen(buffer, "wt+");
		strcat(rec, buffer);
		count++;
		fclose(fname);
	}
	else {

		fp = fopen(rec, "wt+");
	}
	
	m_strHistory = "";
	CString strTemp;
	for (int i = 0; i < nPtr; i++)
	{
		CString prefix = i >= nCurPtr - 1 ? _T("-->") : _T("   ");
		if (pAmazons->IsPlayer1Turn(i))
			strTemp.Format(_T("%s%2d.%s\t"), prefix, i, pAmazons->m_bPlayer1Black ? _T("黑方") : _T("红方"));
		else
			strTemp.Format(_T("%s%2d.%s\t"), prefix, i, pAmazons->m_bPlayer1Black ? _T("红方") : _T("黑方"));

		m_strHistory += strTemp;
		strTemp.Format(_T("%d%d%d%d(%d%d)"),
			history[i].posSelected.i, history[i].posSelected.j,
			history[i].posMoveTo.i, history[i].posMoveTo.j,
			history[i].posShootAt.i, history[i].posShootAt.j
			);
		WriteIn(history[i].posSelected.i, history[i].posSelected.j,
			history[i].posMoveTo.i, history[i].posMoveTo.j,
			history[i].posShootAt.i, history[i].posShootAt.j);
		strTemp += "\r\n";
		m_strHistory += strTemp;
	}
	count = 1;
	fclose(fp);
	line = 1;
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg message handlers

void CHistoryDlg::OnClose()
{
	((CAmazonsView*)m_pView)->HistoryDlgClosed();
	CDialog::OnClose();
}
