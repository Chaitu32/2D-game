#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    public:
        Player(){}
        Player(float x,float y ,color_t color);
        glm::vec3 position;
        double speed;
        void set_position(float x,float y);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        void draw(glm::mat4 VP);
        void decrease_health(float x);
        int  game_check(int martix_size);

    private:
        float health;
        VAO* head;
        VAO* face;
        VAO* body;
        VAO* legs;
};

#endif