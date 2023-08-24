#pragma once
#include "stdafx.h"
#include "resource.h"
#include <windows.h>
#include <io.h>
#include <vector>
#include <string>

class Element
{
public:
	Element(int id, std::string name, std::wstring fileName)
		:m_id(id),
		m_name(name),
		m_fileName(fileName) 
	{
	};
	Element() {};
	int GetId();
	std::string GetName();
	std::wstring GetFileName();
	std::unique_ptr<Gdiplus::Bitmap> GetElementBitmap();
	void SetId(int id);
	void SetName(std::string name);
	void SetFileName(std::wstring fileName);
	void SetElementBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap);
	
private:
	int m_id = 0;
	std::string m_name = "emptyName";
	std::wstring m_fileName = L"emptyFileName";
	std::unique_ptr<Gdiplus::Bitmap> m_elementBitmap;
};

