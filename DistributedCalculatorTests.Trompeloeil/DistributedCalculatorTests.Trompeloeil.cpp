// DistributedCalculatorTests.Trompeloeil.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "trompeloeil.hpp"
#include "FakeDataAccess.h"
#include "FakeRestApiClient.h"
#include "../DistributedCalculator/Calculator.h"

namespace trompeloeil
{
	template <>
	void reporter<specialized>::send(severity s, const char* file, unsigned long line, const char* msg)
	{
		std::ostringstream os;
		if (line) os << file << ':' << line << '\n';
		os << msg;
		auto failure = os.str();
		if (s == severity::fatal)
		{
			FAIL(failure);
		}
		else
		{
			CAPTURE(failure);
			CHECK(failure.empty());
		}
	}
}

using namespace trompeloeil;

TEST_CASE("Calculate with two valid numbers --> server called")
{
	FakeDataAccess fakeDataAccess;
	auto data = std::make_pair(1, 2);
	ALLOW_CALL(fakeDataAccess, GetData()).RETURN(data);

	std::string dummy = "http://base";
	FakeRestApiClient fakeClient(dummy);

	REQUIRE_CALL(fakeClient, HttpGet(eq("/Add?1&2"))).RETURN("3").TIMES(1);

	Calculator calculator(fakeDataAccess, fakeClient);

	calculator.CalculateNextData();
}