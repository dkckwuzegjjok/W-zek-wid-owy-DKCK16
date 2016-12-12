#pragma once
#include <SFML/Graphics.hpp>
#include "warehouse.h"
#include "forklift.h"

class WarehouseView : public sf::Drawable
{
private:
	sf::Texture warehouseTexture;
	sf::Sprite warehouseSprite;

	sf::Texture rackTexture;
	sf::Texture rackHighlightTexture;
	sf::Sprite rackSprite[RACKQNTY];

	sf::Texture rackFrontTexture;
	sf::Sprite rackFrontSprite;

	sf::Texture buttonBackTexture;
	sf::Sprite buttonBackSprite;

	int rackView;

	Warehouse* warehouse;
	Forklift* forklift;

public:
	bool rackHighlight[RACKQNTY];

	WarehouseView();
	~WarehouseView();

	void forkliftUpdate(sf::Time time);
	void flTakePackage(int packageID);

	int getRackView();
	void setRackView(int i);

	sf::Sprite& getRack(int i);
	sf::Sprite& getButtonBack();

	void highlightRack(int index, bool hlValue);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};