// ConfirmPage.cpp : implementation file
//

#include "stdafx.h"
#include "SilentInstaller.h"
#include "ConfirmPage.h"

#include "SilentInstallerDlg.h"
#include "BaiduYun.h"
#include "FileUtils.h"

// ConfirmPage dialog

IMPLEMENT_DYNAMIC(ConfirmPage, CPropertyPage)

ConfirmPage::ConfirmPage(CWnd* pParent /*=NULL*/)
	: WizardPage(ConfirmPage::IDD), path(""), isInstalled(false)
{

}

ConfirmPage::~ConfirmPage()
{
}

void ConfirmPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


void ConfirmPage::setInstallPath(string path)
{
	this->path = path;
}


BEGIN_MESSAGE_MAP(ConfirmPage, CPropertyPage)
END_MESSAGE_MAP()


// ConfirmPage message handlers


BOOL ConfirmPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	pMainDialog->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}


LRESULT ConfirmPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
	//*
	if (!isInstalled) {
		// 拷贝程序文件
		string from = ".";
#ifdef DEBUG
		from.append(".\\Debug");
#endif
		FileUtils::copyRelatively(from.append("\\programs\\*"), path);

		// 静默状态下对快盘类程序进行安装
		BaiduYun byInstaller;
		if (!(byInstaller.install(vDesktop, path))) {
			MessageBox("1、可能是虚拟桌面创建失败；\n2、如果已安装怎么处理？？？\n3、多次查找安装主窗口无果。");
		}
		isInstalled = !(isInstalled);
	}//*/

	return CPropertyPage::OnWizardNext();
}

