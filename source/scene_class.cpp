#include "scene_class.h"
#include "builder_class.h"
using namespace std;

Scene::Scene(float X, float Y)
{
	setArea(X, Y);
}

void Scene::setArea(float x, float y)
{
	area_x = x;
	area_y = y;
}

void Scene::newMushroom(float Radio, float X, float Y)
{
	BuilderClass Shroom(Radio, X, Y);
	Mushrooms_ID.push_back(Shroom);
}