#pragma once
struct ShootingComponent
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "ShootingComponent"
    };

    bool m_canShoot;
};

