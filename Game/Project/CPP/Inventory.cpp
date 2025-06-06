#include "Inventory.h"

Inventory::Inventory(sf::RenderWindow* _window, Player* _player, UIManager* _uiManager) :
	window{ _window }, uiManager{ _uiManager }, player{ _player }, isOpen{ false },
	choose{nullptr}, nowKey{0}, invetState{ [=](float deltaTime) {update();}, [=]() {drawInvent();} }
{	
	auto& event = EventSystem::getInstance();
	event.subscribe<int>("SAVE", [=](const int NON) { save(); });

	event.subscribe<int>("RESET_GAME", [=](const int NON) { items.clear(); });

	event.subscribe<int>("WIN_GAME", [&](const int NON) { items.clear(); });
}

Item* Inventory::takeMaxHeal()
{
	Item* maxHeal = nullptr;

	for (const auto& [item, count] : items)
	{
		auto healItem = dynamic_cast<Item*>(item);
		if (healItem && healItem->type == Heal)
		{
			if (!maxHeal || healItem->id > maxHeal->id)
			{
				maxHeal = healItem;
			}
		}
	}

	return maxHeal;
}

void Inventory::takeItem(Itemble* item, int cnt)
{
	if (item) { items[item] += cnt; }
}

void Inventory::useItem(Itemble* item, int cnt)
{
	if (!item) return;

	if (items[item] - cnt >= 0)
	{
		items[item] -= cnt;

		if (items[item] == 0)
		{
			items.erase(item);
		}
	}
}

void Inventory::save()
{
	std::vector<std::pair<int, int>> inv;

	for (auto it : items)
	{
		inv.push_back({ it.first->id, it.second });
	}

	auto& data = Data::getInstance();
	data.saveInvent(inv);
}

void Inventory::useInvent() 
{ 
	uiManager->deleteNow();
	isOpen = !isOpen;
	window->setMouseCursorVisible(isOpen);

	auto& event = EventSystem::getInstance();
	event.trigger<RenderState*>("SWAP_STATE", isOpen ? &invetState : nullptr);

	if (!isOpen)
	{
		choose = nullptr;
	}
	else
	{
		initInv();
	}
}

void Inventory::initInv()
{
	uiManager->deleteNow();
	uiManager->initInvent(items, choose, player);
}

void Inventory::checkChose()
{
	if (nowKey >= 100)
	{
		selectedItem();
	}
	else
	{
		selectItemById();
	}
}

void Inventory::selectedItem()
{
	if (auto item = dynamic_cast<Item*>(choose); item) 
	{ useSelectedItem(item); }
	else if (auto gun = dynamic_cast<Gun*>(choose); gun) 
	{ useSelectedGun(gun); }
	else if (auto improve = dynamic_cast<Improve*>(choose); improve) 
	{ useSelectedImprove(improve); }
	
	choose = nullptr;
	initInv();
}

void Inventory::selectItemById()
{
	for (const auto& [item, count] : items)
	{
		if (item->id == nowKey)
		{
			choose = item;
			initInv();
			break;
		}
	}
}

void Inventory::useSelectedItem(Item* item)
{
	item->useFunc(player);
	useItem(choose);
}

void Inventory::useSelectedGun(Gun* gun)
{
	if (nowKey == 100)
	{
		if (player->getGun(2) != gun) { player->setGun(gun, 1); }
	}
	else if (nowKey == 101)
	{
		if (player->getGun(1) != gun) { player->setGun(gun, 2); }
	}
	else
	{
		int i = 102;
		for (auto it : gun->improvement)
		{
			if (i == nowKey)
			{
				items[dynamic_cast<Itemble*>(gun->deleteImprove(it.first))] += 1;
				break;
			}

			i++;
		}
	}
}

void Inventory::useSelectedImprove(Improve* improve)
{
	Gun* targetGun = nullptr;

	if (nowKey == 100) { targetGun = player->getGun(1); }
	else if (nowKey == 101) { targetGun = player->getGun(2); }

	if (targetGun)
	{
		useItem(choose);
		if (auto removedImprove = targetGun->trySetImprove(improve); removedImprove)
		{
			items[dynamic_cast<Itemble*>(removedImprove)] += 1;
		}
	}
}

void Inventory::update()
{
	if (!window->hasFocus()) return;

	static bool isMouseDown = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseDown)
	{
		isMouseDown = true;

		int key = uiManager->checkButton();
		if (key != -1)
		{
			nowKey = key;
			checkChose();
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		isMouseDown = false;
	}
}

void Inventory::drawInvent()
{
	uiManager->drawNow();
}
