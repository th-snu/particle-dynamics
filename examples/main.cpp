#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Geometry>
#include "../particles/particle_system.hpp"
#include "../simulation.hpp"
#include "../forces/constantf.hpp"
#include "../forces/drag.hpp"
#include "../forces/gravity.hpp"
#include "../forces/spring.hpp"
#define PI 3.14159265

int frame = 0;
double accel = 10.0;

unsigned timeStep = 30;
bool play = false;

GLdouble rotMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

Simulation sim;

/* set global variables */
int width, height;

bool leftButton = false;
GLfloat mousePosX, mousePosY;

/* vectors that makes the rotation and translation of the cube */
Eigen::Vector3f eye(-300.0f, 200.0f, -300.0f);
Eigen::Vector3f ori(1.0f, 0.0f, 1.0f);
Eigen::Vector2f oriAngle(3.0 * PI / 4.0, PI / 2.0);
Eigen::Vector3f right(0.0f, 0.0f, 1.0f);
Eigen::Vector3f up(0.0f, 1.0f, 0.0f);

void loadGlobalCoord()
{
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], eye[0]+ori[0], eye[1]+ori[1], eye[2]+ori[2], up[0], up[1], up[2]);
	glMultMatrixd(rotMatrix);
}

//------------------------------------------------------------------------
// Moves the screen based on mouse pressed button
//------------------------------------------------------------------------

void glutMotion(int x, int y)
{
	if (leftButton) {
		float dx = x - mousePosX;
		float dy = y - mousePosY;

		mousePosX = x;
		mousePosY = y;

		oriAngle[0] += dx / width;
		oriAngle[1] -= dy / width;

		ori[0] = sin(oriAngle[0])*sin(oriAngle[1]);
		ori[1] = -cos(oriAngle[1]);
		ori[2] = -cos(oriAngle[0])*sin(oriAngle[1]);

		ori.normalize();
		right = ori.cross(up).normalized();
		
		loadGlobalCoord();
	}
	return;
}

//------------------------------------------------------------------------
// Function that handles mouse input
//------------------------------------------------------------------------
void glutMouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			mousePosX = x;
			mousePosY = y;
			leftButton = true;
		}
		else if (state == GLUT_UP)
		{
			leftButton = false;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			play = !play;
		}
		break;
	case 3:break;
	default:break;
	}
	return;
}

void DrawGridPlane() {
	glBegin(GL_LINES);
	glColor3f(1, 0.5, 0.5);
	for (int i = -1000; i < 1001; i+=100){
		glVertex3f(i, 0, -1000);
		glVertex3f(i, 0, 1000);
		glVertex3f(1000, 0, i);
		glVertex3f(-1000, 0, i);
	}
	glColor3f(0.5, 1, 0.5);
	for (int i = -1000; i < 1001; i+=100){
		glVertex3f(i, -1000, 0);
		glVertex3f(i, 1000, 0);
		glVertex3f(1000, i, 0);
		glVertex3f(-1000, i, 0);
	}
	glColor3f(0.5, 0.5, 1);
	for (int i = -1000; i < 1001; i+=100){
		glVertex3f(0, i, -1000);
		glVertex3f(0, i, 1000);
		glVertex3f(0, 1000, i);
		glVertex3f(0, -1000, i);
	}
	glEnd();
}

void display() {
	glClearColor(0, 0.75, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	loadGlobalCoord();

	glPushMatrix();
	DrawGridPlane();
	glColor3f(1, 1, 1);
	for(int i = 0; i < sim.ps.len(); i++){
		glPushMatrix();
		{
			double pos0 = sim.ps.get(i)->pos[0];
			double pos1 = sim.ps.get(i)->pos[1];
			double pos2 = sim.ps.get(i)->pos[2];
			glTranslated(pos0, pos1, pos2);
			glutSolidSphere(4, 4, 4);
		}
		glPopMatrix();
	}
	
	glPopMatrix();

	glutSwapBuffers();
}

void resize(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, .1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		eye += ori * accel;
		break;
	case 's':
		eye -= ori * accel;
		break;
	case 'a':
		eye -= right * accel;
		break;
	case 'd':
		eye += right * accel;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void Timer(int unused)
{
	if (play){
		sim.euler_step(timeStep * 0.001);
	}

	glutPostRedisplay();
	glutTimerFunc(timeStep, Timer, 0);
}

int main(int argc, char** argv) {
	std::vector<Particle *>ps;
	std::vector<Force *>fs;
	for(int i = 0; i < 100; i++){
		ps.push_back(new Particle(Eigen::Vector3d((i%10) * 10, 0, (i/10) * 10), Eigen::Vector3d(0, 100, 0), Eigen::Vector3d(0, 0, 0), i%10 + i/10 + 1));
	}
	fs.push_back(new Gravity(ps, Eigen::Vector3d(0, -10, 0)));
	fs.push_back(new ConstantF(ps, Eigen::Vector3d(5, 0, 0)));
	for(int i = 0; i < 25; i++){
		fs.push_back(new Spring(ps[i*4], ps[i*4 + 1], 3, 10, 0.1));
	}
	
	for(Particle *p : ps)
		sim.add_particle(p);
	
	for(Force *f : fs)
		sim.add_force(f);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 0);
	glutCreateWindow("Particle Dynamics");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(timeStep, Timer, 0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);

	glutMainLoop();

	return 0;
}