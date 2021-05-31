
// OthelloTestDlg.h: файл заголовка
//

#pragma once
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include "OthelloHumanPlayer.h"
#include "OthelloComputerPlayer.h"
#include "OthelloField.h"
class OthelloField;

// Диалоговое окно OthelloTestDlg
class OthelloTestDlg : public CDialogEx
{
	// Создание
public:
	OthelloTestDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OTHELLOTEST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	OthelloField tttField;
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	void CreateBoard(int size);
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);

	OthelloBoard* GetBoard();
	OthelloPlayer* GetCurrentPlayer();
	OthelloPlayer* GetPlayer1();
	OthelloPlayer* GetPlayer2();
private:
	OthelloBoard* board;
	OthelloPlayer* player1;
	OthelloPlayer* player2;
	OthelloPlayer* currentPlayer;
	bool bGameInProgress = false;

	void Cleanup();
	void UpdateName();
public:
	afx_msg void OnDestroy();
	void SetGameInProgress(bool inProgress);
	CButton mStartStopButton;
	CString strPlayerTurn;
	void TogglePlayer();
	afx_msg void OnEnChangeEdit1();
	CString test_str;
	afx_msg void OnStnClickedStatic3();
	CString strPlayer1Cnt;
	CString strPlayer2Cnt;
};