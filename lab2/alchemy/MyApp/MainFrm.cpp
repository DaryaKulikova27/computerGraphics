#include "stdafx.h"
#include <iostream>
#include "resource.h"
#include "MainFrm.h"
#include "Utils.h"

using namespace std;
using namespace Gdiplus;

CMainFrame::CMainFrame()
	:m_font1(L"Courier New", 25, FontStyleBoldItalic),
	m_font2(L"Courier New", 10, FontStyleItalic),
	m_pen(Gdiplus::Color(13, 37, 117), 10),
	m_pen2(Gdiplus::Color(13, 37, 117), 2)
{
	closeIcon = std::make_unique<Gdiplus::Image>(L"./images/close.png");
	std::map<int, Element>::iterator it;
	for (it = gameBrain.GetAllElements()->begin(); it != gameBrain.GetAllElements()->end(); ++it) {
		std::unique_ptr<Gdiplus::Image> img = std::make_unique<Gdiplus::Image>(it->second.GetFileName().c_str());

		if (img.get()->GetLastStatus() != Ok)
		{
			throw std::runtime_error("Failed to open image");
		} 

		elementImages[it->second.GetId()] = std::move(img);
	} 
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

/*
LRESULT CMainFrame::OnSize(UINT, WPARAM, LPARAM, BOOL&)
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
} */

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

void CMainFrame::DrawOpenedCards() {
	Graphics g(m_pBackBuffer.get());
	for (int i = 0; i < gameBrain.GetOpenedElements()->size(); i++) {
		Rect cardPosition = cardPositions[i];
		g.DrawImage(elementImages[gameBrain.GetOpenedElements()->at(i)].get(), cardPosition.X, cardPosition.Y);
	}
}

void CMainFrame::DrawExperimentedElements() {
	Graphics g(m_pBackBuffer.get());

	for (int i = 0; i < experimentedElements.size(); i++) {
		g.DrawImage(elementImages[experimentedElements[i].first].get(), experimentedElements[i].second);
	}
}


void CMainFrame::RedrawBackBuffer(void)
{
	Graphics g(m_pBackBuffer.get());
	// очищаем внеэкранный буфер
	g.Clear(Color(255, 192, 203));

	CRect rcWindow;
	GetClientRect(&rcWindow);

	//CPaintDC dc(m_hWnd);

	// устанавливаем режим устранения ступенчатости при рисовании текста
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	SolidBrush brush(Color(13, 37, 117));
	g.DrawString(L"Открытые элементы", -1, &m_font1, PointF((rcWindow.Width() / 2) * 0.2, 10), &brush);
	g.DrawString(L"Поле для экспериментов", -1, &m_font1, PointF(rcWindow.Width() / 2 + (rcWindow.Width() / 2) * 0.2, 10), &brush);

	// перегородка посередине
	Point myStartPoint = Point(rcWindow.Width() / 2, 0);
	Point myEndPoint = Point(rcWindow.Width() / 2, rcWindow.Height());
	g.DrawLine(&m_pen, myStartPoint, myEndPoint);

	// рисование карточек
	Rect borderForCards = Rect(rcWindow.TopLeft().x + 30, rcWindow.TopLeft().y + 60, (rcWindow.Width() / 2) - 60, rcWindow.Height() - 120);
	//g.DrawRectangle(&m_pen2, borderForCards);

	m_borderForExperimentingField = Rect(rcWindow.Width() / 2 + 30, rcWindow.TopLeft().y + 60, (rcWindow.Width() / 2) - 60, rcWindow.Height() - 120);
	g.DrawRectangle(&m_pen2, m_borderForExperimentingField);

	m_closePosition = Rect(rcWindow.Width() / 2 + rcWindow.Width() / 4, m_borderForExperimentingField.GetBottom() - 60, 50, 50);
	g.DrawImage(closeIcon.get(), m_closePosition);

	SolidBrush brush2(Color(204, 229, 255));
	int cardSpaceWidth = (borderForCards.Width - 5 * CARD_WIDTH) / 4;
	int cardSpaceHeight = (borderForCards.Height - 4 * CARD_HEIGTH) / 3;


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cardPositions.push_back(Rect(borderForCards.X + j * cardSpaceWidth + j * CARD_WIDTH, borderForCards.Y + i * cardSpaceHeight + i * CARD_HEIGTH, CARD_WIDTH, CARD_HEIGTH));
		}
	}

	for (int i = 0; i < cardPositions.size(); i++) {
		g.FillRectangle(&brush2, cardPositions[i]);
	}

	DrawOpenedCards();
	DrawExperimentedElements();
}


bool CMainFrame::IsClickedOriginalElement(Point lastPoint) {
	int id;
	Rect copyCardPos;
	for (int i = 0; i < gameBrain.GetOpenedElements()->size(); i++) {
		Rect cardPos = cardPositions[i];
		if (((cardPos.X <= lastPoint.X) && (lastPoint.X <= cardPos.X + cardPos.Width)) && ((cardPos.Y <= lastPoint.Y) && (lastPoint.Y <= cardPos.Y + cardPos.Height))) {
			id =  gameBrain.GetOpenedElements()->at(i);
			if (GetIndexInExperimentedElements(id) == -1) {
				copyCardPos = Rect(m_borderForExperimentingField.X, m_borderForExperimentingField.Y, CARD_WIDTH, CARD_HEIGTH);
				experimentedElements.push_back(make_pair(id, copyCardPos));
				m_originalElementWasClicked = true; 
				return true;
			}
			return false;
		}
	}
	return false;
}

int CMainFrame::GetIndexInExperimentedElements(int id) {
	for (int i = 0; i < experimentedElements.size(); i++) {
		if (experimentedElements[i].first == id) {
			return i;
		}
	}
	return -1;
}

bool CMainFrame::IsClickedCopyElement(Point lastPoint) {
	for (int i = 0; i < experimentedElements.size(); i++) {
		Rect elementPos = experimentedElements[i].second;
		if (((elementPos.X <= lastPoint.X) && (lastPoint.X <= elementPos.X + elementPos.Width)) && ((elementPos.Y <= lastPoint.Y) && (lastPoint.Y <= elementPos.Y + elementPos.Height))) {
			m_selectedElement = make_pair(experimentedElements[i].first, experimentedElements[i].second);
			m_moving = true;
			return true;
		}
	}
	return false;
}

int CMainFrame::GetIntersectedElement(Point lastPoint) {
	for (int i = 0; i < experimentedElements.size(); i++) {
		if (((lastPoint.X) >= (experimentedElements[i].second.X + 10)) && ((lastPoint.X) <= (experimentedElements[i].second.X + 70))
			&& ((lastPoint.Y) >= (experimentedElements[i].second.Y + 10)) && ((lastPoint.Y) <= (experimentedElements[i].second.Y + 70))) {
			return experimentedElements[i].first;
		}
	}
	return -1;
}

void CMainFrame::MoveCopyElement(Point lastPoint) {
	Point pastCenter = Point(m_selectedElement.second.X + CARD_WIDTH / 2, m_selectedElement.second.Y + CARD_HEIGTH / 2);
	Point offset = lastPoint - pastCenter;
	Rect newPosition = Rect(m_selectedElement.second.X + offset.X, m_selectedElement.second.Y + offset.Y, CARD_WIDTH, CARD_HEIGTH);
	int secondElementId = GetIntersectedElement(lastPoint);
	if (((newPosition.X + CARD_WIDTH / 2) >= (m_closePosition.X + 10)) && ((newPosition.X + CARD_WIDTH / 2) <= (m_closePosition.X + 40))
		&& ((newPosition.Y + CARD_HEIGTH / 2) >= (m_closePosition.Y + 10)) && ((newPosition.Y + CARD_HEIGTH / 2) <= (m_closePosition.Y + 40))) {
		experimentedElements.erase(experimentedElements.begin() + GetIndexInExperimentedElements(m_selectedElement.first));
		m_moving = false;
	}
	else if (secondElementId != -1) {
		std::cout << secondElementId;
		std::vector<int> newElements = gameBrain.GetNewElement(m_selectedElement.first, secondElementId);
		if (newElements.size() > 0) {
			experimentedElements.erase(experimentedElements.begin() + GetIndexInExperimentedElements(m_selectedElement.first));
			experimentedElements.erase(experimentedElements.begin() + GetIndexInExperimentedElements(secondElementId));
			gameBrain.AddNewOpenElement(newElements);
			if (newElements.size() > 1) {
				Rect positionNewElement1 = Rect(lastPoint.X, lastPoint.Y, CARD_WIDTH, CARD_HEIGTH);
				Rect positionNewElement2 = Rect(lastPoint.X + 40, lastPoint.Y, CARD_WIDTH, CARD_HEIGTH);
				experimentedElements.push_back(make_pair(newElements[0], positionNewElement1));
				experimentedElements.push_back(make_pair(newElements[1], positionNewElement2));
			}
			else {
				Rect positionNewElement = Rect(lastPoint.X, lastPoint.Y, CARD_WIDTH, CARD_HEIGTH);
				experimentedElements.push_back(make_pair(newElements[0], positionNewElement));
			}
			m_moving = false;
		}
	}
	else {
		experimentedElements.erase(experimentedElements.begin() + GetIndexInExperimentedElements(m_selectedElement.first));
		experimentedElements.push_back(make_pair(m_selectedElement.first, newPosition));
	}
	InvalidateRect(NULL, TRUE);
}

LRESULT CMainFrame::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	if (m_moving)
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		MoveCopyElement(Point(x, y));
	}

	return 0;
}

LRESULT CMainFrame::OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	m_lastPoint = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if (IsClickedOriginalElement(m_lastPoint) || IsClickedCopyElement(m_lastPoint)) {
		InvalidateRect(NULL, TRUE);
	} 
	
	return 0;
}

LRESULT CMainFrame::OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	m_moving = false;
	return 0;
}