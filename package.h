#pragma once
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class Shelf;

#define SHELF_LO_Y 320
#define SHELF_MID_Y 430
#define SHELF_HI_Y 540
#define SHELF_X 300

enum P_COLOR { RED, BLUE, YELLOW, GREEN, BLACK, WHITE, TRANS };
enum P_MATERIAL { WOOD, METAL };
enum P_STATE { FREE, SHELF };

class Package : public sf::Drawable
{
private:
	static int nextID;

	int ID;

	int height;
	int width;

	P_COLOR color;
	P_MATERIAL material;

	P_STATE state;
	Shelf* shelf;
	int shelfPositionX;

	sf::RectangleShape sprite;

public:
	Package(int height, int width, P_COLOR color, P_MATERIAL material);

	int getID();

	int getHeight();
	int getWidth();

	P_COLOR getColor();
	P_MATERIAL getMaterial();

	Shelf& getShelf();
	int getShelfPositionX();

	void setShelf(Shelf* shelf);
	void setShelfPositionX(int shelfPositionX);
	void setSprite(int shelfID);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
