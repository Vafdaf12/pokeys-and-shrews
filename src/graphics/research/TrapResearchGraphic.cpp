#include "TrapResearchGraphic.h"

#include "raylib.h"
#include "research/TrapResearch.h"
#include "util/util.h"

TrapResearchGraphic::TrapResearchGraphic(const TrapResearch* trap)
    : m_graphic(trap->m_entity->createGraphic()), m_research(trap) {}

void TrapResearchGraphic::draw() {
    m_graphic->setPosition(m_position);
    m_graphic->draw();
    float fac = m_research->getProgress();
    util::drawProgress(m_graphic->getBoundingBox(), 4, 4, fac, SKYBLUE);
}
Rectangle TrapResearchGraphic::getBoundingBox() const {
    m_graphic->setPosition(m_position);
    return m_graphic->getBoundingBox();
}
