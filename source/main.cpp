#include <iostream>
#include "scene_class.h"
#include "builder_class.h"
#include <random>
#include <time.h>
#define PI 3.14159265358979324
// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.

Scene scene_1(1, 1);
float getRandomFloat(float, float);
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	// Set the position of the sphere.
	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);

	for (int i = 0; i < scene_1.Mushrooms_ID.size(); i++)
	{
		scene_1.Mushrooms_ID[i].showMushroom();
	}
	
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
		scene_1.newMushroom(getRandomFloat(0.2, 0.7), getRandomFloat(-1.0, 1.0), getRandomFloat(-1.0, 1.0));
		glutPostRedisplay();
		break;
	case 'p':
		for (int i = 0; i < scene_1.Mushrooms_ID.size(); ++i)
		{
			scene_1.Mushrooms_ID[i].buildShroom();
		}

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

float getRandomFloat(float start, float end)
{
	std::mt19937 rng(time(NULL) * 15000);
	std::uniform_real_distribution<float> uniform_dist(start, end);
	return uniform_dist(rng);
}
