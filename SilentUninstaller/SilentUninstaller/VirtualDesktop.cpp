// VirtualDesktop.cpp : implementation file
//

#include "stdafx.h"
#include "SilentUninstaller.h"
#include "VirtualDesktop.h"

// VirtualDesktop

VirtualDesktop * VirtualDesktop::vDesktop = NULL;

IMPLEMENT_DYNAMIC(VirtualDesktop, CWnd)

VirtualDesktop::VirtualDesktop() : virDesktopName("suiVirtualDesktop")
{
	isOriginalDesktopActive = TRUE;
	isInitialDesktop = TRUE;
}

VirtualDesktop::~VirtualDesktop()
{
}


VirtualDesktop *VirtualDesktop::getVirtualDesktop()
{
	if (vDesktop == NULL) {
		vDesktop = new VirtualDesktop();
	}
	return vDesktop;
}

void VirtualDesktop::create()
{
	if (isInitialDesktop) {	   // ��һ������ʱ��ʼ������
		// Ĭ�������"Default"
		hDesktop = CreateDesktop(virDesktopName, NULL, NULL, 0, GENERIC_ALL , NULL);	

		// ��¼ԭʼ����ľ��
		hOriginalThread = GetThreadDesktop(GetCurrentThreadId());   
		hOriginalInput  = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);
		
		//runProcess("D:\\ktv\\BaiduYun\\uninst.exe");

		// ��ɳ�ʼ�����Ժ󲻻��ٴα����ã���ֹ���������������Դ������
		isInitialDesktop = !isInitialDesktop;
	}
}


bool VirtualDesktop::runProcess(string process)
{
	BOOL bResult = FALSE;
	
	// ��ʼ���������̱���Ľṹ��
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInfo, sizeof(processInfo));
	startupInfo.cb         = sizeof(startupInfo);
	startupInfo.lpDesktop  = virDesktopName.GetBuffer();
	virDesktopName.ReleaseBuffer();

	bResult = ::CreateProcess(NULL, (CT2A)process.c_str(), NULL, NULL, TRUE
		, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo);
	return (TRUE == bResult);
}


BOOL VirtualDesktop::terminateProcess()
{
	// ��ȡ���������ϵĽ��̾��
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.dwProcessId);
	if (hProcess) {
		TRACE("%d\n", processInfo.dwProcessId);
		::TerminateProcess(hProcess, EXIT_SUCCESS);	   // �������������ϵĽ���
	}
	return ::CloseHandle(hProcess);
}


void VirtualDesktop::deleteDesktop()
{
	::CloseDesktop(hDesktop);
	delete vDesktop;
	vDesktop = NULL;
}

void VirtualDesktop::destroy()
{
	// �ر��ɱ����򴴽������������������еĽ���
	if (vDesktop != NULL) {
		terminateProcess();
		deleteDesktop();
	}
}

/*
 * For debug only.
 * switchֻ�踺���л����棬û�б�Ҫ�ٴ�����ر�Virtual Desktop
 */
void VirtualDesktop::switchDesktop()
{
	if (isOriginalDesktopActive) {	   // �Ƿ���ԭʼ����
		//hDesktop = CreateDesktop("Virtual", NULL, NULL, 0, GENERIC_ALL , NULL);	// ������������
		SetThreadDesktop(hDesktop);    // ���������������������� 
		SwitchDesktop(hDesktop);
	}
	else {
		SetThreadDesktop(hOriginalThread); // ��������������ԭʼ���� 
		SwitchDesktop(hOriginalInput);     // �л���ԭʼ����
		//CloseDesktop(hDesktop);	       // �ر���������
	}
	isOriginalDesktopActive = !isOriginalDesktopActive;
}


void VirtualDesktop::listWindows(CEdit *pEdit)
{
	wndFinder.listWindows(hDesktop, pEdit);
}


void VirtualDesktop::findWindows(ProcedureData &pd)
{
	wndFinder.findWindows(hDesktop, &pd);
}


void VirtualDesktop::findChildWindows(HWND hWndParent, ProcedureData &pd)
{
	wndFinder.findChildWindows(hWndParent, &pd);
}


DWORD WINAPI tpFindWindow(LPVOID pParam)
{
	ThreadData *pTd = (ThreadData *)pParam;
	if (pTd == NULL || pTd->hEvent == NULL) return 1;
	::SetThreadDesktop(pTd->wi.hDesktop);
	pTd->wi.hWnd = ::FindWindow(NULL, (pTd->wi.title).c_str());
	::SetEvent(pTd->hEvent);
	return 0;
}

/*
 * �´���һ���̣߳�
 * ���߳���ִ��SetThreadDesktop������ָ�����棬
 * Ȼ����Դ�����ʹ��FindWindow��
 */
HWND VirtualDesktop::findWindow(string title)
{
	HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, "SyncEvent");
	ThreadData td;
	ZeroMemory(&td, sizeof(ThreadData));
	td.hEvent = hEvent;
	td.wi.hDesktop = hDesktop;
	td.wi.title = title;
	HANDLE hThread = CreateThread(NULL, 0,
		tpFindWindow, (LPVOID)&td, 0, NULL);
	WaitForSingleObject(hEvent, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);
	return td.wi.hWnd;
}


BEGIN_MESSAGE_MAP(VirtualDesktop, CWnd)

END_MESSAGE_MAP()



// VirtualDesktop message handlers
