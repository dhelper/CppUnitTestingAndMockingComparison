#pragma once
#include <string>

class RestApiClient
{
	const std::string& _baseUrl;

public:
	RestApiClient(const std::string& baseUrl);
	~RestApiClient();

	virtual std::string HttpGet(std::string& url);
};

