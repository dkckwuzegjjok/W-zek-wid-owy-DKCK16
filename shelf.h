#pragma once
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "package.h"

class Rack;

#define SHELFHEIGHT 100

class Shelf : public sf::Drawable
{
private:
	int ID;
	int height;
	int width;
	Rack* rack;
	std::vector<Package*> packages;

public:
	Shelf(int shelfID, int width, Rack* pRack = NULL);

	int getID();
	Rack& getRack();
	int getPackageQnty();
	Package& getPackage(int index);

	int addPackage(Package& newPackage);
	bool addPackage(Package& newPackage, int positionX);
	bool removePackage(int packageID);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
