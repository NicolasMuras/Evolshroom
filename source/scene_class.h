#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "builder_class.h"
#include <vector>

class Scene
{
	
public:
	Scene(float, float);

	void newMushroom(float, float, float);
	
	// SET
	void setArea(float, float);

	// VARS
	std::vector<BuilderClass> Mushrooms_ID;

private:
	// VARS
	float area_x = 0;
	float area_y = 0;
};

#endif // SCENE_CLASS_H