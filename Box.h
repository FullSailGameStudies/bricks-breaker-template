#pragma once
#include "BaseObject.h"

class Box : public BaseObject
{
public:
	int boxHealth = 3;
	bool doubleThick = false;
	int width = 2;
	int height = 2;
	void Draw() const override;
	bool Contains(int x, int y);
	void DecreaseBoxHealth();
};