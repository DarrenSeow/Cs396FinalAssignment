#pragma once
struct Scale
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Scale"
    };

    xcore::vector2 m_value;
};

property_begin(Scale)
{
    property_var(m_value)
}
property_end()