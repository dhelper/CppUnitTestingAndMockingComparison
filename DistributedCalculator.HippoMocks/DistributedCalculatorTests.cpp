#include "stdafx.h"
#include "CppUnitTest.h"
#include "hippomocks.h"
#include "../DistributedCalculator/DataAccess.h"
#include "../DistributedCalculator/RestApiClient.h"
#include "../DistributedCalculator/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DistributedCalculatorHippoMocks
{		
	TEST_CLASS(DistributedCalculatorTests)
	{
	public:
		
		TEST_METHOD(Calculate_ReturnTwoValidNumbers_ServerCalled)
		{
			MockRepository mocks;

			DataAccess* fakeDataAccess = mocks.Mock<DataAccess>();
			auto data = std::make_pair(1, 2);
			mocks.OnCall(fakeDataAccess, DataAccess::GetData).Return(data);

			RestApiClient* fakeClient = mocks.Mock<RestApiClient>();
			auto called = 0;
			mocks.ExpectCall(fakeClient, RestApiClient::HttpGet)
			.Do([&](std::string& arg)
			{
				if (arg.find("/Add?1&2") != std::string::npos)
					called++;

				return "3";
			});

			Calculator calculator(*fakeDataAccess, *fakeClient);

			calculator.CalculateNextData();
		}

	};
}