#include "TrapResearch.h"
#include "graphics/research/TrapResearchGraphic.h"

void TrapResearch::complete() {
    if (m_pEngine) {
        m_pEngine->trapUnlocked(this, m_entity);
    }
}
gfx::Graphic* TrapResearch::createGraphic() const {
    return new TrapResearchGraphic(this);
}