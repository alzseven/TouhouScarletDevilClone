#pragma once

class Item;
class ItemBehavior
{
	virtual ~ItemBehavior() {};

	virtual void Update(Item* item, float dt) = 0;
	virtual void Collect(Item* item) = 0;

};

