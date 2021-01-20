#include "builder_class.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <time.h>
#define PI 3.14159265358979324
using namespace std;

BuilderClass::BuilderClass(float &radio, float &X, float &Y)
{
	setRandomCurvation();
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

void BuilderClass::showMushroom() const
{
	
	
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i <= stage; ++i)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(0.1 * this->stage, 0.0, 0.0);
		for (int j = 0; j < 20; ++j)
		{
			glVertex3f(circle_group[i][j][0], circle_group[i][j][1], circle_group[i][j][2]);
		}
		glEnd();
		glFlush();
	}
	
	for (int k = 0; k < 12; ++k)
	{
		
		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.1 * this->stage);
		for (int j = 0; j < 20; ++j)
		{
			if (k > 11) {
				continue;
			}
			glVertex3f(cap_group[k][j][0], cap_group[k][j][1], cap_group[k][j][2]);

		}
		glEnd();
		glFlush();
	}

}

void BuilderClass::translateCircle(int group)
{
	if (group == 1)
	{
		for (int i = 0; i < 12; ++i) // This move translate the cap in Z, this way we can simulate the grow movement
		{
			for (int j = 0; j < 20; ++j)
			{
				cap_group[i][j][2] += 0.1;
			}
		}
	}
	else if (group == 2) 
	{
		for (int i = 0; i < stage; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				circle_group[i][j][2] += 0.1;
			}
		}
	}
	else 
	{
		std::cout << "Invalid group \n";
	}

}

void BuilderClass::buildShroom(int &stage, float &Radio, float &X, float &Y)
{
	if (stage == 0)
	{
		for (int circle_stage = 0; circle_stage < 12; circle_stage++)
		{
			buildCapCircles(circle_stage, Radio, X, Y);
		}
		
	}
	if (stage < 23)
	{
		buildTrunk(stage, Radio, X, Y);
		setStage(getStage() + 1);
		translateCircle(1);
	}
	else 
	{
		std::cout << "No se puede agregar mas circulos\n";
	}
	
}

void BuilderClass::setRandomCurvation()
{
	curvation_start = getRandomInt(1, 9);
	std::cout << "curvation_start: " << curvation_start << '\n';
	curvation_end = getRandomInt(10, 23);
	std::cout << "curvation_end: " << curvation_end << '\n';
	curvation_direction = getRandomInt(0, 1);
	std::cout << "curvation_direction: " << curvation_direction << '\n';


	root_curvation_end = getRandomInt(2, 9);
	std::cout << "root_curvation_end: " << root_curvation_end << '\n';
	trunk_curvation_start = getRandomInt(root_curvation_end, 9);
	std::cout << "trunk_curvation_start: " << trunk_curvation_start << '\n';
	trunk_curvation_end = getRandomInt(10, 23);
	std::cout << "trunk_curvation_end: " << trunk_curvation_end << '\n';
}

int BuilderClass::getRandomInt(int start, int end)
{
	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> uniform_dist(start, end);

	return uniform_dist(rng);
}

float BuilderClass::getRandomFloat(int start, int end)
{
	std::mt19937 rng(time(NULL));
	std::uniform_real_distribution<float> uniform_dist(start, end);
	return uniform_dist(rng);
}

void BuilderClass::buildTrunk(int &stage, float &Radio, float &X, float &Y)
{
	float Z = 0.1;
	if (stage < 23)
	{
		if (stage > curvation_start && stage < curvation_end) // Make curvation in the Y axis.
		{
			if (curvation_direction == 0) // Choose the direction
			{
				circle_translation -= ((curvation_end - curvation_start) / 10) * PI / (curvation_end - curvation_start);
			}
			else
			{
				circle_translation += ((curvation_end - curvation_start) / 10) * PI / (curvation_end - curvation_start);
			}
		}

		if (stage > curvation_end && stage < 23) // Reverse the curvation in the Y axis.
		{
			if (curvation_direction == 0) // Reverse direction.
			{
				circle_translation += ((23 - curvation_end) / 10) * PI / (23 - curvation_end);
			}
			else
			{
				circle_translation -= ((23 - curvation_end) / 10) * PI / (23 - curvation_end);
			}
		}

		if (stage < root_curvation_end) // Decremento gradual del radio en la raiz del hongo.
		{
			trunk_curvation += 0.4 * PI / (root_curvation_end); // El "0.4" y el "8" ajusta la suavidad del decremento, es ideal dividir PI por la cantidad de circulos que se veran afectado, este caso son 8 circulos.
		}

		if (stage > trunk_curvation_start && stage < trunk_curvation_end) // Decremento gradual del radio 20 - 23
		{
			if (Radio * (cos(trunk_curvation)) > (Radio / 6))
			{
				trunk_curvation += 0.1 * PI / (trunk_curvation_end - trunk_curvation_start);
			}
		}

		float curved_radio = Radio * (cos(trunk_curvation));
		float temp = Y + curved_radio * sin(circle_translation);
		buildCircle(stage, curved_radio, X, temp, (Z * stage));
	}
	else 
	{
		std::cout << "No se puede agregar mas circulos\n";
	}
}

void BuilderClass::buildCircle(int &stage, float Radio, float &X, float &Y, float Z)
{

	float t = 0; // Angle parameter.
	float inclination_y = 0;
	float inclination_z = 0;
	float angle = 0;

	static float rotation_var = 0;
	if (stage > curvation_start && stage < curvation_end)
	{
		if (curvation_direction == 0)
		{
			rotation_var -= 0.05;
		}
		else {
			rotation_var += 0.05;
		}
		
	}
	if (stage > curvation_end && stage < 23)
	{
		if (curvation_direction == 0)
		{
			rotation_var += 0.05;
		}
		else {
			rotation_var -= 0.05;
		}
	}

	for (int i = 0; i < vertex_quantity; ++i)
	{
		if (stage > curvation_start && stage < curvation_end)
		{
			inclination_y = (Radio) * (cos(circle_inclination));
			inclination_z = (Radio) * (sin(circle_inclination));
			angle = asin(inclination_z / Radio);

			if (curvation_direction == 0)
			{
				circle_inclination -= 2 * PI / 20;
			}
			else
			{
				circle_inclination += 2 * PI / 20;
			}
		}

		if (stage > curvation_end && stage < 23) 
		{
			inclination_y = (Radio) * (cos(circle_inclination));
			inclination_z = (Radio) * (sin(circle_inclination));
			angle = asin(inclination_z / Radio);
			if (curvation_direction == 0)
			{
				circle_inclination += 2 * PI / 20;
			}
			else
			{
				circle_inclination -= 2 * PI / 20;
			}
		}

		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				circle_group[stage][i][j] = X + Radio * cos(t);
			}
			else if(j == 1)
			{
				circle_group[stage][i][j] = (Y + Radio * sin(t));
			}
			else if(j == 2)
			{
				
				circle_group[stage][i][j] = Z + (inclination_z * rotation_var);
			}

		}
		
		t += 2 * PI / vertex_quantity;
	}
}

void BuilderClass::buildCapCircles(int &circle_stage, float &Radio, float &X, float &Y)
{
	float curved_radio;

	float Z = 0.05;

	if (circle_stage == 0) // Decremento gradual del radio 1 - 8
	{
		cap_curvation += 0.5 * PI / 4; // El "0.4" y el "8" ajusta la suavidad del decremento
		buildCapCircle(circle_stage, Radio / 2, X, Y, (Z * circle_stage));
	}
	if (circle_stage > 0 && circle_stage < 12) // Decremento gradual del radio 20 - 25
	{
		cap_curvation += 0.8 * PI / 11;
		curved_radio = Radio * (sin(cap_curvation));
		buildCapCircle(circle_stage, curved_radio, X, Y, (Z * circle_stage));
	}
	
}

void BuilderClass::buildCapCircle(int &circle_stage, float Radio, float &X, float &Y, float Z)
{

	float t = 0; // Angle parameter.

	for (int i = 0; i < vertex_quantity; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				cap_group[circle_stage][i][j] = X + Radio * cos(t);
			}
			else if (j == 1)
			{
				cap_group[circle_stage][i][j] = Y + Radio * sin(t);
			}
			else
			{
				cap_group[circle_stage][i][j] = Z;
			}

		}
		t += 2 * PI / vertex_quantity;
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
