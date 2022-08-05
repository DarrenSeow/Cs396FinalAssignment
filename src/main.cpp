
#include <xecs.h>
#define GLUT_STATIC_LIB
#include <GL/glut.h>
#include <GlutPrint.h>

#include <KeyInputs.h>
#include <RenderingInfo.h>
#include <Components.h>
#include <Grid.h>
#include <Events.h>
#include <Systems.h>
#include <random>
#include <Game.h>
#include <Helper.h>
//---------------------------------------------------------------------------------------
// GAME
//---------------------------------------------------------------------------------------




void UpdateTimer(int value) noexcept
{
    // Post re-paint request to activate display()
    glutPostRedisplay();

    // next timer call milliseconds later
    glutTimerFunc(15, UpdateTimer, 0);
}
int main(int argc, char** argv)
{
	xcore::Init("1945");
    s_Game.m_GameMgr = std::make_unique<xecs::game_mgr::instance>();
    s_Game.Initialize();
    s_Game.InitializeGame();
    glutInitWindowSize(renderingInfo.m_width, renderingInfo.m_height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(xcore::get().m_pAppName);

    glutDisplayFunc([](void) noexcept
        {
            s_Game.m_GameMgr->Run();
            //++iFrame;
            
            if (s_Game.m_Keys.getKey('g')) std::cout << "yay "<< std::endl;
            s_Game.m_Keys.FrameUpdate();
        });  

    glutTimerFunc(0, UpdateTimer, 0);
    
    glutReshapeFunc(
        [](int w, int h) noexcept
        {
            renderingInfo.m_width = w;
            renderingInfo.m_height = h;
        }
    );

    glutKeyboardFunc(
        [](unsigned char Key, int MouseX, int MouseY) noexcept
        {
            s_Game.KeyboardDownFunction(Key, MouseX, MouseY);

        }
    );
    glutKeyboardUpFunc(
        [](unsigned char Key, int MouseX, int MouseY) noexcept
        {
            s_Game.KeyboardUpFunction(Key, MouseX, MouseY);

        }
    );
    glutMouseFunc(
        [](int Button, int State, int MouseX, int MouseY) noexcept
        {
            s_Game.MouseFunction(Button, State, MouseX, MouseY);
        }
    );

    glutMainLoop();

    s_Game.m_GameMgr.reset();
    xcore::Kill();
	return 0;
}

