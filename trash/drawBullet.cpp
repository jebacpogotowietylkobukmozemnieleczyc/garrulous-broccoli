#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h> //Przydatne do wypisywania komunikat?w na konsoli
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#include <iostream>
using namespace glm;

auto rigidy = 20.0f;
float speed = 60; // 60 stopni/s
int lastTime = 0;
float angle;
btRigidBody* fallRigidBody;
btDiscreteDynamicsWorld* dynamicsWorld;

class debugDrawer : public btIDebugDraw{
public:
debugDrawer();
void    drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar   distance,int lifeTime,const btVector3& color);
void    reportErrorWarning(const char* warningString);
void    draw3dText(const btVector3& location,const char* textString);
void    setDebugMode(int debugMode);
int     getDebugMode() const;
void drawAabb(const btVector3& from,const btVector3& to,const btVector3& color);

void  drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
};
/*
class GLDebugDrawer : public btIDebugDraw
{
int m_debugMode;

public:

//GLDebugDrawer() {};
//virtual ~GLDebugDrawer();

void    drawLine(const btVector3& from,const btVector3& to,const btVector3&  fromColor, const btVector3& toColor);

//virtual void    drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
};
*/
debugDrawer::debugDrawer(){

}
/*
void debugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
    float tmp[ 6 ] = { from.getX(), from.getY(), from.getZ(),
        to.getX(), to.getY(), to.getZ() };
    glPushMatrix();
    {
        glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);
        glVertexPointer( 3,
                        GL_FLOAT,
                        0,
                        &tmp );

        glPointSize( 5.0f );
        glDrawArrays( GL_POINTS, 0, 2 );
        glDrawArrays( GL_LINES, 0, 2 );
    }
    glPopMatrix();

    }
*/
void debugDrawer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color){

}
void    debugDrawer::reportErrorWarning(const char* warningString) {

}
void debugDrawer::draw3dText(const btVector3& location,const char* textString) {

}
void debugDrawer::setDebugMode(int debugMode){

}
int debugDrawer::getDebugMode() const{
return 0;
}
void debugDrawer::drawAabb(const btVector3& from,const btVector3& to,const btVector3& color)
{
}

void    debugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor)
{

    glBegin(GL_LINES);
        glColor3f(fromColor.getX(), fromColor.getY(), fromColor.getZ());
        glVertex3d(from.getX(), from.getY(), from.getZ());
        glColor3f(fromColor.getX(), fromColor.getY(), fromColor.getZ());
        glVertex3d(to.getX(), to.getY(), to.getZ());
    glEnd();

}

void displayFrame(void) {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  mat4 P = perspective(50.0f, 1.0f, 1.0f, 50.0f);
  mat4 V = lookAt(vec3(0.0f, 0.0f, -20.0f), vec3(0.0f, 0.0f, 0.0f),
                  vec3(0.0f, 1.0f, 0.0f));
  mat4 M = mat4(1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(value_ptr(P));
  glMatrixMode(GL_MODELVIEW);

  M = translate(M, vec3(2.0f,rigidy, 0.0f));
  M = rotate(M, angle, vec3(0.0f, 1.0f, 0.0f));
  glLoadMatrixf(value_ptr(V * M));
  glColor3d(1, 1, 0);
  glutSolidTorus(0.5, 1.5, 10, 10);
  glBegin(GL_LINES);
      glColor3f(1,1,1);
      glVertex3d(-1,1,1);
      glColor3f(1,1,1);
      glVertex3d(1,5,1);
  glEnd();
  dynamicsWorld->debugDrawWorld();
  glutSwapBuffers();
}

void nextFrame(void) {
  int actTime = glutGet(GLUT_ELAPSED_TIME);
  int interval = actTime - lastTime;

  lastTime = actTime;
  angle += speed * interval / 1000.0;
  if (angle > 360)
    angle -= 360;
  dynamicsWorld->stepSimulation(1 / 60.f, 10);

  btTransform trans;
  fallRigidBody->getMotionState()->getWorldTransform(trans);
  rigidy = trans.getOrigin().getY();
  std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
  glutPostRedisplay();
}

int main(int argc, char* argv[]) {
  // OpenGL  Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Program OpenGL");
  glutDisplayFunc(displayFrame);

  // Tutaj kod inicjuj?cy
  glutIdleFunc(nextFrame);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);

  // Bullet
  // World
  std::cout << "Hello World!" << std::endl;

  // Build the broadphase
  btBroadphaseInterface* broadphase = new btDbvtBroadphase();

  // Set up the collision configuration and dispatcher
  btDefaultCollisionConfiguration* collisionConfiguration =
      new btDefaultCollisionConfiguration();
  btCollisionDispatcher* dispatcher =
      new btCollisionDispatcher(collisionConfiguration);

  // The actual physics solver
  btSequentialImpulseConstraintSolver* solver =
      new btSequentialImpulseConstraintSolver;

  // The world.
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
                                              collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0, -10, 0));

  //debug

  debugDrawer *debug;
  debug = new debugDrawer();
  debug->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
  dynamicsWorld->setDebugDrawer(debug);

//  dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
  // collison
  btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

  btCollisionShape* fallShape = new btSphereShape(1);

  // rigidbody
  btDefaultMotionState* groundMotionState = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2, 0)));
  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
      0, groundMotionState, groundShape, btVector3(0, 0, 0));
  btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
  dynamicsWorld->addRigidBody(groundRigidBody);

  btDefaultMotionState* fallMotionState = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, rigidy, 0)));
  btScalar mass = 1;
  btVector3 fallInertia(0, 0, 0);
  fallShape->calculateLocalInertia(mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(
      mass, fallMotionState, fallShape, fallInertia);
  fallRigidBody = new btRigidBody(fallRigidBodyCI);
  dynamicsWorld->addRigidBody(fallRigidBody);



  glutMainLoop();

  // clean bullet
  dynamicsWorld->removeRigidBody(fallRigidBody);
  delete fallRigidBody->getMotionState();
  delete fallRigidBody;

  dynamicsWorld->removeRigidBody(groundRigidBody);
  delete groundRigidBody->getMotionState();
  delete groundRigidBody;

  delete dynamicsWorld;
  delete solver;
  delete dispatcher;
  delete collisionConfiguration;
  delete broadphase;

  return 0;
}
