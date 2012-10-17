// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __QUIT_CTRL_HPP__
#define __QUIT_CTRL_HPP__

#include <Windows.h>

namespace CCTool{

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type);

//³ÌÐòÍË³ö¿ØÖÆ
class QuitCtrl
{
public:
	enum CtrlState{run,quit};
	
	QuitCtrl()
	{
		ctrl_state = run;
		SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
	}

	CtrlState getState() const
	{
		return ctrl_state;
	}

	friend BOOL WINAPI console_ctrl_handler(DWORD ctrl_type);

protected:
private:

	static CtrlState ctrl_state;

};

QuitCtrl::CtrlState QuitCtrl::ctrl_state = QuitCtrl::run;

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type)
{
	switch (ctrl_type)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		
		QuitCtrl::ctrl_state = QuitCtrl::quit;
		return TRUE;
	default:
		return FALSE;
	}
}

void QuitDlay(int time)
{
	for (int i = time ;i > 0 ; i--)
	{
		printf("Normal Quit! %d...\r",i);
		Sleep(1000);
	}
}

}
#endif