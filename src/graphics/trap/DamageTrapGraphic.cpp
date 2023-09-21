#include "DamageTrapGraphic.h"

#include "core/Resources.h"
#include "entity/DamageTrap.h"
#include "graphics/TileGraphic.h"

DamageTrapGraphic::DamageTrapGraphic(const DamageTrap* trap)
    : m_texture(Resources::getTexture("res/damage_trap.png")), m_pTrap(trap) {}
void DamageTrapGraphic::draw() {

    float scale = TileGraphic::TILE_WIDTH / float(m_texture.width);
    DrawTextureEx(m_texture, m_position, 0, scale, WHITE);
}