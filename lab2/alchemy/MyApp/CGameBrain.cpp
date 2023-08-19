#include "CGameBrain.h"

void CGameBrain::InitGameElements() {
    std::map<std::string, std::wstring>::iterator it = elementsResources.begin();
    for (int i = 0; it != elementsResources.end(); it++, i++) {
        Element element(i, it->first, it->second);
        m_elements[i] = element;
    }
}

std::vector<int>* CGameBrain::GetOpenedElements() {
    return &m_openedElements;
};

std::map<int, Element>* CGameBrain::GetAllElements() {
    return &m_elements;
}

Element* CGameBrain::GetElementById(int id) {
    return &m_elements[id];
}

Element CGameBrain::GetCopyElementById(int id) {
    return m_elements[id];
}