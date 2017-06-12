// DistibutedCalculator.FakeIt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "fakeit.hpp"
#include "../DistributedCalculator/Calculator.h"

using namespace fakeit;

bool has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

TEST_CASE("Calculate with two valid numbers --> server called")
{
	Mock<DataAccess> fakeDataAccess;

	auto data = std::make_pair(1, 2);
	When(Method(fakeDataAccess, GetData)).Return(data);

	std::string dummy = "http://base";
	Mock<RestApiClient> fakeClient;

	When(Method(fakeClient, HttpGet)).Return("3");

	Calculator calculator(fakeDataAccess.get(), fakeClient.get());

	calculator.CalculateNextData();

	Verify(Method(fakeClient, HttpGet)).AtLeastOnce();
}