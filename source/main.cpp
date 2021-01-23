#include <iostream>
#include "scene_class.h"
#include "builder_class.h"
#include <random>
#include <time.h>

#define PI 3.14159265358979324

#define VERTICES 0
#define INDICES 1
#define SHROOM 0
#define CAP 1

static unsigned int stripIndices[3000] = { 0 };
static unsigned int stripIndicesCap[1500] = { 0 };
// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.

static unsigned int vao[2]; // Array of VAO ids.
static unsigned int buffer[2]; // Array of buffer ids.

Scene scene_1(1, 1);

void fillIndices(std::vector<unsigned int> index, bool mode)
{
	
	if (mode == 1)
	{
		for (int i = 0; i < index.size(); i++)
		{
			stripIndices[i] = index[i];
		}
	}
	else if (mode == 0)
	{
		for (int i = 0; i < index.size(); i++)
		{
			stripIndicesCap[i] = index[i];
		}
	}

}
float getRandomFloat(float start, float end)
{
	std::mt19937 rng(time(NULL) * 15000);
	std::uniform_real_distribution<float> uniform_dist(start, end);
	return uniform_dist(rng);

}

void updateShrooms()
{
	for (int i = 0; i < scene_1.total_entities; ++i)
	{

		glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES + i]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].circle_group) + sizeof(scene_1.Mushrooms_ID[i].colors_group), &scene_1.Mushrooms_ID[i].circle_group[0], GL_DYNAMIC_DRAW);

		// Copy vertex coordinates data into first half of vertex buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].circle_group), scene_1.Mushrooms_ID[i].circle_group);

		// Bind and fill indices buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES + i]);
		fillIndices(scene_1.Mushrooms_ID[i].indices, 1);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_DYNAMIC_DRAW);

		// Enable two vertex arrays: co-ordinates and color.
		glEnableClientState(GL_VERTEX_ARRAY);

		// Specify vertex and color pointers to the start of the respective data.
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindVertexArray(vao[SHROOM + i]);
	}
}

void updateCaps()
{
	for (int i = 0; i < scene_1.Mushrooms_ID.size(); ++i)
	{
		// Bind vertex buffer and reserve space.
		glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES + i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].cap_group) + sizeof(scene_1.Mushrooms_ID[i].cap_colors), &scene_1.Mushrooms_ID[i].cap_group[0], GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].cap_group), scene_1.Mushrooms_ID[i].cap_group);

		// Bind and fill indices buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES + i]);
		fillIndices(scene_1.Mushrooms_ID[i].indices_cap, 0);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndicesCap), stripIndicesCap, GL_DYNAMIC_DRAW);

		// Enable two vertex arrays: co-ordinates and color.
		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindVertexArray(vao[CAP + i]);
	}
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);

	// Bind the vertex array oobject to set up our vertex buffers and index buffer
	
	updateShrooms();
	glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);

	updateCaps();
	glDrawElements(GL_TRIANGLES, 1500, GL_UNSIGNED_INT, 0);
	

	// Shows the guides
	/*for (int i = 0; i < scene_1.Mushrooms_ID.size(); i++)
	{
		scene_1.Mushrooms_ID[i].showMushroom();
	}*/
	
	glutSwapBuffers();

}

// Initialization routine.
void setup()
{

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glGenVertexArrays(2, vao); // Generate VAO ids.

	// BEGIN bind VAO id vao[SHROOM] to the set of vertex array calls following.
	glBindVertexArray(vao[SHROOM]);

	glGenBuffers(2, buffer);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[0].circle_group) + sizeof(scene_1.Mushrooms_ID[0].colors_group), &scene_1.Mushrooms_ID[0].circle_group[0], GL_DYNAMIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[0].circle_group), scene_1.Mushrooms_ID[0].circle_group);

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[0].circle_group), sizeof(scene_1.Mushrooms_ID[0].colors_group), scene_1.Mushrooms_ID[0].colors_group);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);
	fillIndices(scene_1.Mushrooms_ID[0].indices, 1);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_DYNAMIC_DRAW);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(scene_1.Mushrooms_ID[0].circle_group)));
	// END bind VAO id vao[SHROOM].
	// -----------------------------------------------------------------------------------------------------------------------------------------------
	// BEGIN bind VAO id vao[TRIANGLE] to the set of vertex array calls following.
	glBindVertexArray(vao[CAP]);
	glGenBuffers(2, buffer);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[0].cap_group) + sizeof(scene_1.Mushrooms_ID[0].cap_colors), &scene_1.Mushrooms_ID[0].cap_group[0], GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[0].cap_group), scene_1.Mushrooms_ID[0].cap_group);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[0].cap_group), sizeof(scene_1.Mushrooms_ID[0].cap_colors), scene_1.Mushrooms_ID[0].cap_colors);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);
	fillIndices(scene_1.Mushrooms_ID[0].indices_cap, 0);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndicesCap), stripIndicesCap, GL_DYNAMIC_DRAW);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(scene_1.Mushrooms_ID[0].cap_group)));
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		scene_1.newMushroom(getRandomFloat(0.2, 0.7), getRandomFloat(-1.0, 1.0), getRandomFloat(-1.0, 1.0), getRandomFloat(0.0, 0.3), getRandomFloat(0.0, 0.3), getRandomFloat(0.0, 0.3));
		setup();
		glutPostRedisplay();
		break;
	case 's':
		scene_1.Mushrooms_ID[0].showIndices();
		glutPostRedisplay();
		break;
	case 'p':
		for (int i = 0; i < scene_1.total_entities; ++i)
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
	std::cout << "Press the arrow keys to move around the scene." << std::endl
		<< "Press the space bar to rotate the scene." << std::endl
		<< "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	Angle += 240.0;
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

	

	glutMainLoop();
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------
