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
           
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_X > renderingInfo.m_width + _scale.m_value.m_X * 2)
        {
           
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_Y < -_scale.m_value.m_Y * 2)
        {
            DeleteEntity(_entity);
        }
        else if (_position.m_value.m_Y > renderingInfo.m_height + _scale.m_value.m_Y * 2)
        {
           
            DeleteEntity(_entity);
        }
    }
};

struct EnemyCollidedPlayerSystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "EnemyCollidedPlayerSystem"
    };
    xecs::query::instance m_QueryEnemy;
    xecs::query::instance m_QueryPlayer;
    xecs::query::instance m_QueryGamePlay;

    using query = std::tuple
        <
        xecs::query::one_of<EnemyBulletTag,BasicEnemyTag,ShootingEnemyTag>

        >;
    void OnGameStart(void) noexcept
    {
        m_QueryEnemy.AddQueryFromTuple<query>();
        m_QueryPlayer.m_Must.AddFromComponents<PlayerTag>();
        m_QueryGamePlay.m_Must.AddFromComponents<Gameplay>();
    }
    __inline
        void OnUpdate(void) noexcept
    {
        //
        // Update all the bullets
        //
        for (std::int16_t Y = 0; Y < grid::cell_y_count; ++Y)
            for (std::int16_t X = 0; X < grid::cell_x_count; ++X)
            {
                auto pShareFilter = findShareFilter(GridCells{ .m_X = X, .m_Y = Y });
                if (pShareFilter == nullptr) continue;

                Foreach(*pShareFilter, m_QueryEnemy, [&](entity& _entity, const Position& _position,const Scale& _scale) constexpr noexcept
                    {
                        // If I am dead because some other bullet killed me then there is nothing for me to do...
                        if (_entity.isZombie()) return;
                        grid::Search(*this, *pShareFilter, X, Y, m_QueryPlayer, [&](entity& _player, const Position& _pos, const Scale& _playerscale)  constexpr noexcept
                            {
                                if (_player.isZombie()) return false;
                                const auto enemyDist = _scale.m_value.getLengthSquared();
                                const auto playerDist = _playerscale.m_value.getLengthSquared();
                                if ((_pos.m_value - _position.m_value).getLengthSquared() < enemyDist + playerDist)
                                {
                                    DeleteEntity(_entity);
                                    DeleteEntity(_player);
                                    Foreach(Search(m_QueryGamePlay), [&](Gameplay& _gameplay)
                                        {
                                            _gameplay.m_value = false;
                                        });
                                    return true;
                                }

                                return false;
                            });
                    });
            }
    }
};
struct PlayerBulletCollisionSystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "PlayerBulletCollisionSystem"
    };
    xecs::query::instance m_QueryPlayerBullets;
    xecs::query::instance m_QueryEnemy;
    xecs::query::instance m_QueryScore;
    using query = std::tuple
        <
        xecs::query::must<Bullet, PlayerBulletTag>
        >;
    void OnGameStart(void) noexcept
    {
        m_QueryPlayerBullets.AddQueryFromTuple<query>();
        m_QueryEnemy.m_OneOf.AddFromComponents<BasicEnemyTag,ShootingEnemyTag>();
        m_QueryScore.m_Must.AddFromComponents<Score>();
    }
    __inline
        void OnUpdate(void) noexcept
    {
        //
        // Update all the bullets
        //
        for (std::int16_t Y = 0; Y < grid::cell_y_count; ++Y)
            for (std::int16_t X = 0; X < grid::cell_x_count; ++X)
            {
                auto pShareFilter = findShareFilter(GridCells{ .m_X = X, .m_Y = Y });
                if (pShareFilter == nullptr) continue;

                Foreach(*pShareFilter, m_QueryPlayerBullets, [&](entity& _entity, const Position& _position,const Bullet& _bullet,const Scale& _scale) constexpr noexcept
                    {
                        // If I am dead because some other bullet killed me then there is nothing for me to do...
                        if (_entity.isZombie()) return;

                        grid::Search(*this, *pShareFilter, X, Y, m_QueryEnemy, [&](entity& _enemy, const Position& _pos,const Scale& _enemyScale)  constexpr noexcept
                            {
                                if (_enemy.isZombie()) return false;
                               
                                const auto enemyDist = _scale.m_value.getLengthSquared();
                                const auto playerDist = _enemyScale.m_value.getLengthSquared();
                                if ((_pos.m_value - _position.m_value).getLengthSquared() < enemyDist + playerDist)
                                {
                                    DeleteEntity(_entity);
                                    DeleteEntity(_enemy);
                                    Foreach(Search(m_QueryScore), [&](Score& _score)
                                        {
                                            std::cout << _score.m_value << std::endl;
                                            _score.m_value += 100;
                                        });
                                    return true;
                                }

                                return false;
                            });
                    });
            }
    }
};
