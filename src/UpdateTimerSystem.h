#pragma once
struct UpdateTimerSystem : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "update_timer"
    };

    using update = xecs::event::instance<>;

    using events = std::tuple
        < update
        >;


    __inline constexpr
        void operator()(timer& Timer) const noexcept
    {
        Timer.m_Value -= 0.01f;

        SendEventFrom<update>(this);
        //if (Timer.m_Value <= 0)
        //{
        //    //void)AddOrRemoveComponents<std::tuple<>, std::tuple<timer>>(Entity);
        //}
    }
};

struct PlayerShootingTimerSystem : xecs::system::instance
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<UpdateTimerSystem, UpdateTimerSystem::update>
    {
        .m_pName = "RenderingShipSystem"
    };

    using query = std::tuple
        <
        xecs::query::must<PlayerTag>
        >;

    constexpr auto shootingDelayTimer = 2.0f;
    void operator()(const Timer& _timer) const noexcept
    {
       if(_timer <= 0.0f)
       {
           _timer = shootingDelayTimer;
       }
    }
};