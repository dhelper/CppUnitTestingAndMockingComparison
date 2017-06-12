// DistributedCalculatorTests.GMock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gmock/gmock.h"
#include "FakeDataAccess.h"
#include "FakeRestApiClient.h"
#include "../DistributedCalculator/Calculator.h"

using namespace testing;

TEST(DistributedCalculatorTests, Calculate_ReturnTwoValidNumbers_ServerCalled)
{
	FakeDataAccess fakeDataAccess;
	auto data = std::make_pair(1,2);
	EXPECT_CALL(fakeDataAccess, GetData()).WillRepeatedly(Return(data));
	
	std::string dummy = "http://base";
	FakeRestApiClient fakeClient(dummy);

	EXPECT_CALL(fakeClient, HttpGet(StrEq("/Add?1&2"))).Times(1).WillOnce(Return("3"));

	Calculator calculator(fakeDataAccess, fakeClient);

	calculator.CalculateNextData();
}

int main(int argc, char** argv)
{
	InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

