// BowlingTests.Catch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../BowlingGame/Game.h"

void RollSeveral(Game& game, int rolls, int pins) {
	for (int i = 0; i < rolls; i++) {
		game.Roll(pins);
	}
}

TEST_CASE("Simple Bowling score -- without score or strike", "[BowlingKata]")
{
	Game game;

	SECTION("All rolls are gutter balls --> score == 0") {
		RollSeveral(game, 20, 0);

		REQUIRE(game.Score() == 0);
	}

	SECTION("All rolls are 1 --> score == 20") {
		RollSeveral(game, 20, 1);

		REQUIRE(game.Score() == 20);
	}

	SECTION("All rolls are 2 --> score == 40", "[Run me]") {
		RollSeveral(game, 20, 2);

		REQUIRE(game.Score() == 40);
	}
}

TEST_CASE("Using spare")
{
	Game game;

	SECTION("Spare in the first round --> value equals secod round first roll + 10")
	{
		game.Roll(7);
		game.Roll(3);
		game.Roll(4);
		RollSeveral(game, 17, 0);

		REQUIRE(game.Score() == 18);
	}
}

SCENARIO("First roll is strike")
{
	GIVEN("Bowled strike on first turn")
	{
		Game game;
		game.Roll(10);

		WHEN("All rest rolls are gutter balls")
		{
			RollSeveral(game, 18, 0);
			THEN("Total score is 10")
			{
				REQUIRE(game.Score() == 10);
			}
		}

		WHEN("Next two rolls are not spare or strike")
		{
			game.Roll(3);
			game.Roll(4);
			RollSeveral(game, 16, 0);

			THEN("Total score is 10 plus twice the sum of these rolls")
			{
				REQUIRE(game.Score() == 24);
			}
		}

		WHEN("Next roll is spare then all gutter balls")
		{
			game.Roll(3);
			game.Roll(7);
			RollSeveral(game, 16, 0);

			THEN("Total score is 30")
			{
				REQUIRE(game.Score() == 30);
			}
		}

		WHEN("Next roll is spare then roll five")
		{
			game.Roll(3);
			game.Roll(7);
			game.Roll(5);
			RollSeveral(game, 15, 0);

			THEN("Total score is 40")
			{
				REQUIRE(game.Score() == 40);
			}
		}

		WHEN("Next two rolls are strike then gutter balls")
		{
			game.Roll(10);
			game.Roll(10);
			RollSeveral(game, 16, 0);

			THEN("Total score is 60")
			{
				REQUIRE(game.Score() == 60);
			}
		}
	}
}