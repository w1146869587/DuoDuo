// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;

	//启动UDP接收
	CUDPRecver::getSingleton().StartUDPRecv();

	//发送广播消息，当前设备出场了
	CUDPSender::getSingleton().SendBroadcast(CDataCenter::getSingleton().m_LocalInfo.m_strName.c_str(),
		CDataCenter::getSingleton().m_LocalInfo.m_strClientID.c_str(), CDataCenter::getSingleton().m_LocalInfo.m_nPort);
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
// 	SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
// 	notify->ShowNotify(L"Hello SOUI",L"这可能是一个提示");
	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}

void CMainDlg::OnFindDevice(EventArgs *e)
{
	EventFindDevice* pEvt = sobj_cast<EventFindDevice>(e);
	if (pEvt)
	{
		/*	2019-04-09 modify by yangjinpeng
		* 1、新设备上线发送的广播消息
		* 2、将该设备加入到通讯录中
		* 3、向该设备回一个自己信息
		*/

		//broadcast_request
		CUDPSender::getSingleton().SendBroadcastRequest(pEvt->m_strIP, CDataCenter::getSingleton().m_LocalInfo.m_strName.c_str(),
			CDataCenter::getSingleton().m_LocalInfo.m_strClientID.c_str(), CDataCenter::getSingleton().m_LocalInfo.m_nPort);
	}
}