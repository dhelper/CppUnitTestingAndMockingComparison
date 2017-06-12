#pragma once
class Game
{
	int _rolls[21];
	int _round;
public:
	Game();
	~Game();

	int Score() const;
	void Roll(int);
};

