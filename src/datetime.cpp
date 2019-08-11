#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <ctime>
#include "datetime.h"
using namespace std;


/**
* Default constructor for current system time/date   
*/
DateTime::DateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon +1;
    day = timeinfo->tm_mday;
}
/**
 * Alternative constructor 
 */
DateTime::DateTime(int hh, int mm, int ss, int y, int m, int d){
  hour = hh;
  min = mm;
  sec = ss;
  year = y;
  month = m;
  day = d;
}

/**
 * Return true if the timestamp is less-than other's
 *
 * @return result of less-than comparison of timestamp
 */
bool DateTime::operator<(const DateTime& other) const{
  if (year < other.year)
    return true;
  if (year > other.year)
    return false;

  if (month < other.month)
    return true;
  if (month > other.month)
    return false;

  if (day < other.day)
    return true;
  if (day > other.day)
    return false;

  if (hour < other.hour)
    return true;
  if (hour > other.hour)
    return false;

  if (min < other.min )
    return true;
  if (min > other.min )
    return false;

  if (sec < other.sec )
    return true;
  if (min > other.sec )
    return false;

  return false;
}

/**
 * Outputs the timestamp to the given ostream in format:
 *   YYYY-MM-DD HH:MM:SS
 *
 * @return the ostream passed in as an argument
 */
ostream& operator<<(ostream& os, const DateTime& other){
  os << setfill('0') << setw(4) << other.year; 
  os << "-";
  os << setfill('0') << setw(2) << other.month;
  os << "-";
  os << setfill('0') << setw(2) << other.day;
  os << " ";
  os << setfill('0') << setw(2) << other.hour;
  os << ":";
  os << setfill('0') << setw(2) << other.min;
  os << ":";
  os << setfill('0') << setw(2) << other.sec;

  return os;
}

/**
 * Inputs the timestamp to the given istream expecting the format:
 *   YYYY-MM-DD HH:MM:SS
     0123456789 01234567
 *  Returns if an error in the format with the DateTime set to the
 *   current system time/date
 *   
 *
 * @return the istream passed in as an argument
 */
istream& operator>>(istream& is, DateTime& dt){
  string d, t;
  is >> d >> t; 
  
  //checking format -- a bit convoluted, but thorough:  
  if( d.size()!=10 && t.size()!=8 ) {return is;}
  if(  !( isdigit(d[0]) && isdigit(d[1]) && isdigit(d[2])
          && isdigit(d[3]) && isdigit(d[5]) && isdigit(d[6]) && isdigit(d[8]) 
          && isdigit(d[9]) && isdigit(t[0]) && isdigit(t[1]) && isdigit(t[3]) 
          && isdigit(t[4]) && isdigit(t[6]) && isdigit(t[7]) && d[4] == '-'
          && d[7] == '-' && t[2] == ':' && t[5] == ':' ) ) { cout << "ERROR"; return is;}
  
  dt.year = stoi( d.substr(0,4) );
  dt.month = stoi ( d.substr(5,2) );
  dt.day = stoi ( d.substr(8,2) );
  dt.hour = stoi ( t.substr(0,2) );
  dt.min = stoi ( t.substr(3,2) );
  dt.sec = stoi ( t.substr(6,2) );

  return is;
  }
