#include "state.h"
#include "WorldMap.h"

using namespace state;
using namespace render;

WorldMap::WorldMap()
{
	// Chargement des images
	sf::Image image1;
	image1.loadFromFile("res/Map_Argentina.png");
	images.push_back(image1);

	std::shared_ptr<GraphicElement> pays1 = std::make_shared<GraphicElement>();
	//pays1->


}
