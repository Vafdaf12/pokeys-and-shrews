#pragma once

#include "core/GameObject.h"
#include "render/Drawable.h"
#include "research/ResearchTask.h"
#include "ui/Button.h"

#include <map>
#include <set>
#include <utility>

class ResearchTask;

class ResearchManager : public gfx::Graphic, public GameObject {
public:
    ResearchManager(Engine* engine) : GameObject(engine) {}

    void draw() override;
    void update(float dt) override;

    void addResearch(ResearchTask* task);
    bool removeResearch(const ResearchTask* task);

    gfx::Rect getBoundingBox() const override;

private:
    static constexpr gfx::Vec2 OFFSET = {20, 165};
    static constexpr gfx::Vec2 WIDTH = {75, 75};

    void onClick(ResearchTask* task);
    void layout();

    std::set<const ResearchTask*> m_enqueued;
    std::map<const ResearchTask*, std::unique_ptr<gfx::DrawableDecorator>>
        m_research;
};