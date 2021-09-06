#include "stats.h"

Stats::Stats() {
	for (const auto &key: METHODS) {
		method_stats_[key] = 0;
	}
	for (const auto &key: URI) {
		uri_stats_[key] = 0;
	}
}

void Stats::AddMethod(string_view method) {
	if (METHODS.count(method) != 0) { method_stats_[method]++; }
	else { method_stats_["UNKNOWN"]++; }
}

void Stats::AddUri(string_view uri) {
	if (URI.count(uri) != 0) { uri_stats_[uri]++; }
	else { uri_stats_["unknown"]++; }
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats_;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats_;
}

HttpRequest ParseRequest(string_view line) {
	HttpRequest result;
	size_t pos = 0;
	size_t space = 0;
	size_t pos_end = line.npos;
	while(line[pos] == ' ') { ++pos; }
	for (auto i = 0; i < 3; ++i) {
		space = line.find(' ', pos);
		switch (i) {
			case 0:
				result.method = space == pos_end ? line.substr(pos) : line.substr(pos, space - pos);
				pos = space + 1;
				break;
			case 1:
				result.uri = space == pos_end ? line.substr(pos) : line.substr(pos, space - pos);
				pos = space + 1;
				break;
			case 2:
				result.protocol = space == pos_end ? line.substr(pos) : line.substr(pos, space - pos);
				pos = space + 1;
				break;
		}
	}
	return result;
}