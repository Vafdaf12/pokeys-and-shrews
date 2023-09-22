#include "LabelResearch.h"
#include "core/Engine.h"
#include "ui/Label.h"

#include "raylib.h"

void LabelResearch::complete() {
    if (m_pEngine) m_pEngine->researchCompleted(this, this);
}
void LabelResearch::cancel() {
    if (m_pEngine) m_pEngine->researchCancelled(this, this);
}
Graphic* LabelResearch::createGraphic() const {
    return new ui::Label(GetFontDefault(), m_text);
}