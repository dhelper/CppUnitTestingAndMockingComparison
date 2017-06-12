#include "stdafx.h"
#include "Calculator.h"
#include <sstream>

using namespace std;

Calculator::Calculator(DataAccess& dataAccess, RestApiClient& restClient) : _dataAccess(dataAccess), _client(restClient)
{
}


Calculator::~Calculator()
{
}

int Calculator::CalculateNextData() const
{
	auto data = _dataAccess.GetData();

	ostringstream oss;
	oss << "/Add?" << data.first << "&" << data.second;
	auto result = _client.HttpGet(oss.str());

	return stoi(result);
}
