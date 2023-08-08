#pragma once
#include "stdafx.h"
#include "resource.h"
#include "Element.h"
#include <iostream>
#include <map>

class CGameBrain
{
public:
	CGameBrain() { 
		InitGameElements(); 
	};
	std::vector<int>* GetOpenedElements();
	std::map<int, Element>* GetAllElements();
	Element* GetElementById(int id);

private:
	void InitGameElements();
	std::map<int, Element> m_elements;
	std::vector<int> m_openedElements{19, 8, 4, 0};
	const int numberOfElements = 20;
	std::map<std::string, std::wstring> elementsResources = {
		{"water", L"./images/water.jpg"},
		{"fire", L"./images/fire.jpg"},
		{"air", L"./images/air.jpg"},
		{"earth", L"./images/earth.jpg"},
		{"lava", L"./images/lava.jpg"},
		{"dust", L"./images/dust.jpg"},
		{"gunpowder", L"./images/gunpowder.jpg"},
		{"explosion", L"./images/explosion.jpg"},
		{"smoke", L"./images/smoke.jpg"},
		{"energy", L"./images/energy.jpg"},
		{"rock", L"./images/rock.jpg"},
		{"storm", L"./images/storm.jpg"},
		{"metal,", L"./images/metal.jpg"},
		{"electricity", L"./images/electricity.jpg"},
		{"hydrogen", L"./images/hydrogen.jpg"},
		{"oxygen", L"./images/oxygen.jpg"},
		{"swamp", L"./images/swamp.jpg"},
		{"life", L"./images/life.jpg"},
		{"bacteria", L"./images/bacteria.jpg"},
		{"alcohol", L"./images/alcohol.png"}
	};
};

