#pragma once



static struct Game
{
    using game_mgr_uptr = std::unique_ptr<xecs::game_mgr::instance>;

  //  RenderingInfo   m_renderingInfo;
    game_mgr_uptr   m_GameMgr = nullptr;
    int             m_MouseX{};
    int             m_MouseY{};
    bool            m_MouseLeft{};
    bool            m_MouseRight{};
    Keys            m_Keys{};
    int             m_DisplayGridInfo{ 0 };

    void Initialize() noexcept
    {
       

        m_GameMgr->RegisterComponents<
            Position, 
            Scale, 
            Velocity,
            Timer, 
            GridCells,
            PlayerTag,
            ShootingComponent,
            Bullet,
            BasicEnemyTag,
            ShootingEnemyTag,
            EnemyBulletTag,
            PlayerBulletTag,
            Color,
            Rotate,
            Score,
            Gameplay>();

        m_GameMgr->RegisterGlobalEvents<
            OnKeyboardTriggeredEvent,
            OnKeyboardTriggerUpEvent>();
        
        m_GameMgr->RegisterSystems<
            PlayerOnKeyDownSystem,
            PlayerOnKeyUpSystem,
            UpdateMovementSystem,  
            PlayerMovementSystem,
            UpdateTimerSystem,
            ShootingTimerSystem,
            UpdateShootingEnemySystem,
            BulletDestroyOnTimerSystem,
            
            DestroyObjectOutOfScreenSystem,
            EnemyCollidedPlayerSystem,
            PlayerBulletCollisionSystem,
            SpawnShootingEnemySystem,
            SpawnBasicEnemySystem,
            RenderingSystem,
            RenderingShipSystem,
            RenderBulletSystem,
            ScoreSystem,
            GameplaySystem
        >();
    }
    void InitializeGame() noexcept
    {
        m_GameMgr->getOrCreateArchetype< Position, Velocity, Scale,Timer,GridCells,PlayerTag,ShootingComponent,Color,Rotate>()
            .CreateEntities(1, [&](Position& position, Velocity& velocity, Scale& _scale, Timer& timer, GridCells& cells, ShootingComponent& _shootingComp,Color& _color,Rotate& _rotate) noexcept
                {
                    position.m_value = xcore::vector2{ static_cast<float>(renderingInfo.m_width) /2.0f
                                                         , static_cast<float>(renderingInfo.m_height)/2.0f
                    };

                    cells = grid::ComputeGridCellFromWorldPosition(position.m_value);

                    velocity.m_value = 0;
                    _color.m_value = { 1.0f,1.0f,0.0f };
                    _scale.m_value = 15;
                    _rotate.m_value = 0;
                    timer.m_value = 2.0f;
                    _shootingComp.m_canShoot = true;

                });

        //basic enemy spawner
        m_GameMgr->getOrCreateArchetype<BasicEnemyTag, Timer>()
            .CreateEntities(1, [&](Timer& _timer)
                {
                    _timer.m_value = 2.0f;
                });


        //shooting enemy spawner
        m_GameMgr->getOrCreateArchetype<ShootingEnemyTag, Timer>()
            .CreateEntities(1, [&](Timer& _timer)
                {
                    _timer.m_value = 5.0f;
                });
        m_GameMgr->getOrCreateArchetype<Score, Gameplay>().CreateEntities(1, [&](Score& _score, Gameplay& _playerAlive)
        {
            _score.m_value = 0;
            _playerAlive.m_value = true;
        });
        
    }
    void KeyboardDownFunction(unsigned char _key, int _mouseX, int _mouseY) noexcept
    {
        m_Keys.setKeyState(_key, true);
        m_MouseX = _mouseX;
        m_MouseY = _mouseY;
        m_GameMgr->SendGlobalEvent< OnKeyboardTriggeredEvent>(_key);
    }

    void KeyboardUpFunction(unsigned char _key, int _mouseX, int _mouseY) noexcept
    {
        m_Keys.setKeyState(_key, false);
        m_MouseX = _mouseX;
        m_MouseY = _mouseY;
        m_GameMgr->SendGlobalEvent< OnKeyboardTriggerUpEvent>(_key);
    }
    
    void MouseFunction(int _button, int _state, int _mouseX, int _mouseY) noexcept
    {
        m_MouseX = _mouseX;
        m_MouseY = _mouseY;

        if (_button == GLUT_LEFT_BUTTON) s_Game.m_MouseLeft = (_state == GLUT_DOWN);
        else if (_button == GLUT_RIGHT_BUTTON) s_Game.m_MouseRight = (_state == GLUT_DOWN);
    }
} s_Game;