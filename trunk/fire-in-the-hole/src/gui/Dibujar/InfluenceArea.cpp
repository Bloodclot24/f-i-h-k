#include "gui/Dibujar/InfluenceArea.h"

InfluenceArea::InfluenceArea(const InfluenceRectangle& influenceRectangle) {
	m_area.push_back(influenceRectangle);
}

InfluenceArea::InfluenceArea(const std::vector<InfluenceRectangle>& influenceRectangles) :
	m_area(influenceRectangles) {
}

InfluenceArea::InfluenceArea(std::vector<InfluenceArea>& influenceArea) {
	//Merge de todas las areas.
	for (std::vector<InfluenceArea>::iterator it = influenceArea.begin(); it != influenceArea.end(); ++it)
		for (std::vector<InfluenceRectangle>::iterator it2 = (*it).m_area.begin(); it2 != (*it).m_area.end(); ++it2)
			m_area.push_back((*it2));
}

InfluenceArea::~InfluenceArea() {

}

bool InfluenceArea::touch(int x, int y) {
	for (std::vector<InfluenceRectangle>::iterator it = m_area.begin(); it != m_area.end(); ++it)
		if ((*it).touch(x, y))
			return true;
	return false;
}

bool InfluenceArea::touch(InfluenceArea& influenceArea) {
	for (std::vector<InfluenceRectangle>::iterator it = m_area.begin(); it != m_area.end(); ++it)
		for (std::vector<InfluenceRectangle>::iterator it2 = influenceArea.m_area.begin(); it2 != influenceArea.m_area.end(); ++it2)
			if ((*it).touch((*it2)))
				return true;
	return false;
}

void InfluenceArea::addRectangle(InfluenceRectangle& influenceRectangle) {
	m_area.push_back(influenceRectangle);
}
