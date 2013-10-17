#ifndef Date_h
#define Date_h
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace DateNS {
	
	class Date {
	public:
		class Bad_date : public logic_error {
		public:
			Bad_date(const string& msg) : logic_error(msg) {}
		};		// exception class
		Date(int mon = 0, int day = 0, int year = 0);
		void add_month(int n);
		void add_day(int n);
		void add_year(int n);

		int day() const;
		int month() const;
		int year() const;
		string string_rep() const;
		bool isdefaultdate();

		// allows changing default date
		static void set_defaultdate(int m, int d, int y);
    const Date& operator=(const Date& otherDate);
	private:
		bool is_valid();
		int d, m, y;
		static Date defaultdate;
		
	};

	// helper functions
	bool is_date(int mm, int dd, int yy);
	bool is_leapyear(int yy);

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	bool operator<(const Date& a, const Date& b);
	bool operator>(const Date& a, const Date& b);
  
	int date_diff(const Date& a, const Date& b, string datepart);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& d);

}  // end DateNS

#endif
