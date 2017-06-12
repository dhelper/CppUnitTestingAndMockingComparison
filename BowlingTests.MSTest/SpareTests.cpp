#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BowlingGame/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BowlingTestsMSTest
{
	TEST_CLASS(SpareTests)
	{
		Game game;
	public:

		TEST_METHOD_INITIALIZE(RollSpareInFirstRound)
		{
			game.Roll(7);
			game.Roll(3);
		}

		TEST_METHOD(SecondRoundZero_ScoreIsZero)
		{
			game.Roll(0);
			game.Roll(0);

			Assert::AreEqual(10, game.Score());
		}

		TEST_METHOD(RollSomeValueInSecondRound_ScoreEqualValuePlusTenPlusRound)
		{
			game.Roll(4);
			game.Roll(2);

			Assert::AreEqual(20, game.Score());
		}
	};
}