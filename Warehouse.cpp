#include "warehouse.h"
#include <Windows.h>

Warehouse::Warehouse()
{
	racks = new Rack*[RACKQNTY];
	for (int i = 0; i < RACKQNTY; i++)
	{
		racks[i] = new Rack(i + 1, RACKWIDTH);
	}

	//TEST LOSOWE PACZKI
	for (int i = 0; i < RACKQNTY; i++)
	{
		for (int j = 0; j < SHELFQNTY; j++)
		{
			Package* package = new Package(rand() % 60 + 41, rand() % 40 + 61, P_COLOR(rand() % 6), P_MATERIAL(rand() % 2));
			racks[i]->getShelf(j).addPackage(*package, rand() % 100);
			package = new Package(rand() % 60 + 41, rand() % 40 + 61, P_COLOR(rand() % 6), P_MATERIAL(rand() % 2));
			racks[i]->getShelf(j).addPackage(*package, rand() % 100 + 200);
			package = new Package(rand() % 60 + 41, rand() % 40 + 61, P_COLOR(rand() % 6), P_MATERIAL(rand() % 2));
			racks[i]->getShelf(j).addPackage(*package, rand() % 100 + 400);
		}
	}
}

Warehouse::~Warehouse()
{
	for (int i = 0; i < RACKQNTY; i++)
	{
		delete racks[i];
	}
	delete[] racks;
}

Rack& Warehouse::getRack(int index)
{
	return *racks[index];
}

Package* Warehouse::getPackage(int packageID)
{
	for (int i = 0; i < RACKQNTY; i++)
	{
		for (int j = 0; j < SHELFQNTY; j++)
		{
			for (int k = 0; k < racks[i]->getShelf(j).getPackageQnty(); k++)
			{
				if (racks[i]->getShelf(j).getPackage(k).getID() == packageID)
				{
					return &racks[i]->getShelf(j).getPackage(k);
				}
			}
		}
	}
	return NULL;
}