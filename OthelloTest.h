
// OthelloTest.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// OthelloTestApp:
// Сведения о реализации этого класса: OthelloTest.cpp
//

class OthelloTestApp : public CWinApp
{
public:
	OthelloTestApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern OthelloTestApp theApp;
