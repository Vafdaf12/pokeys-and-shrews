#include "SDL_rect.h"
#include "core/Graphic.h"

#include <vector>

class LairExplorer;

class LairExplorerGraphic : public Graphic {
public:
    LairExplorerGraphic(LairExplorer* explorer) : m_pExplorer(explorer) {}

    void draw(TargetType target) const override;
    void update();

private:
    LairExplorer* m_pExplorer;
    std::vector<SDL_Point> m_points;
};