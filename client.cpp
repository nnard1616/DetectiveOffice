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
    return osObject;
}

bool operator< (const Client& a, const Client& b){
    if (upper(a.LastName) < upper(b.LastName))
        return true;
    else if (upper(a.LastName) == upper(b.LastName)){
        if (upper(a.FirstName) < upper(b.FirstName))
            return true;
        else
            return false;
    }
    else
        return false;
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

void Client::removeCase(Case *inCase){
    for (auto itr = caseList->begin(); itr != caseList->end(); itr++){
        if(&*itr == inCase){
            caseList->erase(itr);
            break;
        }
    }
}

Case* Client::findCase(string query){
    vector<string> searchTerms = split(query);
    vector<Case*> hits;
    char choice[10];

    for (auto itr = caseList->begin(); itr != caseList->end(); itr++)
        if (greedy_phrase_comparison(itr->description(), query))
            hits.push_back(&*itr);//I can't believe this fucking works. :P
    if (hits.size() > 1){
        cout << "Found " << hits.size() << " relevant cases: " << endl;
        int c = 1;
        for (auto itr = hits.begin(); itr != hits.end(); itr++){
            cout << c << ") " << **itr << endl;
            c++;
        }
        cout << "Please enter the number of the case you wish to select: ";
        cin >> choice;
        cout << "The case is currently selected: " << endl << *(hits[atoi(choice)-1]) << endl;
        return hits[atoi(choice)-1];
    }
    else if(hits.size() ==1){
        cout << "Found 1 case, and it is currently selected: " << endl << *(hits[0]) << endl;
        return hits[0];
    }
    else
        cout << "No relevant cases found" << endl;
    return nullptr;
}

void Client::printInfo(){
    cout << LastName << ", "
         << FirstName << " | "
         << Address << " | "
         << ZipCode << " | "
         << EmailAddress << endl;
}


void Client::calcDues(){
    float estDue = 0.0;
    float actDue = 0.0;
    for (auto itr = caseList->begin(); itr != caseList->end(); itr++){
        if (itr->isCompleted() == true)
            actDue += itr->calcDue();
        else
            estDue += itr->calcDue();
    }

    cout << "Actual Amount Due for Completed Cases: $" << actDue << endl
         << "Estimated Amount Due for Incomplete Cases: $" << estDue << endl;
}

void Client::sortCases(){
    vector<Case> ordered;
    do{
        vector<Case>::iterator earliest = caseList->begin();
        for (auto itr = caseList->begin(); itr != caseList->end(); itr++){
            if(*itr < *earliest)
                earliest = itr;
            else if(not(*itr < *earliest) && not(*earliest < *itr)) //same start date
                if (upper(itr->description()) < upper(earliest->description()))//sort by description
                    earliest = itr;
        }
        ordered.push_back(*earliest);
        caseList->erase(earliest);
    } while (caseList->size() != 0);
    caseList->swap(ordered);//I'm so fucking clever. xD
}
