#include "TrapResearch.h"
#include "graphics/research/TrapResearchGraphic.h"

void TrapResearch::complete() {
    if (m_pEngine) {
        m_pEngine->researchCompleted(this, this);
        m_pEngine->trapUnlocked(this, m_entity);
    }
}
void TrapResearch::cancel() {
    if (m_pEngine) m_pEngine->researchCancelled(this, this);
}
Graphic* TrapResearch::createGraphic() const {
    return new TrapResearchGraphic(this);
}