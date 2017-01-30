#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
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

	std::vector<sf::Vector2i> take_path;
	std::vector<sf::Vector2i> package_take_path;
	std::vector<sf::Vector2i> put_path;
	std::vector<sf::Vector2i> package_put_path;
	bool path_end_package_state;

	void makeTakePath(sf::Vector2i goal);
	void makePutPath(sf::Vector2i goal);

	void setPackageSprite();
	void updatePackageSprite();
	void setPackageSpriteColor(P_COLOR color);

	sf::RenderWindow* window;

public:
	Forklift();

	void update(sf::Time time);
	void takePackage(Package& newPackage);
	bool putPackage(Shelf& shelf);

	bool isMoving();

	int getPosX();
	int getPosY();
	int getRotation();
	Package* getPackage();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void feedInfo(sf::RenderWindow& newWindow);
};