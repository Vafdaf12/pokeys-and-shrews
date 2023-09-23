#include "TeleportTrapGraphic.h"

#include "core/Resources.h"
#include "entity/TeleportTrap.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include "util/util.h"

TeleportTrapGraphic::TeleportTrapGraphic(const TeleportTrap* trap)
    : m_texture(Resources::getTexture("res/teleport_trap.png")), m_pTrap(trap) {
}
void TeleportTrapGraphic::draw() {

    float scale = TileGraphic::TILE_WIDTH / float(m_texture.width);
    Color c = WHITE;
    if (!m_pTrap->m_cooldown.isComplete()) {
        c.a = 150;
    }
    DrawTextureEx(m_texture, m_position, 0, scale, c);
    if (!m_pTrap->m_cooldown.isComplete()) {
        util::drawProgress(
            getBoundingBox(), 4, 4, m_pTrap->m_cooldown.getProgress(), ORANGE);
    }
}
Rectangle TeleportTrapGraphic::getBoundingBox() const {
    return {m_position.x,
        m_position.y,
        TileGraphic::TILE_WIDTH,
        TileGraphic::TILE_WIDTH};
}