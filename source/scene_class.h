#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "builder_class.h"
#include <vector>

#define VERTICES 0
#define INDICES 1

class Scene
{
	
public:
	Scene(float, float);

	void newMushroom(float, float, float, float, float, float);
	
	// SET
	void setArea(float, float);

	// VARS
	std::vector<BuilderClass> Mushrooms_ID;
	
	int total_entities = 0;

private:
	// VARS
	
	float area_x = 0;
	float area_y = 0;
};

#endif // SCENE_CLASS_H
