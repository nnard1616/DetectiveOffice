#ifndef Case_h
#define Case_h

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include "Date.h"

using namespace DateNS;

class Case{
  friend ostream& operator<< (ostream& osObject, const Case& query);
  friend bool operator<(const Case& a, const Case& b);//for sorting by startDate
  public:
    Case();//default
    Case(string inDesc, Date inStart, float inRate, int inEstHours); //not completed
    Case(string inDesc, Date inStart, Date inEnd, float inRate, int inEstHours, float inActHours);//completed
    Case(const Case& orig);//copy constructor
    string description(){return CaseDesc;}

    void setCompletion(Date inDate, int inHours);
    bool isCompleted(){ return completed;}
    bool operator==(const Case& query) const;
  private:
    string CaseDesc;
    Date StartDate, EndDate;
    float Rate, ActHours;
    int EstHours;
    bool completed;
};

vector<string> split(string query);
bool equal_to_insensitive( char c1, char c2 );
int case_insensitive_comparison( const string& s1, const string& s2 );
bool greedy_phrase_comparison(const string &searchField, const string& query);//semi greedy, actually :P
#endif
