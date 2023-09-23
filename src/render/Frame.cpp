#include "Frame.h"
#include "core/Resources.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include "render/Drawable.h"
#include "util/util.h"
using namespace gfx;

Frame::Frame(std::unique_ptr<Drawable> internal, int padding)
    : DrawableDecorator(std::move(internal)),
      _texture(Resources::getTexture("res/frame.png")), _padding(padding) {}

void Frame::draw() {
    Rect r = getBoundingBox();
    float w = TileGraphic::TILE_WIDTH;

    Rect tl = {r.x, r.y, w, w};
    Rect tr = {r.x + r.width - w, r.y, w, w};
    Rect bl = {r.x, r.y + r.height - w, w, w};
    Rect br = {r.x + r.width - w, r.y + r.height - w, w, w};

    DrawTexturePro(_texture, {0, 0, 16, 16}, tl, {tl.x, tl.y}, 0, WHITE);
    DrawTexturePro(_texture, {16, 0, 16, 16}, tr, {tr.x, tr.y}, 0, WHITE);
    DrawTexturePro(_texture, {0, 16, 16, 16}, bl, {bl.x, tl.y}, 0, WHITE);
    DrawTexturePro(_texture, {16, 16, 16, 16}, br, {br.x, tr.y}, 0, WHITE);
}
Rect Frame::getBoundingBox() const {
    return util::inset(_pInternal->getBoundingBox(), _padding);
}