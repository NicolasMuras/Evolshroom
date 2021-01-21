#ifndef BUILDER_CLASS_H
#define BUILDER_CLASS_H
#include <GL/glew.h>
#include <GL/freeglut.h>

class BuilderClass
{
public:
	
	BuilderClass(float radio, float X, float Y);

	void buildShroom();
	void buildCap(int&, float&, float&, float&, int&);
	void buildTrunk();
	void buildCapCircles(int&);
	void buildCircle(float&, float);
	void buildCapCircle(int&, float, float);
	int getRandomInt(int, int);
	float getRandomFloat(int, int);
	void showMushroom() const;

	void setStage(int);
	int getStage() const;

	float circle_inclination = 0;
	float circle_translation = 0;
	float trunk_curvation = 0;
	float cap_curvation = 0;
	int stage = 0;
	const int vertex_quantity = 20;

	// Procedural vars
	int curvation_start = 1;
	int curvation_end = 23;
	bool curvation_direction = 0;
	float curvature_size = 1;

	int root_curvation_end = 5;
	int trunk_curvation_start = 1;
	int trunk_curvation_end = 23;
private:
	void y_translateCap(float, int, float);
	void z_inclinationCap(float, int);

	// SET
	void setLocation(float, float, float);
	void setRandomCurvation();

	// VARS
	float X_Loc = 0;
	float Y_Loc = 0;
	float Radio_Loc = 0;

	float cap_group[12][20][3] = { 0 };
	float cap_radius[12] = { 0 };
	float circle_group[24][20][3] = { 0 };
};
#endif // BUILDER_CLASS_H
