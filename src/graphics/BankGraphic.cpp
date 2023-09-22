
#include "BankGraphic.h"

#include "core/Resources.h"
#include "entity/Bank.h"
#include "graphics/TileGraphic.h"

BankGraphic::BankGraphic(const Bank* trap)
    : m_texture(Resources::getTexture("res/bank.png")), m_pTrap(trap) {}
void BankGraphic::draw() {

    float scale = TileGraphic::TILE_WIDTH / float(m_texture.width);
    DrawTextureEx(m_texture, m_position, 0, scale, WHITE);
}
Rectangle BankGraphic::getBoundingBox() const {
    return {m_position.x,
        m_position.y,
        TileGraphic::TILE_WIDTH,
        TileGraphic::TILE_WIDTH};
}