#ifndef BUILDER_CLASS_H
#define BUILDER_CLASS_H
#include <GL/glew.h>
#include <GL/freeglut.h>

class BuilderClass
{
public:
	
	BuilderClass(int &vertexquantity, float &radio, float &X, float &Y, int &y_segments);

	void buildShroom(int &, float &, float &, float &);
	void buildCap(int&, float&, float&, float&, int&);
	void buildTrunk(int&, float&, float&, float&);
	void buildCapCircles(int&, float&, float&, float&);
	void buildCircle(int&, float, float&, float&, float);
	void buildCapCircle(int&, float, float&, float&, float);
	void deleteCircle();
	void showTrunk() const;

	void setStage(int);
	int getStage() const;

	float trunk_curvation = 0;
	float cap_curvation = 0;
	int stage = 0;
	const int vertex_quantity = 20;
private:
	void translateCircle(int);
	void scalateCircle();
	void rotateCircle();

	// SET
	void setLocation();


	// GET
	float* getLocation() const;
	float* getCircle(int) const;


	// VARS
	float cap_group[12][20][3] = { 0 };
	float circle_group[24][20][3] = { 0 };
};
#endif // BUILDER_CLASS_H

