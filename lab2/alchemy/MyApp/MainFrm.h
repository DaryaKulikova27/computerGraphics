#pragma once
#include "CGameBrain.h"

using namespace Gdiplus;

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler
{
public:
	CMainFrame();
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAIN_MENU)

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_MENU_EXIT, OnFileExit)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

private:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void RedrawBackBuffer(void);
	void DrawOpenedCards();
	void DrawExperimentedElements();
	bool IsClickedOriginalElement(Point lastPoint);
	bool IsClickedCopyElement(Point lastPoint);
	void MoveCopyElement(Point lastPoint);
	int GetIndexInExperimentedElements(int id);
	int GetIntersectedElement(Point lastPoint);

	std::unique_ptr<Gdiplus::Bitmap> m_pBackBuffer;

	std::wstring m_fileName;
	bool m_moving{ false };
	bool m_originalElementWasClicked{ false };
	Gdiplus::Point m_lastPoint{ 0, 0 };
	Gdiplus::Pen m_pen;
	Gdiplus::Pen m_pen2;
	Gdiplus::Font m_font1;
	Gdiplus::Font m_font2;
	const int CARD_WIDTH = 80;
	const int CARD_HEIGTH = 80;
	Rect m_borderForExperimentingField;
	Rect m_closePosition;
	std::vector<Rect> cardPositions;
	std::map<int, std::unique_ptr<Gdiplus::Image>> elementImages;
	std::unique_ptr<Gdiplus::Image> closeIcon;
	std::vector<std::pair<int, Rect>> experimentedElements;
	std::pair<int, Rect> m_selectedElement;
	
	CGameBrain gameBrain = CGameBrain();
};
