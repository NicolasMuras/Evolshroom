#include "scene_class.h"
#include "builder_class.h"

Scene::Scene(float X, float Y)
{
	setArea(X, Y);
}

void Scene::setArea(float x, float y)
{
	area_x = x;
	area_y = y;
}

void Scene::newMushroom(float Radio, float X, float Y, float red, float green, float blue)
{
	BuilderClass Shroom(Radio, X, Y, red, green, blue);
	Mushrooms_ID.push_back(Shroom);
	total_entities++;
}
