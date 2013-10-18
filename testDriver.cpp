#include "case.h"
#include <vector>
#include "client.h"
#include "UIDetectiveOffice.h"

void string_case() {
   string saying1( "A bird in the hand is worth two in the bush" );
   string saying2( "A Bird in the hand is worth two in the bush" );

   cout << "USING compare()\n";

   // equivalent of strcmp()
   int result = saying1.compare( saying2 );
   if( result < 0 )
      cout << "\"" << saying1 << "\"\nis less than\n\""
         << saying2 << "\"";
   else if( result > 0 )
      cout << "\"" << saying1 << "\"\nis greater than\n\""
         << saying2 << "\"";
   else
      cout << "\"" << saying1 << "\"\nis equal to \n\""
         << saying2 << "\"";

   // now do again, using < and >

   cout << "\n\nUSING < AND >\n";

   // equivalent of strcmp()
   if( saying1 < saying2 )
      cout << "\"" << saying1 << "\"\nis less than\n\""
         << saying2 << "\"";
   else if( saying1 > saying2 )
      cout << "\"" << saying1 << "\"\nis greater than\n\""
         << saying2 << "\"";
   else
      cout << "\"" << saying1 << "\"\nis equal to\n\""
         << saying2 << "\"";
   cout << "\n---------------------------" << endl;
}

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

//  Frank.findCase("lost");

  list<int> iList;
  iList.push_back(1);
  iList.push_back(2);
  iList.push_back(3);

  for (auto itr = iList.begin(); itr != iList.end(); itr++){
      cout << *itr << " ";
  }
  cout << endl;

//  char thing[10];
//  cin >> thing;
//  cout << atoi(thing)*3;

  if (Frank < Buck)
      cout << 'a' << endl;
  else if (not(Frank<Buck) && not(Buck<Frank))
      cout << 'b' << endl;
  else
      cout << 'c' << endl;

  cout << "Unsorted" << endl << Frank;
  Frank.sortCases();
  cout << "Sorted" << endl << Frank;

    std::string foo = "alpha";
    std::string bar = "beta";

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


    string_case();
//    cout << uppercase("fuck") <<endl;
    string str7 = "fuck you asshole";
    cout << upper(str7) << endl;

    str1 = "btolen car";
    str2 = "Cheating Hussie";

    if (upper(str1) < upper(str2))
        cout << "Fuck" << endl;
    else
        cout << "bitch" << endl;

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
