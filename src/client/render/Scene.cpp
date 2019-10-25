#include "Scene.h"

using namespace state;
using namespace render;

Scene::Scene()
{
}

void Scene::Draw()
{
	worldMap->Draw(renderWindow);
	unitRepresentation->Draw(renderWindow);
        //unitSelection->Draw(renderWindow);
	return;
}

void Scene::Update()
{
	//worldMap->Update();
	unitRepresentation->Update(renderWindow);
        //unitSelection->Update(renderWindow);
	return;
}

