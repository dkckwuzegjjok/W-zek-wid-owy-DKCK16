#include "package.h"
#include <windows.h>

int Package::nextID = 100;

Package::Package(int height, int width, P_COLOR color, P_MATERIAL material)
	: ID(nextID++), height(height), width(width), 
	color(color), material(material), 
	state(P_STATE::FREE), shelf(NULL), shelfPositionX(0)
{

}

int Package::getID()
{
	return ID;
}

int Package::getHeight()
{
	return height;
}

int Package::getWidth()
{
	return width;
}

P_COLOR Package::getColor()
{
	return color;
}

P_MATERIAL Package::getMaterial()
{
	return material;
}

Shelf& Package::getShelf()
{
	return *shelf;
}

int Package::getShelfPositionX()
{
	return shelfPositionX;
}

void Package::setShelf(Shelf* newShelf)
{
	if (newShelf)
		state = SHELF;
	else
		state = FREE;
	shelf = newShelf;
}

void Package::setShelfPositionX(int newShelfPositionX)
{
	shelfPositionX = newShelfPositionX;
}

void Package::setSprite(int shelfID)
{
	sprite.setSize(sf::Vector2f(float(width - 6), float(height - 6)));
	sprite.setOutlineColor(sf::Color(40, 40, 40));
	sprite.setOutlineThickness(3);

	switch (color)
	{
	case RED:
		sprite.setFillColor(sf::Color(165, 34, 34));
		break;
	case BLUE:
		sprite.setFillColor(sf::Color(69, 79, 183));
		break;
	case YELLOW:
		sprite.setFillColor(sf::Color(232, 216, 71));
		break;
	case GREEN:
		sprite.setFillColor(sf::Color(113, 188, 98));
		break;
	case BLACK:
		sprite.setFillColor(sf::Color(33, 33, 32));
		break;
	case WHITE:
		sprite.setFillColor(sf::Color(234, 233, 227));
		break;
	case TRANS:
		sprite.setFillColor(sf::Color::Transparent);
		break;
	default:
		break;
	}

	switch (shelfID)
	{
	case 1:
		sprite.setPosition(float(SHELF_X + shelfPositionX + 3), float(SHELF_LO_Y - height + 3));
		break;
	case 2:
		sprite.setPosition(float(SHELF_X + shelfPositionX + 3), float(SHELF_MID_Y - height + 3));
		break;
	case 3:
		sprite.setPosition(float(SHELF_X + shelfPositionX + 3), float(SHELF_HI_Y - height + 3));
		break;
	default:
		break;
	}
}

void Package::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite);
	if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(200, 200, 200));
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(3);
		rect.setSize(sf::Vector2f(250, 90));
		rect.setPosition(10, 10);

		sf::Font font;
		font.loadFromFile("arial.ttf");

		int rackID = info / 100;
		int shelfID = (info % 100) / 10;
		int packageNo = info % 10;
		std::string string = std::string("Paczka numer ") + std::to_string(ID) 
							+ std::string("\nRegal: ") + std::to_string(rackID) 
							+ std::string("\nPoziom: ") + std::to_string(shelfID) 
							+ std::string("\nJest to ") + std::to_string(packageNo) + std::string(". paczka na tej polce.");

		sf::Text text;
		text.setFillColor(sf::Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
		text.setPosition(rect.getPosition().x + 10, rect.getPosition().y + 10);
		text.setString(sf::String(string));

		target.draw(rect);
		target.draw(text);
	}
}

void Package::feedInfo(int newInfo, sf::RenderWindow& newWindow)
{
	info = newInfo;
	window = &newWindow;
}