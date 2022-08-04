#pragma once


struct Rotate
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "RotateComponent"
    };
    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        TextFile.Field("Value", m_value).clear();
        return{};
    }

    float m_value;
};

property_begin(Rotate)
{
    property_var(m_value)
}
property_end()