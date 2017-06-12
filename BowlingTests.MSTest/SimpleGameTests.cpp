#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BowlingGame/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BowlingTestsMSTest
{		
	void RollSeveral(Game& game, int rolls, int pins) {
		for (int i = 0; i < rolls; i++) {
			game.Roll(pins);
		}
	}

	TEST_CLASS(SimpleGameTests)
	{
		Game game;
	public:
		
		TEST_METHOD(AllRollsAreGutterBalls_ScoreIsZero)
		{
			RollSeveral(game, 20, 0);

			Assert::AreEqual(0, game.Score());
		}

		TEST_METHOD(AllRollsAreOne_ScoreIs20)
		{
			RollSeveral(game, 20, 1);

			Assert::AreEqual(20, game.Score());
		}

		TEST_METHOD(AllRollsAreTwo_ScoreIs40)
		{
			RollSeveral(game, 20, 2);

			Assert::AreEqual(40, game.Score());
		}
	};
}