#include "builder_class.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <time.h>
#define PI 3.14159265358979324
using namespace std;

BuilderClass::BuilderClass(float radio, float X, float Y)
{
	setLocation(radio, X, Y);
	setRandomVars();
}

void BuilderClass::setStage(int value)
{
	stage = value;
}

int BuilderClass::getStage() const {
	return stage;
}

void BuilderClass::setLocation(float radio, float x, float y) 
{
	X_Loc = x;
	Y_Loc = y;
	Radio_Loc = radio;
}

void BuilderClass::setRandomVars() // Set variables that generate variations on the mushroom geometry
{
	std::cout << "----------------------- MUSHROOM-INFO ----------------------- \n";

	max_stage = getRandomInt(18, 25);
	std::cout << "max_stage: " << max_stage << '\n';

	root_curvation_end = getRandomInt(2, 9);
	std::cout << "root_curvation_end: " << root_curvation_end << '\n';

	curvation_start = getRandomInt(2, 9);
	std::cout << "curvation_start: " << curvation_start << '\n';
	if (curvation_start > 7)
	{
		curvation_end = getRandomInt((max_stage/2), max_stage);
	}
	else {
		curvation_end = getRandomInt((max_stage/2) - 4, max_stage);
	}
	std::cout << "curvation_end: " << curvation_end << '\n';

	curvation_direction = getRandomInt(0, 1);
	std::cout << "curvation_direction: " << curvation_direction << '\n';

	trunk_curvation_start = curvation_start;
	std::cout << "trunk_curvation_start: " << trunk_curvation_start << '\n';
	trunk_curvation_end = curvation_end;
	std::cout << "trunk_curvation_end: " << trunk_curvation_end << '\n';

	curvature_size = getRandomFloat(1, 2);
	std::cout << "curvature_size: " << curvature_size << '\n';

	min_trunk_width = getRandomFloat(3, 8);
	std::cout << "min_trunk_width: " << min_trunk_width << '\n';

	cap_flatness = getRandomFloat(3, 7) / 100;
	std::cout << "cap_flatness: " << cap_flatness << '\n';

	std::cout << "------------------------------------------------------------- \n";
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

void BuilderClass::showMushroom() const  // Draw the mushroom in the window
{
	for (int i = 0; i <= getStage(); ++i)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(0.1 * getStage(), 0.0, 0.0);
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
		glColor3f(0.0, 0.0, 0.1 * getStage());
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

void BuilderClass::buildShroom() // Build shrooms main function
{
	if (getStage() == 0)
	{
		for (int circle_stage = 0; circle_stage < 12; circle_stage++)
		{
			buildCapCircles(circle_stage);
		}
		
	}
	if (getStage() < max_stage)
	{
		buildTrunk();
		setStage(getStage() + 1);
	}
	
}

void BuilderClass::buildTrunk() // Implement random generated vars to build the shroom.
{
	float Z = 0.1; // Height multiplicator.
	if (getStage() < max_stage)
	{
		if (getStage() > curvation_start && getStage() < curvation_end) // Make translation in the circles of the trunk.
		{
			if (curvation_direction == 0) // Choose the direction
			{
				circle_translation -= ((curvation_end - curvation_start) / 10) * PI / (curvation_end - curvation_start) * curvature_size;
			}
			else
			{
				circle_translation += ((curvation_end - curvation_start) / 10) * PI / (curvation_end - curvation_start) * curvature_size;
			}
		}

		if (getStage() > curvation_end && getStage() < max_stage) // Reverse the translation in the circles of the trunk.
		{
			if (curvation_direction == 0) // Reverse direction.
			{
				circle_translation += ((max_stage - curvation_end) / 10) * PI / (23 - curvation_end) * curvature_size;
			}
			else
			{
				circle_translation -= ((max_stage - curvation_end) / 10) * PI / (23 - curvation_end) * curvature_size;
			}
		}

		if (getStage() < root_curvation_end) // Decremento gradual del radio en la raiz del hongo.
		{
			trunk_curvation += 0.4 * PI / (root_curvation_end); // El "0.4" y el "8" ajusta la suavidad del decremento, es ideal dividir PI por la cantidad de circulos que se veran afectado, este caso son 8 circulos.
		}

		if (getStage() > trunk_curvation_start && getStage() < trunk_curvation_end) // Decremento gradual del radio 20 - 23
		{
			if (Radio_Loc * (cos(trunk_curvation)) > (Radio_Loc / min_trunk_width))
			{
				trunk_curvation += 0.1 * PI / (trunk_curvation_end - trunk_curvation_start);
			}
		}

		float curved_translation_y = Y_Loc + Radio_Loc * (cos(trunk_curvation)) * sin(circle_translation);
		float curved_translation_x = X_Loc + Radio_Loc * (cos(trunk_curvation)) * cos(circle_translation);

		buildCircle(curved_translation_y, curved_translation_x,(Z * getStage()));
	}
}

void BuilderClass::buildCircle(float curved_translation_y, float curved_translation_x, float Z) // Build the circle with the current curved radius and translations.
{

	float angle = 0; // Angle parameter.
	//float inclination_y = 0;
	float inclination_z = 0;
	float Radio = Radio_Loc * (cos(trunk_curvation));
	static float rotation_var = 0;

	if (getStage() > curvation_start && getStage() < curvation_end)
	{
		if (curvation_direction == 0)
		{
			rotation_var -= 0.015;
		}
		else {
			rotation_var += 0.015;
		}
		
	}
	else if (getStage() > curvation_end && getStage() < max_stage)
	{
		if (curvation_direction == 0)
		{
			rotation_var += 0.015;
		}
		else {
			rotation_var -= 0.015;
		}
	}

	for (int i = 0; i < vertex_quantity; ++i)
	{
		if (getStage() > curvation_start && getStage() < curvation_end)
		{

			//inclination_y = (Radio) * (cos(circle_inclination));
			inclination_z = (Radio) * (sin(circle_inclination));

			if (curvation_direction == 0)
			{
				circle_inclination -= 2 * PI / 20;
			}
			else
			{
				circle_inclination += 2 * PI / 20;
			}
		}
		else if (getStage() > curvation_end && getStage() < max_stage)
		{
			//inclination_y = (Radio) * (cos(circle_inclination));
			inclination_z = (Radio) * (sin(circle_inclination));
			
			if (curvation_direction == 0)
			{
				circle_inclination += 2 * PI / 20;
			}
			else
			{
				circle_inclination -= 2 * PI / 20;
			}
		}

		// Cap follows the trunk
		z_inclinationCap(rotation_var, i);
		y_translateCap(curved_translation_y, i, angle);
		x_translateCap(curved_translation_x, i, angle);

		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				circle_group[getStage()][i][j] = (curved_translation_x + Radio * cos(angle));
			}
			else if(j == 1)
			{
				circle_group[getStage()][i][j] = (curved_translation_y + Radio * sin(angle));
			}
			else if(j == 2)
			{
				circle_group[getStage()][i][j] = Z + (inclination_z * rotation_var);
			}

		}
		
		angle += 2 * PI / vertex_quantity;
	}
}

void BuilderClass::z_inclinationCap(float rotation, int vertex)
{
	float Z = cap_flatness;
	for (int i = 0; i < 12; ++i)
	{
		cap_group[i][vertex][2] = (getStage() * 0.1) + (Z * i) + ((cap_radius[i] * sin(circle_inclination)) * rotation);
	}
}

void BuilderClass::y_translateCap(float y_curvation, int vertex, float angle) // This translate the shroom cap on Y axis.
{
	for (int i = 0; i < 12; ++i)
	{
		cap_group[i][vertex][1] = y_curvation + cap_radius[i] * sin(angle);
	}
}

void BuilderClass::x_translateCap(float x_curvation, int vertex, float angle) // This translate the shroom cap on Y axis.
{
	for (int i = 0; i < 12; ++i)
	{
		cap_group[i][vertex][0] = x_curvation + cap_radius[i] * cos(angle);
	}
}

void BuilderClass::buildCapCircles(int &circle_stage) // Build cap circles main function, set the radius curvature of the cap circles.
{

	float Z = cap_flatness;

	if (circle_stage == 0)
	{
		cap_curvation += 0.5 * PI / 4;
		cap_radius[circle_stage] = Radio_Loc / 2;
		buildCapCircle(circle_stage, Radio_Loc / 2, (Z * circle_stage));
	}
	if (circle_stage > 0 && circle_stage < 12)
	{
		cap_curvation += 0.8 * PI / 11;
		cap_radius[circle_stage] = Radio_Loc * (sin(cap_curvation));
		buildCapCircle(circle_stage, cap_radius[circle_stage], (Z * circle_stage));
	}
	
}

void BuilderClass::buildCapCircle(int &circle_stage, float Radio, float Z) // Build the current cap circle with the given parameters.
{

	float t = 0; // Angle parameter.

	for (int i = 0; i < vertex_quantity; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 0)
			{
				cap_group[circle_stage][i][j] = X_Loc + Radio * cos(t);
			}
			else if (j == 1)
			{
				cap_group[circle_stage][i][j] = Y_Loc + Radio * sin(t);
			}
			else
			{
				cap_group[circle_stage][i][j] = Z;
			}

		}
		t += 2 * PI / vertex_quantity;
	}
}
