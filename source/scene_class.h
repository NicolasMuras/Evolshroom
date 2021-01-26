#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H
#include "strain_class.h"
#include "builder_class.h"
#include <vector>

#define VERTICES 0
#define INDICES 1

class Scene
{
	
public:
	Scene(float, float);

	void newMushroom(Strain id);

	// SET
	void setArea(float, float);

	// GET
	float getArea_x();
	float getArea_y();

	// VARS
	std::vector<BuilderClass> Mushrooms_ID;
	
	int total_entities = 0;

private:
	// VARS
	
	float area_x = 0;
	float area_y = 0;
};

#endif // SCENE_CLASS_H
