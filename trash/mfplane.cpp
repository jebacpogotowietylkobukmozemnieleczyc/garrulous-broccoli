#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tga.h"
//#include "cube.h"
int cubeVertexCount=0;
double deg2rad(double deg)
{
     return deg*3.14159265/180.f;
}
float cubeVertices[]={
    -20,-1,-20,
     0,-1,-20,
    20,-1,-20,
    -20,-1,0,
     0,-1,0,
    20,-1,0,
    -20,-1,20,
     0,-1,20,
    20,-1,20,
 };

float startx = -20;
float startz = -20;
float endx =20;
float endz =20;
float divx = 16;
float divz = 16;
int t =2;
std::vector<float> vec;
std::vector<unsigned int > vecind;
std::vector<float> veccolor;
void InitVec(){
int v =0;
float stepx = (endx - startx) / divx;
float stepz = (endz - startz) / divz;
    for (int i = 0; i <= divz; ++i) {
        for (int j = 0; j <= divx; ++j) {
           int x =startx + j*stepx;
           int z =startz + i * stepz;
           vec.push_back(x);
           vec.push_back(t*(cos(deg2rad(x*15))+sin(deg2rad(z*15))));
           vec.push_back(z);
           std::cout <<  startx + j*stepx<< ' ' << -1  << ' ' << startz + i * stepz << std::endl;

           if(i<divz && j < divx){
           vecind.push_back(v);
           vecind.push_back(v+divx+1);
           vecind.push_back(v+divx+2);
           vecind.push_back(v+1);
           std::cout <<  v<< "www" << v+divx+1  << ' ' << v+divx+2<< ' ' << v+1 << std::endl;
           }

           veccolor.push_back(1);
           veccolor.push_back(0);
           veccolor.push_back(0);
           ++v;
        }
    }
}


float cubeColors[]={
    1,0,0, 0,1,0, 0,0,1, 1,1,1, 1,1,1, 1,1,1, 1,0,1, 1,1,0, 0,1,1,
};

unsigned int  ind[]={
    0,3,4,1, 1,4,5,2, 3,6,7,4, 4,7,8,5,
};

float speed_x=0; 
float speed_y=0; 
int lastTime=0;
float angle_x;
float angle_y;

GLuint tex;

void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 M;
	glm::mat4 V=glm::lookAt(
        glm::vec3(0.0f,10.0f,-50.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	
	glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	
		
	M=glm::mat4(1.0f);
	M=glm::rotate(M,angle_y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::rotate(M,angle_x,glm::vec3(1.0f,0.0f,0.0f));
	glLoadMatrixf(glm::value_ptr(V*M));

	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,0,vec.data());
    glColorPointer(3,GL_FLOAT,0,veccolor.data());
		
    glDrawElements(GL_QUADS,vecind.size(),GL_UNSIGNED_INT,vecind.data());
	glDisableClientState(GL_VERTEX_ARRAY);	
	glDisableClientState(GL_COLOR_ARRAY);
	
	glutSwapBuffers();
}


void nextFrame(void) {
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	angle_x+=speed_x*interval/1000.0;
	angle_y+=speed_y*interval/1000.0;
	if (angle_x>360) angle_x-=360;
	if (angle_x>360) angle_x+=360;
	if (angle_y>360) angle_y-=360;
	if (angle_y>360) angle_y+=360;
	
	glutPostRedisplay();
}

void keyDown(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      speed_y=60;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-60;
      break;
    case GLUT_KEY_UP: 
      speed_x=60;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-60;
      break;  
  }
}

void keyUp(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      speed_y=0;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-0;
      break;
    case GLUT_KEY_UP: 
      speed_x=0;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-0;
      break;  
  }
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");        
	glutDisplayFunc(displayFrame);
	glutIdleFunc(nextFrame);

	//Tutaj kod inicjujacy	
	glewInit();
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	
	
	glEnable(GL_DEPTH_TEST);

    InitVec();
    glutMainLoop();	

    return 0;
}
