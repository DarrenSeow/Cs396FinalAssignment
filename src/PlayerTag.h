#pragma once
struct PlayerTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "Player"
    };
};
struct PlayerBulletTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "PlayerBulletTag"
    };
};

struct EnemyBulletTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "PlayerBulletTag"
    };
};

struct Score
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Score"
    };
    int m_value;
};
struct Gameplay
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Gameplay"
    };
    bool m_value;
};