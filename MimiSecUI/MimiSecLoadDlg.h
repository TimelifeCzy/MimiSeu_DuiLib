////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//		Master Log View WinDlg
//		Author info: 
//			timelife 2020/11/25 version_0.1
//		Transparent loading of the form SecLog
//		
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#define TIMER_ID_PROGRESS (1000)

class MimiSecLoadDlg : public WindowImplBase
{
public:
	MimiSecLoadDlg();
	~MimiSecLoadDlg();

public:
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();

	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	void InstallStart();
	void InstallFinished();

private:
	CAnimationTabLayoutUI *m_pStepTabLayout;
	CLabelUI	*m_pInstallText;
	CProgressUI	*m_pProgressBar;
};

