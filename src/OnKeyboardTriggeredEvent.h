#pragma once

struct OnKeyboardTriggeredEvent : xecs::event::instance<const unsigned char>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "OnKeyboardTriggeredEvent"
	};
};