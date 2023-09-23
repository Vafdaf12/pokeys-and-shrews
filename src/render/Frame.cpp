#include "Frame.h"
#include "core/Resources.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include "render/Drawable.h"
#include "util/util.h"
#include <stdio.h>
using namespace gfx;

Frame::Frame(std::unique_ptr<Drawable> internal, int padding)
    : DrawableDecorator(std::move(internal)),
      _texture(Resources::getTexture("res/frame_small.png")),
      _padding(padding) {}

void Frame::draw() {
    Rect r = getBoundingBox();
    printf("%p, %f, %f, %f, %f\n", this, r.x, r.y, r.width, r.height);
    float w = TileGraphic::TILE_WIDTH;
    float tw = 8;

    Rect tl = {r.x, r.y, w, w};
    Rect tr = {r.x + r.width - w, r.y, w, w};
    Rect bl = {r.x, r.y + r.height - w, w, w};
    Rect br = {r.x + r.width - w, r.y + r.height - w, w, w};

    DrawTexturePro(_texture, {0, 0, tw, tw}, tl, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {tw, 0, tw, tw}, tr, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {0, tw, tw, tw}, bl, {0, 0}, 0, WHITE);
    DrawTexturePro(_texture, {tw, tw, tw, tw}, br, {0, 0}, 0, WHITE);
    getInternal()->draw();
}
Rect Frame::getBoundingBox() const {
    return util::inset(_pInternal->getBoundingBox(), _padding);
}