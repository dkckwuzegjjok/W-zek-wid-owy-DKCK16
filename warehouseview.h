#pragma once
#include <tchar.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "warehouse.h"
#include "forklift.h"

struct Command
{
	int order;
	P_COLOR color;
	P_MATERIAL material;
	int category;
	int fromRackID;
	int fromShelfID;
	int toRackID;
	int toShelfID;
	int side;
	int packageID;
};

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

	std::vector<Command*>commandQueue;
	std::string answerText;
	void setAnswer(std::string answer);

	int flTakePackage(int packageID);
	bool flPutPackage(int rackID, int shelfID);

public:
	bool rackHighlight[RACKQNTY];

	WarehouseView();
	~WarehouseView();

	void update(sf::RenderWindow& window);
	TCHAR* getAnswer();

	void forkliftUpdate(sf::Time time);
	void processCommand(long long CmdID);
	Package* getFlPackage();
	Package* getPackage(int packageID);

	int getRackView();
	void setRackView(int i);

	sf::Sprite& getRack(int i);
	sf::Sprite& getButtonBack();

	void highlightRack(int index, bool hlValue);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};