#include "Frame.h"
#include "core/Resources.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include "render/Drawable.h"
#include "util/util.h"
#include <stdio.h>
using namespace gfx;

Frame::Frame(Texture2D tex,
    std::unique_ptr<Drawable> internal,
    float padding,
    float size,
    ZOrder order)
    : DrawableDecorator(std::move(internal)), _texture(tex), _padding(padding),
      _size(size), _order(order) {}

void Frame::draw() {
    Rect r = getBoundingBox();
    float w = _size / 2.f;
    float tw = _texture.width / 2.f;

    Rect tl = {r.x, r.y, w, w};
    Rect tr = {r.x + r.width - w, r.y, w, w};
    Rect bl = {r.x, r.y + r.height - w, w, w};
    Rect br = {r.x + r.width - w, r.y + r.height - w, w, w};

    if (_order == Fg) getInternal()->draw();
    DrawTexturePro(_texture, {0, 0, tw, tw}, tl, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {tw, 0, tw, tw}, tr, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {0, tw, tw, tw}, bl, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {tw, tw, tw, tw}, br, {0, 0}, 0, WHITE);
    if (_order == Bg) getInternal()->draw();
}
Rect Frame::getBoundingBox() const {
    return util::inset(_pInternal->getBoundingBox(), _padding);
}
