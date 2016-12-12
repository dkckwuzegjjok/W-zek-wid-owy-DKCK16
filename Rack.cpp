#include "rack.h"

Rack::Rack(int ID, int width) 
	: ID(ID), width(width)
{
	shelves = new Shelf*[SHELFQNTY];
	for (int i = 0; i < SHELFQNTY; i++)
	{
		shelves[i] = new Shelf(i + 1, width, this);
	}
}

Rack::~Rack()
{
	for (int i = 0; i < SHELFQNTY; i++)
	{
		delete shelves[i];
	}
	delete[] shelves;
}


int Rack::getID()
{
	return ID;
}

int Rack::getWidth()
{
	return width;
}

Shelf& Rack::getShelf(int index)
{
	return *shelves[index];
}

void Rack::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < SHELFQNTY; i++)
		target.draw(*shelves[i]);
}