#include "warehouseview.h"
#include <Windows.h>

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

	answerText = "";
}

WarehouseView::~WarehouseView()
{
	delete warehouse;
	delete forklift;
}

void WarehouseView::update(sf::RenderWindow& window)
{
	for (int i = 0; i < RACKQNTY; i++)
	{
		for (int j = 0; j < SHELFQNTY; j++)
		{
			for (int k = 0; k < warehouse->getRack(i).getShelf(j).getPackageQnty(); k++)
				warehouse->getRack(i).getShelf(j).getPackage(k).feedInfo((i + 1) * 100 + (j + 1) * 10 + (k + 1), window);
		}
	}
	forklift->feedInfo(window);

	if (commandQueue.empty())
		return;

	switch (commandQueue[0]->order)
	{
	case 1:
	{
		if (commandQueue[0]->packageID == 0)
		{
			setAnswer(std::string("Brak informacji o numerze paczki do przewiezienia.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
		else if (commandQueue[0]->toRackID == 0)
		{
			setAnswer(std::string("Brak informacji o numerze docelowego regalu.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
		else if (commandQueue[0]->toShelfID == 0)
		{
			setAnswer(std::string("Brak informacji o numerze docelowej polki.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
		else
		{
			if (getFlPackage() && commandQueue[0]->packageID != getFlPackage()->getID())
			{
				setAnswer(std::string("Na wozku znajduje sie juz paczka o numerze ") + std::to_string(getFlPackage()->getID()) + ".\n");
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
			else if (getFlPackage() && commandQueue[0]->packageID == getFlPackage()->getID())
			{
				commandQueue[0]->order = 6;
			}
			else
			{
				if (Package* package = getPackage(commandQueue[0]->packageID))
				{
					if (commandQueue[0]->fromRackID != 0 && commandQueue[0]->fromShelfID == 0 && package->getShelf().getRack().getID() != commandQueue[0]->fromRackID)
					{
						setAnswer(std::string("Podanej paczki nie ma na regale numer ") + std::to_string(commandQueue[0]->fromRackID) + std::string(".\n"));
						commandQueue[0]->order = 4;
					}
					else if (commandQueue[0]->fromRackID == 0 && commandQueue[0]->fromShelfID != 0 && package->getShelf().getID() != commandQueue[0]->fromShelfID)
					{
						setAnswer(std::string("Podanej paczki nie ma na polce numer ") + std::to_string(commandQueue[0]->fromShelfID) + std::string(".\n"));
						commandQueue[0]->order = 4;
					}
					else if (commandQueue[0]->fromRackID != 0 && commandQueue[0]->fromShelfID != 0)
					{
						if (package->getShelf().getRack().getID() != commandQueue[0]->fromRackID)
						{
							setAnswer(std::string("Podanej paczki nie ma na regale numer ") + std::to_string(commandQueue[0]->fromRackID) + std::string(".\n"));
							commandQueue[0]->order = 4;
						}
						else if (package->getShelf().getID() != commandQueue[0]->fromShelfID)
						{
							setAnswer(std::string("Podanej paczki nie ma na polce numer ") + std::to_string(commandQueue[0]->fromShelfID) + std::string(".\n"));
							commandQueue[0]->order = 4;
						}
						else
						{
							commandQueue[0]->order = 5;
							Command* temp = new Command;
							*temp = *commandQueue[0];
							temp->order = 6;
							commandQueue.insert(commandQueue.begin() + 1, temp);
						}
					}
					else
					{
						commandQueue[0]->order = 5;
						Command* temp = new Command;
						*temp = *commandQueue[0];
						temp->order = 6;
						commandQueue.insert(commandQueue.begin() + 1, temp);
					}
				}
				else
				{
					setAnswer(std::string("Paczka o podanym numerze nie istnieje.\n"));
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
				}
			}
		}
	}
	break;
	case 2:
	{
		if (commandQueue[0]->packageID == 0)
		{
			commandQueue[0]->order = 6;
		}
		else if (commandQueue[0]->toRackID == 0)
		{
			setAnswer(std::string("Brak informacji o numerze docelowego regalu.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
		else if (commandQueue[0]->toShelfID == 0)
		{
			setAnswer(std::string("Brak informacji o numerze docelowej polki.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
		else
		{
			if (getFlPackage() && commandQueue[0]->packageID != getFlPackage()->getID())
			{
				setAnswer(std::string("Na wozku znajduje sie juz paczka o numerze ") + std::to_string(getFlPackage()->getID()) + ".\n");
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
			else if (getFlPackage() && commandQueue[0]->packageID == getFlPackage()->getID())
			{
				commandQueue[0]->order = 6;
			}
			else
			{
				commandQueue[0]->order = 5;
				Command* temp = new Command;
				*temp = *commandQueue[0];
				temp->order = 6;
				commandQueue.insert(commandQueue.begin() + 1, temp);
			}
		}
	}
	break;
	case 4:
	{
		if (commandQueue[0]->packageID)
		{
			Package* package = getPackage(commandQueue[0]->packageID);
			if (package)
			{
				setAnswer(std::string("Paczka o numerze ") + std::to_string(commandQueue[0]->packageID) + std::string(" znajduje sie regale nr ")
						+ std::to_string(package->getShelf().getRack().getID()) + std::string(", na polce nr ") + std::to_string(package->getShelf().getID()) + ".\n");
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
			else if (getFlPackage() && getFlPackage()->getID() == commandQueue[0]->packageID)
			{
				setAnswer(std::string("Paczka o numerze ") + std::to_string(commandQueue[0]->packageID) + " znajduje sie na wozku widlowym.\n");
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
			else
			{
				setAnswer(std::string("Paczka o podanym numerze nie istnieje.\n"));
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
		}
		else
		{
			setAnswer(std::string("Brak informacji o numerze paczki do znalezienia.\n"));
			delete commandQueue[0];
			commandQueue.erase(commandQueue.begin());
		}
	}
	break;
	case 5:
	{
		if (!forklift->isMoving())
		{
			if (commandQueue[0]->packageID == 0)
			{
				setAnswer(std::string("Brak informacji o numerze paczki do pobrania."));
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
			else
			{
				if (Package* package = getPackage(commandQueue[0]->packageID))
				{
					if (commandQueue[0]->fromRackID != 0 && commandQueue[0]->fromShelfID == 0 && package->getShelf().getRack().getID() != commandQueue[0]->fromRackID)
					{
						setAnswer(std::string("Podanej paczki nie ma na regale numer ") + std::to_string(commandQueue[0]->fromRackID) + std::string(".\n"));
						commandQueue[0]->order = 4;
						break;
					}
					else if (commandQueue[0]->fromRackID == 0 && commandQueue[0]->fromShelfID != 0 && package->getShelf().getID() != commandQueue[0]->fromShelfID)
					{
						setAnswer(std::string("Podanej paczki nie ma na polce numer ") + std::to_string(commandQueue[0]->fromShelfID) + std::string(".\n"));
						commandQueue[0]->order = 4;
						break;
					}
					else if (commandQueue[0]->fromRackID != 0 && commandQueue[0]->fromShelfID != 0)
					{
						if (package->getShelf().getRack().getID() != commandQueue[0]->fromRackID)
						{
							setAnswer(std::string("Podanej paczki nie ma na regale numer ") + std::to_string(commandQueue[0]->fromRackID) + std::string(".\n"));
							commandQueue[0]->order = 4;
							break;
						}
						else if (package->getShelf().getID() != commandQueue[0]->fromShelfID)
						{
							setAnswer(std::string("Podanej paczki nie ma na polce numer ") + std::to_string(commandQueue[0]->fromShelfID) + std::string(".\n"));
							commandQueue[0]->order = 4;
							break;
						}
					}
				}

				int result = flTakePackage(commandQueue[0]->packageID);

				switch (result)
				{
				case 0:
					setAnswer(std::string("Paczka o podanym numerze nie istnieje.\n"));
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
					break;
				case 1:
					setAnswer(std::string("Zdjeto paczke nr ") + std::to_string(commandQueue[0]->packageID) + ".\n");
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
					break;
				default:
					setAnswer(std::string("Na wozku znajduje sie juz paczka o numerze ") + std::to_string(result) + ".\n");
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
					break;
				}
			}
		}
	}
	break;
	case 6:
	{
		if (!forklift->isMoving())
		{
			if (Package* package = getFlPackage())
			{
				if (flPutPackage(commandQueue[0]->toRackID, commandQueue[0]->toShelfID))
				{
					setAnswer(std::string("Przewieziono paczke nr ") + std::to_string(package->getID()) + ".\n");
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
				}
				else
				{
					setAnswer(std::string("Brak miejsca na wskazanej polce.\n"));
					delete commandQueue[0];
					commandQueue.erase(commandQueue.begin());
				}
			}
			else
			{
				setAnswer(std::string("Brak informacji o numerze paczki do przewiezienia.\n"));
				delete commandQueue[0];
				commandQueue.erase(commandQueue.begin());
			}
		}
	}
	break;
	default:
		setAnswer(std::string("Nie rozpoznano polecenia.\n"));
		commandQueue.erase(commandQueue.begin());
	break;
	}
}

TCHAR* WarehouseView::getAnswer()
{
	TCHAR* answer = new TCHAR[answerText.size() + 1];
	answer[answerText.size()] = 0;
	std::copy(answerText.begin(), answerText.end(), answer);
	answerText = "";
	return answer;
}

void WarehouseView::forkliftUpdate(sf::Time time)
{
	forklift->update(time);
}

void WarehouseView::processCommand(long long CmdID)
{
	if (CmdID)
	{
		Command* command = new Command;

		command->order = int(CmdID / 100000000000);
		command->color = P_COLOR((CmdID % 100000000000) / 10000000000);
		command->material = P_MATERIAL((CmdID % 10000000000) / 1000000000);
		command->category = int((CmdID % 1000000000) / 100000000);
		command->fromRackID = int((CmdID % 100000000) / 10000000);
		command->fromShelfID = int((CmdID % 10000000) / 1000000);
		command->toRackID = int((CmdID % 1000000) / 100000);
		command->toShelfID = int((CmdID % 100000) / 10000);
		command->side = int((CmdID % 10000) / 1000);
		command->packageID = int(CmdID % 1000);

		if (command->fromRackID > 6 || command->toRackID > 6)
			setAnswer(std::string("Podany regal nie istnieje.\n"));
		else if (command->fromShelfID > 3 || command->toShelfID > 3)
			setAnswer(std::string("Podana polka nie istnieje.\n"));

		if (command->order == 1 || command->order == 2 || command->order == 4 || command->order == 5)
			commandQueue.push_back(command);
		else
			setAnswer(std::string("Nie rozpoznano polecenia.\n"));
	}
	else
	{
		setAnswer(std::string("Nie rozpoznano polecenia.\n"));
	}
}

void WarehouseView::setAnswer(std::string answer)
{
	answerText += answer;
}

int WarehouseView::flTakePackage(int packageID)
{
	if (forklift->getPackage())
		return forklift->getPackage()->getID();
	Package* targetPackage = warehouse->getPackage(packageID);
	if (targetPackage)
	{
		forklift->takePackage(*targetPackage);
		return 1;
	}
	return 0;
}

bool WarehouseView::flPutPackage(int rackID, int shelfID)
{
	Shelf& shelf = warehouse->getRack(rackID - 1).getShelf(shelfID - 1);
	if (forklift->putPackage(shelf))
		return true;
	else 
		return false;
}

Package* WarehouseView::getFlPackage()
{
	return forklift->getPackage();
}

Package* WarehouseView::getPackage(int packageID)
{
	return warehouse->getPackage(packageID);
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