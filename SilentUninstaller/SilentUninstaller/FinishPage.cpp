// FinishPage.cpp : implementation file
//

#include "stdafx.h"
#include "SilentUninstaller.h"
#include "FinishPage.h"
#include "afxdialogex.h"

#include "SilentUninstallerDlg.h"

#include "FileUtils.h"

// FinishPage dialog

IMPLEMENT_DYNAMIC(FinishPage, CPropertyPage)

FinishPage::FinishPage()
	: WizardPage(FinishPage::IDD)
{
}

FinishPage::~FinishPage()
{
}

void FinishPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FinishPage, CPropertyPage)
END_MESSAGE_MAP()


// FinishPage message handlers


BOOL FinishPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class

	// Change button next to finish.
	pMainDialog->SetWizardButtons(PSWIZB_FINISH);
	// Disable cancel button.
	GetParent()->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	return CPropertyPage::OnSetActive();
}


BOOL FinishPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	// !!! Do NOT test this in your develop working directory.
	FileUtils::emptyCurDir();
	FileUtils::batSelfDelete();

	return WizardPage::OnWizardFinish();
}

