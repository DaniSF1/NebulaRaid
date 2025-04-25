#pragma once
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "../utils/GameWorld.h"
#include "BerserkerMovementMode.h"


class BerserkerMovement : public IMovementBehavior
{
public:
	BerserkerMovement();
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;
	void changeCicle(Enemy* enemy);
	BerserkerMovementMode getMode() { return mode; }

private:
	const float stalkingSpeed = 500.f;
	const float speed = 300.f;
	const float damageThreshold = 40.f;
	const float radius = 250.f;
	const float tpDelay = 2.f;
	const float cycleTime = 20.f;

	float lastHealth = 0.f;
	bool finished = false;
	float currentCycle = cycleTime;
	float tpTime = tpDelay;
	float maxActiveSec = 240.f;
	Player* player;
	BerserkerMovementMode mode = BerserkerMovementMode::Random;
	Vector2 targetPos, direction;
	Rectangle movBounds = { 0.f, 0.f, 720.f, 400.f };
	float offsetX;
	float offsetY;
	float targetX;
};