#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;
vector<string> split(string query);
bool equal_to_insensitive( char c1, char c2 );
int case_insensitive_comparison( const string& s1, const string& s2 );
bool greedy_phrase_comparison(const string &searchField, const string& query);//semi greedy, actually :P
#endif // HELPERFUNCTIONS_H
