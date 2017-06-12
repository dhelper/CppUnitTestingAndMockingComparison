#pragma once
#include "../DistributedCalculator/RestApiClient.h"
#include "gmock/gmock.h"

class FakeRestApiClient : public RestApiClient
{
public:
	
	FakeRestApiClient(const std::string& baseUrl)
		: RestApiClient(baseUrl)
	{
	}

	MOCK_METHOD1(HttpGet, std::string(std::string&));
};
