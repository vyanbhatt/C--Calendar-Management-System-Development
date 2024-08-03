#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// My global functions

// Using this to implement getDay function

int check_leap(int year) {

  if (year % 100 == 0) {
    if (year % 400 == 0)
      return 366;
    else
      return 365;
  } else if (year % 4 == 0)
    return 366;

  else
    return 365;
}

int days_in_cur_month(int m, int y) {
  int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (m == 2 && check_leap(y))
    return 29;
  return month_days[m];
}

// Date class
class Date {

private:
  int dayOfMonth;   // any number between [1...31]
  int month;        // any number between [1...12]
  int year;         // any year
  string dayOfWeek; // stores what day it is. Monday,Tuesday etc

public:
  // consturctors
  Date(int d, int m, int y) {
    dayOfMonth = d;
    month = m;
    year = y;
  }

  Date() {}

  // All the getters
  string get_dayOfWeek() { return dayOfWeek; }

  int get_dayOfMonth() { return dayOfMonth; }

  int get_month() { return month; }

  int get_year() { return year; }

  // All the setters
  void set_dayOfWeek(string name) { dayOfWeek = name; }

  void set_month(int m) { month = m; }

  void set_year(int y) { year = y; }

  void set_date(int d) { dayOfMonth = d; }
};

// Operator == overloading
bool operator==(Date d1, Date d2) {
  if (d1.get_dayOfMonth() == d2.get_dayOfMonth() &&
      d1.get_month() == d2.get_month() && d1.get_year() == d2.get_year())
    return true;
  return false;
}

// Class Note
class Notes {
  string content;
  Date date;

public:
  Notes(Date d, string s) {
    date = d;
    content = s;
  }

  Date get_d() { return date; }
  string get_s() { return content; }
};

bool is_valid_date(Date d) {
  int dayOfMonth = d.get_dayOfMonth();
  int month = d.get_month();
  int year = d.get_year();
  int num_days_cur_month = days_in_cur_month(month, year);
  if (dayOfMonth < 1 || dayOfMonth > 31 || month < 1 || month > 12 ||
      (dayOfMonth == 29 && check_leap(year) != 366 && month == 2) ||
      dayOfMonth > num_days_cur_month)
    return false;

  else
    return true;
}

// Class Calendar
class Calendar {
  // All the vectors
  vector<Date> holidays; // stores holidays
  vector<Notes> n_list;  // stores notes
  vector<Date> meetings; // stores meetings

public:
  // Returns num of days in cur month and year
  int days_in_cur_month(int m, int y) {
    int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (m == 2 && check_leap(y))
      return 29;
    return month_days[m];
  }

  // Adds meeting
  void add_meeting(Date d) { meetings.push_back(d); }

  // Checks if there's a meeting on that date and return true if there's
  bool check_meeting(Date d) {
    if (meetings.empty())
      return false;
    else {
      for (int i = 0; i < meetings.size(); i++) {
        if (meetings[i] == d)
          return true;
      }
    }
    return false;
  }

  // Gives day name on the given date
  string
  getDay(Date d) // This method finds day name using 2023 as the base year
  {
    int dayOfMonth = d.get_dayOfMonth();
    int month = d.get_month();
    int year = d.get_year();

    if (!is_valid_date(d))
      return "Invalid input";
    // storing the days and puting dummy so to directly access month index
    int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Days of the week
    string days[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                     "Thursday", "Friday", "Saturday"};

    int sum = 0;

    // Calculate total days since a reference date
    for (int i = 1; i < year; i++) {
      sum = sum + check_leap(i);
    }

    for (int j = 1; j < month; j++) {
      sum = sum + month_days[j];
      if (j == 2 && check_leap(year) == 366)
        sum++; // Add an extra day for February in leap years
    }

    sum += dayOfMonth;

    int temp = sum % 7;
    d.set_dayOfWeek(days[temp]);
    return d.get_dayOfWeek();
  }

  // Returns month name
  string getMonth(Date d) {
    if (!is_valid_date(d))
      return "Invalid input";
    string months[] = {"January",   "February", "March",    "April",
                       "May",       "June",     "July",     "August",
                       "September", "October",  "November", "December"};

    int month = d.get_month();
    return months[month - 1];
  }

  // returns year
  string getYear(Date d) {
    if (!is_valid_date(d))
      return "Invalid input";

    int y = d.get_year();
    return to_string(y);
  }

  // Gives number of days between two given dates
  int getDistanceBetweenDates(Date d1, Date d2) {
    int sum = 0;
    Calendar c;

    if (c.isPreceded(d1, d2)) {
      swap(d1, d2);
    }

    int year_d1 = d1.get_year(), year_d2 = d2.get_year();
    int month_d1 = d1.get_month(), month_d2 = d2.get_month();
    int day_d1 = d1.get_dayOfMonth(), day_d2 = d2.get_dayOfMonth();

    if (year_d1 == year_d2) {
      if (month_d1 == month_d2) {
        sum = day_d2 - day_d1;
      } else {
        for (int m = month_d1 + 1; m < month_d2; m++) {
          sum += days_in_cur_month(m, year_d1);
        }
        sum += days_in_cur_month(month_d1, year_d1) - day_d1 + day_d2;
      }
    } else {
      for (int m = month_d1 + 1; m <= 12; m++) {
        sum += days_in_cur_month(m, year_d1);
      }
      sum += days_in_cur_month(month_d1, year_d1) - day_d1;

      for (int y = year_d1 + 1; y < year_d2; y++) {
        sum += check_leap(y);
      }

      for (int m = 1; m < month_d2; m++) {
        sum += days_in_cur_month(m, year_d2);
      }
      sum += day_d2;
    }

    return sum;
  }

  // Gives valid date by either adding t or subtracting t from given date
  Date iterateDates(Date d, int t) {

    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
      return d;
    }
    if (t >= 0) { // Adding days
      while (t > 0) {
        int cur_mdays = days_in_cur_month(d.get_month(), d.get_year());
        int rem_days = cur_mdays - d.get_dayOfMonth() + 1;

        if (rem_days > t) {
          d.set_date(d.get_dayOfMonth() + t);
          t = 0;
        } 
        else {
          t -= rem_days;
          d.set_date(1);
          d.set_month(d.get_month() + 1);
          if (d.get_month() > 12) {
            d.set_month(1);
            d.set_year(d.get_year() + 1);
          }
        }
      }
    }
    // My subtraction logic
    else {
      t = abs(t);
      while (t > 0) {
        if (d.get_dayOfMonth() > t) {
          d.set_date(d.get_dayOfMonth() - t);
          t = 0;
        } 
        else {
          t -= d.get_dayOfMonth();
          d.set_month(d.get_month() - 1);
          if (d.get_month() < 1) {
            d.set_month(12);
            d.set_year(d.get_year() - 1);
          }
          int prev_mdays = days_in_cur_month(d.get_month(), d.get_year());
          d.set_date(prev_mdays);
        }
      }
    }
    return d;
  }

  // Returns true if the date is preceded else false
  bool isPreceded(Date d1, Date d2) {
    if (!is_valid_date(d1) || !is_valid_date(d2)) {
      cout << "Invalid input" << endl;
      return false;
    }
    if (d1.get_year() > d2.get_year())
      return true;

    else if (d1.get_year() < d2.get_year())
      return false;

    else if (d1.get_month() > d2.get_month())
      return true;

    else if (d1.get_month() < d2.get_month())
      return false;

    else if (d1.get_dayOfMonth() > d2.get_dayOfMonth())
      return true;

    else
      return false;
  }

  // Adds holiday
  void addHoliday(Date d) {
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
    }
    Date holiday(d.get_dayOfMonth(), d.get_month(), d.get_year());
    holidays.push_back(holiday);
  }

  // Gives next holiday
  Date getNextHoliday(Date d) {
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
      return d;
    }
    Calendar c;

    for (int i = 0; i < 6; i++) {
      d = c.iterateDates(d, 1);
      string next_day = c.getDay(d);

      if (next_day == "Saturday" || next_day == "Sunday") {
        return d;
      } else if (!holidays.empty()) {
        for (int j = 0; j < holidays.size(); j++) {
          if (d == holidays[j]) {
            return d;
          }
        }
      }
    }
    return d;
  }

  // returns next week day
  Date getNextWeekDay(Date d) {
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
      return d;
    }
    Calendar c;
    Date temp = d;
    d.set_date(d.get_dayOfMonth() + 1);
    string cur_day = c.getDay(d);
    int next_day = d.get_dayOfMonth();
    int year = d.get_year();
    int month = d.get_month();

    while (cur_day == "Saturday" || cur_day == "Sunday" ||
           find(holidays.begin(), holidays.end(), d) != holidays.end()) {

      if (next_day > days_in_cur_month(month, year)) {
        next_day = 1;
        if (month == 12) {
          month = 1;
          year++;
        } else {
          month++;
        }
      } else
        next_day++;
      d.set_date(next_day);
      d.set_month(month);
      d.set_year(year);
      cur_day = getDay(d);
    }
    return d;
  }

  // Returns number of holidays
  int getNumberOfHolidays(int month, int year) {
    if (month > 12 || month < 1) {
      cout << "Invalid input" << endl;
      return -1;
    }
    Calendar c;
    int cur_days = days_in_cur_month(month, year);
    int count = 0;
    if (holidays.empty())
      return 0;
    else {
      for (int i = 0; i < cur_days; i++) {
        Date temp(i + 1, month, year);
        if ((holidays[i].get_month() == month &&
             holidays[i].get_year() == year) ||
            c.getDay(temp) == "Sunday" || c.getDay(temp) == "Saturday")
          count++;
      }
    }

    return count;
  }

  // Prints the whole calender for given month and year
  void printMonthOfYear(int month, int year) {
    if (month > 12 || month < 1) {
      cout << "Invalid input" << endl;
      return;
    }
    Calendar c;
    Date curr_date(1, month, year);

    string first_day = c.getDay(curr_date);
    string days[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                     "Thursday", "Friday", "Saturday"};

    cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

    // shifting the first till first day
    int i = 0;
    while (i < 7 && days[i] != first_day) {
      cout << setw(4) << " ";
      i++;
    }

    // Print the dates of the month
    while (curr_date.get_month() == month) {
      cout << setw(3) << curr_date.get_dayOfMonth();

      curr_date = iterateDates(curr_date, 1);

      if (c.getDay(curr_date) == "Sunday") {
        cout << endl;
      } else {
        cout << " "; // adjust space amongst same week days
      }
    }
  }

  // Adds note on given date
  void addNoteToDate(Date d, string note) {
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
    }
    Notes temp(d, note);
    n_list.push_back(temp);
  }

  // Removes note if present else returns false
  bool removeNoteFromDate(Date d) {
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
      return false;
    }
    if (n_list.empty())
      return false;
    else {
      for (int i = 0; i < n_list.size(); i++) {
        if (n_list[i].get_d() == d) {
          n_list.erase(n_list.begin() + i);
          return true;
        }
      }
    }
    return false;
  }

  // Retuns vector of notes from given date within n days
  vector<Notes> getNotesFromDateTillN(Date d, int n) {
    vector<Notes> result;
    if (!is_valid_date(d)) {
      cout << "Invalid input" << endl;
      return result;
    }

    if (n_list.empty())
      return result;
    Calendar c;
    while (n--) {
      d = c.iterateDates(d, 1);
      for (int i = 0; i < n_list.size(); i++) {
        if (n_list[i].get_d() == d)
          result.push_back(n_list[i]);
      }
    }
    return result;
  }
};

// Returns free dates for both fellows
vector<Date> getFreeDates(Calendar c1, Calendar c2, int month, int year) {
  vector<Date> result;
  if (month < 1 || month > 12) {
    cout << "Invalid input" << endl;
    return result;
  }
  Date cur_date(1, month, year);

  int num_days = c1.days_in_cur_month(month, year);
  for (int i = 1; i <= num_days; i++) {
    if (c1.getDay(cur_date) != "Sunday" && c1.getDay(cur_date) != "Saturday" &&
        c1.check_meeting(cur_date) == 0 && c2.check_meeting(cur_date) == 0) {
      result.push_back(cur_date);
    }
    cur_date = c1.iterateDates(cur_date, 1);
  }
  return result;
}


int main() {
  

  return 0;
}
