#pragma once
#include <stdlib.h>
#include <math.h>
#include "rack.h"
#include "shelf.h"
#include "package.h"

#define RACKQNTY 6

class Warehouse
{
	Rack** racks;

public:
	Warehouse();
	~Warehouse();

	Rack& getRack(int index);

	Package* getPackage(int packageID);
};