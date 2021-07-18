#include"player.h"
#include"main.h"

Player::Player(float x,float y ,color_t color){
    this->position = glm::vec3(x,y,0);
    speed = 1;
    this->health = 100;
    static  GLfloat vertex_semicirclebuffer[300*3];
    glm::vec3 centre = glm::vec3(0.0f,0.5f,0.0f);
    double triangle_angle = glm::radians(1.8f);
    //for buliding semi-circle
    for(int i=0;i<100;i++){
        //side vertex of triangle
        vertex_semicirclebuffer[i*9] = -1*0.5f*glm::cos(i*triangle_angle)+centre.x; //x co-ordinate
        vertex_semicirclebuffer[i*9+1] = 0.5f*glm::sin(i*triangle_angle)+centre.y;  //y co-ordinate
        vertex_semicirclebuffer[i*9+2] = 0.0f+centre.z;  //z co-ordinate
        //centre
        vertex_semicirclebuffer[i*9+3] = centre.x;
        vertex_semicirclebuffer[i*9+4] = centre.y;
        vertex_semicirclebuffer[i*9+5] = centre.z;
        //top vertex of triangle
        vertex_semicirclebuffer[i*9+6] = -1*0.5f*glm::cos((i+1)*triangle_angle)+centre.x; //x co-ordinate
        vertex_semicirclebuffer[i*9+7] = 0.5f*glm::sin((i+1)*triangle_angle)+centre.y;  //y co-ordinate
        vertex_semicirclebuffer[i*9+8] = 0.0f+centre.z;  //z co-ordinate
    }
    //glass of helmet
    static const GLfloat vertex_facebuffer[]={
        -0.25f,0.625f,0.0f,
        -0.25f,0.875f,0.0f,
        0.25f,0.875f,0.0f,
        0.25f,0.875f,0.0f,
        0.25f,0.625f,0.0f,
        -0.25f,0.625f,0.0f,
    };
    //body of player
    static const GLfloat vertex_bodybuffer[]={
        0.5f,0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f
    };
    //Legs of player
    static const GLfloat vertex_legsbuffer[]={
        0.01f,-0.5f,0.0f,
        0.01f,-1.0f,0.0f,
        0.5f,-1.0f,0.0f,
        0.5f,-1.0f,0.0f,
        0.5f,-0.5f,0.0f,
        0.01f,-0.5f,0.0f,

        -0.01f,-0.5f,0.0f,
        -0.01f,-1.0f,0.0f,
        -0.5f,-1.0f,0.0f,
        -0.5f,-1.0f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.01f,-0.5f,0.0f,

    };
    color_t light_color;
    light_color.r = color.r/2;light_color.b = color.b/2;light_color.g = color.g/2;
    this->head = create3DObject(GL_TRIANGLES,100*3,vertex_semicirclebuffer,color,GL_FILL);
    this->face = create3DObject(GL_TRIANGLES,2*3,vertex_facebuffer,light_color,GL_FILL);
    this->body = create3DObject(GL_TRIANGLES,2*3,vertex_bodybuffer,color,GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES,2*2*3,vertex_legsbuffer,color,GL_FILL);
}

void Player::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->head);
    draw3DObject(this->face);
    draw3DObject(this->legs);
}

void Player::set_position(float x,float y){
    this->position.x = x;
    this->position.y = y;
}

void Player::decrease_health(float x){
    if (this->health!=0)
    this->health-=x;
}

void Player::move_left(){
    this->position.x-=1;
}

void Player::move_right(){
    this->position.x+=1;
}

void Player::move_up(){
    this->position.y+=1;
}

void Player::move_down(){
    this->position.y-=1;
}


int Player::game_check(int martix_size){
    int x = position.x/2;
    int y = position.y/2;
    if(x==martix_size-1&&y==martix_size-1)
        return 1;
    return 0;
}