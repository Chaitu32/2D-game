#include "main.h"

#ifndef MAZE_H
#define MAZE_H

class Maze{
    public:
        Maze(){}
        Maze(float x1,float y1, color_t color,int size_ofmaze);
        void draw(glm::mat4 VP);
        glm::vec3 position;
        glm::vec3 scaling;
        int check_movement(glm::vec3 cur_pos,int change_x,int change_y);

    private:
        int N;
        std::vector<bool> maze_representation;
        VAO* object;
};

#endif