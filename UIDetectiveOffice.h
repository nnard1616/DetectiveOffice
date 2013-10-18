#ifndef UIDETECTIVEOFFICE_H
#define UIDETECTIVEOFFICE_H
#include "Date.h"
#include "client.h"
#include "case.h"
#include <list>

class UIDetectiveOffice
{
private:
    list<Client> clientlist;
    Client* currClient;
    Case* currCase;

    char menu();

    void addClient();
    void findClient();//find client by last name
    void removeClient();
    void printClientInfo();//prints name and address
    void printclientFile();//prints name and address plus case list

    void addCaseToClient();//adds case to client just found
    void findCaseFromClient(); //find case from client just found, use greedy search alg
    void printCaseInfo();//print info of case just found
    void removeCaseFromClient(); //remove case from client just found, develop client.removeCase to take a Case pointer
    void calculateTotalDue(); // Prints the total amount due for all cases for client just found

    void listAllClientInfo();//prints name and address for all clients
    void listAllClientFiles();//prints name and address plus case list for all clients

    void populateClients();

public:
    UIDetectiveOffice();
    void process();
};

#endif // UIDETECTIVEOFFICE_H
