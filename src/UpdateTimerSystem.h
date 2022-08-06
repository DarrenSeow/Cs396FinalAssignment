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

struct BulletDestroyOnTimerSystem : xecs::system::instance 
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
struct UpdateShootingEnemySystem : xecs::system::instance
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<UpdateTimerSystem, UpdateTimerSystem::update>
    {
        .m_pName = "UpdateShootingEnemySystem"
    };



    static constexpr float shootInterval = 0.5f;
    using query = std::tuple <xecs::query::must<ShootingEnemyTag>>;

    __inline void OnGameStart()
    {
        m_playerQuery.m_Must.AddFromComponents<PlayerTag>();
        m_bulletPrefab = CreatePrefab<Position, Velocity, Scale, Bullet, GridCells, Color,EnemyBulletTag>([&](Color& _color) noexcept
            {
                _color.m_value = { 1.0f,0.5f,0.0f };
            });
    }



    __inline void operator()(entity& _entity, Timer& _timer, ShootingComponent& _shootingComponent, Position& _position) noexcept
    {
        if (_timer.m_value <= 0.0f)
        {
            _shootingComponent.m_canShoot = false;
            _timer.m_value = shootInterval;
            Foreach(Search(m_playerQuery), [&](const Position& _Position)
                {
                    auto direction = _Position.m_value - _position.m_value;
                    const auto directionSquare = direction.getLengthSquared();
                    CreatePrefabInstance(1, m_bulletPrefab,
                        [&](Position& _pos, Velocity& _vel, Bullet& _bullet, GridCells& _cell, Scale& _scale) noexcept
                        {
                            direction /= std::sqrt(directionSquare);
                            _vel.m_value = direction * 5.0f;
                            _pos.m_value = _position.m_value + _vel.m_value;

                            _bullet.m_shipOwner = _entity;
                            _scale.m_value.m_X = 5.0f;
                            _scale.m_value.m_Y = 8.0f;
                            _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                        });
                });

        }
    }
    xecs::prefab::guid m_bulletPrefab{};
    xecs::query::instance m_playerQuery{};
};




