#include <GL/gl.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "fractal.hpp"

void Fractal::FractalStep (int depth,float startx, float starty,float startz,float size){
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                if( (x==1 && y==1) || (x==1 && z==1) || (y==1 && z==1) )continue;
                if(depth!=0){
                    FractalStep(--depth,startx+x*size,starty+y*size,startz+z*size,size/3);
                   ++depth;
                    continue;
                }
             glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
    glm::mat4 V=glm::lookAt(glm::vec3(0.0f,0.0f,-50.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 M=glm::mat4(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);


    //M=rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
    M = glm::translate(M,glm::vec3(startx+x*size,starty+y*size,startz+z*size));
    glLoadMatrixf(glm::value_ptr(V*M));
    glColor3d(0.5,0.5,0.5);
    glutSolidCube(size);


            }
        }
    }


}

void Fractal::DrawFractal(){
    FractalStep(depth_,startx_,starty_,startz_,size_);
}
