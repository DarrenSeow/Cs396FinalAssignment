#pragma once

struct InputSystem : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "InputSystem"
	};
	using query = std::tuple
		<
		//xecs::query::one_of<entity>,
		xecs::query::must<PlayerTag>
		>;


	void operator()(Velocity& _velocity) noexcept
	{
		
		if (m_keys->getKey('w'))
		{	
			_velocity.m_value.m_Y = -1;
		}
		else if (m_keys->getKey('s'))
		{
			_velocity.m_value.m_Y = 1;
		}
		else
		{
			_velocity.m_value.m_Y = 0;
		}
		if (m_keys->getKey('d'))
		{
			_velocity.m_value.m_X = 1;
		}
		else if (m_keys->getKey('a'))
		{
			_velocity.m_value.m_X = -1;
		}
		else
		{
			_velocity.m_value.m_X = 0;
		}


	}

	inline static Keys* m_keys = nullptr;	
};