#pragma once

struct UpdateMovementSystem : xecs::system::instance
{
    
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "UpdateMovementSystem"
    };

    __inline void operator()(Position& _position, const Velocity& _velocity, GridCells& _gridcell) noexcept
    {
       // std::cout << _velocity.m_value.m_X  << " " << _velocity.m_value.m_Y << std::endl;
        _position.m_value += _velocity.m_value;
        _gridcell = grid::ComputeGridCellFromWorldPosition(_position.m_value);
    }
};

struct PlayerMovementSystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "PlayerMovementSystem"
    };
    using query = std::tuple
        <
        xecs::query::must<PlayerTag>
        >;
    __inline void operator()(Position& _position, Velocity& _velocity, GridCells& _gridcell,Scale& _scale) noexcept
    {
        // std::cout << _velocity.m_value.m_X  << " " << _velocity.m_value.m_Y << std::endl;
        if (_position.m_value.m_X < 0.0f)
        {
            _position.m_value.m_X = 0.0f;
        }
        else if (_position.m_value.m_X > static_cast<float>(renderingInfo.m_width))
        {
            _position.m_value.m_X = static_cast<float>(renderingInfo.m_width);
        }
        else if (_position.m_value.m_Y < -_scale.m_value.m_Y)
        {
            _position.m_value.m_Y = 0.0f;
        }
        else if (_position.m_value.m_Y > static_cast<float>(renderingInfo.m_height))
        {
            _position.m_value.m_Y = static_cast<float>(renderingInfo.m_height);
        }
    }
};


