#pragma once
#include "../DistributedCalculator/RestApiClient.h"
#include "trompeloeil.hpp"

class FakeRestApiClient : public RestApiClient
{
public:

	FakeRestApiClient(const std::string& baseUrl)
		: RestApiClient(baseUrl)
	{
	}

	MAKE_MOCK1(HttpGet, std::string(std::string&), override);
};
