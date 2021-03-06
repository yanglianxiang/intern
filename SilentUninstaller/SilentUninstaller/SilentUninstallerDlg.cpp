// SilentInstallerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SilentUninstaller.h"
#include "SilentUninstallerDlg.h"

// SilentInstallerDlg

IMPLEMENT_DYNAMIC(SilentUninstallerDlg, CPropertySheet)

SilentUninstallerDlg::SilentUninstallerDlg()
	:CPropertySheet("", NULL, 0), ALT_X("ALT+X")
{
	// 去掉帮助按钮
	m_psh.dwFlags &= ~PSH_HASHELP;          // 前缀是PSH_
#ifdef DEBUG
	wPage.m_psp.dwFlags &= ~PSP_HASHELP;    // 前缀是PSP_
#endif
	cPage.m_psp.dwFlags &= ~PSP_HASHELP;
	fPage.m_psp.dwFlags &= ~PSP_HASHELP;

	/*
	 * AddPage adds the CPropertyPage object to the CPropertySheet object's list of pages 
	 * but does not actually create the window for the page. 
	 * The framework postpones creation of the window for the page until the user selects that page.
	 */
#ifdef DEBUG
	AddPage(&wPage);
#endif
	AddPage(&cPage);
	AddPage(&fPage);

	// 将Property sheet设置为向导模式
	SetWizardMode();

	vDesktop = VirtualDesktop::getVirtualDesktop();
}

SilentUninstallerDlg::SilentUninstallerDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

SilentUninstallerDlg::SilentUninstallerDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	
}

SilentUninstallerDlg::~SilentUninstallerDlg()
{
}


BOOL SilentUninstallerDlg::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	
	/*
	 * GlobalAddAtom函数得到的值在0xC000到0xFFFF之间，所以减掉0xC000来满足RegisterHotKey的调用要求。
	 */
	altX = ::GlobalAddAtom(ALT_X) - 0xC000;
	/*
	 * Identifier of the hot key. No other hot key in the calling thread should have the same identifier. 
	 * An application must specify a value in the range 0x0000 through 0xBFFF. 
	 * A shared dynamic-link library (DLL) must specify a value in the range 0xC000 through 0xFFFF.
	 * 为了避免与其他动态链接库定义的热键冲突，一个DLL必须使用GlobalAddAtom函数获得热键的标识符。
	 */
	::RegisterHotKey(m_hWnd, altX, MOD_ALT, 'X'); 	// 设置热键为 ALT+X

	// 创建虚拟桌面
	vDesktop->create();

	return bResult;
}


VirtualDesktop *SilentUninstallerDlg::getVirtualDesktop()
{
	return vDesktop;
}


BEGIN_MESSAGE_MAP(SilentUninstallerDlg, CPropertySheet)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)	   // 链接热键消息
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// InstallDlg message handlers


LRESULT SilentUninstallerDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (wParam == altX)	{    // 消息为 Alt+X 时
		vDesktop->switchDesktop();
	}
	return TRUE;
}


/*
 * 点击关闭按钮会发送WM_DESTROY消息
 */
void SilentUninstallerDlg::OnDestroy()
{
	CPropertySheet::OnDestroy();

	// TODO: Add your message handler code here
	
	// 注销热键
	::UnregisterHotKey(m_hWnd, altX);

	// 移除ATOM
	::GlobalDeleteAtom(altX + 0xC000);

	// 销毁虚拟桌面
	vDesktop->destroy();
}

