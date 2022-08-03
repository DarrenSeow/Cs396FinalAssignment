#pragma once


static struct Game
{
    using game_mgr_uptr = std::unique_ptr<xecs::game_mgr::instance>;

    RenderingInfo   m_renderingInfo;
    game_mgr_uptr   m_GameMgr = nullptr;
    int             m_MouseX{};
    int             m_MouseY{};
    bool            m_MouseLeft{};
    bool            m_MouseRight{};
    Keys            m_Keys{};
    int             m_DisplayGridInfo{ 0 };


    void Initialize() noexcept
    {
        RenderingSystem::renderingInfo = &m_renderingInfo;
        InputSystem::m_keys = &m_Keys;
        m_GameMgr->RegisterComponents<Position, Scale, Velocity,Timer, GridCells,PlayerTag>();

        m_GameMgr->RegisterGlobalEvents<OnKeyboardTriggeredEvent,OnKeyboardTriggerUpEvent>();
        
        m_GameMgr->RegisterSystems<
            //InputSystem,
            PlayerOnKeyDownSystem,
            PlayerOnKeyUpSystem,
            UpdateMovementSystem,
            RenderingSystem,
            RenderingGridSystem, 
            RenderingShipSystem>();
       
    }
    void InitializeGame() noexcept
    {
        m_GameMgr->getOrCreateArchetype< Position, Velocity, Scale,Timer,GridCells,PlayerTag>()
            .CreateEntities(1, [&](Position& position, Velocity& velocity, Scale& _scale, Timer& timer, GridCells& cells, PlayerTag _player) noexcept
                {
                    position.m_value = xcore::vector2{ static_cast<float>(std::rand() % m_renderingInfo.m_width)
                                                         , static_cast<float>(std::rand() % m_renderingInfo.m_height)
                    };

                    cells = grid::ComputeGridCellFromWorldPosition(position.m_value);

                    velocity.m_value = 0;

                    _scale.m_value = 15;
                    timer.m_value = 0.5f;
                    _player.m_canShoot = true;
                });
        m_GameMgr->getOrCreateArchetype< Position, Velocity,Scale, Timer, GridCells>()
            .CreateEntities(1, [&](Position& position, Velocity& velocity, Scale& _scale,Timer& timer, GridCells& cells) noexcept
                {
                    position.m_value = xcore::vector2{ static_cast<float>(std::rand() % m_renderingInfo.m_width)
                                                         , static_cast<float>(std::rand() % m_renderingInfo.m_height)
                    };

                    cells = grid::ComputeGridCellFromWorldPosition(position.m_value);

                    velocity.m_value = 0;
                    _scale.m_value = 3;
                    timer.m_value = std::rand() / static_cast<float>(RAND_MAX) * 8;
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