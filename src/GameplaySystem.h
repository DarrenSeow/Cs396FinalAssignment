#pragma once

struct GameplaySystem : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "GameplaySystem"
    };

    using query = std::tuple
        <
        xecs::query::must<Gameplay>
        >;

    __inline
        void operator()(const Gameplay& _gameplay,Score& _score) noexcept
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        if(!_gameplay.m_value)
            GlutPrint(renderingInfo.m_width/2 - 100, renderingInfo.m_width /2 - 100, "GameOver, Your Score: %d", _score.m_value);

    }
};
