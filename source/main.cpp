#include <iostream>
#include "builder_class.h"

#define PI 3.14159265358979324
// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.
static float X = 0.0; // X-coordinate of center of circle.
static float Y = 0.0; // Y-coordinate of center of circle.
static float X_2 = 1.0; // X-coordinate of center of circle.
static float Y_2 = 1.0; // Y-coordinate of center of circle.
static float Radio = 0.3;
static int numVertices = 5;
static int y_segments = 1;
static float z_height = 0.1;

BuilderClass hongo_1(Radio, X, Y);

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	// Set the position of the sphere.
	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);
	
	hongo_1.showMushroom();

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		numVertices++;
		glutPostRedisplay();
		break;
	case '-':
		if (numVertices > 3) numVertices--;
		glutPostRedisplay();
		break;
	case 'p':
		hongo_1.buildShroom(hongo_1.stage, Radio, X, Y);
		glutPostRedisplay();
		break;
	case 'r':
		Xvalue = Yvalue = Angle = 0.0;
		glutPostRedisplay();
		break;
	case ' ':
		Angle += 10.0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) Yvalue += 0.1;
	if (key == GLUT_KEY_DOWN) Yvalue -= 0.1;
	if (key == GLUT_KEY_LEFT) Xvalue -= 0.1;
	if (key == GLUT_KEY_RIGHT) Xvalue += 0.1;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the arrow keys to move the sphere." << std::endl
		<< "Press the space bar to rotate the sphere." << std::endl
		<< "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Evolshroom.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// Register the callback function for non-ASCII key entry.
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
