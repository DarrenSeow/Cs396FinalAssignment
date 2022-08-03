#pragma once

struct PlayerOnKeyUpSystem : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnKeyboardTriggerUpEvent>
	{
		.m_pName = "PlayerOnKeyUpSystem"
	};

	void OnGameStart() noexcept
	{
		m_playerQuery.m_Must.AddFromComponents<PlayerTag>();

	}

	void OnEvent(const unsigned char _key) noexcept
	{
		Foreach(Search(m_playerQuery), [&](Velocity& _velocity)
			{
				//const bool upPressed = _key.m_keys[static_cast<uint8_t>('w')];
				//const bool downPressed = _key.m_keys[static_cast<uint8_t>('s')];

				
				//if (!_key.getKey('w') && _key.getKeyUp('s'))
				//{
				//
				//	_velocity.m_value.m_Y = 0;
				//}
				//
				//const bool leftPressed = _key.m_keys[static_cast<uint8_t>('a')];
				//const bool rightPressed = _key.m_keys[static_cast<uint8_t>('d')];
				//
				//if (!_key.getKey('a') &&  !_key.getKey('d'))
				//{
				//
				//	_velocity.m_value.m_X = 0;
				//}
				switch (_key)
				{
				case 'w':
				case 's':
					_velocity.m_value.m_Y = 0;
					break;
				case 'a':
				case 'd':
					_velocity.m_value.m_X = 0;
				default:
					break;
				}
			});

	}


	xecs::query::instance m_playerQuery{};
};