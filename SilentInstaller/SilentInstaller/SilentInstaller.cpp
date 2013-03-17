
// SilentInstaller.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SilentInstaller.h"
#include "SilentInstallerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSilentInstallerApp

BEGIN_MESSAGE_MAP(CSilentInstallerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSilentInstallerApp construction

CSilentInstallerApp::CSilentInstallerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSilentInstallerApp object

CSilentInstallerApp theApp;


// CSilentInstallerApp initialization

BOOL CSilentInstallerApp::InitInstance()
{
	//* 创建互斥体，让程序只能打开一次
	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("SilentInstallerMutex"));
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		::CloseHandle(hMutex);
		hMutex = NULL;
		MessageBox(NULL, _T("安装程序正在运行中！"), _T("提示："), MB_ICONWARNING | MB_OK);
		CString titles[3] = { "Welcome", "Setting", "Finish" };    // 安装程序三个页面的title
		for (int i = 0; i < 3; ++i) {
			HWND prevWnd = FindWindow(NULL, titles[i]);
			if (prevWnd != NULL) {
				::ShowWindow(prevWnd, SW_SHOWNORMAL);
				::SetForegroundWindow(prevWnd);
				break;
			}
		}
		return FALSE;
	}
	if(hMutex) ::ReleaseMutex(hMutex);    //*/

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	SilentInstallerDlg dlg;
	//m_pMainWnd = &dlg;
	dlg.DoModal();

	/*INT_PTR nResponse = dlg.DoModal();
	// 无论DoModal返回什么，if-else都根本执行不到。WHY?
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}*/

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

