#include "CGameBrain.h"

void CGameBrain::InitGameElements() {
    std::map<std::string, std::wstring>::iterator it = elementsResources.begin();
    for (int i = 0; it != elementsResources.end(); it++, i++) {
        Element element(i, it->first, it->second);
        m_elements[i] = std::move(element);
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
    return std::move(m_elements[id]);
}

std::vector<int> CGameBrain::GetNewElement(int id1, int id2) {
    for (int i = 0; i < m_combinations.size(); i++) {
        if ((m_combinations[i][0] == id1 || m_combinations[i][0] == id2) && (m_combinations[i][1] == id1 || m_combinations[i][1] == id2)) {
            std::vector<int> newElements(m_combinations[i].begin() + 2, m_combinations[i].end());
            return newElements;
        }
    }
    return std::vector<int>();
}

void CGameBrain::AddNewOpenElement(std::vector<int> idElements) {
    for (int i = 0; i < idElements.size(); i++) {
        for (int j = 0; j < m_openedElements.size(); j++) {
            if (m_openedElements[j] == idElements[i]) {
                return;
            }
        }
        m_openedElements.push_back(idElements[i]);
    }
}