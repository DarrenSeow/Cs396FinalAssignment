#pragma once

struct Color
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "BasicEnemyTag"
    };
    xcore::vector3 m_value;
};