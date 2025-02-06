#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	
}

void Scene::setMap(Map map)
{
	this->map = map;
}

void Scene::render(RenderWindow& window)
{
	map.DrawMap(window);
}

void Scene::update(RenderWindow& window)
{		
	
}
