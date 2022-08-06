#pragma once

struct RenderingSystem : xecs::system::instance
{
   // inline static RenderingInfo* renderingInfo = nullptr;
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "RenderingSystem"
    };

    using update = xecs::event::instance<>;

    using events = std::tuple
        < update
        >;
    __inline void OnPreUpdate(void) noexcept
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glViewport(0, 0, renderingInfo.m_width, renderingInfo.m_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, renderingInfo.m_width, 0, renderingInfo.m_height, -1, 1);
        glScalef(1, -1, 1);
        glTranslatef(0, -static_cast<float>(renderingInfo.m_height), 0);

    }
    __inline
        void OnUpdate(void) noexcept
    {
        SendEventFrom<update>(this);        
    }
    __inline void OnPostUpdate(void) noexcept
    {
        glutSwapBuffers();
    }
};