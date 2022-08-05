#pragma once


struct DestroyObjectOutOfScreenSystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "DestroyObjectOutOfScreenSystem"
    };

    __inline void operator()(entity& _entity,Position& _position, const Scale& _scale) noexcept
    {
        if (_position.m_value.m_X < -_scale.m_value.m_X*2)
        {
            std::cout << " Out Of Screen Left" << std::endl;
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_X > renderingInfo.m_width + _scale.m_value.m_X * 2)
        {
            std::cout << " Out Of Screen Right" << std::endl;
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_Y < -_scale.m_value.m_Y * 2)
        {
            std::cout << " Out Of Screen Up" << std::endl;
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_Y > renderingInfo.m_height + _scale.m_value.m_Y * 2)
        {
            std::cout << " Out Of Screen Down" << std::endl;
            DeleteEntity(_entity);
        }
    }
};