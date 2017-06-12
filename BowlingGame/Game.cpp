#include "stdafx.h"
#include "Game.h"
#include <cstring>

Game::Game() : _round(0)
{
	std::memset(_rolls, 0, sizeof(_rolls));
}


Game::~Game()
{
}

int Game::Score() const {
	int total = 0;
	for (int i = 0; i < 21; ++i) {
		if (_rolls[i] == 10)
		{
			if (_round > i + 2)
			{
				total += 10 + _rolls[i + 2] + _rolls[i + 3];
			}
		}
		else if (_rolls[i] + _rolls[i + 1] == 10) {
			total += 10 + _rolls[i + 2];
			i++;
		}
		else
		{
			total += _rolls[i];
		}
	}

	return total;
}

void Game::Roll(int pins)
{
	_rolls[_round++] = pins;

	if (pins == 10)
	{
		_round++;
	}
}
