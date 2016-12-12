#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include "warehouse.h"

#define FL_INIT_POS_X 50
#define FL_INIT_POS_Y 750

#define FL_TOP_PATH_Y 50
#define FL_BOT_PATH_Y 750

class Forklift : public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	Package* package;
	sf::RectangleShape package_sprite;

	std::vector<sf::Vector2i> path;
	std::vector<sf::Vector2i> package_take_path;

	void makePath(sf::Vector2i goal);

	void setPackageSprite();
	void updatePackageSprite();
	void setPackageSpriteColor(P_COLOR color);

public:
	Forklift();

	void update(sf::Time time);
	void takePackage(Package& newPackage);

	int getPosX();
	int getPosY();
	int getRotation();
	Package& getPackage();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};