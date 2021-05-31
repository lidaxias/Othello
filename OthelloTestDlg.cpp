
// TicTacToeTestDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "OthelloTest.h"
#include "OthelloTestDlg.h"
#include "afxdialogex.h"
#include "OthelloPlayer.h"
#include "OthelloComputerPlayer.h"
#include "OthelloHumanPlayer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CStartupDlg.h"


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Диалоговое окно OthelloTestDlg



OthelloTestDlg::OthelloTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OTHELLOTEST_DIALOG, pParent)
	, strPlayerTurn(_T(""))
	, test_str(_T(""))
	, strPlayer1Cnt(_T(""))
	, strPlayer2Cnt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	board = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	currentPlayer = nullptr;
}

void OthelloTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OTHELLOFIELD, tttField);
	DDX_Control(pDX, IDC_BUTTON2, mStartStopButton);
	DDX_Text(pDX, IDC_STATIC1, strPlayerTurn);
	DDX_Text(pDX, IDC_STATIC4, strPlayer1Cnt);
	DDX_Text(pDX, IDC_STATIC5, strPlayer2Cnt);
}

BEGIN_MESSAGE_MAP(OthelloTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &OthelloTestDlg::OnBnClickedButton2)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT1, &OthelloTestDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Обработчики сообщений OthelloTestDlg

BOOL OthelloTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	tttField.SetGameParent(this);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void OthelloTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void OthelloTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR OthelloTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void OthelloTestDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (bGameInProgress)
	{
		Cleanup();
		this->SetGameInProgress(false);
		this->Invalidate();
	}
	else
	{
		CStartupDlg sdlg;
		sdlg.SetDlgParent(this);
		int nRes = sdlg.DoModal();

		if (nRes == IDOK)
		{
			currentPlayer = player1;
			this->SetGameInProgress(true);
			this->UpdateName();
			this->Invalidate();
		}
	}
}

void OthelloTestDlg::CreateBoard(int size)
{
	this->board = new OthelloBoard(size);
}

void OthelloTestDlg::CreatePlayer1(CString name, int type)
{
	if (type == 0)
		this->player1 = new OthelloHumanPlayer();
	else 
		this->player1 = new OthelloComputerPlayer();

	player1->SetupPlayer(name, CellType_X);
	player1->SetBoard(this->board);
}

void OthelloTestDlg::CreatePlayer2(CString name, int type)
{
	if (type == 0)
		this->player2 = new OthelloHumanPlayer();
	else
		this->player2 = new OthelloComputerPlayer();

	player2->SetupPlayer(name, CellType_O);
	player2->SetBoard(this->board);
}

OthelloBoard* OthelloTestDlg::GetBoard()
{
	return board;
}

OthelloPlayer* OthelloTestDlg::GetCurrentPlayer()
{
	return currentPlayer;
}
OthelloPlayer* OthelloTestDlg::GetPlayer1()
{
	return player1;
}
OthelloPlayer* OthelloTestDlg::GetPlayer2()
{
	return player2;
}
void OthelloTestDlg::Cleanup()
{
	// очистка статического текста
	strPlayerTurn = L"";
	strPlayer1Cnt = L"";
	strPlayer2Cnt = L"";
	UpdateData(FALSE);

	if (player1 != nullptr)
	{
		delete player1;
		player1 = nullptr;
	}
	if (player2 != nullptr)
	{
		delete player2;
		player2 = nullptr;
	}
	if (board != nullptr)
	{
		delete board;
		board = nullptr;
	}
	currentPlayer = nullptr;
}


void OthelloTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: добавьте свой код обработчика сообщений
	Cleanup();
}


void OthelloTestDlg::SetGameInProgress(bool inProgress)
{
	this->bGameInProgress = inProgress;
	this->tttField.SetGameInProgress(inProgress);
	if (inProgress)
	{
		mStartStopButton.SetWindowTextW(L"Остановить");
	}
	else
	{
		mStartStopButton.SetWindowTextW(L"Запустить");
		Cleanup();
	}
}
void OthelloTestDlg::UpdateName()
{
	CString str;
	str.Format(L"Ход игрока: %s", currentPlayer->GetName());
	strPlayerTurn = str;
	UpdateData(FALSE);
}


void  OthelloTestDlg::TogglePlayer()
{
	if (currentPlayer != player1)
		currentPlayer = player1;
	else
		currentPlayer = player2;
	UpdateName();
}

void OthelloTestDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void OthelloTestDlg::OnStnClickedStatic3()
{
	// TODO: добавьте свой код обработчика уведомлений
}
