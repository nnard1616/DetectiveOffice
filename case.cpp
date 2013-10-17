#include "case.h"
#include "Date.h"
using namespace DateNS;
ostream& operator<< (ostream& osObject, const Case& query){
  osObject << '\t';
  if (query.completed)
      osObject << query.CaseDesc  << " | "
               << query.StartDate << " | "
               << query.EndDate   << " | "
               << query.Rate      << " | "
               << query.EstHours  << " | "
               << query.ActHours  << " | "
               << "Amount Due: $" << query.Rate*query.ActHours;
  else
      osObject << query.CaseDesc  << " | "
               << query.StartDate << " | "
               << query.Rate      << " | "
               << query.EstHours  << " | "
               << "Estimated Due: $" << query.Rate*query.EstHours;
  return osObject;
}

bool operator< (const Case& a, const Case& b){
  if (a.StartDate < b.StartDate)
    return true;
  else
    return false;
}

bool Case::operator==(const Case& query) const{
    if (strcmp(this->CaseDesc.c_str(), query.CaseDesc.c_str()) != 0)
        return false;
    else
        return true;
}

Case::Case(){
  CaseDesc = "-EMPTY-";
  Rate = 0.0;
  ActHours = 0.0;
  EstHours = 0;
  completed = false;
}

Case::Case(string inDesc, Date inStart, float inRate, int inEstHours){
  CaseDesc = inDesc;
  StartDate = inStart;
  Rate = inRate;
  EstHours = inEstHours;
  completed = false;
}

Case::Case(string inDesc, Date inStart, Date inEnd, float inRate, int inEstHours, float inActHours){
  CaseDesc = inDesc;
  StartDate = inStart;
  EndDate = inEnd;
  Rate = inRate;
  EstHours = inEstHours;
  ActHours = inActHours;
  completed = true;
}

Case::Case(const Case &orig){
  CaseDesc = orig.CaseDesc;
  StartDate = orig.StartDate;
  EndDate = orig.EndDate;
  Rate = orig.Rate;
  EstHours = orig.EstHours;
  ActHours = orig.ActHours;
  completed = orig.completed;
}

void Case::setCompletion(Date inDate, int inHours){
  EndDate = inDate;
  ActHours = inHours;
  completed = true;  
}

float Case::calcDue(){
    if (completed)
        return (Rate*ActHours);
    else
        return (Rate*EstHours);
}


