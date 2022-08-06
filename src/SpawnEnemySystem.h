#pragma once

struct SpawnBasicEnemySystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "SpawnBasicEnemySystem"
    };
    using query = std::tuple
        <
        xecs::query::must<BasicEnemyTag>,
        xecs::query::none_of<Position>
        >;

    static constexpr float spawnInterval = 2.0f;

    __inline void OnGameStart()
    {
        m_enemyPrefab = CreatePrefab< Position, Velocity, Scale,GridCells, BasicEnemyTag, Color, Rotate>(
            [&](Position& position, Velocity& velocity, Scale& _scale, GridCells& cells, Color& _color, Rotate& _rotate) noexcept
                {
                   
                    _color.m_value = { 1.0f,0.0f,0.0f };
                    _scale.m_value = 15;
                });
    }
    __inline void operator()(Timer& _timer) noexcept
    {
        if (_timer.m_value <= 0.0f)
        {
            _timer.m_value = spawnInterval;
            
            //spawn basic enemies
            switch (std::rand() % 4)
            {
            case 0:
                SpawnHorizontalDownLineOfEnemy(std::rand() % 10 + 5);
                break;
            case 1:
                SpawnHorizontalUpLineOfEnemy(std::rand() % 3 + 5);
                break;
            case 2:
                SpawnVerticalRightLineOfEnemy(std::rand() % 3 + 5);
                break;
            case 3:
                SpawnVerticalLeftLineOfEnemy(std::rand() % 3 + 5);
                break;
            }
        }
    }
    __inline void SpawnVerticalLeftLineOfEnemy(const int _numOfEnemies)
    {
        for (size_t i = 0; i < _numOfEnemies; ++i)
        {
            CreatePrefabInstance(1, m_enemyPrefab,
                [&](Position& _pos, Velocity& _vel, GridCells& _cell, Rotate& _rotate, const Scale& _scale) noexcept
                {

                    _vel.m_value.m_X = -5.0f;
                    _pos.m_value = { static_cast<float>(renderingInfo.m_width)  , i * (renderingInfo.m_height / _numOfEnemies) + _scale.m_value.m_Y };
                    _rotate.m_value = 90.0f;
                    _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                });
        }
    }
    __inline void SpawnVerticalRightLineOfEnemy(const int _numOfEnemies)
    {
        for (size_t i = 0; i < _numOfEnemies; ++i)
        {
            CreatePrefabInstance(1, m_enemyPrefab,
                [&](Position& _pos, Velocity& _vel, GridCells& _cell, Rotate& _rotate, const Scale& _scale) noexcept
                {

                    _vel.m_value.m_X = 5.0f;
                    _pos.m_value = { 0  , i * (renderingInfo.m_height / _numOfEnemies) + _scale.m_value.m_Y };
                    _rotate.m_value = -90.0f;
                    _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                });
        }
    }
    __inline void SpawnHorizontalDownLineOfEnemy(const int _numOfEnemies)
    {
        for (size_t i = 0; i < _numOfEnemies; ++i)
        {
            CreatePrefabInstance(1, m_enemyPrefab,
                [&](Position& _pos, Velocity& _vel, GridCells& _cell, Rotate& _rotate,const Scale& _scale) noexcept
                {

                    _vel.m_value.m_Y = 5.0f;
                    _pos.m_value = { i * (renderingInfo.m_width/ _numOfEnemies) + _scale.m_value.m_X  , 0 };
                    _rotate.m_value = 180.0f;
                    _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                });
        }
    }

    __inline void SpawnHorizontalUpLineOfEnemy(const int _numOfEnemies)
    {
        for (size_t i = 0; i < _numOfEnemies; ++i)
        {
            CreatePrefabInstance(1, m_enemyPrefab,
                [&](Position& _pos, Velocity& _vel, GridCells& _cell, Rotate& _rotate, const Scale& _scale) noexcept
                {

                    _vel.m_value.m_Y = -5.0f;
                    _pos.m_value = { i * (renderingInfo.m_width / _numOfEnemies) + _scale.m_value.m_X  , static_cast<float>(renderingInfo.m_height) };
                    _rotate.m_value = 0.0f;
                    _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                });
        }
    }
    xecs::prefab::guid m_enemyPrefab{};
};



struct SpawnShootingEnemySystem : xecs::system::instance
{

    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "SpawnShootingEnemySystem"
    };
    using query = std::tuple
        <
        xecs::query::must<ShootingEnemyTag>,
        xecs::query::none_of<Position>
        >;

    static constexpr float spawnInterval = 10.0f;


    __inline void OnGameStart()
    {
        m_enemyPrefab = CreatePrefab< Position, Velocity, Scale, GridCells, BasicEnemyTag, Color, Rotate,ShootingComponent, ShootingEnemyTag,Timer>(
            [&](Position& position, Velocity& velocity, Scale& _scale, GridCells& cells, Color& _color, Rotate& _rotate, ShootingComponent& _shootingComponent,Timer& _timer) noexcept
            {
                _shootingComponent.m_canShoot = false;
                _timer.m_value = 0.2f;
                _color.m_value = { 1.0f,0.0f,1.0f };
                _scale.m_value = 15;
            });
    }
    __inline void operator()(Timer& _timer) noexcept
    {
        if (_timer.m_value <= 0.0f)
        {
            _timer.m_value = spawnInterval;

            //spawn basic enemies
            
            SpawnHorizontalDownLineOfEnemy(std::rand() % 8 + 7);

            
        }
    }
   
    __inline void SpawnHorizontalDownLineOfEnemy(const int _numOfEnemies)
    {
        for (size_t i = 0; i < _numOfEnemies; ++i)
        {
            CreatePrefabInstance(1, m_enemyPrefab,
                [&](Position& _pos, Velocity& _vel, GridCells& _cell, Rotate& _rotate, const Scale& _scale) noexcept
                {

                    _vel.m_value.m_Y = 3.0f;
                    _pos.m_value = { i * (renderingInfo.m_width / _numOfEnemies) + _scale.m_value.m_X  , 0 };
                    _rotate.m_value = 180.0f;
                    _cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
                });
        }
    }
    xecs::prefab::guid m_enemyPrefab{};
};
