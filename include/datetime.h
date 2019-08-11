#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>

/**
 * Models a timestamp in format YYYY-MM-DD HH:MM:SS 
 */
struct DateTime
{
  DateTime();
  DateTime(int hh, int mm, int ss, int year, int month, int day);
  bool operator<(const DateTime& other) const;
  friend std::ostream& operator<<(std::ostream& os, const DateTime& other);
  friend std::istream& operator>>(std::istream& is, DateTime& dt);
  int hour;
  int min;
  int sec;
  int year;
  int month;
  int day;
};

#endif
