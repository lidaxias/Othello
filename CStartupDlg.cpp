// CStartupDlg.cpp: файл реализации
//

#include "pch.h"
#include "OthelloTest.h"
#include "CStartupDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CStartupDlg

IMPLEMENT_DYNAMIC(CStartupDlg, CDialogEx)

CStartupDlg::CStartupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, strSizeEdit(_T(""))
	, strPlayerName1(_T(""))
	, strPlayerName2(_T(""))
{

}

CStartupDlg::~CStartupDlg()
{
}

void CStartupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mSizeEdit);
	DDX_Text(pDX, IDC_EDIT1, strSizeEdit);
	DDX_Control(pDX, IDC_SPIN1, mSizeSpin);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER1, strPlayerName1);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER2, strPlayerName2);
	DDX_Control(pDX, IDC_COMBOTYPEPLAYER1, mTypePlayer1);
	DDX_Control(pDX, IDC_COMBOTYPEPLAYER2, mTypePlayer2);
}


BEGIN_MESSAGE_MAP(CStartupDlg, CDialogEx)
	ON_BN_CLICKED(ID_STARTBUTTON, &CStartupDlg::OnBnClickedStartbutton)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CStartupDlg::OnDeltaposSpin1)
	ON_BN_CLICKED(IDCANCEL, &CStartupDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений CStartupDlg


BOOL CStartupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strPlayerName1=L"Чёрный ворон";
	strPlayerName2=L"Белая ворона";
	UpdateData(false);
	mSizeSpin.SetBuddy(&mSizeEdit);
	mSizeSpin.SetRange(4, 10);
	mSizeSpin.SetPos(6);

	mTypePlayer1.SetCurSel(0);
	mTypePlayer2.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CStartupDlg::OnBnClickedStartbutton()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	if ((strPlayerName1 == L"") || (strPlayerName2 == L""))
	{
		AfxMessageBox(L"Имя игрока не может быть пустым");
		return;
	}
	if (strPlayerName1 == strPlayerName2)
	{
		AfxMessageBox(L"Одинаковые имена игроков!");
		return;
	}
	int bs = _ttoi(strSizeEdit);
	dlgParent->CreateBoard(bs);
	dlgParent->CreatePlayer1(strPlayerName1, mTypePlayer1.GetCurSel());
	dlgParent->CreatePlayer2(strPlayerName2, mTypePlayer2.GetCurSel());
	// начальные 4 фишки 
	dlgParent->GetBoard()->SetCell(bs / 2-1, bs / 2-1, CellType_O);
	dlgParent->GetBoard()->SetCell(bs / 2, bs / 2, CellType_O);
	dlgParent->GetBoard()->SetCell(bs / 2, bs / 2-1, CellType_X);
	dlgParent->GetBoard()->SetCell(bs / 2-1, bs / 2, CellType_X);
	this->EndDialog(IDOK);
}

void CStartupDlg::SetDlgParent(OthelloTestDlg* p)
{
	this->dlgParent = p;
}

void CStartupDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}


void CStartupDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
