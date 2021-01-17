#ifndef BUILDER_CLASS_H
#define BUILDER_CLASS_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
class BuilderClass
{
public:
	BuilderClass(int &vertexquantity, float &radio, float &X, float &Y, int &y_segments);

	void buildCap(int&, float&, float&, float&, int&);
	void buildTrunk(int&, float&, float&, float&);
	void buildCircle(int&, float, float&, float&, float);

private:
	void translateCircle();
	void scalateCircle();
	void rotateCircle();

	// SET
	void setLocation();

	// GET
	std::vector<float> getLocation() const;
	std::vector<float> getCircle(int) const;

	// VARS
	int stage;
	std::vector<float> location = {0, 0};
	std::vector<float> circles = {0, 0};
};
#endif // BUILDER_CLASS_H
