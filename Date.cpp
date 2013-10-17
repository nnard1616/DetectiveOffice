#include "Date.h"
#include <sstream>

using namespace DateNS;

int mondays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(int mm, int dd, int yy)
{
	m = mm ? mm : defaultdate.m;
	d = dd ? dd : defaultdate.d;
	y = yy ? yy : defaultdate.y;

	if (!is_valid()) {
		ostringstream errmsg;
		errmsg << "Bad date: " << m << "/" << d << "/" << y;
		throw Bad_date(errmsg.str());
	}
}

bool Date::is_valid() {
	if (y < 2010)
		return false;
	return is_date(m, d, y);
}

inline int Date::month() const { return m; }
inline int Date::day() const { return d; }
inline int Date::year() const { return y; }

bool DateNS::is_date(int mm, int dd, int yy) {
	if (mm < 1 || mm > 12)
		return false;
	if (dd < 1)
		return false;
	if ((mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) && (dd > 31))
		return false;
	if ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && (dd > 30))
		return false;
	if (is_leapyear(yy) && (mm == 2) && (dd > 29))
		return false;
	if ((mm == 2) && (dd > 28))
		return false;
	return true;
}

bool DateNS::is_leapyear(int yy) {
	if (yy % 400 == 0) return true;
	if (yy % 100 == 0) return false;
	if (yy % 4 == 0) return true;
	return false;
}

void Date::add_day(int dd) {
	if (dd < -731 || dd > 731)
		throw Date::Bad_date("Increment > +/- 2 years");
	mondays[2] = is_leapyear(y) ? 29 : 28;
	int ddw;
	if (dd == 0)
		return;
	if (dd < 0) {
		ddw = -dd;
		while (ddw > 0) {
			if (ddw > d) {
				ddw -= d;
				--m;
				if (m == 0) {
					--y;
					mondays[2] = is_leapyear(y) ? 29 : 28; 
					m = 12;
				}
				d = mondays[m];
			}
			else {
				d -= ddw;
				ddw = 0;
			}
		}
	}
	else {
		ddw = dd;
		while (ddw > 0) {
			int currmondays = mondays[m];
			if (d + ddw > currmondays) {
				ddw -= currmondays - d;
				d = 0;
				++m;
				if (m == 13) {
					++y;
					mondays[2] = is_leapyear(y) ? 29 : 28;
					m = 1;
				}
			}
			else {
				d += ddw;
				ddw = 0;
			}
		}
	}
}

string Date::string_rep() const {
	ostringstream res;
	res << m << "/" << d << "/" << y;
	return res.str();
}

const Date& Date::operator=(const Date& otherDate){
  if (this != &otherDate){
    d = otherDate.d;
    m = otherDate.m;
    y = otherDate.y;
  }
  return *this;
}
bool DateNS::operator==(const Date& d1, const Date& d2) {
	if (d1.year() != d2.year())
		return false;
	if (d1.month() != d2.month())
		return false;
	if (d1.day() != d2.day())
		return false;
	return true;
}

bool DateNS::operator!=(const Date& d1, const Date& d2) {
	return !(d1 == d2);
}

bool DateNS::operator<(const Date& d1, const Date& d2) {
	if (d1.year() < d2.year())
		return true;
	if (d1.year() == d2.year()) {
		if (d1.month() < d2.month())
			return true;
		if (d1.month() == d2.month())
			if (d1.day() < d2.day())
				return true;
			else
				return false;
		else
			return false;
	}
	return false;
}

bool DateNS::operator>(const Date& d1, const Date& d2) {
	if (d1 == d2 || d1 < d2)
		return false;
	else
		return true;
}

int DateNS::date_diff(const Date& a, const Date& b, string datepart) {
	int lm, ld, ly, em, ed, ey;
	int sign;
	if (a < b) {
		lm = a.month(); ld = a.day(); ly = a.year();
		em = b.month(); ed = b.day(); ey = b.year();
		sign = 1;
	}
	else {
		lm = b.month(); ld = b.day(); ly = b.year();
		em = a.month(); ed = a.day(); ey = a.year();
		sign = -1;
	}
	if (datepart[0] == 'd') {
		mondays[2] = is_leapyear(ly) ? 29 : 28;
		int totaldays = 0;
		while (ly < ey) {
			// get days to end of month for low
			totaldays += mondays[lm] - ld;
			++lm;
			if (lm == 13) {
				++ly;
				mondays[2] = is_leapyear(ly) ? 29 : 28;
				lm = 1;
			}
			ld = 0;
		}
		while (lm < em) {
			totaldays += mondays[lm] - ld;
			++lm;
			ld = 0;
		}
		totaldays += ed - ld;
		return sign * totaldays;
	}
	if (datepart[0] == 'm') {
		int totalmons = 0;
		while (ly < ey) {
			totalmons = 12 - lm;
			lm = 0;
			++ly;
		}
		totalmons += em - ly;
		if (ed < ld)
			--totalmons;
		return sign * totalmons;
	}
	if (datepart[0] == 'y') {
		int totalyears = 0;
		totalyears = ey - ly;
		if (em < lm)
			--totalyears;
		return sign * totalyears;
	}
	throw invalid_argument("datediff expects d, m, or y as datepart desired");
	return 0;
}

// set initial defaultdate
Date Date::defaultdate(1,1,2010);

void Date::set_defaultdate(int m, int d, int y) {
	defaultdate = Date(m, d, y);
}

bool Date::isdefaultdate() {
	if (m == defaultdate.m && d == defaultdate.d && y == defaultdate.y)
		return true;
	else
		return false;
}

istream& DateNS::operator>>(istream& istrm, Date& d) {
	int mm, dd, yy;
	istrm >> mm >> dd >> yy;
	Date tempDate(mm, dd, yy);
	d = tempDate;
	return istrm;
}

ostream& DateNS::operator<<(ostream& ostrm, const Date& d) {
	ostrm << d.string_rep();
	return ostrm;
}
