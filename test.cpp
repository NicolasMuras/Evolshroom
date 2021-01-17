///////////////////////////////////////////////////////////////
// moveSphere.cpp
//
// This program allows the user to move a sphere to demonstrate
// distortion at the edges of the viewing frustum.
//
// Interaction:
// Press the arrow keys to move the sphere.
// Press the space bar to rotate the sphere..
// Press r to reset.
//
// Sumanta Guha.
///////////////////////////////////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#define PI 3.14159265358979324
// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.
static float X = 0.0; // X-coordinate of center of circle.
static float Y = 0.0; // Y-coordinate of center of circle.
static float Radio = 0.4;
static int numVertices = 5;
static int y_segments = 1;
static float z_height = 0.1;

// Drawing routine.
void drawScene(void)
{
	float t = 0; // Angle parameter.
	float t_90 = 0;
	int i;
	int j;
	float eje_x = 0;
	float eje_y = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();        
	// Set the position of the sphere.
	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numVertices; ++i)
	{
		glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		eje_x = X + Radio * cos(t);
		eje_y = Y + Radio * sin(t);

		// CAP
		glVertex3f(0.0, 0.0, 0.2);
		glVertex3f(X + Radio * cos(t), Y + Radio * sin(t), 0.0);
		glVertex3f(X + Radio * cos(t + 2 * PI / numVertices), Y + Radio * sin(t + 2 * PI / numVertices), 0.0);

		// Y SEGMENT STARTUP 
		glVertex3f(eje_x, eje_y, 0.0);
		glVertex3f(X + (Radio * 1.2) * cos(t), Y + (Radio * 1.2) * sin(t), -0.2);
		glVertex3f(X + (Radio * 1.2) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.2) * sin(t + 2 * PI / numVertices), -0.2);

		glVertex3f(X + Radio * cos(t + 2 * PI / numVertices), Y + Radio * sin(t + 2 * PI / numVertices), 0.0);
		glVertex3f(eje_x, eje_y, 0.0);
		glVertex3f(X + (Radio * 1.2) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.2) * sin(t + 2 * PI / numVertices), -0.2);
		// Y SEGMENTS

		for (j = 0; j < y_segments; ++j)
		{
			glColor3f( j * 0.05,j * 0.1 , j * 0.2);
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t), Y + (Radio * (1.4 + j * 0.2)) * sin(t), -0.4 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.4 + (j * -0.2));

			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.2 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.4 + (j * -0.2));
		}


		t += 2 * PI / numVertices;
		t_90 += 0.5 * PI / y_segments;

		/*glColor3f(0.0, 1.0, 1.0);
		// Y SEGMENTS
		glVertex3f(X + (Radio * 1.2) * cos(t), Y + (Radio * 1.2) * sin(t), -0.2);
		glVertex3f(X + (Radio * 1.4) * cos(t), Y + (Radio * 1.4) * sin(t), -0.4);
		glVertex3f(X + (Radio * 1.4) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.4) * sin(t + 2 * PI / numVertices), -0.4);

		glVertex3f(X + (Radio * 1.2) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.2) * sin(t + 2 * PI / numVertices), -0.2);
		glVertex3f(X + (Radio * 1.2) * cos(t), Y + (Radio * 1.2) * sin(t), -0.2);
		glVertex3f(X + (Radio * 1.4) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.4) * sin(t + 2 * PI / numVertices), -0.4);

		glColor3f(1.0, 0.0, 0.0);
		// Y SEGMENTS
		glVertex3f(X + (Radio * 1.4) * cos(t), Y + (Radio * 1.4) * sin(t), -0.4);
		glVertex3f(X + (Radio * 1.6) * cos(t), Y + (Radio * 1.6) * sin(t), -0.6);
		glVertex3f(X + (Radio * 1.6) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.6) * sin(t + 2 * PI / numVertices), -0.6);
		
		glVertex3f(X + (Radio * 1.4) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.4) * sin(t + 2 * PI / numVertices), -0.4);
		glVertex3f(X + (Radio * 1.4) * cos(t), Y + (Radio * 1.4) * sin(t), -0.4);
		glVertex3f(X + (Radio * 1.6) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.6) * sin(t + 2 * PI / numVertices), -0.6);

		glColor3f(0.3, 0.3, 0.4);
		// Y SEGMENTS
		glVertex3f(X + (Radio * 1.6) * cos(t), Y + (Radio * 1.6) * sin(t), -0.6);
		glVertex3f(X + (Radio * 1.8) * cos(t), Y + (Radio * 1.8) * sin(t), -0.8);
		glVertex3f(X + (Radio * 1.8) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.8) * sin(t + 2 * PI / numVertices), -0.8);

		glVertex3f(X + (Radio * 1.6) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.6) * sin(t + 2 * PI / numVertices), -0.6);
		glVertex3f(X + (Radio * 1.6) * cos(t), Y + (Radio * 1.6) * sin(t), -0.6);
		glVertex3f(X + (Radio * 1.8) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.8) * sin(t + 2 * PI / numVertices), -0.8);

		glColor3f(0.1, 0.7, 0.2);
		// Y SEGMENTS
		glVertex3f(X + (Radio * 1.8) * cos(t), Y + (Radio * 1.8) * sin(t), -0.8);
		glVertex3f(X + (Radio * 2) * cos(t), Y + (Radio * 2) * sin(t), -1);
		glVertex3f(X + (Radio * 2) * cos(t + 2 * PI / numVertices), Y + (Radio * 2) * sin(t + 2 * PI / numVertices), -1);

		glVertex3f(X + (Radio * 1.8) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.8) * sin(t + 2 * PI / numVertices), -0.8);
		glVertex3f(X + (Radio * 1.8) * cos(t), Y + (Radio * 1.8) * sin(t), -0.8);
		glVertex3f(X + (Radio * 2) * cos(t + 2 * PI / numVertices), Y + (Radio * 2) * sin(t + 2 * PI / numVertices), -1);*/


	}

	glEnd();

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
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
		y_segments++;
		glutPostRedisplay();
		break;
	case 'o':
		y_segments--;
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
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("moveSphere.cpp");
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
