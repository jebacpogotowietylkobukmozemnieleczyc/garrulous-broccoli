#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h> //Przydatne do wypisywania komunikat?w na konsoli
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



float speed=60; //60 stopni/s
int lastTime=0;
float angle;
void FractalStep (int depth,float startx, float starty,float startz,float size){
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                if( (x==1 && y==1) || (x==1 && z==1) || (y==1 && z==1) )continue;
                if(depth!=0){
                    FractalStep(--depth,startx+x*size,starty+y*size,startz+z*size,size/3);
                   ++depth;
                    continue;
                }
    glm::mat4 M=glm::mat4(1.0);
    glm::mat4 V=glm::lookAt(glm::vec3(0.0f,0.0f,-50.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));


    M=glm::rotate(M,10.0f,glm::vec3(1.0f,1.0f,0.0f));
    M = glm::translate(M,glm::vec3(startx+x*size,starty+y*size,startz+z*size));
    glLoadMatrixf(glm::value_ptr(V*M));
    glColor3d(0.5,0.5,0.5);
    glutSolidCube(size);


            }
        }
    }


}

void displayFrame(void) {
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
             glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);
FractalStep(2,0,0,0,2);
            glutSwapBuffers();

}

/*
void nextFrame(void) {
    int actTime=glutGet(GLUT_ELAPSED_TIME);
    int interval=actTime-lastTime;
    lastTime=actTime;
    angle+=speed*interval/1000.0;
    if (angle>360) angle-=360;
    glutPostRedisplay();
}
*/

void InitOpenGL(int *argc, char** argv){
     glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Program OpenGL");
    glutDisplayFunc(displayFrame);
 //glutIdleFunc(nextFrame);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);

}

int main(int argc, char* argv[]) {
    InitOpenGL(&argc,argv);
   glutMainLoop();
    return 0;
}
