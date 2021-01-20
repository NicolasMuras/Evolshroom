#ifndef BUILDER_CLASS_H
#define BUILDER_CLASS_H
#include <GL/glew.h>
#include <GL/freeglut.h>

class BuilderClass
{
public:
	
	BuilderClass(float &radio, float &X, float &Y);

	void buildShroom(int &, float &, float &, float &);
	void buildCap(int&, float&, float&, float&, int&);
	void buildTrunk(int&, float&, float&, float&);
	void buildCapCircles(int&, float&, float&, float&);
	void buildCircle(int&, float, float&, float&, float);
	void buildCapCircle(int&, float, float&, float&, float);
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

	int root_curvation_end = 5;
	int trunk_curvation_start = 1;
	int trunk_curvation_end = 23;
private:
	void translateCircle(int);
	void scalateCircle();
	void rotateCircle();

	// SET
	void setLocation();
	void setRandomCurvation();

	// GET
	float* getLocation() const;
	float* getCircle(int) const;


	// VARS
	float cap_group[12][20][3] = { 0 };
	float circle_group[24][20][3] = { 0 };
};
#endif // BUILDER_CLASS_H
