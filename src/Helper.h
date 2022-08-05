#pragma once


template< typename... T_ARGS>
void GlutPrint(const int x, const int y, const char* const pFmt, T_ARGS&&... Args) noexcept
{
    std::array<char, 256> FinalString;
    const auto len = sprintf_s(FinalString.data(), FinalString.size(), pFmt, Args...);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, renderingInfo.m_width, 0, renderingInfo.m_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, renderingInfo.m_height - (y + 20));
    for (int i = 0; i < len; ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, FinalString[i]);
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}