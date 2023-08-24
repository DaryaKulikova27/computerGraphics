#include "Element.h"

int Element::GetId() {
	return m_id;
}

std::string Element::GetName() {
	return m_name;
}

std::wstring Element::GetFileName() {
	return m_fileName;
}

std::unique_ptr<Gdiplus::Bitmap> Element::GetElementBitmap() {
	return std::move(m_elementBitmap);
}

void Element::SetId(int id) {
	m_id = id;
}

void Element::SetName(std::string name) {
	m_name = name;
}

void Element::SetFileName(std::wstring fileName) {
	m_fileName = fileName;
}

void Element::SetElementBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap) {
	m_elementBitmap = std::move(bitmap);
}