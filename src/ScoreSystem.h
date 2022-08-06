#pragma once

struct ScoreSystem : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "ScoreSystem"
    };

    using query = std::tuple
        <
        xecs::query::must<Score>
        >;

    __inline
        void operator()(const Score& _score) noexcept
    {
       glColor3f(1.0f, 1.0f, 1.0f);
       GlutPrint(15, 15, "Score: %d", _score.m_value);     
  
    }
};
