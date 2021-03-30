#include "stdafx.h"
#include "MimiSecBaseDlg.h"
#include "MimiSecUI.h"

MimiSecBaseDlg::MimiSecBaseDlg(void)
{
	// Init Menu ptr
	m_pMenu = NULL;
}

MimiSecBaseDlg::~MimiSecBaseDlg(void)
{

}

DuiLib::CDuiString MimiSecBaseDlg::GetSkinFile()
{
	return _T("MimiSecBaseDlg.xml");
}

LPCTSTR MimiSecBaseDlg::GetWindowClassName(void) const
{
	return _T("MimiSecBase");
}

void MimiSecBaseDlg::InitWindow()
{
	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("Firewalllistview")));
	CListContainerElementUI* pListItem = new CListContainerElementUI();
	pListItem->SetChildVAlign(DT_VCENTER);
	pListItem->SetFixedHeight(30);
	pListItem->SetManager(&m_pm, NULL, false);
	pListItem->SetFixedWidth(100);
	pList->Add(pListItem);
	//CButtonUI* pBtn1 = new CButtonUI();
	//pBtn1->SetManager(&m_pm, NULL, false);
	//pBtn1->SetAttribute(_T("style"), _T("btn_style"));
	//pBtn1->SetText(_T("´úÂë°¢´ô"));
	//pBtn1->SetFixedHeight(20);
	//pBtn1->SetFixedWidth(30);
	//pListItem->Add(pBtn1);
	//CButtonUI* pBtn2 = new CButtonUI();
	//pBtn2->SetManager(&m_pm, NULL, false);
	//pBtn2->SetAttribute(_T("style"), _T("btn_style"));
	//pBtn2->SetText(_T("20001"));
	//pListItem->Add(pBtn2);

	CDialogBuilder builder1;
	CListContainerElementUI* pListItem1 = (CListContainerElementUI*)builder1.Create(_T("listitem.xml"), NULL, this, &m_pm, NULL);

	CControlUI* pLabel = pListItem1->FindSubControl(_T("troy"));
	if (pLabel != NULL) pLabel->SetText(_T("abc_troy"));
	pList->Add(pListItem1);
	for (int i = 0; i < 20; i++)
	{
		CListTextElementUI* pItem = new CListTextElementUI();
		pItem->SetFixedHeight(30);
		pList->Add(pItem);
		pItem->SetText(0, _T("123"));
		pItem->SetText(1, _T("456"));
		pItem->SetText(2, _T("789"));
		pItem->SetTextColor(0, 0xff0000ff);
		pItem->SetTextColor(1, 0xffff0000);
		pItem->SetTextColor(2, 0xffffff00);
	}
}

void MimiSecBaseDlg::Notify(TNotifyUI &msg)
{
	CDuiString name = msg.pSender->GetName();

	// Buttion handle: Page switching
	if (msg.sType == _T("selectchanged"))
	{
		CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("base_tab_switch")));
		if (name.CompareNoCase(_T("ScanButton")) == 0) 
			pTabSwitch->SelectItem(1);
		if (name.CompareNoCase(_T("ScanExitButton")) == 0)
			pTabSwitch->SelectItem(0);

		// Firewall_tab_pane1
		if (name.CompareNoCase(_T("FirewallButton")) == 0)
			pTabSwitch->SelectItem(2);
		if (name.CompareNoCase(_T("FirewallExitButton")) == 0)
			pTabSwitch->SelectItem(0);
	}
	return WindowImplBase::Notify(msg);
}

/*
@ public WinBase
	Hnadle Button Msg
*/
void MimiSecBaseDlg::OnClick(TNotifyUI &msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	// Button Switch Start: WinDlg 
	if (sCtrlName == _T("closebtn"))
	{
		this->Close();
		return;
	}
	else if (sCtrlName == _T("minbtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		return;
	}
	else if (sCtrlName == _T("restorebtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		return;
	}
	else if (sCtrlName.CompareNoCase(_T("menubtn")) == 0)
	{
		CMenuWnd::GetGlobalContextMenuObserver().SetMenuCheckInfo(&m_MenuInfos);

		if (m_pMenu != NULL) {
			delete m_pMenu;
			m_pMenu = NULL;
		}
		m_pMenu = new CMenuWnd();
		CDuiPoint point;
		::GetCursorPos(&point);
		m_pMenu->Init(NULL, _T("menu.xml"), point, &m_pm);
		CMenuWnd::SetMenuItemInfo(_T("menu_help"), true);

		CMenuUI* rootMenu = m_pMenu->GetMenuUI();

		m_pMenu->ResizeMenu();
	}
	// Button Switch End: WinDlg 

	// ScanWinDlgButton_Start：Scan Tab Wwitch
	else if (sCtrlName.CompareNoCase(_T("FullScanButton")) == 0)
	{
		CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("scan_tab_switch")));
		pTabSwitch->SelectItem(0);
		auto pfrmFullScan = static_cast<CLabelUI*>(m_pm.FindControl(_T("FullScanHor_Ver")));
		auto pfrmQuickScan = static_cast<CLabelUI*>(m_pm.FindControl(_T("QuickScanHor_Ver")));
		pfrmFullScan->SetBkColor(0xffff9900);
		pfrmQuickScan->SetBkColor(0xffffffff);
	}
	else if (sCtrlName.CompareNoCase(_T("QuickScanButton")) == 0)
	{
		CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("scan_tab_switch")));
		pTabSwitch->SelectItem(1);
		auto pfrmFullScan = static_cast<CLabelUI*>(m_pm.FindControl(_T("FullScanHor_Ver")));
		auto pfrmQuickScan = static_cast<CLabelUI*>(m_pm.FindControl(_T("QuickScanHor_Ver")));
		pfrmFullScan->SetBkColor(0xffffffff);
		pfrmQuickScan->SetBkColor(0xffff9900);
	}
}
