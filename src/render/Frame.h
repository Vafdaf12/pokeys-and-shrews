#pragma once
#include "Drawable.h"
#include "render/Drawable.h"

namespace gfx {
class Frame : public DrawableDecorator {
public:
    enum ZOrder {
        Bg,
        Fg,

    };

    Frame(Texture2D tex,
        std::unique_ptr<Drawable> internal,
        float padding,
        float size,
        ZOrder z = Bg);

    virtual void draw() override;
    virtual Rect getBoundingBox() const override;

private:
    Tex2D _texture;
    float _padding;
    float _size;
    ZOrder _order;
};

} // namespace gfx