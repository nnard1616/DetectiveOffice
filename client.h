#ifndef Client_h
#define Client_h
#include "case.h"

class Client{
  friend ostream& operator<< (ostream& osObject, const Client& query);//prints client info and case info
  friend bool operator<(const Client& a, const Client& b);//for sorting by client lastname
  public:
    Client();
    Client(string inLname, string inFname, string inAddr, string inZip, string inEAddr);

    void addCase(Case inCase);
    void removeCase(Case *inCase);
    Case *findCase(string query);
    void calcDues();
    void printInfo();//prints just client info, not case info

    string lname(){return LastName;}
    void sortCases();
    int numCases(){return caseList->size();}

  private:
    vector<Case> *caseList;
    string LastName, FirstName, Address, ZipCode, EmailAddress;

};


#endif
