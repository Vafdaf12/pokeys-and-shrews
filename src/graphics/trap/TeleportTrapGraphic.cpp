#include "TeleportTrapGraphic.h"

#include "core/Resources.h"
#include "entity/TeleportTrap.h"
#include "graphics/TileGraphic.h"

TeleportTrapGraphic::TeleportTrapGraphic(const TeleportTrap* trap)
    : m_texture(Resources::getTexture("res/teleport_trap.png")), m_pTrap(trap) {
}
void TeleportTrapGraphic::draw() {

    float scale = TileGraphic::TILE_WIDTH / float(m_texture.width);
    DrawTextureEx(m_texture, m_position, 0, scale, WHITE);
}