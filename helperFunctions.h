#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>


using namespace std;
vector<string> split(string query);
bool greedy_phrase_comparison(const string &searchField, const string& query);//semi greedy, actually :P
string upper(const string query);
#endif // HELPERFUNCTIONS_H
