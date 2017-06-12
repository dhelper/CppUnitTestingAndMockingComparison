#pragma once
#include "DataAccess.h"
#include "RestApiClient.h"

class Calculator
{
	DataAccess& _dataAccess;
	RestApiClient& _client;
public:
	Calculator(DataAccess& dataAccess, RestApiClient& restClient);
	~Calculator();

	int CalculateNextData() const;
};

