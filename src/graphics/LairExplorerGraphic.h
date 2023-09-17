#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/Graphic.h"

#include <vector>

class LairExplorer;

class LairExplorerGraphic : public Graphic {
public:
    LairExplorerGraphic(LairExplorer* explorer);

    void draw(TargetType target) const override;
    void update(uint32_t dt);

private:
    SDL_Color m_color;
    SDL_Point m_cur;
    SDL_Point m_dest;
    LairExplorer* m_pExplorer;
    std::vector<SDL_Point> m_points;
};