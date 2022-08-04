#pragma once
struct Bullet
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "Bullet"
    };

    xcore::err Serialize(xecs::serializer::stream& TextFile, bool) noexcept
    {
        return TextFile.Field("ShipOwner", m_shipOwner);
    }

    xecs::component::entity m_shipOwner;
};

property_begin(Bullet)
{
    property_var(m_shipOwner)
}
property_end()