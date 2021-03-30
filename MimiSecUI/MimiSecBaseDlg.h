////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//		Master Base WinDlg
//		Author info: 
//			1. timelife 2020/11/30 version_0.1
//		Modu: Scan && Filtering && RePort && Updata
//		Menu: Tools && MySoft
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
class MimiSecBaseDlg : public WindowImplBase
{
public:
	MimiSecBaseDlg();
	~MimiSecBaseDlg();

public:
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual void Notify(TNotifyUI &msg);

	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		PostQuitMessage(0);
		return 0;
	}

	// onclik
	virtual void OnClick(TNotifyUI& msg);

	void InitWindow();

	CMenuWnd* m_pMenu;
	CStdStringPtrMap m_MenuInfos;
};

