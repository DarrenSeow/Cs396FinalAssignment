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

   using query = std::tuple
       <
       xecs::query::must<Timer>
       >;

    __inline void OnGameStart() noexcept
    {
        m_timerQuery.AddQueryFromTuple<query>();
    }
    __inline void OnUpdate() noexcept
    {
        Foreach(Search(m_timerQuery),
            [&](Timer& _timer)
            {
                if (_timer.m_value > 0.0)
                    _timer.m_value -= 0.01f;
                else
                    _timer.m_value = 0.0f;
            });

        SendEventFrom<update>(this);
    }


    xecs::query::instance m_timerQuery{};
};

struct ShootingTimerSystem : xecs::system::instance
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<UpdateTimerSystem, UpdateTimerSystem::update>
    {
        .m_pName = "ShootingTimerSystem"
    };

    //using query = std::tuple
    //    <
    //    xecs::query::must<PlayerTag>
    //    >;

    static constexpr auto shootingDelayTimer = 0.2f;

    void operator()(Timer& _timer, ShootingComponent& _shootingComp) const noexcept
    {
       if(!_shootingComp.m_canShoot && _timer.m_value <= 0.0f)
       {
           _shootingComp.m_canShoot = true;
           _timer.m_value = shootingDelayTimer;
       }
    }
};

struct BulletDestroySystem : xecs::system::instance 
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<UpdateTimerSystem, UpdateTimerSystem::update>
    {
        .m_pName = "BulletDestroySystem"
    };

    using query = std::tuple
        <
        xecs::query::must<Bullet>
        >;

    
    void operator()(entity& _entity,Timer& _timer) const noexcept
    {
        if (_timer.m_value <= 0.0f)
        {           
            DeleteEntity(_entity);
        }
    }
};



