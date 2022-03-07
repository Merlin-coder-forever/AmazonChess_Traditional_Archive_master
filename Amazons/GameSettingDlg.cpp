// GameSettings.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "AmazonsApp.h"
#include "GameSettingDlg.h"
#include <iostream>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameSettings dialog


CGameSettingDlg::CGameSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameSettingDlg::IDD, pParent)
	, m_nPlayer1Type(0)
	, m_nPlayer2Type(0)
	, m_nPlayer1IsBlack(0)
	, m_nPlayer1IsFirst(0)
{
	//{{AFX_DATA_INIT(CGameSettings)
	//}}AFX_DATA_INIT
}

void CGameSettingDlg::Init(int nPlayer1Type, int nPlayer2Type,  bool bPlayer1IsBlack, bool bPlayer1IsFirst)
{
	//true的话索引是0，false索引是1
	m_nPlayer1Type = nPlayer1Type;
	m_nPlayer1IsBlack = bPlayer1IsBlack ? 0 : 1;
	m_nPlayer1IsFirst = bPlayer1IsFirst ? 0 : 1;

	m_nPlayer2Type = nPlayer2Type;
	m_nPlayer2IsBlack = bPlayer1IsBlack ? 1 : 0;
	m_nPlayer2IsFirst = bPlayer1IsFirst ? 1 : 0;
}

void CGameSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameSettings)
	DDX_Radio(pDX, IDC_RADIO_P1_BLACK, m_nPlayer1IsBlack);
	DDX_Radio(pDX, IDC_RADIO_P1_FIRST, m_nPlayer1IsFirst);

	DDX_Radio(pDX, IDC_RADIO_P2_BLACK, m_nPlayer2IsBlack);
	DDX_Radio(pDX, IDC_RADIO_P2_FIRST, m_nPlayer2IsFirst);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_PLAYER1, m_choosePlayerType1);
	DDX_Control(pDX, IDC_COMBO_PLAYER2, m_choosePlayerType2);
}


BEGIN_MESSAGE_MAP(CGameSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CGameSettings)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_P1_BLACK, &CGameSettingDlg::OnBnClickedRadioP1Color)
	ON_BN_CLICKED(IDC_RADIO_P1_RED, &CGameSettingDlg::OnBnClickedRadioP1Color)
	ON_BN_CLICKED(IDC_RADIO_P2_BLACK, &CGameSettingDlg::OnBnClickedRadioP2Color)
	ON_BN_CLICKED(IDC_RADIO_P2_RED, &CGameSettingDlg::OnBnClickedRadioP2Color)
	ON_BN_CLICKED(IDC_RADIO_P1_FIRST, &CGameSettingDlg::OnBnClickedRadioP1Turn)
	ON_BN_CLICKED(IDC_RADIO_P1_SECOND, &CGameSettingDlg::OnBnClickedRadioP1Turn)
	ON_BN_CLICKED(IDC_RADIO_P2_FIRST, &CGameSettingDlg::OnBnClickedRadioP2Turn)
	ON_BN_CLICKED(IDC_RADIO_P2_SECOND, &CGameSettingDlg::OnBnClickedRadioP2Turn)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_PLAYER1, &CGameSettingDlg::OnCbnSelchangeComboPlayer1)
	ON_EN_CHANGE(IDC_EDIT1, &CGameSettingDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CGameSettingDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameSettings message handlers



void CGameSettingDlg::OnBnClickedRadioP1Color()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nPlayer2IsBlack = m_nPlayer1IsBlack == 0 ? 1 : 0;
	UpdateData(FALSE);
}


void CGameSettingDlg::OnBnClickedRadioP2Color()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nPlayer1IsBlack = m_nPlayer2IsBlack == 0 ? 1 : 0;
	UpdateData(FALSE);
}


void CGameSettingDlg::OnBnClickedRadioP1Turn()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nPlayer2IsFirst = m_nPlayer1IsFirst == 0 ? 1 : 0;
	UpdateData(FALSE);
}


void CGameSettingDlg::OnBnClickedRadioP2Turn()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nPlayer1IsFirst = m_nPlayer2IsFirst == 0 ? 1 : 0;
	UpdateData(FALSE);
}


BOOL CGameSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_choosePlayerType1.AddString(_T("人"));
	m_choosePlayerType1.AddString(_T("电脑"));
	m_choosePlayerType1.SetCurSel(m_nPlayer1Type);
	m_choosePlayerType2.AddString(_T("人"));
	m_choosePlayerType2.AddString(_T("电脑"));
	m_choosePlayerType2.SetCurSel(m_nPlayer2Type);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGameSettingDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_nPlayer1Type = m_choosePlayerType1.GetCurSel();
	m_nPlayer2Type = m_choosePlayerType2.GetCurSel();
	
	CString buff1;
	std::string buff2;
	FILE * fp;
	char buffer[512] = { 0 };
	_getcwd(buffer, 1024);
	char outfile[128] = { 0 };

	strcat(buffer, "\\name.txt");

	fp = fopen(buffer, "wt+");
	GetDlgItem(IDC_EDIT1)->GetWindowText(buff1);
	buff2 = CT2A(buff1.GetBuffer());
	fputs(buff2.c_str(), fp);
	GetDlgItem(IDC_EDIT2)->GetWindowText(buff1);
	buff2 = CT2A(buff1.GetBuffer());
	fputs("\n", fp);
	fputs(buff2.c_str(), fp);
	fclose(fp);
	CDialog::OnOK();
}


void CGameSettingDlg::OnCbnSelchangeComboPlayer1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameSettingDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}


void CGameSettingDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}
