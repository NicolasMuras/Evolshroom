#include <iostream>
#include "scene_class.h"
#include "builder_class.h"
#include <random>
#include <time.h>
#include "SOIL2.h"

// Globals.

#define VERTICES 0
#define INDICES 1
#define SHROOM 0
#define CAP 1

static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.
static char guidesMode = 'a';
static int width, height; // OpenGL window size.

static unsigned int stripIndices[15][3000] = { 0 };
static unsigned int stripIndicesCap[15][1500] = { 0 };
static unsigned int vao[15][2]; // Array of VAO ids.
static unsigned int buffer[15][2]; // Array of buffer ids.

Scene scene_1(1, 1);
Strain selected_strain(1);
GLuint textures[10] = { 1 };

void writeStrokeString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
void drawText()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glWindowPos2i(30, 112);

	std::string s = selected_strain.getName();
	int n = s.length();
	char buffer[30];
	memset(buffer, 0, 30);
	strcpy_s(buffer, sizeof(s), s.c_str());

	writeStrokeString(GLUT_BITMAP_HELVETICA_18, (char *)buffer);
	glColor3f(1.0f, 0.2f, 0.1f);
	glWindowPos2i(30, 87);

	s = selected_strain.getBiome();
	n = s.length();
	memset(buffer, 0, 30);
	strcpy_s(buffer, sizeof(s), s.c_str());

	writeStrokeString(GLUT_BITMAP_HELVETICA_18, (char *)buffer);
}
GLuint textureInit(const char* image_path)
{
	// TEXTURE INIT
	int image_width = 0;
	int image_height = 0;

	unsigned char* image = SOIL_load_image(image_path, &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE_LOADING_FAILED" << "\n";
	}
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texture0;
}
void drawStars(int calification)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	for (int i = 0; i < calification; i++)
	{
		glBegin(GL_QUADS);
		glColor3f(255, 255, 255);
		glTexCoord2f(0, 1);
		glVertex2f(100 + (i * 50), 10);
		glTexCoord2f(0, 0);
		glVertex2f(100 + (i * 50), 50);
		glTexCoord2f(1, 0);
		glVertex2f(140 + (i * 50), 50);
		glTexCoord2f(1, 1);
		glVertex2f(140 + (i * 50), 10);
		glTexCoord2f(0, 1);
		glEnd();
	}
}
void drawHUD(void)
{
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (textures[0] == 1)  // Load textures once time
	{
		textures[0] = textureInit("hud/hud.png");
		textures[1] = textureInit("hud/star.png");
	}

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);

	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);
	glTexCoord2f(0, 0);
	glVertex2f(0, 150);
	glTexCoord2f(1, 0);
	glVertex2f(1000, 150);
	glTexCoord2f(1, 1);
	glVertex2f(1000, 0);
	glTexCoord2f(0, 1);

	glEnd();

	drawStars(selected_strain.getID());

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void guideMode()
{
	if (guidesMode == 'a')
	{
		// Shows the guides
		for (int i = 0; i < scene_1.Mushrooms_ID.size(); i++)
		{
			scene_1.Mushrooms_ID[i].showGuides();
		}
	}

}
void fillIndices(std::vector<unsigned int> index, bool mode, int array_id)
{

	if (mode == 1)
	{
		for (int i = 0; i < index.size(); i++)
		{
			stripIndices[array_id][i] = index[i];
		}
	}
	else if (mode == 0)
	{
		for (int i = 0; i < index.size(); i++)
		{
			stripIndicesCap[array_id][i] = index[i];
		}
	}

}
void updateShrooms()
{
	for (int i = 0; i < scene_1.Mushrooms_ID.size(); i++)
	{

		glBindVertexArray(vao[i][SHROOM]);

		glBindBuffer(GL_ARRAY_BUFFER, buffer[i][VERTICES]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].circle_group) + sizeof(scene_1.Mushrooms_ID[i].colors_group), &scene_1.Mushrooms_ID[i].circle_group[0], GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].circle_group), scene_1.Mushrooms_ID[i].circle_group);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i][INDICES]);
		fillIndices(scene_1.Mushrooms_ID[i].getIndices(), 1, i);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices[i]), stripIndices[i], GL_DYNAMIC_DRAW);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);



		glBindVertexArray(vao[i][CAP]);

		glBindBuffer(GL_ARRAY_BUFFER, buffer[i][VERTICES]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].cap_group) + sizeof(scene_1.Mushrooms_ID[i].cap_colors), &scene_1.Mushrooms_ID[i].cap_group[0], GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].cap_group), scene_1.Mushrooms_ID[i].cap_group);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i][INDICES]);
		fillIndices(scene_1.Mushrooms_ID[i].getCapIndices(), 0, i);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndicesCap[i]), stripIndicesCap[i], GL_DYNAMIC_DRAW);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glDrawElements(GL_TRIANGLES, 1500, GL_UNSIGNED_INT, 0);

	}
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glLoadIdentity();

	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);


	updateShrooms();
	guideMode();
	drawHUD();
	drawText();



	glutSwapBuffers();
	glutPostRedisplay();
}

// Initialization routine.
void setup(int i)
{
	glGenVertexArrays(2, vao[i]); // Generate VAO ids.

	// BEGIN bind VAO id vao[SHROOM] to the set of vertex array calls following.
	glBindVertexArray(vao[i][SHROOM]);

	glGenBuffers(2, buffer[i]);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[i][VERTICES]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].circle_group) + sizeof(scene_1.Mushrooms_ID[i].colors_group), &scene_1.Mushrooms_ID[i].circle_group[0], GL_DYNAMIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].circle_group), scene_1.Mushrooms_ID[i].circle_group);

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].circle_group), sizeof(scene_1.Mushrooms_ID[i].colors_group), scene_1.Mushrooms_ID[i].colors_group);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i][INDICES]);
	fillIndices(scene_1.Mushrooms_ID[i].getIndices(), 1, i);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices[i]), stripIndices[i], GL_DYNAMIC_DRAW);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(scene_1.Mushrooms_ID[i].circle_group)));
	// END bind VAO id vao[SHROOM].

	// -----------------------------------------------------------------------------------------------------------------------------------------------
	// BEGIN bind VAO id vao[TRIANGLE] to the set of vertex array calls following.
	glBindVertexArray(vao[i][CAP]);
	glGenBuffers(2, buffer[i]);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[i][VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].cap_group) + sizeof(scene_1.Mushrooms_ID[i].cap_colors), &scene_1.Mushrooms_ID[i].cap_group[0], GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scene_1.Mushrooms_ID[i].cap_group), scene_1.Mushrooms_ID[i].cap_group);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scene_1.Mushrooms_ID[i].cap_group), sizeof(scene_1.Mushrooms_ID[i].cap_colors), scene_1.Mushrooms_ID[i].cap_colors);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i][INDICES]);
	fillIndices(scene_1.Mushrooms_ID[i].getCapIndices(), 0, i);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndicesCap[i]), stripIndicesCap[i], GL_DYNAMIC_DRAW);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(scene_1.Mushrooms_ID[i].cap_group)));
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
		scene_1.newMushroom(selected_strain);
		setup(scene_1.Mushrooms_ID.size() - 1);
		glutPostRedisplay();
		break;
	case 's':
		if (guidesMode == 'a')
		{
			guidesMode = 'b';
		}
		else if (guidesMode == 'b')
		{
			guidesMode = 'a';
		}
		glutPostRedisplay();
		break;
	case 'p':
		for (int i = 0; i < scene_1.total_entities; ++i)
		{
			scene_1.Mushrooms_ID[i].buildShroom();
		}
		glutPostRedisplay();
		break;
	case '1':
		selected_strain.selectStrain(1);
		selected_strain.selectFungi(1);
		selected_strain.selectSpecie(1);
		break;
	case '2':
		selected_strain.selectStrain(2);
		selected_strain.selectFungi(2);
		selected_strain.selectSpecie(2);
		break;
	case '3':
		selected_strain.selectStrain(3);
		selected_strain.selectFungi(3);
		selected_strain.selectSpecie(3);
		break;
	case '4':
		selected_strain.selectStrain(4);
		selected_strain.selectFungi(4);
		selected_strain.selectSpecie(4);
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

// Main routine.
int main(int argc, char **argv)
{
	Angle += 240.0;
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
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glutMainLoop();
}
