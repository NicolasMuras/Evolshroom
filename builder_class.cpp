#include "builder_class.h"
#include <iostream>
#include <stdexcept>

#define PI 3.14159265358979324
using namespace std;

BuilderClass::BuilderClass(int &vertexquantity, float &radio, float &X, float &Y, int &y_segments)
{
	//setLocation();
}

void BuilderClass::setStage(int value)
{
	this->stage = value;
}

int BuilderClass::getStage() const {
	return stage;
}

/*void BuilderClass::setLocation() 
{
	location[0] = 0;
	location[1] = 0;
}*/

/*float* BuilderClass::getLocation() const {
	return location;
}

float* BuilderClass::getCircle(int id) const {
	return circles;
}*/

void BuilderClass::showTrunk() const
{
	int i = 0;
	
	glClear(GL_COLOR_BUFFER_BIT);

	for (; i <= stage; ++i)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 20; ++j)
		{
			glColor3f(0.1 * this->stage, 0.0, 0.0);
			glVertex3f(circle_group[i][j][0], circle_group[i][j][1], circle_group[i][j][2]);
		}
		glEnd();
		glFlush();
	}
}

void BuilderClass::buildTrunk(int &stage, float &Radio, float &X, float &Y)
{
	float Z = 0.1;
	if (stage < 23)
	{
		if (stage < 8) // Decremento gradual del radio 1 - 8
		{
			trunk_curvation += 0.4 * PI / 8; // El "0.4" y el "8" ajusta la suavidad del decremento
		}
		if (stage > 20 && stage < 25) // Decremento gradual del radio 20 - 25
		{
			trunk_curvation += 0.2 * PI / 8;
		}
		float curved_radio = Radio * (cos(trunk_curvation));

		buildCircle(stage, curved_radio, X, Y, (Z * stage));

		setStage(getStage() + 1);
	}
	else 
	{
		std::cout << "No se puede agregar mas circulos\n";
	}
}

void BuilderClass::buildCircle(int &stage, float Radio, float &X, float &Y, float Z)
{

	float t = 0; // Angle parameter.

	for (int i = 0; i < vertex_quantity; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				circle_group[stage][i][j] = X + Radio * cos(t);
			}
			else if(j == 1)
			{
				circle_group[stage][i][j] = Y + Radio * sin(t);
			}
			else 
			{
				circle_group[stage][i][j] = Z;
			}

		}
		t += 2 * PI / vertex_quantity;
	}
}

void BuilderClass::deleteCircle()
{

	for (int i = 0; i < vertex_quantity; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				circle_group[stage][i][j] = 0;
			}
			else if (j == 1)
			{
				circle_group[stage][i][j] = 0;
			}
			else
			{
				circle_group[stage][i][j] = 0;
			}

		}
	}
	setStage(getStage() - 1);
}

void BuilderClass::buildCapCircles(int &stage, float &Radio, float &X, float &Y)
{
	float Z = 0.1;
	if (stage < 23)
	{
		if (stage < 8) // Decremento gradual del radio 1 - 8
		{
			trunk_curvation += 0.4 * PI / 8; // El "0.4" y el "8" ajusta la suavidad del decremento
		}
		if (stage > 20 && stage < 25) // Decremento gradual del radio 20 - 25
		{
			trunk_curvation += 0.2 * PI / 8;
		}
		float curved_radio = Radio * (cos(trunk_curvation));

		buildCircle(stage, curved_radio, X, Y, (Z * stage));

		setStage(getStage() + 1);
	}
	else
	{
		std::cout << "No se puede agregar mas circulos\n";
	}
}

void BuilderClass::buildCap(int &stage, float &Radio, float &X, float &Y, int &numVertices)
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
		glVertex3f(0.0, 0.0, 0.2 + stage * 0.1);
		glVertex3f(X + Radio * cos(t), Y + Radio * sin(t), stage * 0.1);
		glVertex3f(X + Radio * cos(t + 2 * PI / numVertices), Y + Radio * sin(t + 2 * PI / numVertices), stage * 0.1);

		// Y SEGMENT STARTUP 
		glVertex3f(eje_x, eje_y, stage * 0.1);
		glVertex3f(X + (Radio * 1.2) * cos(t), Y + (Radio * 1.2) * sin(t), -0.1 + stage * 0.1);
		glVertex3f(X + (Radio * 1.2) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.2) * sin(t + 2 * PI / numVertices), -0.1 + stage * 0.1);

		glVertex3f(X + Radio * cos(t + 2 * PI / numVertices), Y + Radio * sin(t + 2 * PI / numVertices), stage * 0.1);
		glVertex3f(eje_x, eje_y, stage * 0.1);
		glVertex3f(X + (Radio * 1.2) * cos(t + 2 * PI / numVertices), Y + (Radio * 1.2) * sin(t + 2 * PI / numVertices), -0.1 + stage * 0.1);

		t += 2 * PI / numVertices;

		// Y SEGMENTS pow((j * 0.2), PI)))

		/*for (j = 0; j < y_segments; ++j)
		{
			glColor3f(j * 0.05, j * 0.1, j * 0.2);
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), numVertices * 0.1 + (j * -0.1));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t), Y + (Radio * (1.4 + j * 0.2)) * sin(t), (-0.1 + numVertices * 0.1) + (j * -0.1));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), (-0.1 + numVertices * 0.1) + (j * -0.1));

			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.2 + j * 0.2)) * sin(t + 2 * PI / numVertices), numVertices * 0.1 + (j * -0.1));
			glVertex3f(X + (Radio * (1.2 + j * 0.2)) * cos(t), Y + (Radio * (1.2 + j * 0.2)) * sin(t), numVertices * 0.1 + (j * -0.1));
			glVertex3f(X + (Radio * (1.4 + j * 0.2)) * cos(t + 2 * PI / numVertices), Y + (Radio * (1.4 + j * 0.2)) * sin(t + 2 * PI / numVertices), (-0.1 + numVertices * 0.1) + (j * -0.1));
		}*/
		
		//t_90 += 0.5 * PI / y_segments;
	}
	glEnd();
}
