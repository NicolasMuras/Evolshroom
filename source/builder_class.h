#ifndef BUILDER_CLASS_H
#define BUILDER_CLASS_H

#include "strain_class.h"
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <type_traits>
#include <random>
#include <time.h>

class BuilderClass
{
public:
	
	BuilderClass(Strain id);

	// MAIN FUNCTIONS
	void buildStrain(Strain);
	void buildShroom();

	void showGuides() const;
	void showBuilderInfo();

	std::vector<unsigned int> getIndices();
	std::vector<unsigned int> getCapIndices();

	// Vertex data
	float cap_group[12][20][3] = { 0 };
	float cap_colors[12][20][3] = { 0 };
	float circle_group[30][20][3] = { 0 };
	float colors_group[30][20][3] = { 0 };

private:
	// Const vars
	const int vertex_quantity = 20;

	// Build functions
	void buildTrunk();
	void buildCapCircles(int&);
	void buildCircle(float, float, float);
	void buildCapCircle(int&, float, float);
	void y_translateCap(float, int, float);
	void x_translateCap(float, int, float);
	void z_inclinationCap(float, int);

	void generateIndices(std::vector<unsigned int>&, int);
	void generateIndicesCap();
	void generateColors();
	void generateColorsCap();

	// SET
	void setStage(int);
	void setLocation(float, float, float);
	void setTrunkColors(float, float, float);
	void setCapColors(float, float, float);

	// GET
	int getStage() const;

	template<class generic>
	using uniform_distribution =
		typename std::conditional<
		std::is_floating_point<generic>::value,
		std::uniform_real_distribution<generic>,
		typename std::conditional<
		std::is_integral<generic>::value,
		std::uniform_int_distribution<generic>,
		void
		>::type
	>::type;
	template<class generic>
	generic getRandomNumber(generic, generic) const;



	// VARS
	float X_Loc = 0;
	float Y_Loc = 0;
	float Radio_Loc = 0;
	float circle_inclination = 0;
	float circle_translation = 0;
	float trunk_curvation = 0;
	float cap_curvation = 0;
	int stage = 0;

	// Procedural vars
	int root_curvation_end = 5;
	int curvation_start = 1;
	int curvation_end = 23;
	bool curvation_direction = 0;
	int trunk_curvation_start = 1;
	int trunk_curvation_end = 23;
	float curvature_size = 1;
	int max_stage = 23;
	float min_trunk_width = 5.5;
	float cap_flatness = 0.05;
	float red_cap = 0.2;
	float green_cap = 0.2;
	float blue_cap = 0.2;
	float red_trunk = 0.2;
	float green_trunk = 0.2;
	float blue_trunk = 0.2;

	// Vertex data
	float cap_radius[12] = { 0 };

	std::vector<unsigned int> indices = { 1 };
	std::vector<unsigned int> indices_cap = { 1 };
};
#endif // BUILDER_CLASS_H
