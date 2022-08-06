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

		m_bulletPrefab = CreatePrefab<Position, Velocity,Scale, Bullet, GridCells,Color,PlayerBulletTag>([&](Color& _color) noexcept
			{
				_color.m_value = 1.0f;
			});
	}


	static constexpr auto speed = 5;
	void OnEvent(const unsigned char _key) noexcept
	{
		Foreach(Search(m_playerQuery), [&](const entity& _entity,Velocity& _velocity,ShootingComponent& _shootingComp,Position& _position)
			{
				switch(_key)
				{
					case 'w':
						_velocity.m_value.m_Y = -speed;
						break;
					case 's':
						_velocity.m_value.m_Y = speed;
						break;
					case 'a':
						_velocity.m_value.m_X = -speed;
						break;
					case 'd':
						_velocity.m_value.m_X = speed;
						break;
					case ' ':
						if (_shootingComp.m_canShoot)
						{
							_shootingComp.m_canShoot = false;

							CreatePrefabInstance(1, m_bulletPrefab, 
								[&](Position& _pos, Velocity& _vel, Bullet& _bullet, GridCells& _cell,Scale& _scale) noexcept
								{
									
									_vel.m_value.m_Y =  -10.0f;
									_pos.m_value = _position.m_value + _vel.m_value;

									_bullet.m_shipOwner = _entity;
									_scale.m_value.m_X = 5.0f;
									_scale.m_value.m_Y = 8.0f;
									_cell = grid::ComputeGridCellFromWorldPosition(_pos.m_value);
								});
						}
						break;
				}
				
			});

	}
	xecs::prefab::guid m_bulletPrefab{};
	xecs::query::instance m_playerQuery{};
};