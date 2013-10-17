#include "client.h"
#include <algorithm>

ostream& operator<< (ostream& osObject, const Client& query){
    osObject << query.LastName << ", "
             << query.FirstName << " | "
             << query.Address << " | "
             << query.ZipCode << " | "
             << query.EmailAddress << endl;
    for (auto itr = query.caseList->begin(); itr != query.caseList->end(); itr++)
        osObject << *itr << endl;
}

Client::Client(){
    LastName = "";
    FirstName = "";
    Address = "";
    ZipCode = "";
    EmailAddress = "";
    caseList = nullptr;
}

Client::Client(string inLname, string inFname, string inAddr, string inZip, string inEAddr){
    LastName = inLname;
    FirstName = inFname;
    Address = inAddr;
    ZipCode = inZip;
    EmailAddress = inEAddr;
    caseList = new vector<Case>;
    caseList->reserve(10);
}

void Client::addCase(Case inCase){
    caseList->push_back(inCase);
}

void Client::removeCase(Case *inCase){//test when making UI
    for (auto itr = caseList->begin(); itr != caseList->end(); itr++){
        if(&*itr == inCase)
            cout << "Hello!" << endl;
    }
}

void Client::findCase(string query){
    vector<string> searchTerms = split(query);
    vector<Case*> hits;
    for (auto itr = caseList->begin(); itr != caseList->end(); itr++)
        if (greedy_phrase_comparison(itr->description(), query))
            hits.push_back(&*itr);//I can't believe this fucking works. :P

    cout << "Your query is similar to these cases: \n";
    for (auto itr = hits.begin(); itr != hits.end(); itr++)
        cout << **itr << endl;
}
