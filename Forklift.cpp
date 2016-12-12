#include "forklift.h"

Forklift::Forklift()
	: package(NULL)
{
	texture.loadFromFile("forklift.png");
	sprite.setTexture(texture);
	sprite.setOrigin(50, 50);
	sprite.setPosition(FL_INIT_POS_X, FL_INIT_POS_Y);
	sprite.setRotation(90);

	setPackageSprite();
}

void Forklift::update(sf::Time time)
{
	float distance = float(time.asMilliseconds()) * float(0.2);

	if (!path.empty())
	{
		if ((float)path[0].y < sprite.getPosition().y)
			sprite.setRotation(0);
		else if ((float)path[0].y > sprite.getPosition().y)
			sprite.setRotation(180);
		else if ((float)path[0].x < sprite.getPosition().x)
			sprite.setRotation(270);
		else if ((float)path[0].x > sprite.getPosition().x)
			sprite.setRotation(90);
	}
	else if (package_take_path.size() > 1)
	{
		if ((float)package_take_path[0].x < sprite.getPosition().x)
			sprite.setRotation(270);
		else if ((float)package_take_path[0].x > sprite.getPosition().x)
			sprite.setRotation(90);
	}

	if (!path.empty())
	{
		if (path[0].y == (int)sprite.getPosition().y && path[0].x <= (int)sprite.getPosition().x)
		{
			if (distance < sprite.getPosition().x - (float)path[0].x)
			{
				sprite.move(sf::Vector2f(-1 * distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(path[0]));
				path.erase(path.begin());
			}
		}
		else if (path[0].y == (int)sprite.getPosition().y && path[0].x > (int)sprite.getPosition().x)
		{
			if (distance < (float)path[0].x - sprite.getPosition().x)
			{
				sprite.move(sf::Vector2f(distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(path[0]));
				path.erase(path.begin());
			}
		}
		else if (path[0].y < (int)sprite.getPosition().y)
		{
			if (distance < sprite.getPosition().y - (float)path[0].y)
			{
				sprite.move(sf::Vector2f(0, -1 * distance));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(path[0]));
				path.erase(path.begin());
			}
		}
		else if (path[0].y > (int)sprite.getPosition().y)
		{
			if (distance < (float)path[0].y - sprite.getPosition().y)
			{
				sprite.move(sf::Vector2f(0, distance));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(path[0]));
				path.erase(path.begin());
			}
		}
	}
	else if (!package_take_path.empty())
	{
		if (package_take_path[0].x <= (int)sprite.getPosition().x)
		{
			if (distance < sprite.getPosition().x - (float)package_take_path[0].x)
			{
				sprite.move(sf::Vector2f(-1 * distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(package_take_path[0]));
				package_take_path.erase(package_take_path.begin());
				if (!package_take_path.empty())
				{
					package->getShelf().removePackage(package->getID());
					setPackageSpriteColor(package->getColor());
				}
			}
		}
		else
		{
			if (distance < (float)package_take_path[0].x - sprite.getPosition().x)
			{
				sprite.move(sf::Vector2f(distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(package_take_path[0]));
				package_take_path.erase(package_take_path.begin());
				if (!package_take_path.empty())
				{
					package->getShelf().removePackage(package->getID());
					setPackageSpriteColor(package->getColor());
				}
			}
		}
	}

	updatePackageSprite();
}

void Forklift::takePackage(Package& newPackage)
{
	int rackID = newPackage.getShelf().getRack().getID();
	sf::Vector2i goal;
	sf::Vector2i packagePosition;
	if (rackID % 2)
	{
		int posY = FL_TOP_PATH_Y + 50 + newPackage.getShelfPositionX() + (newPackage.getWidth() / 2);
		goal = sf::Vector2i(50 + (rackID / 2) * 400, posY);
		packagePosition = sf::Vector2i(goal.x + 20, posY);
	}
	else
	{
		int posY = FL_BOT_PATH_Y - 50 - newPackage.getShelfPositionX() - (newPackage.getWidth() / 2);
		goal = sf::Vector2i(-50 + (rackID / 2) * 400, posY);
		packagePosition = sf::Vector2i(goal.x - 20, posY);
	}
	makePath(goal);
	package_take_path.push_back(packagePosition);
	package_take_path.push_back(goal);

	package = &newPackage;
}

void Forklift::makePath(sf::Vector2i goal)
{
	if (sprite.getPosition() == sf::Vector2f(goal))
	{
		return;
	}
	else if (sprite.getPosition().x == goal.x)
	{
		path.push_back(goal);
	}
	else if (sprite.getPosition().y == FL_TOP_PATH_Y || sprite.getPosition().y == FL_BOT_PATH_Y)
	{
		path.push_back(sf::Vector2i(goal.x, (int)sprite.getPosition().y));
		path.push_back(goal);
	}
	else if ((sprite.getPosition().y - FL_TOP_PATH_Y) + (goal.y - FL_TOP_PATH_Y) < (FL_BOT_PATH_Y - FL_TOP_PATH_Y))
	{
		path.push_back(sf::Vector2i((int)sprite.getPosition().x, FL_TOP_PATH_Y));
		path.push_back(sf::Vector2i(goal.x, FL_TOP_PATH_Y));
		path.push_back(goal);
	}
	else
	{
		path.push_back(sf::Vector2i((int)sprite.getPosition().x, FL_BOT_PATH_Y));
		path.push_back(sf::Vector2i(goal.x, FL_BOT_PATH_Y));
		path.push_back(goal);
	}
}

void Forklift::setPackageSprite()
{
	package_sprite.setSize(sf::Vector2f(45, 24));
	package_sprite.setOrigin(sf::Vector2f(23, 50));
	package_sprite.setPosition(sprite.getPosition());
	package_sprite.setRotation(sprite.getRotation());
	package_sprite.setFillColor(sf::Color::Transparent);
}

void Forklift::updatePackageSprite()
{
	package_sprite.setPosition(sprite.getPosition());
	package_sprite.setRotation(sprite.getRotation());
}

void Forklift::setPackageSpriteColor(P_COLOR color)
{
	switch (color)
	{
	case RED:
		package_sprite.setFillColor(sf::Color(165, 34, 34));
		break;
	case BLUE:
		package_sprite.setFillColor(sf::Color(69, 79, 183));
		break;
	case YELLOW:
		package_sprite.setFillColor(sf::Color(232, 216, 71));
		break;
	case GREEN:
		package_sprite.setFillColor(sf::Color(113, 188, 98));
		break;
	case BLACK:
		package_sprite.setFillColor(sf::Color(33, 33, 32));
		break;
	case WHITE:
		package_sprite.setFillColor(sf::Color(234, 233, 227));
		break;
	case TRANS:
		package_sprite.setFillColor(sf::Color::Transparent);
		break;
	default:
		break;
	}

	if (color != TRANS)
	{
		package_sprite.setOutlineColor(sf::Color(40, 40, 40));
		package_sprite.setOutlineThickness(2);
	}
}

int Forklift::getPosX()
{
	return (int)sprite.getPosition().x;
}

int Forklift::getPosY()
{
	return (int)sprite.getPosition().y;
}

int Forklift::getRotation()
{
	return (int)sprite.getRotation();
}

Package& Forklift::getPackage()
{
	return *package;
}

void Forklift::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(package_sprite);
}
