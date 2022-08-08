#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

int rabin_karp(const string& s, const string& pattern);

void get_next(const string& pattern, vector<int>& next);

int kmp(const string& s, const string& pattern);