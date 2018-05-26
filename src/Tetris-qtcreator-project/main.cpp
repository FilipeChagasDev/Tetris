// ANSI C Headers
#include <unistd.h>
#include <stdint.h>
// CPP Libs
#include <iostream>
#include <thread>
// Graphics Libs
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <drawtext.h> // library repository -> https://github.com/jtsiomb/libdrawtext
// My Project Libs
#include "tetrisgenerators.hpp"
#include "tetrismatrix.hpp"
#include "tetristimer.hpp"
#include "tetrisformation.hpp"
#include "formations/tformation.hpp"

using namespace std;

//constants
const int window_width = 340, window_height = 620;
const char *fontlocation = "serif.ttf";

//globals
struct dtx_font *font;
GLFWwindow *window;
TetrisMatrix matrix;

//declarations
bool right_key_last_state;
bool left_key_last_state;
bool down_key_last_state;
bool enter_key_last_state;
bool space_key_last_state;
void doWindowEvents(TetrisFormation *formation);
void countdown(int seconds);
void initWindow();
void printHelp();

/*void fillMatrix()
{
    for(int x = 0; x < TetrisMatrix::width; x++)
        for(int y = 10; y < TetrisMatrix::height; y++)
        {
            mat.addBlock(x,y, (float)x/TetrisMatrix::width, (float)y/TetrisMatrix::height , 0.5f);
        }
}*/

int main()
{
    //fillMatrix();
    glfwInit(); //initializing glfw
    printHelp();

    // ----------- GAME BEGIN ------------------
    gamebegin: //part of the algorithm where the game is started

    initWindow(); //creating main window



    matrix.defineRenderArea( 10 , 10 , window_width - 20 , window_height - 20);
    matrix.clear();

    countdown(5);

    glClear(GL_COLOR_BUFFER_BIT);
    matrix.render();

    glfwSwapBuffers(window);

    TetrisFormation *current_formation = nullptr;

    // -------------- MAIN LOOP ----------------
    TetrisTimer FormationMoveTimer(USEC_UNITY/2);
    while(true)
    {
        FormationMoveTimer.update(); //updating elapsed time value
        doWindowEvents(current_formation);

        if(FormationMoveTimer.every()) //run the code inside the if every half second
        {
            if(current_formation == nullptr)
            //run the code inside the if whenever it is necessary to create a new formation
            {
                current_formation = generateFormation(&matrix, 5, 0); //create a new formation

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                current_formation->render();
                glfwSwapBuffers(window);
                //--------------------------

                usleep(500000);

                //if there is no space for the formation to move down, go to the gameover
                if(!current_formation->canMoveDown()) goto gameover;
            }

            //render matrix and formation
            glClear(GL_COLOR_BUFFER_BIT);
            matrix.render();
            current_formation->render();
            glfwSwapBuffers(window);
            //--------------------------

            if(!current_formation->moveDown())
            //if it is not possible to move the formation down, drop it and delete it
            {
                current_formation->drop();
                delete current_formation;
                current_formation = nullptr;
            }
        }

        glfwPollEvents();
    }

    // -------------- GAME OVER ----------------
    gameover:
    glfwDestroyWindow(window);
    {
        cout << "GAME OVER" << endl << "do you want to restart? [y/n]" << endl;
        char feedback;
        while (1)
        {
            cin >> feedback;

            if(feedback == 'y' || feedback == 'Y') goto gamebegin;
            else
                if(feedback == 'n' || feedback == 'N') break; //if the feedback is 'n' or 'N', break loop and finalize program
                else cout << "what? i can't understand it..." << endl << "do you want to restart? [y/n]" << endl;
        }
    }

    return 0;
}

// ----------- definitions --------------

void printHelp()
{
    cout << "T E T R I S" << endl
         << "by Filipe Chagas" << endl
         << "   Keyboard commands:" << endl
         << "   arrows : move" << endl
         << "   enter : clockwise rotation" << endl
         << "   shift + enter : anticlockwise rotation" << endl
         << "   space : horizontal invertion" << endl
         << "   shift + space : vertical invertion" << endl;
}

void doWindowEvents(TetrisFormation *formation)
{
    if(glfwWindowShouldClose(window)) exit(0);

    if(formation != nullptr)
    {
        int right_key_state = glfwGetKey(window, GLFW_KEY_RIGHT);
        int left_key_state = glfwGetKey(window, GLFW_KEY_LEFT);
        int down_key_state = glfwGetKey(window, GLFW_KEY_DOWN);
        int enter_key_state = glfwGetKey(window, GLFW_KEY_ENTER);
        int space_key_state = glfwGetKey(window, GLFW_KEY_SPACE);
        int shift_key_state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);

        // ---------------- RIGHT KEY ------------------
        if(right_key_state == GLFW_PRESS )
        {
            if(right_key_last_state == false)
            {
                formation->moveRight();
                right_key_last_state = true;

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                formation->render();
                glfwSwapBuffers(window);
                //--------------------------
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
                formation->moveLeft();
                left_key_last_state = true;

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                formation->render();
                glfwSwapBuffers(window);
                //--------------------------
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
                formation->moveDown();
                down_key_last_state = true;

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                formation->render();
                glfwSwapBuffers(window);
                //--------------------------
            }
        }
        else //if(down_key_state == GLFW_RELEASE)
        {
            if(down_key_last_state == true)
            {
                down_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- ENTER KEY ---------------------
        if(enter_key_state == GLFW_PRESS )
        {
            if(enter_key_last_state == false)
            {
                if(shift_key_state == GLFW_PRESS) formation->clockwiseRotate();
                else formation->anticlockwiseRotate();
                enter_key_last_state = true;

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                formation->render();
                glfwSwapBuffers(window);
                //--------------------------
            }
        }
        else //if(enter_key_state == GLFW_RELEASE)
        {
            if(enter_key_last_state == true)
            {
                enter_key_last_state = false;
            }
        }
        // ----------------------------------------------

        // --------------- SPACE KEY ---------------------
        if(space_key_state == GLFW_PRESS )
        {
            if(space_key_last_state == false)
            {
                if(shift_key_state == GLFW_PRESS) formation->invertY();
                else formation->invertX();

                space_key_last_state = true;

                //render matrix and formation
                glClear(GL_COLOR_BUFFER_BIT);
                matrix.render();
                formation->render();
                glfwSwapBuffers(window);
                //--------------------------
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

void countdown(int seconds)
{
    char str[50];
    int countdown_time = seconds;
    TetrisTimer timer(USEC_UNITY);
    while (countdown_time >= 0)
    {
        usleep(1);
        timer.update();
        doWindowEvents(nullptr);

        if(timer.every())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            matrix.render();

            glPushMatrix();
                glTranslatef(70, 300, 0);
                glRotatef(180, 1, 0, 0);
                glColor3f(1, 1, 1);
                sprintf(str,"Countdown - %d",countdown_time);
                dtx_string(str);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(60, 200, 0);
                glScalef(1.5,1.5,0);
                glRotatef(180, 1, 0, 0);
                glColor3f(1,0.5,0);
                dtx_string("T E T R I S");

                glScalef(1/1.5,1/1.5,0);
                glTranslatef( 0 , -50 ,0);
                dtx_string("By Filipe Chagas");
            glPopMatrix();

            glfwSwapBuffers(window);

            countdown_time -= 1;
        }
        glfwPollEvents();
    }
}

void initWindow()
{
    right_key_last_state = false;
    left_key_last_state = false;
    down_key_last_state = false;
    enter_key_last_state = false;
    space_key_last_state = false;

    window = glfwCreateWindow(window_width,window_height, "Tetris by Filipe Chagas" , nullptr, nullptr);

    glfwSetWindowSizeLimits(window,window_width,window_height,window_width,window_height); //fixed window size
    glEnable(GL_MULTISAMPLE);

    glfwMakeContextCurrent(window);

    glClearColor(0.05,0.07,0.1,1);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,window_width,window_height,0,-0.1,1);
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    glViewport(0,0,window_width,window_height);
    glClear(GL_COLOR_BUFFER_BIT);

    if(!(font = dtx_open_font(fontlocation, 24)))
    {
        cerr << "error : cannot load font" << endl;
        throw;
    }
    dtx_use_font(font, 24);
}
