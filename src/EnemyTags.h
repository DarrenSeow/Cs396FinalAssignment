#pragma once
struct BasicEnemyTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "BasicEnemyTag"
    };
};


struct ShootingEnemyTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "ShootingEnemyTag"
    };
};