#pragma once
#include "BaseObject.h"

class Ball : public BaseObject
{
public:
	bool moving = false;
	bool paused = false;
	int x_velocity = 0;
	int y_velocity = 0;
	void Update();
};