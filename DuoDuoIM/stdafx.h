// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#pragma warning(disable:4996)
#pragma warning(disable:4482)
#pragma warning(disable:4018)

#define  _CRT_SECURE_NO_WARNINGS
#define	 DLL_SOUI
#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>
#include <event/NotifyCenter.h>
#include <com-cfg.h>
#include "trayicon/SShellNotifyIcon.h"
#include "resource.h"
#define R_IN_CPP	//定义这个开关来
#include "res\resource.h"
using namespace SOUI;

#include <string>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


#define PORT_DUODUO	9099

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"