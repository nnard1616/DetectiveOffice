#include "UIDetectiveOffice.h"

UIDetectiveOffice::UIDetectiveOffice(){
    populateClients();
    currClient = nullptr;
    currCase = nullptr;
}

char UIDetectiveOffice::menu(){
    char choice;
    string inchoice;
    bool notanoption = true;
    do{
       cout << "A) Add a new client" << endl
            << "F) Find a client by last name" << endl
            << "R) Remove client just found" << endl
            << "I) Print client info just found" << endl
            << "C) Print client info and case info just found" << endl
            << "S) Search for case for client just found" << endl
            << "D) Delete case just found" << endl
            << "E) Print total amount due for client just found" << endl
            << "L) List all clients on file" << endl
            << "K) List all clients on file with case info" << endl
            << "X) Exit" << endl;
       cin >>  inchoice;
       choice = toupper(inchoice[0]);
       string choicecheck(1,choice);
       if (choicecheck.find_first_of("AFRICSDELKX") == string::npos)
           cout << inchoice << " not in the list of options; redo" << endl;
       else
           notanoption = false;
    } while (notanoption == true);
    return choice;
}

void UIDetectiveOffice::process() {
    char choice;
    do {
        choice = menu();
        switch(choice) {
            case 'A':
              addClient();
              break;
            case 'F':
              findClient();
              break;
            case 'R':
              removeClient();
              break;
            case 'I':
              printClientInfo();
              break;
            case 'C':
              printclientFile();
              break;
            case 'S':
              findCaseFromClient();
              break;
            case 'D':
              removeCaseFromClient();
              break;
            case 'E':
              calculateTotalDue();
              break;
            case 'L':
              listAllClientInfo();
              break;
            case 'K':
              listAllClientFiles();
              break;
            case 'X':
              ;
            default:
              cout << "User entered " << choice << " for their choice" << endl;
        }
    } while (choice != 'X');
}

void UIDetectiveOffice::populateClients(){
    Client Client1("Grimmes", "Sally", "489431 Bekjf Rd", "459125", "ssally@gmail.com");
    Client1.addCase(Case("Lost Hat", Date(10, 1, 2013), 5.5, 45));
    Client1.addCase(Case("Missing Fork", Date(10, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    Client1.addCase(Case("Raccoon in Attic", Date(9, 3, 2013), Date(9, 7, 2013), 50, 2, 3));
    Client1.addCase(Case("Missing Spatula", Date(10, 1, 2013), 7.5, 2));
    clientlist.push_back(Client1);

    Client Client2("Star", "Patrick", "15 Rock Rd", "154112", "rock@gmail.com");
    Client2.addCase(Case("Lost Under Rock", Date(10, 13, 2013), 5.5, 45));
    Client2.addCase(Case("Lost Rock at Beach", Date(10, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    Client2.addCase(Case("Pants on Head", Date(10, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    clientlist.push_back(Client2);

    Client Client3("Squarepants", "SpongeBob", "15 Pineapple Rd", "154112", "pineapple@gmail.com");
    Client3.addCase(Case("Stolen Spatula", Date(10, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    Client3.addCase(Case("Missing Spats", Date(8, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    Client3.addCase(Case("Friend Stole Pet Snail", Date(6, 3, 2013), Date(10, 7, 2013), 10.3, 2, 95));
    clientlist.push_back(Client3);

    Client Frank("Grimmes", "Frank", "45654 Evergreen Terr", "684651", "f.grimmes@gmail.com");
    Frank.addCase(Case("Lost Dog", Date(10,12, 2013), Date(10,13,2013), 20.5, 9, 20));
    Frank.addCase(Case("Cheating Hussie", Date(9,12, 2013), 5.5, 9));
    Frank.addCase(Case("Missing child", Date(6,12, 2013), Date(7,13,2013), 7.8, 100, 2));
    Frank.addCase(Case("Lost Car", Date(7,12, 2013), Date(10,9,2013), 5.0, 17, 15));
    clientlist.push_back(Frank);

}

void UIDetectiveOffice::addClient(){
    char choice = 'N';
    string inchoice;
    string lname, fname, addr, zip, eaddr;
    cout << "Please enter Last Name: ";
    cin >> lname;
    cout << "Please enter First Name: ";
    cin >> fname;
    cout << "Please enter Address: ";
    getline(cin, addr);// gets remaining newline in buffer
    getline(cin, addr);// actually populates desc with line of data
    cout << "Please enter Zip Code: ";
    cin >> zip;
    cout << "Please enter Email Address: ";
    cin >> eaddr;
    Client temp(lname, fname, addr, zip, eaddr);

    string iscompleted;
    string desc;
    Date sDate, eDate;
    float rt, ah;
    int eh;
    do{
        cout << "Would you like to add a case to the client's file? (y/n): ";
        cin >> inchoice;
        choice = toupper(inchoice[0]);

        if (choice == 'Y'){
            do{
                cout << "Is this case completed? (y/n): ";
                cin >> iscompleted;
            } while (toupper(iscompleted[0]) != 'Y' && toupper(iscompleted[0]) != 'N');

            cout << "Please enter Case Description: ";
            getline(cin, desc);
            getline(cin, desc);
            cout << "Please enter start date (mm dd yyyy): ";
            cin >> sDate;
            cout << "Please enter pay rate: ";
            cin >> rt;
            cout << "Please enter estimated hours to completion: ";
            cin  >> eh;
            if (toupper(iscompleted[0]) == 'Y'){
                cout << "Please enter end date (mm dd yyyy): ";
                cin >> eDate;
                cout << "Please enter actual hours to completion: ";
                cin >> ah;
                temp.addCase(Case(desc, sDate, eDate, rt, eh, ah));
            }
            else
                temp.addCase(Case(desc, sDate, rt, eh));
        }
    } while (choice == 'Y');
    clientlist.push_back(temp);
}

void UIDetectiveOffice::findClient(){
    cout << "Please enter last name to search by: ";
    string qName;
    char choice[10];
    cin >> qName;
    vector<Client*> hits;
    for (auto itr = clientlist.begin(); itr != clientlist.end(); itr++)
        if (case_insensitive_comparison(itr->lname(), qName) == 0)
            hits.push_back(&*itr);
    if (hits.size() > 1){
        cout << "Found " << hits.size() << " clients by that name: " << endl;
        int c = 1;
        for (auto itr = hits.begin(); itr != hits.end(); itr++){
            cout << c << ") " << **itr << endl;
            c++;
        }
        cout << "Please enter the number of the client you wish to select: ";
        cin >> choice;
        cout << "The client is currently selected: " << endl << *(hits[atoi(choice)-1]);
        currClient = hits[atoi(choice)-1];
    }
    else if(hits.size() ==1){
        cout << "Found 1 client by that name, and they are currently selected: " << endl << *(hits[0]);
        currClient = hits[0];
    }
    else
        cout << "No one found with that name" << endl;
}

void UIDetectiveOffice::removeClient(){
    if (currClient == nullptr)
        cout << "No client is selected" << endl;
    else
        for (auto itr = clientlist.begin(); itr != clientlist.end(); itr++)
            if (&*itr == currClient){
                currClient = nullptr;
                currCase = nullptr;
                clientlist.erase(itr);
                cout << "Successfully removed the client\n";
                break;
            }
}

void UIDetectiveOffice::printClientInfo(){
    if (currClient == nullptr)
        cout << "No client is selected" << endl;
    else
        currClient->printInfo();
}

void UIDetectiveOffice::printclientFile(){
    if (currClient == nullptr)
        cout << "No client is selected" << endl;
    else
        cout << *currClient << endl;
}

void UIDetectiveOffice::findCaseFromClient(){
    string query;
    if (currClient == nullptr)
        cout << "No client is selected" << endl;
    else{
        cout << "Please enter search terms: ";
        getline(cin, query);
        getline(cin, query);
        currCase = currClient->findCase(query);
    }
}

void UIDetectiveOffice::removeCaseFromClient(){
    if (currCase == nullptr)
        cout << "No case is selected" << endl;
    else{
        currClient->removeCase(currCase);
        cout<< "Success" << endl;
        currCase = nullptr;
    }
}

void UIDetectiveOffice::calculateTotalDue(){
    if (currClient == nullptr)
        cout << "No Client is selected" << endl;
    else
        currClient->calcDues();
}

void UIDetectiveOffice::listAllClientInfo(){
    for (auto itr = clientlist.begin(); itr != clientlist.end(); itr++)
        itr->printInfo();
}

void UIDetectiveOffice::listAllClientFiles(){
    for (auto itr = clientlist.begin(); itr != clientlist.end(); itr++)
        cout << *itr << endl;
}
