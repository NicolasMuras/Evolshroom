// test
#include "builder_class.h"
#include <iostream>
#include <stdexcept>

#define PI 3.14159265358979324
using namespace std;

BuilderClass::BuilderClass(int &vertexquantity, float &radio, float &X, float &Y, int &y_segments)
{
	setLocation();
}


void BuilderClass::setLocation() 
{
	location[0] = 0;
	location[1] = 0;
}

std::vector<float> BuilderClass::getLocation() const {
	return location;
}

std::vector<float> BuilderClass::getCircle(int id) const {
	return circles;
}

void BuilderClass::buildTrunk(int &numVertices, float &Radio, float &X, float &Y)
{
	float t = 0; // Angle parameter.
	float Z = 0.1;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 1; i < numVertices; ++i)
	{
		buildCircle(numVertices, (Radio * (cos(t))), X, Y, (Z * i));
		if (i < 8) // Hace mas ancho los primeros 8 circulos
		{
			t += 0.4 * PI / 8;
		}
		if (i > 20 && i < 25)
		{
			t += 0.2 * PI / 8;
		}
	}
}

void BuilderClass::buildCircle(int &numVertices, float Radio, float &X, float &Y, float Z)
{

	float t = 0; // Angle parameter.
	int i;

	// Draw a line loop with vertices at equal angles apart on a circle
	// with center at (X, Y) and radius R, The vertices are colored randomly.
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < numVertices; ++i)
	{
		glColor3f(1.0 * Z,0.0,0.0);
		glVertex3f(X + Radio * cos(t), Y + Radio * sin(t), Z);
		t += 2 * PI / numVertices;
	}
	glEnd();
	glFlush();
}

void BuilderClass::buildCap(int &numVertices, float &Radio, float &X, float &Y, int &y_segments)
{
	float t = 0; // Angle parameter.
	float t_90 = 0;
	int i;
	int j;
	float eje_x = 0;
	float eje_y = 0;

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


		// Y SEGMENTS pow((j * 0.2), PI)))

		for (j = 0; j < y_segments; ++j)
		{
			glColor3f(j * 0.05, j * 0.1, j * 0.2);
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t), Y + (Radio * (1.4 + j * 0.2)) * sin(t), -0.4 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.4 + (j * -0.2));

			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.2 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), -0.2 + (j * -0.2));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), -0.4 + (j * -0.2));
		}
		t += 2 * PI / numVertices;
		t_90 += 0.5 * PI / y_segments;
	}
	glEnd();
}
