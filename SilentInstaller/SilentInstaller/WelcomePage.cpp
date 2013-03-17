// WelcomePage.cpp : implementation file
//

#include "stdafx.h"
#include "SilentInstaller.h"
#include "WelcomePage.h"
#include "afxdialogex.h"

#include "WindowFinder.h"
#include "SilentInstallerDlg.h"

// WelcomePage dialog

IMPLEMENT_DYNAMIC(WelcomePage, CPropertyPage)

WelcomePage::WelcomePage()
	: CPropertyPage(WelcomePage::IDD)
{
}

WelcomePage::~WelcomePage()
{
}

void WelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, edit);
}


BEGIN_MESSAGE_MAP(WelcomePage, CPropertyPage)
	ON_BN_CLICKED(IDC_LIST_WINDOWS_BUTTON, &WelcomePage::OnBnClickedListWindowsButton)
	ON_BN_CLICKED(IDC_LIST_CHILD_WINDOWS_BUTTON, &WelcomePage::OnBnClickedListChildWindowsButton)
END_MESSAGE_MAP()


// WelcomePage message handlers


BOOL WelcomePage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet *sheet = (CPropertySheet *)GetParent();
	sheet->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}


void WelcomePage::OnBnClickedListWindowsButton()
{
	// TODO: Add your control notification handler code here
	edit.SetWindowText("");
	WindowFinder wndFinder;
	wndFinder.listWindows(&edit);

	SilentInstallerDlg *pSiDlg = (SilentInstallerDlg *)GetParent();
	pSiDlg->getVirtualDesktop()->listWindows(&edit);
}


void WelcomePage::OnBnClickedListChildWindowsButton()
{
	// TODO: Add your control notification handler code here
	edit.SetWindowText("");
	WindowFinder wndFinder;
	HWND hWnd = wndFinder.find("百度云 安装");   // 百度云 安装
	wndFinder.listChildWindows(hWnd, &edit);
}
