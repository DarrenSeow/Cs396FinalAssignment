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