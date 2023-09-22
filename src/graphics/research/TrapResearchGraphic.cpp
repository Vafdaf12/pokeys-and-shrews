#include "TrapResearchGraphic.h"

#include "research/TrapResearch.h"

TrapResearchGraphic::TrapResearchGraphic(const TrapResearch* trap)
    : m_graphic(trap->createGraphic()) {}

void TrapResearchGraphic::draw() {
    m_graphic->setPosition(m_position);
    m_graphic->draw();
}
Rectangle TrapResearchGraphic::getBoundingBox() const {
    m_graphic->setPosition(m_position);
    return m_graphic->getBoundingBox();
}
