// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// 实验报告里面多写点感想，即对函数的理解，以及调用的顺序，步骤等。思考为什么是这样子调用的，为什么参数是这样子设置的？。。。等等你觉得值得研究的问题。
#include <stdlib.h>
#include "glut.h"

#define X 0
#define Y 1
#define Z 2

float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f
float fTpRtt = 0.0f;

bool bPersp = false;
bool bAnim = false;
bool bRtt = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };
float target[] = { 0, 0, 0 };
//todo; hint: you may need another ARRAY when you operate the teapot

//todo
//hint: some additional parameters may needed here when you operate the teapot

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	// 在这个函数范围内，横x深y纵z
	// teapot
	glPushMatrix();
	glTranslatef(target[0], target[1], target[2]);
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0); // notice the rotation here, you may have a TRY removing this line to see what it looks like.
	// 以下横x纵y深z
	// hint: when operate the teapot, you may need to change some parameters
	glRotatef(fTpRtt, 0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glPopMatrix();

	// table
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	// leg1
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	// leg2
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	// leg3
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	// leg4
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp) {
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {//hint: eye[] and center[] are the keys to solve the problems
		eye[X] -= 0.1;
		center[X] -= 0.1;
		break;
	}
	case 'd': {
		eye[X] += 0.1;
		center[X] += 0.1;
		break;
	}
	case 'w': {
		eye[Y] += 0.1;
		center[Y] += 0.1;
		break;
	}
	case 's': {
		eye[Y] -= 0.1;
		center[Y] -= 0.1;
		break;
	}
	case 'z': {
		eye[Z] -= 0.2;
		center[Z] -= 0.2;
		break;
	}
	case 'c': {
		eye[Z] += 0.2;
		center[Z] += 0.2;
		break;
	}

			  //茶壶相关操作
	case 'l': {//hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		if (target[X] <= 2) {
			target[X] += 0.2;
		}
		break;
	}
	case 'j': {
		if (target[X] >= -2) {
			target[X] -= 0.2;
		}
		break;
	}
	case 'i': {
		if (target[Y] <= 1.5) {
			target[Y] += 0.2;
		}
		break;
	}
	case 'k': {
		if (target[Y] >= -1.5) {
			target[Y] -= 0.2;
		}
		break;
	}
	case 'e': {
		bRtt = !bRtt;
		break;
	}
	}
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[X], eye[Y], eye[Z],
		center[X], center[Y], center[Z],
		0, 1, 0);				// 场景（0，0，8）的视点中心（0, 0, 0），Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();							// Draw Scene

	if (bAnim) fRotate += 0.5f;
	if (bRtt) fTpRtt += 0.5f;
	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}