// Graphics Libs
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    const char *fontlocation = "/System/Library/Fonts/Keyboard.ttf";
#else
    const char *fontlocation = "serif.ttf";
    #include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>
#include <drawtext.h> // library repository -> https://github.com/jtsiomb/libdrawtext
// My Project Libs
#include "tetrisgenerators.hpp"
#include "tetrismatrix.hpp"
#include "tetristimer.hpp"
#include "tetrisformation.hpp"

using namespace std;

// ANSI C Headers
#include <unistd.h>
#include <stdint.h>
// CPP Libs
#include <iostream>
#include <thread>
#include <mutex>



//constants
const int window_width = 510, window_height = 620;

//globals
struct dtx_font *font;
GLFWwindow *window;

TetrisMatrix matrix;

TetrisFormation *current_formation;
mutex current_formation_mutex;

TetrisTimer AutoMoveTimer(USEC_UNITY/2);

bool render_interruption_semaphore;
mutex render_interruption_mutex;
void render_interruption_call();
void render_interruption_listen();

bool game_paused;
void pauseGame();

//declarations
void KeyboardEvents();
void homeScreen(int seconds);
void initWindow();
void printHelp();
void renderBackground(float red, float green, float blue);
void renderInfo();
void renderAll();
void playGame();
bool gameOver();

/* -----------------------------------------------------------------------------------
   ------------------------------ MAIN FUNCTION --------------------------------------
   ----------------------------------------------------------------------------------- */

int main()
{
    render_interruption_semaphore = false;

    glfwInit(); //initializing glfw
    printHelp();

    do
    {
        game_paused = false;
        initWindow(); //creating main window
        matrix.defineRenderArea( 10 , 10 , window_width - 190 , window_height - 20);
        matrix.clear();
        homeScreen(5);
        playGame();
        if(window != nullptr) glfwDestroyWindow(window);
        if(current_formation != nullptr)
        {
            delete current_formation;
            current_formation = nullptr;
        }
    }while(gameOver());

    return 0;
}

/* -----------------------------------------------------------------------------------
   ----------------------------------------------------------------------------------- */

void printHelp()
{
    cout << "T E T R I S" << endl
         << "created by Filipe Chagas (https://github.com/FilipeChagasDev)" << endl
         << "`coldfries` updates by Gustavo Ale (https://github.com/GustavoAle)" << endl
         << "   Keyboard commands:" << endl
         << "   left & right arrows : move" << endl
         << "   up arrow : flip (clockwise rotation)" << endl
         << "   space : pause" << endl;
}

void initWindow()
{
    /*right_key_last_state = false;
    left_key_last_state = false;
    down_key_last_state = false;
    enter_key_last_state = false;
    space_key_last_state = false;
*/
    window = glfwCreateWindow(window_width,window_height, "Tetris by Filipe Chagas" , nullptr, nullptr);

    glfwSetWindowSizeLimits(window,window_width,window_height,window_width,window_height); //fixed window size
    glEnable(GL_MULTISAMPLE);

    glfwMakeContextCurrent(window);

    glClearColor(0.1,0.1,0.1,1);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,window_width,window_height,0,-0.1,1);
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    glViewport(0,0,window_width,window_height);
    glClear(GL_COLOR_BUFFER_BIT);

    cout << fontlocation << endl;

    if(!(font = dtx_open_font(fontlocation, 24)))
    {
        cerr << "error : cannot load font" << endl;
        throw;
    }
    dtx_use_font(font, 24);
}

void renderBackground(float red, float green, float blue)
{
    float top_x = matrix.getGraphX(), top_y = 0;
    float bottom_x = matrix.getGraphWidth() + top_x, bottom_y = matrix.getGraphHeight() + matrix.getGraphY();

    glBegin(GL_POLYGON);
        glColor3f(red, green, blue);
        glVertex2f(top_x, top_y);
        glVertex2f(top_x, bottom_y);
        glVertex2f(bottom_x, bottom_y);
        glVertex2f(bottom_x, top_y);
    glEnd();
}

void renderInfo()
{
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(360,50,0);
        glRotatef(180,1,0,0);
        dtx_string("next:");
    glPopMatrix();
    getNextFormation()->renderSample(390,120);
}

void renderAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    renderBackground(0,0,0);
    matrix.render();
    current_formation->render();
    renderInfo();
    glfwSwapBuffers(window);
}

void render_interruption_call()
{
    render_interruption_mutex.lock();
    render_interruption_semaphore = true;
    render_interruption_mutex.unlock();
}

void render_interruption_listen()
{
    if(render_interruption_semaphore)
    {
        renderAll();
        render_interruption_mutex.lock();
        render_interruption_semaphore = false;
        render_interruption_mutex.unlock();
    }
}

void playGame()
{
    AutoMoveTimer.reset();
    AutoMoveTimer.setEveryInterval(USEC_UNITY/2);
    glClear(GL_COLOR_BUFFER_BIT);

    renderBackground(0,0,0);
    matrix.clear();
    matrix.render();

    glfwSwapBuffers(window);

    current_formation = nullptr;

    // -------------- MAIN LOOP ----------------
    while(true)
    {
        AutoMoveTimer.update(); //updating elapsed time value

        KeyboardEvents();

        render_interruption_listen();

        if(AutoMoveTimer.every() && !game_paused) //run the code inside the if every half second
        {
            if(current_formation == nullptr)
            //run the code inside the if whenever it is necessary to create a new formation
            {
                current_formation_mutex.unlock();
                current_formation_mutex.lock();

                current_formation = generateFormation(&matrix, 5, 0); //create a new formation
                renderAll();
                usleep(AutoMoveTimer.getEveryInterval());

                //if there is no space for the formation to move down, go to the gameover
                if(!current_formation->canMoveDown()) return; //goto gameover;

                current_formation_mutex.unlock();
            }


            renderAll();

            current_formation_mutex.lock();
            if(!current_formation->moveDown())
            //if it is not possible to move the formation down, drop it and delete it
            {
                current_formation->drop();
                delete current_formation;
                current_formation = nullptr;
                matrix.promptfullRows();
            }
            current_formation_mutex.unlock();
        }

        glfwPollEvents();
    }

}

void pauseGame()
{
    game_paused = !game_paused;

    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(360,600,0);
        glRotatef(180,1,0,0);
        dtx_string("PAUSED");
    glPopMatrix();

    glfwSwapBuffers(window);
}

bool right_key_last_state;
bool left_key_last_state;
bool down_key_last_state;
bool up_key_last_state;
bool space_key_last_state;

void KeyboardEvents()
{
    if(glfwWindowShouldClose(window)) exit(0);

    if(current_formation != nullptr)
    {
        int right_key_state = glfwGetKey(window, GLFW_KEY_RIGHT);
        int left_key_state = glfwGetKey(window, GLFW_KEY_LEFT);
        int down_key_state = glfwGetKey(window, GLFW_KEY_DOWN);
        int up_key_state = glfwGetKey(window, GLFW_KEY_UP);
        int space_key_state = glfwGetKey(window, GLFW_KEY_SPACE);
        int shift_key_state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);

        // ---------------- RIGHT KEY ------------------
        if(right_key_state == GLFW_PRESS )
        {
            if(right_key_last_state == false)
            {
                if(!game_paused)
                {
                    current_formation_mutex.lock();
                        current_formation->moveRight();
                    current_formation_mutex.unlock();

                    thread thread_move([]()
                    {
                        uintmax_t time = TetrisTimer::getSystemUseconds();
                        while (TetrisTimer::getSystemUseconds() < time + USEC_UNITY/3)
                        {
                            if(glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS) return;
                        }

                        while (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS)
                        {
                            current_formation_mutex.lock();
                               if(current_formation != nullptr) current_formation->moveRight();
                               else
                               {
                                   current_formation_mutex.unlock();
                                   break;
                               }
                            current_formation_mutex.unlock();

                            render_interruption_call();
                            usleep(USEC_UNITY/15);
                        }
                    });
                    thread_move.detach();
                    renderAll();
                }

                right_key_last_state = true;

            }
        }
        else //if(right_key_state == GLFW_RELEASE)
        {
            if(right_key_last_state == true)
            {
                right_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- LEFT KEY ---------------------
        if(left_key_state == GLFW_PRESS )
        {
            if(left_key_last_state == false)
            {
                if(!game_paused)
                {
                    current_formation_mutex.lock();
                        current_formation->moveLeft();
                    current_formation_mutex.unlock();

                    thread thread_move([]()
                    {
                        uintmax_t time = TetrisTimer::getSystemUseconds();
                        while (TetrisTimer::getSystemUseconds() < time + USEC_UNITY/3)
                        {
                            if(glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) return;
                        }

                        while (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS &&
                               glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS)
                        {
                            current_formation_mutex.lock();
                                if(current_formation != nullptr) current_formation->moveLeft();
                                else
                                {
                                    current_formation_mutex.unlock();
                                    break;
                                }
                            current_formation_mutex.unlock();

                            render_interruption_call();

                            usleep(USEC_UNITY/15);
                        }

                    });//end thread
                    thread_move.detach();
                    renderAll();
                }

                left_key_last_state = true;
            }
        }
        else //if(left_key_state == GLFW_RELEASE)
        {
            if(left_key_last_state == true)
            {
                left_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- DOWN KEY ---------------------
        if(down_key_state == GLFW_PRESS )
        {
            if(down_key_last_state == false)
            {
                if(!game_paused)
                {
                    current_formation_mutex.lock();
                        current_formation->moveDown();
                    current_formation_mutex.unlock();

                    usleep(USEC_UNITY/15);
                    AutoMoveTimer.setEveryInterval(USEC_UNITY/15);
                    renderAll();
                }

                down_key_last_state = true;
            }
        }
        else //if(down_key_state == GLFW_RELEASE)
        {
            if(down_key_last_state == true)
            {
                AutoMoveTimer.setEveryInterval(USEC_UNITY/2);
                down_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- UP KEY ---------------------
        if(up_key_state == GLFW_PRESS )
        {
            if(up_key_last_state == false)
            {
                if(!game_paused)
                {
                    current_formation->clockwiseRotate();
                    renderAll();
                }

                up_key_last_state = true;
            }
        }
        else //if(enter_key_state == GLFW_RELEASE)
        {
            if(up_key_last_state == true)
            {
                up_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- SPACE KEY ---------------------
        if(space_key_state == GLFW_PRESS )
        {
            if(space_key_last_state == false)
            {
                pauseGame();
                space_key_last_state = true;

            }
        }
        else //if(space_key_state == GLFW_RELEASE)
        {
            if(space_key_last_state == true)
            {
                space_key_last_state = false;
            }
        }
        // ----------------------------------------------


    }
}

void homeScreen(int seconds)
{
    char str[50];
    int countdown_time = seconds;
    TetrisTimer timer(USEC_UNITY);
    while (countdown_time >= 0)
    {
        usleep(1);
        timer.update();
        KeyboardEvents();

        if(timer.every())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            matrix.render();

            glPushMatrix();
                glTranslatef(150, 350, 0);
                glRotatef(180, 1, 0, 0);
                glColor3f(1, 1, 1);
                sprintf(str,"Countdown - %d",countdown_time);
                dtx_string(str);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(140, 200, 0);
                glScalef(1.5,1.5,0);
                glRotatef(180, 1, 0, 0);
                glColor3f(1,0.5,0);
                dtx_string("T E T R I S");

                glScalef(1/1.5,1/1.5,0);
                glTranslatef( 0 , -50 ,0);
                dtx_string("By Filipe Chagas");

                glScalef(1/1.5,1/1.5,0);
                glTranslatef( 0 , -50 ,0);
                dtx_string("*coldfries* by Gustavo Ale");
            glPopMatrix();

            glfwSwapBuffers(window);

            countdown_time -= 1;
        }
        glfwPollEvents();
    }
}

bool gameOver()
{
    cout << "GAME OVER" << endl << "do you want to restart? [y/n]" << endl;
    char feedback;
    while (1)
    {
        cin >> feedback;

        if(feedback == 'y' || feedback == 'Y') return true;
        else
            if(feedback == 'n' || feedback == 'N') return false; //if the feedback is 'n' or 'N', break loop and return false
            else cout << "what? i can't understand it..." << endl << "do you want to restart? [y/n]" << endl;
    }
}




