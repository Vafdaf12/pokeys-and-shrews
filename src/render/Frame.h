#pragma once
#include "Drawable.h"
#include "render/Drawable.h"

namespace gfx {
class Frame : public DrawableDecorator {
public:
    Frame(std::unique_ptr<Drawable> internal, int padding);

    virtual void draw() override;
    virtual Rect getBoundingBox() const override;

private:
    Tex2D _texture;
    int _padding;
};

} // namespace gfx