// BowlingTests.Mettle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mettle/header_only.hpp"
#include "../BowlingGame/Game.h"

using namespace mettle;
 
void RollSeveral(Game& game, int rolls, int pins) {
	for (int i = 0; i < rolls; i++) {
		game.Roll(pins);
	}
}

suite<> first("simple tests", [](auto &_) {
	_.test("When all rolles are gutterballs --> score is 0", []() {
		Game game;
		
		RollSeveral(game, 20, 0);

		expect(game.Score(), equal_to(0));
	});
	
	_.test("When all rolles are one --> score is 20", []() {
		Game game;
		
		RollSeveral(game, 20, 1);

		expect(game.Score(), equal_to(20));
	});
	
	_.test("When all rolles are two --> score is 40", []() {
		Game game;
		
		RollSeveral(game, 20, 2);

		expect(game.Score(), equal_to(40));
	});
});

struct SpareTests {
	Game game;
};

suite<SpareTests> fix("fixture suite", [](auto &_) {

	_.setup([](SpareTests &f) {
		f.game.Roll(7);
		f.game.Roll(3);
	});

	_.test("next round is zero --> score is 10", [](SpareTests &f) {
		f.game.Roll(0);
		f.game.Roll(0);

		expect(f.game.Score(), equal_to(10));
	});

	_.test("Spare in the first round --> value equals secod round first roll + 10", [](SpareTests &f) {
		f.game.Roll(4);
		f.game.Roll(0);

		expect(f.game.Score(), equal_to(18));
	});
});