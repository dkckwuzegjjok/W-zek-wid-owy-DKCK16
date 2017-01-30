#include "shelf.h"
#include <Windows.h>

Shelf::Shelf(int shelfID, int width, Rack* pRack) 
	: ID(shelfID), width(width), rack(pRack)
{
	height = SHELFHEIGHT;
}

int Shelf::getID()
{
	return ID;
}

Rack& Shelf::getRack()
{
	return *rack;
}

int Shelf::getPackageQnty()
{
	return (int)packages.size();
}

Package& Shelf::getPackage(int index)
{
	return *packages[index];
}

int Shelf::addPackage(Package& newPackage)
{
	int x = 0;

	for (int i = 0; i < packages.size(); i++)
	{
		if (packages[i]->getShelfPositionX() - x >= newPackage.getWidth())
		{
			newPackage.setShelf(this);
			newPackage.setShelfPositionX(x);
			newPackage.setSprite(ID);
			packages.insert(packages.begin() + i, &newPackage);
			return x;
		}
		else
		{
			x = packages[i]->getShelfPositionX() + packages[i]->getWidth();
		}
	}

	if (width - x >= newPackage.getWidth())
	{
		newPackage.setShelf(this);
		newPackage.setShelfPositionX(x);
		newPackage.setSprite(ID);
		packages.push_back(&newPackage);
		return x;
	}

	return -1;
}

bool Shelf::addPackage(Package& newPackage, int positionX)
{
	int x = 0;

	for (int i = 0; i < packages.size(); i++)
	{
		if (packages[i]->getShelfPositionX() > positionX
			&& x <= positionX
			&& packages[i]->getShelfPositionX() - positionX >= newPackage.getWidth())
		{
			newPackage.setShelf(this);
			newPackage.setShelfPositionX(positionX);
			newPackage.setSprite(ID);
			packages.insert(packages.begin() + i, &newPackage);
			return true;
		}
		else
		{
			x = packages[i]->getShelfPositionX() + packages[i]->getWidth();
		}
	}

	if (width > positionX
		&& x <= positionX
		&& width - x >= newPackage.getWidth())
	{
		newPackage.setShelf(this);
		newPackage.setShelfPositionX(positionX);
		newPackage.setSprite(ID);
		packages.push_back(&newPackage);
		return true;
	}

	return false;
}

bool Shelf::removePackage(int packageID)
{
	for (int i = 0; i < packages.size(); i++)
	{
		if (packages[i]->getID() == packageID)
		{
			packages[i]->setShelf(NULL);
			packages[i]->setShelfPositionX(0);
			packages.erase(packages.begin() + i);
			return true;
		}
	}
	return false;
}

void Shelf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < packages.size(); i++)
		target.draw(*packages[i]);
}
