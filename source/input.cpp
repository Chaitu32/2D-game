#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "player.h"
#include "maze.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;
extern Player player1;
extern Maze maze1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    int check;
    if (action == GLFW_RELEASE) {
        switch (key) {
        case GLFW_KEY_W:
        check =maze1.check_movement(player1.position,0,1);
        if(check==0)
        player1.move_up();
        break;
        case GLFW_KEY_A:
        check =maze1.check_movement(player1.position,-1,0);
        if(check==0)
        player1.move_left();
        break;
        case GLFW_KEY_S:
        check =maze1.check_movement(player1.position,0,-1);
        if(check==0)
        player1.move_down();
        break;
        case GLFW_KEY_D:
        check =maze1.check_movement(player1.position,1,0);
        if(check==0)
        player1.move_right();
        break;
        default:
        break;
        }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
}
