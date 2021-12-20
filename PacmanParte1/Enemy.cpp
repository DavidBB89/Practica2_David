#include "Enemy.h"
void Enemy::RandomDirection()
{
	int random = rand() %  4;
	switch (random) {
	case 0:
		direction = { 0,1 };
		break;
	case 1:
		direction = { 0,-1 };
		break;
	case 2:
		direction = { 1,0 };
		break;
	case 3:
		direction = { -1,0 };
		break;
	}
}
Enemy::Enemy() {
	spawn = { 0,0 };
	position = spawn;
	direction = { 0,0 };
	character = 'X';
	background = ConsoleUtils::CONSOLE_COLOR::BLACK;
	foreground = ConsoleUtils::CONSOLE_COLOR::RED;
}

Enemy::Enemy(COORD _spawn, float _spawn_countdown)
{
	spawn_countdown = TimeManager::getInstance().time + _spawn_countdown;
	spawn = _spawn;
	position = spawn;
	direction = { 0,0 };
	character = 'X';

	powerup_countdown = 0;

	background = ConsoleUtils::CONSOLE_COLOR::BLACK;
	foreground = ConsoleUtils::CONSOLE_COLOR::RED;

	foreground_nopowerup = ConsoleUtils::CONSOLE_COLOR::RED;
	foreground_powerup = ConsoleUtils::CONSOLE_COLOR::CYAN;
}

void Enemy::PowerUpPicked()
{
	powerup_countdown = TimeManager::getInstance().time + powerUpTime;
}

Enemy::ENEMY_STATE Enemy::Update(Map* _map, COORD playerPos)
{
	ENEMY_STATE state = ENEMY_STATE::ENEMY_NORMAL;
	if (spawn_countdown < TimeManager::getInstance().time) {

		RandomDirection();

		COORD newPosition = position;
		newPosition.X += direction.X;
		newPosition.Y += direction.Y;

		if (newPosition.X < 0)
		{
			newPosition.X = _map->Width - 1;
		}
		newPosition.X %= _map->Width;

		if (newPosition.Y < 0)
		{
			newPosition.Y = _map->Height - 1;
		}
		newPosition.Y %= _map->Height;

		switch (_map->GetTile(newPosition.X, newPosition.Y))
		{
		case Map::MAP_TILES::MAP_WALL:
			newPosition = position;
			break;
		}
		position = newPosition;

		
		if (position.X == playerPos.X && position.Y == playerPos.Y)
		{
			if (powerup_countdown <= TimeManager::getInstance().time)
			{
				state = ENEMY_STATE::ENEMY_EATED;
			}
			else
			{
				state = ENEMY_STATE::ENEMY_KILLED;
			}

		}
		if (powerup_countdown <= TimeManager::getInstance().time)
		{
			foreground = foreground_nopowerup;
		}
		else
		{
			foreground = foreground_powerup;
		}
	}
	return state;
}

void Enemy::Kill()
{
	position = spawn;
	spawn_countdown = TimeManager::getInstance().time + spawnTime;
}

void Enemy::Draw()
{
	if (spawn_countdown < TimeManager::getInstance().time)
	{
		ConsoleUtils::Console_SetPos(position);
		ConsoleUtils::Console_SetColor(foreground, background);
		std::cout << character;
	}
}
