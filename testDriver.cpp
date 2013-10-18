#include "case.h"
#include "client.h"
#include "UIDetectiveOffice.h"

void testDriver(){
  Case testCase;
  cout << testCase << endl;
  testCase = Case("Lost a Cat", Date(10,11,2013), 15.50, 20);
  cout << testCase << endl;
  if (testCase.isCompleted()) cout << "Yes\n";
  else cout << "No\n";
  testCase.setCompletion(Date(10,15,2013), 25);
  cout << testCase << endl;
  if (testCase.isCompleted()) cout << "Yes\n";
  else cout << "No\n";

  Case testCase2;
  testCase2 = testCase;
  if (testCase2 == testCase)
      cout << "Yup" << endl;

  Client Frank("Grimmes", "Frank", "45654 Evergreen Terr", "684651", "f.grimmes@gmail.com");

  Frank.addCase(Case("Stolen Car", Date(7,12, 2013), Date(10,9,2013), 5.0, 17, 15));
  Frank.addCase(testCase);
  Frank.addCase(Case("Lost Dog", Date(10,11, 2013), Date(10,13,2013), 20.5, 9, 20));
  Frank.addCase(Case("Missing child", Date(6,12, 2013), Date(7,13,2013), 7.8, 100, 2));
  Frank.addCase(Case("Cheating Hussie", Date(7,12, 2013), 5.5, 9));

  Client Buck("Grimmes", "Christie", "45654 Evergreen Terr", "684651", "f.grimmes@gmail.com");
  Frank.removeCase(&testCase);

  string str1 = "Hello There Dave";
  string str2 = "Hello There Frank";
  string str3 = "frankr";
  string str4 = "FraNkf";

  vector<string> sList = split(str1);
  for (auto itr = sList.begin(); itr != sList.end(); itr++)
      cout << (*itr) << " | ";
  cout << endl;
  cout << strcmp(str1.c_str(), str2.c_str()) << endl;

  cout << "------------------------------------" << endl;

  cout << case_insensitive_comparison(str3, str4) << endl;


  list<int> iList;
  iList.push_back(1);
  iList.push_back(2);
  iList.push_back(3);

  for (auto itr = iList.begin(); itr != iList.end(); itr++){
      cout << *itr << " ";
  }
  cout << endl;

  if (Frank < Buck)
      cout << 'a' << endl;
  else if (not(Frank<Buck) && not(Buck<Frank))
      cout << 'b' << endl;
  else
      cout << 'c' << endl;

  cout << "Unsorted" << endl << Frank;
  Frank.sortCases();
  cout << "Sorted" << endl << Frank;


}

int main() {
	cout << "Run test driver (T) or user interface (U): ";
	char choice, inchoice;
	cin >> inchoice;
	choice = toupper(inchoice);
	if (choice == 'T')
		testDriver();
	else if (choice == 'U') {
        UIDetectiveOffice ui;
        ui.process();
	}
	return 0;
}
