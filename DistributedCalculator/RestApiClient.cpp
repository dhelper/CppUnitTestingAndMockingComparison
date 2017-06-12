#include "stdafx.h"
#include "RestApiClient.h"
#include "curl/curl.h"

using namespace std;

RestApiClient::RestApiClient(const string& baseUrl): _baseUrl(baseUrl) {
}


RestApiClient::~RestApiClient()
{
}

string buffer;
size_t curl_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
	buffer.append(static_cast<char*>(ptr), size*nmemb);
	return size*nmemb;
}

string RestApiClient::HttpGet(string& url)
{
	CURL *curl = curl_easy_init();
	if (!curl)
	{
		// TODO: handle error
		curl_easy_cleanup(curl);
		return "";
	}

	buffer.clear();
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

	curl_easy_setopt(curl, CURLOPT_URL, _baseUrl + url.c_str());

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}");
	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (res != CURLE_OK)
	{
		// TODO: handle error

		return "";
	}

	return buffer;
}