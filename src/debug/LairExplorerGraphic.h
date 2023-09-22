#pragma once
#include "core/Graphic.h"
#include "raylib.h"

#include <vector>

class LairExplorer;

class LairExplorerGraphic : public Graphic {
public:
    LairExplorerGraphic(LairExplorer* explorer);

    void draw() override;
    void update(float dt) override;

    Rectangle getBoundingBox() const override;

private:
    Color m_color;
    Vector2 m_cur;
    LairExplorer* m_pExplorer;
    std::vector<Vector2> m_points;
};