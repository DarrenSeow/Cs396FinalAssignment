#pragma once


struct RenderingShipSystem : xecs::system::instance
{
    constexpr static auto typedef_v =
        xecs::system::type::child_update<RenderingSystem, RenderingSystem::update>
    {
        .m_pName = "RenderingShipSystem"
    };

    using query = std::tuple
        <
        xecs::query::one_of<entity>,
        xecs::query::must<PlayerTag>
        >;

    void OnPreUpdate(void) noexcept
    {
       // glBegin(GL_TRIANGLES);
    }

    void OnPostUpdate(void) noexcept
    {
       // glEnd();
    }

    void operator()(const entity& _entity, const Position& _position,const Scale& _scale, const Timer* _timer) const noexcept
    {
        glColor3f(1.0f, 1.0f, 0.0f);

        // Apply Transformation Matrix to quad
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(_position.m_value.m_X, _position.m_value.m_Y, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, -1.0f);
        glScalef(_scale.m_value.m_X, _scale.m_value.m_Y, 0.0f);

        // Render a quad
        glBegin(GL_TRIANGLES);
        //glVertex2f(0.5f, 0.5f);
        //glVertex2f(0.5f, -0.5f);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f(-0.5f, 0.5f);

        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();

        glPopMatrix();
    }
};