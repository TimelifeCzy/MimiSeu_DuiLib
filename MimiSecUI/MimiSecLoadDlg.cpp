#include "stdafx.h"
#include "MimiSecLoadDlg.h"

MimiSecLoadDlg::MimiSecLoadDlg(void)
	: m_pInstallText(NULL)
	, m_pProgressBar(NULL)
{

}

MimiSecLoadDlg::~MimiSecLoadDlg(void)
{

}


DuiLib::CDuiString MimiSecLoadDlg::GetSkinFile()
{
	return _T("skin.xml");
}

LPCTSTR MimiSecLoadDlg::GetWindowClassName(void) const
{
	return _T("MainWnd");
}

void MimiSecLoadDlg::InstallStart()
{
	SetTimer(GetHWND(), TIMER_ID_PROGRESS, 100, NULL);
}

void MimiSecLoadDlg::InstallFinished()
{
	m_pInstallText->SetText(_T("OK"));
	KillTimer(GetHWND(), TIMER_ID_PROGRESS);
	Sleep(100);
	this->Close();
}

LRESULT MimiSecLoadDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (TIMER_ID_PROGRESS == wParam)
	{
		CDuiString strPercent;
		strPercent = m_pInstallText->GetText();
		if (strPercent.GetLength())
		{
			int size_str = WideCharToMultiByte(CP_UTF8, 0, strPercent, -1, 0, 0, NULL, NULL);

			char* point_new_array = new char[size_str];

			WideCharToMultiByte(CP_UTF8, 0, strPercent, -1, point_new_array, size_str, NULL, NULL);

			int nVal = atoi(point_new_array);

			delete[] point_new_array;
			point_new_array = NULL;

			if (nVal > 95)
			{
				m_pInstallText->SetText(L"100%");
				InstallFinished();
			}
			else
			{
				nVal += 5;
				strPercent.Format(L"%d", nVal);
				m_pInstallText->SetText(strPercent + L"%");
			}
		}
	}
	return 0;
}

/*
@ Handle Timer Msg
	call OnTimer ---> 10% increase
*/
LRESULT MimiSecLoadDlg::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;

	switch (uMsg)
	{
	case WM_TIMER: lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	default: break;
	}

	return lRes;
}

void MimiSecLoadDlg::Notify(TNotifyUI &msg)
{
	// Timer
	InstallStart();
	WindowImplBase::Notify(msg);
}

void MimiSecLoadDlg::InitWindow()
{
	try
	{
		//
		// Init timer SetText(0%)
		//
		WindowImplBase::InitWindow();
		m_pInstallText = static_cast<CLabelUI*>(m_pm.FindControl(_T("textProgress")));
		m_pInstallText->SetText(L"0%");
	}
	catch (...)
	{
		throw "CMainWnd::Init";
	}
}

