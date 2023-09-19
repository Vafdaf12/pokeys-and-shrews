#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/Graphic.h"

#include <vector>

class LairExplorer;

class LairExplorerGraphic : public Graphic {
public:
    LairExplorerGraphic(TargetType target, LairExplorer* explorer);

    void draw() const override;
    void update(uint32_t dt) override;

private:
    SDL_Color m_color;
    SDL_Point m_cur;
    LairExplorer* m_pExplorer;
    std::vector<SDL_Point> m_points;
};