#pragma once

#include "http_request.h"

#include <string_view>
#include <string>
#include <map>
#include <set>

using namespace std;

class Stats {
public:
	Stats();

	void AddMethod(string_view method);
	void AddUri(string_view uri);

	const map<string_view, int> &GetMethodStats() const;
	const map<string_view, int> &GetUriStats() const;

private:
	map<string_view, int> method_stats_;
	map<string_view, int> uri_stats_;

	const set<string_view> METHODS =
			{"GET",
			 "POST",
			 "PUT",
			 "DELETE",
			 "UNKNOWN"};

	const set<string_view> URI =
			{"/",
			 "/order",
			 "/product",
			 "/basket",
			 "/help",
			 "unknown"};
};

HttpRequest ParseRequest(string_view line);