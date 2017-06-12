// BowlingTests.GTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "../BowlingGame/Game.h"

using namespace testing;


void RollSeveral(Game& game, int rolls, int pins) {
	for (int i = 0; i < rolls; i++) {
		game.Roll(pins);
	}
}

TEST(SimpleGameTests, AllRollsAreGutterBalls_ScoreIsZero)
{
	Game game;

	RollSeveral(game, 20, 0);

	ASSERT_EQ(0, game.Score());
}

TEST(SimpleGameTests, AllRollsAreOne_ScoreIs20)
{
	Game game;

	RollSeveral(game, 20, 1);

	ASSERT_EQ(20, game.Score());
}

TEST(SimpleGameTests, AllRollsAreTwo_ScoreIs40)
{
	Game game;

	RollSeveral(game, 20, 2);

	ASSERT_EQ(40, game.Score());
}


int main(int argc, char** argv)
{
	InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

