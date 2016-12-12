#pragma once
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "shelf.h"

#define SHELFQNTY 3
#define RACKWIDTH 600

class Rack : public sf::Drawable
{
private:
	int ID;
	int width;
	Shelf** shelves;

public:
	Rack(int ID, int width);
	~Rack();

	int getID();
	int getWidth();
	Shelf& getShelf(int index);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};