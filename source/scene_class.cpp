#include "scene_class.h"
#include "builder_class.h"
#include <iostream>
Scene::Scene(float X, float Y)
{
	setArea(X, Y);
}

void Scene::setArea(float x, float y)
{
	area_x = x;
	area_y = y;
}

float Scene::getArea_x()
{
	return area_x;
}

float Scene::getArea_y()
{
	return area_y;
}

void Scene::newMushroom(Strain id)
{
	BuilderClass Shroom(id);
	Mushrooms_ID.push_back(Shroom);
	total_entities++;
}
