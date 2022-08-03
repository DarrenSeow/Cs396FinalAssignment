#pragma once
struct OnKeyboardTriggerUpEvent : xecs::event::instance<const unsigned char>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "OnKeyboardTriggerUpEvent"
	};
};