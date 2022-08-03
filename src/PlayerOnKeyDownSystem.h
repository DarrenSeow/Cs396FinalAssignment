#pragma once

struct PlayerOnKeyDownSystem : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnKeyboardTriggeredEvent>
	{
		.m_pName = "PlayerOnKeyDownSystem"
	};

	void OnGameStart() noexcept
	{
		m_playerQuery.m_Must.AddFromComponents<PlayerTag>();
		
	}

	void OnEvent(const unsigned char _key) noexcept
	{
		Foreach(Search(m_playerQuery), [&](Velocity& _velocity,Timer* _timer)
			{
				switch(_key)
				{
					case 'w':
						_velocity.m_value.m_Y = -1;
						break;
					case 's':
						_velocity.m_value.m_Y = 1;
						break;
					case 'a':
						_velocity.m_value.m_X = -1;
						break;
					case 'd':
						_velocity.m_value.m_X = 1;
						break;
					case ' ':
						if (_timer->m_value <= 0)
							std::cout << "help" << std::endl;
						break;
				}
				
			});

	}


	xecs::query::instance m_playerQuery{};
};