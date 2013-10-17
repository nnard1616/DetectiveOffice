#ifndef Client_h
#define Client_h
#include <vector>
#include "case.h"

class Client{
  friend ostream& operator<< (ostream& osObject, const Client& query);
  public:
    Client();
    Client(string inLname, string inFname, string inAddr, string inZip, string inEAddr);

    void addCase(Case inCase);
    void removeCase(Case *inCase);
    void findCase(string query);
    float calcDues(float inRate, float inHours);
    void printHi(){cout << "Hi!" << endl;}

  private:
    vector<Case> *caseList;
    string LastName, FirstName, Address, ZipCode, EmailAddress;

};


#endif