#include "forklift.h"

Forklift::Forklift()
	: package(NULL),
	path_end_package_state(false)
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

	if (!take_path.empty())
	{
		if ((float)take_path[0].y < sprite.getPosition().y)
			sprite.setRotation(0);
		else if ((float)take_path[0].y > sprite.getPosition().y)
			sprite.setRotation(180);
		else if ((float)take_path[0].x < sprite.getPosition().x)
			sprite.setRotation(270);
		else if ((float)take_path[0].x > sprite.getPosition().x)
			sprite.setRotation(90);
	}
	else if (package_take_path.size() > 1)
	{
		if ((float)package_take_path[0].x < sprite.getPosition().x)
			sprite.setRotation(270);
		else if ((float)package_take_path[0].x > sprite.getPosition().x)
			sprite.setRotation(90);
	}

	if (!take_path.empty())
	{
		if (take_path[0].y == (int)sprite.getPosition().y && take_path[0].x <= (int)sprite.getPosition().x)
		{
			if (distance < sprite.getPosition().x - (float)take_path[0].x)
			{
				sprite.move(sf::Vector2f(-1 * distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(take_path[0]));
				take_path.erase(take_path.begin());
			}
		}
		else if (take_path[0].y == (int)sprite.getPosition().y && take_path[0].x > (int)sprite.getPosition().x)
		{
			if (distance < (float)take_path[0].x - sprite.getPosition().x)
			{
				sprite.move(sf::Vector2f(distance, 0));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(take_path[0]));
				take_path.erase(take_path.begin());
			}
		}
		else if (take_path[0].y < (int)sprite.getPosition().y)
		{
			if (distance < sprite.getPosition().y - (float)take_path[0].y)
			{
				sprite.move(sf::Vector2f(0, -1 * distance));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(take_path[0]));
				take_path.erase(take_path.begin());
			}
		}
		else if (take_path[0].y > (int)sprite.getPosition().y)
		{
			if (distance < (float)take_path[0].y - sprite.getPosition().y)
			{
				sprite.move(sf::Vector2f(0, distance));
			}
			else
			{
				sprite.setPosition(sf::Vector2f(take_path[0]));
				take_path.erase(take_path.begin());
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

	//=================================================================================

	if (take_path.empty() && package_take_path.empty())
	{
		if (!put_path.empty())
		{
			if ((float)put_path[0].y < sprite.getPosition().y)
				sprite.setRotation(0);
			else if ((float)put_path[0].y > sprite.getPosition().y)
				sprite.setRotation(180);
			else if ((float)put_path[0].x < sprite.getPosition().x)
				sprite.setRotation(270);
			else if ((float)put_path[0].x > sprite.getPosition().x)
				sprite.setRotation(90);
		}
		else if (package_put_path.size() > 1)
		{
			if ((float)package_put_path[0].x < sprite.getPosition().x)
				sprite.setRotation(270);
			else if ((float)package_put_path[0].x > sprite.getPosition().x)
				sprite.setRotation(90);
		}

		if (!put_path.empty())
		{
			if (put_path[0].y == (int)sprite.getPosition().y && put_path[0].x <= (int)sprite.getPosition().x)
			{
				if (distance < sprite.getPosition().x - (float)put_path[0].x)
				{
					sprite.move(sf::Vector2f(-1 * distance, 0));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(put_path[0]));
					put_path.erase(put_path.begin());
				}
			}
			else if (put_path[0].y == (int)sprite.getPosition().y && put_path[0].x > (int)sprite.getPosition().x)
			{
				if (distance < (float)put_path[0].x - sprite.getPosition().x)
				{
					sprite.move(sf::Vector2f(distance, 0));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(put_path[0]));
					put_path.erase(put_path.begin());
				}
			}
			else if (put_path[0].y < (int)sprite.getPosition().y)
			{
				if (distance < sprite.getPosition().y - (float)put_path[0].y)
				{
					sprite.move(sf::Vector2f(0, -1 * distance));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(put_path[0]));
					put_path.erase(put_path.begin());
				}
			}
			else if (put_path[0].y > (int)sprite.getPosition().y)
			{
				if (distance < (float)put_path[0].y - sprite.getPosition().y)
				{
					sprite.move(sf::Vector2f(0, distance));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(put_path[0]));
					put_path.erase(put_path.begin());
				}
			}
		}
		else if (!package_put_path.empty())
		{
			if (package_put_path[0].x <= (int)sprite.getPosition().x)
			{
				if (distance < sprite.getPosition().x - (float)package_put_path[0].x)
				{
					sprite.move(sf::Vector2f(-1 * distance, 0));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(package_put_path[0]));
					package_put_path.erase(package_put_path.begin());
					if (!package_put_path.empty())
					{
						package = NULL;
						setPackageSpriteColor(P_COLOR::TRANS);
					}
				}
			}
			else
			{
				if (distance < (float)package_put_path[0].x - sprite.getPosition().x)
				{
					sprite.move(sf::Vector2f(distance, 0));
				}
				else
				{
					sprite.setPosition(sf::Vector2f(package_put_path[0]));
					package_put_path.erase(package_put_path.begin());
					if (!package_put_path.empty())
					{
						package = NULL;
						setPackageSpriteColor(P_COLOR::TRANS);
					}
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
	makeTakePath(goal);
	package_take_path.push_back(packagePosition);
	package_take_path.push_back(goal);

	package = &newPackage;
	path_end_package_state = true;
}

bool Forklift::putPackage(Shelf& shelf)
{
	int x = shelf.addPackage(*package);
	if (x >= 0)
	{
		int rackID = shelf.getRack().getID();
		sf::Vector2i goal;
		sf::Vector2i newPackagePosition;
		if (rackID % 2)
		{
			int posY = FL_TOP_PATH_Y + 50 + x + (package->getWidth() / 2);
			goal = sf::Vector2i(50 + (rackID / 2) * 400, posY);
			newPackagePosition = sf::Vector2i(goal.x + 20, posY);
		}
		else
		{
			int posY = FL_BOT_PATH_Y - 50 - x - (package->getWidth() / 2);
			goal = sf::Vector2i(-50 + (rackID / 2) * 400, posY);
			newPackagePosition = sf::Vector2i(goal.x - 20, posY);
		}
		makePutPath(goal);
		package_put_path.push_back(newPackagePosition);
		package_put_path.push_back(goal);

		return true;
	}
	else
		return false;
}

bool Forklift::isMoving()
{
	if (take_path.empty() && package_take_path.empty() && put_path.empty() && package_put_path.empty())
		return false;
	else
		return true;
}

void Forklift::makeTakePath(sf::Vector2i goal)
{
	if (sprite.getPosition() == sf::Vector2f(goal))
	{
		return;
	}
	else if (sprite.getPosition().x == goal.x)
	{
		take_path.push_back(goal);
	}
	else if (sprite.getPosition().y == FL_TOP_PATH_Y || sprite.getPosition().y == FL_BOT_PATH_Y)
	{
		take_path.push_back(sf::Vector2i(goal.x, (int)sprite.getPosition().y));
		take_path.push_back(goal);
	}
	else if ((sprite.getPosition().y - FL_TOP_PATH_Y) + (goal.y - FL_TOP_PATH_Y) < (FL_BOT_PATH_Y - FL_TOP_PATH_Y))
	{
		take_path.push_back(sf::Vector2i((int)sprite.getPosition().x, FL_TOP_PATH_Y));
		take_path.push_back(sf::Vector2i(goal.x, FL_TOP_PATH_Y));
		take_path.push_back(goal);
	}
	else
	{
		take_path.push_back(sf::Vector2i((int)sprite.getPosition().x, FL_BOT_PATH_Y));
		take_path.push_back(sf::Vector2i(goal.x, FL_BOT_PATH_Y));
		take_path.push_back(goal);
	}
}

void Forklift::makePutPath(sf::Vector2i goal)
{
	sf::Vector2f startPosition;
	if (take_path.empty() && package_take_path.empty())
		startPosition = sf::Vector2f(sprite.getPosition());
	else if (package_take_path.empty())
		startPosition = sf::Vector2f(take_path[take_path.size() - 1]);
	else
		startPosition = sf::Vector2f(package_take_path[package_take_path.size() - 1]);

	if (startPosition == sf::Vector2f(goal))
	{
		return;
	}
	else if (startPosition.x == goal.x)
	{
		put_path.push_back(goal);
	}
	else if (startPosition.y == FL_TOP_PATH_Y || startPosition.y == FL_BOT_PATH_Y)
	{
		put_path.push_back(sf::Vector2i(goal.x, (int)startPosition.y));
		put_path.push_back(goal);
	}
	else if ((startPosition.y - FL_TOP_PATH_Y) + (goal.y - FL_TOP_PATH_Y) < (FL_BOT_PATH_Y - FL_TOP_PATH_Y))
	{
		put_path.push_back(sf::Vector2i((int)startPosition.x, FL_TOP_PATH_Y));
		put_path.push_back(sf::Vector2i(goal.x, FL_TOP_PATH_Y));
		put_path.push_back(goal);
	}
	else
	{
		put_path.push_back(sf::Vector2i((int)startPosition.x, FL_BOT_PATH_Y));
		put_path.push_back(sf::Vector2i(goal.x, FL_BOT_PATH_Y));
		put_path.push_back(goal);
	}
}

void Forklift::setPackageSprite()
{
	package_sprite.setSize(sf::Vector2f(50, 30));
	package_sprite.setOrigin(sf::Vector2f(25, 50));
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
	else
	{
		package_sprite.setOutlineColor(sf::Color(40, 40, 40));
		package_sprite.setOutlineThickness(0);
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

Package* Forklift::getPackage()
{
	return package;
}

void Forklift::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(package_sprite);
	if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(200, 200, 200));
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(3);
		rect.setSize(sf::Vector2f(250, 50));
		rect.setPosition(10, 10);

		sf::Font font;
		font.loadFromFile("arial.ttf");

		std::string string;
		if (package)
			string = std::string("Na wozku widlowym zanjduje sie\npaczka o numerze ") + std::to_string(package->getID()) + std::string(".");
		else
			string = std::string("Aktualnie na wozku widlowym\nnie ma zadnej paczki.");

		sf::Text text;
		text.setFillColor(sf::Color::Black);
		text.setFont(font);
		text.setCharacterSize(15);
		text.setPosition(rect.getPosition().x + 7, rect.getPosition().y + 7);
		text.setString(sf::String(string));

		target.draw(rect);
		target.draw(text);
	}
}

void Forklift::feedInfo(sf::RenderWindow& newWindow)
{
	window = &newWindow;
}
