#include "stdafx.h"
#include <iostream>
#include "resource.h"
#include "MainFrm.h"
#include "Utils.h"

using namespace std;
using namespace Gdiplus;

CMainFrame::CMainFrame()
{
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	// Создаем внеэкранный буфер
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_pBackBuffer.reset(new Bitmap(screenWidth, screenHeight, PixelFormat32bppARGB));

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	unsigned clientWidth = rcClient.Width();
	unsigned clientHeight = rcClient.Height();

	if (!m_pBackBuffer.get() ||
		(clientWidth > m_pBackBuffer->GetWidth()) ||
		(clientHeight > m_pBackBuffer->GetHeight())
		)
	{
		m_pBackBuffer.reset(new Bitmap(clientWidth, clientHeight, PixelFormat32bppARGB));
	}

	InvalidateRect(NULL, TRUE);

	return 0;
}

LRESULT CMainFrame::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// ничего не делаем
	return 0;
}

LRESULT CMainFrame::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(*this);

	RedrawBackBuffer();
	
	Graphics g(dc);
	if (m_pBackBuffer.get())
	{
		// перекидываем внеэкранный буфер на экран
		g.DrawImage(m_pBackBuffer.get(), 0, 0);
	}
	
	return 0;
}

CRect* GetFitRect(CRect& window, CRect& img) {
	CRect fitRect{ 0, 0, 0, 0 };
	float windowRatio = (float) window.Height() / (float) window.Width();
	float imgRatio = (float) img.Height() / (float) img.Width();
	float scale = windowRatio > imgRatio ? (float) window.Width() / (float) img.Width() : (float) window.Height() / (float) img.Height();
	float fitWidth = img.Width() * scale;
	float fitHeight = img.Height() * scale;

	fitRect.top = (window.Height() - fitHeight) / 2;
	fitRect.left = (window.Width() - fitWidth) / 2;

	fitRect.bottom = fitRect.top + fitHeight;
	fitRect.right = fitRect.left + fitWidth;

	return &fitRect;
}

void CMainFrame::RedrawBackBuffer(void)
{
	Graphics g(m_pBackBuffer.get());

	// очищаем внеэкранный буфер
	g.Clear(Color(255, 192, 203));

	CRect rcWindow;
	GetClientRect(&rcWindow);

	if (m_pLoadedImage.get() != NULL) {
		CRect bounds{ 0,0, (int)m_pLoadedImage.get()->GetWidth(), (int)m_pLoadedImage.get()->GetHeight() };

		CRect imgBounds = GetFitRect(rcWindow, bounds);

		g.DrawImage(CMainFrame::m_pLoadedImage.get(), imgBounds.left, imgBounds.top, imgBounds.Width(), imgBounds.Height());
	}
}

LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(
		TRUE,				
		NULL,				
		m_fileName.c_str(),	
		OFN_FILEMUSTEXIST,
		_T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
		_T("All files\0*.*\0")
		_T("\0")
	);	

	if (dlg.DoModal(*this) == IDOK)
	{
		Image img(dlg.m_szFileName);
		if (img.GetLastStatus() == Ok)
		{
			m_pLoadedImage = auto_ptr<Bitmap>(
				new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB)
				);
			Graphics g(m_pLoadedImage.get());
			g.DrawImage(&img, 0, 0);

			SetDocumentName(dlg.m_szFileName);

			InvalidateRect(NULL, TRUE);
		}
	}

	return 0;
}

LRESULT CMainFrame::OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CFileDialog dlg(
		FALSE,				
		_T("jpg"),			
		m_fileName.c_str(),	
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
		_T("All files\0*.*\0")
		_T("\0")
	);

	if (dlg.DoModal() == IDOK)
	{
		if (CUtils::SaveImage(dlg.m_szFileName, *m_pLoadedImage.get(), 75))
		{
			SetDocumentName(dlg.m_szFileName);
		}
		else
		{
			AtlMessageBox(*this, _T("Failed to save file"));
		}
	}

	return 0;
}

LRESULT CMainFrame::OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (!m_fileName.empty())
	{
		if (!CUtils::SaveImage(m_fileName, *m_pLoadedImage.get(), 75))
		{
			AtlMessageBox(*this, _T("Failed to save file"));
		}
	}

	return 0;
}

void CMainFrame::SetDocumentName(std::wstring const& documentName)
{
	m_fileName = documentName;

	SetWindowText(
		(m_fileName.empty() ? _T("Untitled") : CUtils::GetFileName(documentName)).c_str()
	);

	BOOL enableSaving = !m_fileName.empty();

	UIEnable(ID_FILE_SAVE, enableSaving, TRUE);
	UIEnable(ID_FILE_SAVE_AS, enableSaving, TRUE);
}

CPoint CMainFrame::GetRelativePoint(CPoint absoluteCoord) {
	CRect rcWindow;
	GetClientRect(&rcWindow);
	CRect imageSize{ 0, 0, (int)m_pLoadedImage.get()->GetWidth(), (int)m_pLoadedImage.get()->GetHeight() };
	CRect fitRect = GetFitRect(rcWindow, imageSize);
	CPoint relativePoint = absoluteCoord - fitRect.TopLeft();
	float scale = (float)imageSize.Width() / (float)fitRect.Width();
	relativePoint.x = scale * relativePoint.x;
	relativePoint.y *= scale;
	return relativePoint;
}

LRESULT CMainFrame::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	cout << "in OnMouseMove" << endl;
	if (m_isDrawing)
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		CPoint relativePointStart = GetRelativePoint(CPoint(m_lastPoint.X, m_lastPoint.Y));
		CPoint relativePointEnd = GetRelativePoint(CPoint(x, y));

		Graphics graphics(m_pLoadedImage.get());
		graphics.DrawLine(&m_pen, (int) relativePointStart.x, (int) relativePointStart.y, (int) relativePointEnd.x, (int) relativePointEnd.y);

		m_lastPoint = Point(x, y);
		InvalidateRect(NULL, TRUE);
	}

	return 0;
}

LRESULT CMainFrame::OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	m_isDrawing = true;
	m_lastPoint = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	return 0;
}

LRESULT CMainFrame::OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	m_isDrawing = false;
	return 0;
}