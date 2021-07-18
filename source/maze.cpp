#include "main.h"
#include "maze.h"

using namespace std;

Maze::Maze(float x1,float y1,color_t color,int size_of_maze){

    this->position = glm::vec3(x1,y1,0);
    this->scaling = glm::vec3(1,2,1);
    srand(time(0));
    this->N = size_of_maze;
    //cout<<"Check"<<endl;
    std::vector<int> adj[N*N];
    for(int y=0;y<N;y++)
        for(int x=0;x<N;x++){
            int index = y*N+x;
            if(x-1>=0)adj[index].push_back(index-1);
            if(x+1<N)adj[index].push_back(index+1);
            if(y-1>=0)adj[index].push_back(index-N);
            if(y+1<N)adj[index].push_back(index+N);
        }
    //cout<<"Check"<<endl;
    
    int max_lines = N*2*(N+1);
    bool check[max_lines]={0};
    int count = max_lines;
    std::stack<int> st;
    st.push(0);
    //cout<<"Check"<<endl;
    bool check2[N*N]={0};
    check2[0] = 1;
    while(!st.empty()){
        int cur = st.top();
        //cout<<cur<<endl;
        int len =adj[cur].size();
        int index_next = int(rand()%len);
        int value;
        bool temp_check=0;
        for(int j=0;j<len;j++)
            if(check2[adj[cur][(j+index_next)%len]]==0){
                temp_check=1;
                value= adj[cur][(j+index_next)%len];
            }
        if(temp_check==0){
            st.pop();
            continue;
        }
        check2[value]=1;
        st.push(value);
        //cout<<index_next<<endl;
        //for(auto i:adj[cur])cout<<"@"<<i<<endl;
        //for(auto i:adj[value])cout<<"#"<<i<<endl;
        // adj[cur].erase(adj[cur].begin()+index_next);
        //for(auto i:adj[cur])cout<<"@"<<i<<endl;
        //cout<<value<<endl;
        // auto remove_element = std::find(adj[value].begin(),adj[value].end(),cur);
        // int indexto_remove = remove_element- adj[value].begin();
        //cout<<"Check"<<endl;
        //for(auto i:adj[value])cout<<"#"<<i<<endl;
        // adj[value].erase(adj[value].begin()+indexto_remove);
        //for(auto i:adj[value])cout<<"@"<<i<<endl;
        //cout<<"Check2"<<endl;
        if(abs(cur-value)==N){
            check[std::max(cur,value)]=1;
            //cout<<"&"<<std::max(cur,value)<<endl;
        }
        else{
            check[((std::max(cur,value))%N)*N+(std::max(cur,value))/N+N*(N+1)]=1;
            //cout<<"&"<<((std::max(cur,value))%N)*N+(std::max(cur,value))/N+N*(N+1)<<endl;
        }
        count--;
    }
    //cout<<"Check"<<endl;
    cout<<count<<endl;
    GLfloat vertex_linedatabuffer[count*2*3];
    int index_vertex = 0;
    int x,y;
    for(int i=0;i<max_lines;i++){
        if(check[i]==1)continue;
        //cout<<"%"<<i<<endl;
        if(i<max_lines/2){
            x= (i%N);
            y= i/N;
            vertex_linedatabuffer[index_vertex] = float(x)*2;
            vertex_linedatabuffer[index_vertex+1] = float(y)*2;
            vertex_linedatabuffer[index_vertex+2] = 0.0f;
            index_vertex+=3;
            vertex_linedatabuffer[index_vertex] = float(x+1)*2;
            vertex_linedatabuffer[index_vertex+1] = float(y)*2;
            vertex_linedatabuffer[index_vertex+2] = 0.0f;
            index_vertex+=3;
        }
        else{
            y= (i%N);
            x= int(i/N)%(N+1);
            vertex_linedatabuffer[index_vertex] = float(x)*2;
            vertex_linedatabuffer[index_vertex+1] = float(y)*2;
            vertex_linedatabuffer[index_vertex+2] = 0.0f;
            index_vertex+=3;
            vertex_linedatabuffer[index_vertex] = float(x)*2;
            vertex_linedatabuffer[index_vertex+1] = float(y+1)*2;
            vertex_linedatabuffer[index_vertex+2] = 0.0f;
            index_vertex+=3;
        }
    }
    //cout<<"Check"<<endl;
    this->object = create3DObject(GL_LINES,count*2,vertex_linedatabuffer,color,GL_FILL);
    //cout<<"Check"<<endl;
    for(int i=0;i<max_lines;i++)this->maze_representation.push_back(check[i]);
}

void Maze::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

int Maze::check_movement(glm::vec3 cur_pos,int change_x,int change_y){
    int x = int(cur_pos.x/2);
    int y = int(cur_pos.y/2);
    int new_x = int((cur_pos.x+change_x)/2);
    int new_y = int((cur_pos.y+change_y)/2);
    if(cur_pos.x+change_x<=0 ||cur_pos.y+change_y<=0) return 1;
    //cout<<new_x<<" "<<new_y<<endl;
    if(new_x==x && new_y==y)return 0;
    if(new_x<0||new_x>=N||new_y<0||new_y>=N)return 1;
    if(change_x!=0&& change_y==0 && int(cur_pos.y)%2){
        int cur = y*N+x;
        int value = new_y*N+new_x;
        int index = ((std::max(cur,value))%N)*N+(std::max(cur,value))/N+N*(N+1);
        //cout<<maze_representation[index]<<endl;
        return !maze_representation[index];
    }
    else if(change_y!=0&& change_x==0 ){
        int cur = y*N+x;
        int value = new_y*N+new_x;
        //cout<<maze_representation[std::max(cur,value)]<<endl;
        return !this->maze_representation[std::max(cur,value)];
    }
    return 1;
}