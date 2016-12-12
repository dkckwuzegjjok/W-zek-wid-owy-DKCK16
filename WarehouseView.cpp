#include "warehouseview.h"

WarehouseView::WarehouseView()
	: rackView(0)
{
	warehouseTexture.loadFromFile("warehouse.png");
	warehouseSprite.setTexture(warehouseTexture);
	warehouseSprite.setOrigin(0, 0);
	warehouseSprite.setPosition(0, 0);

	rackTexture.loadFromFile("rack.png");
	rackHighlightTexture.loadFromFile("rack_highlight.png");

	for (int i = 0; i < RACKQNTY; i++)
	{
		rackHighlight[i] = false;
		rackSprite[i].setTexture(rackTexture);
		rackSprite[i].setOrigin(50, 302);
		if (i % 2)
		{
			rackSprite[i].setPosition(float(i * 200 + 50), float(400));
		}
		else
		{
			rackSprite[i].setPosition(float(i * 200 + 150), float(400));
		}
	}

	rackFrontTexture.loadFromFile("rack_front.png");
	rackFrontSprite.setTexture(rackFrontTexture);
	rackFrontSprite.setOrigin(310, 190);
	rackFrontSprite.setPosition(600, 400);

	buttonBackTexture.loadFromFile("button_back.png");
	buttonBackSprite.setTexture(buttonBackTexture);
	buttonBackSprite.setOrigin(60, 20);
	buttonBackSprite.setPosition(600, 100);

	warehouse = new Warehouse();
	forklift = new Forklift();
}

WarehouseView::~WarehouseView()
{
	delete warehouse;
	delete forklift;
}

void WarehouseView::forkliftUpdate(sf::Time time)
{
	forklift->update(time);
}

void WarehouseView::flTakePackage(int packageID)
{
	forklift->takePackage(*warehouse->getPackage(packageID));
}

int WarehouseView::getRackView()
{
	return rackView;
}

void WarehouseView::setRackView(int i)
{
	rackView = i;
}

sf::Sprite& WarehouseView::getRack(int i)
{
	return rackSprite[i];
}

sf::Sprite& WarehouseView::getButtonBack()
{
	return buttonBackSprite;
}

void WarehouseView::highlightRack(int index, bool hlValue)
{
	if (hlValue)
	{
		rackSprite[index].setTexture(rackHighlightTexture);
	}
	else
	{
		rackSprite[index].setTexture(rackTexture);
	}
	rackHighlight[index] = hlValue;
}

void WarehouseView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (rackView > 0 && rackView <= RACKQNTY)
	{
		target.draw(rackFrontSprite);
		target.draw(warehouse->getRack(rackView - 1));
		target.draw(buttonBackSprite);
	}
	else
	{
		target.draw(warehouseSprite);

		target.draw(*forklift);

		for (int i = 0; i < RACKQNTY; i++)
		{
			target.draw(rackSprite[i]);
		}
	}
}