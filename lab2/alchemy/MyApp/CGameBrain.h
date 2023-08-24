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
	Element GetCopyElementById(int id);
	std::vector<int> GetNewElement(int id1, int id2);
	void AddNewOpenElement(std::vector<int> idElements);

private:
	void InitGameElements();
	std::map<int, Element> m_elements;
	std::vector<int> m_openedElements{ 19, 8, 4, 0 };
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
	std::vector<std::vector<int>> m_combinations = {
		{8, 4, 11},
		{0, 4, 3},
		{8, 3, 9},
		{9, 8, 7, 16},
		{0, 8, 6},
		{11, 19, 15},
		{0, 6, 17}, 
		{8, 15, 13}, 
		{13, 6, 5}, 
		{5, 19, 10, 14}, 
		{19, 4, 18}, 
		{8, 19, 1}, 
		{18, 6, 12}, 
		{12, 18, 2}
	};
};

