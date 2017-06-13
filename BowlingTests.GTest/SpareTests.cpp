#include "stdafx.h"
#include "gtest/gtest.h"
#include "../BowlingGame/Game.h"

using namespace testing;

class SpareTests : public Test
{
protected:
	Game game;

	void SetUp() override
	{
		game.Roll(7);
		game.Roll(3);
	}
};

TEST_F(SpareTests, SecondRoundZero_ScoreIsTen)
{
	game.Roll(0);
	game.Roll(0);

	ASSERT_EQ(10, game.Score());
}

TEST_F(SpareTests, RollSomeValueInSecondRound_ScoreEqualValuePlusTenPlusRound)
{
	game.Roll(4);
	game.Roll(2);

	ASSERT_EQ(20, game.Score());
}