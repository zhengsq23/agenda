#ifndef DATE_H
#define DATE_H

#include <initializer_list>
#include <string>
#include<iostream>
#include<sstream>
using namespace std; 
bool isDigit(char s){
  if(s<'0'||s>'9')return false;
  else return true;
}

class Date {
 public:
  /**
  * @brief default constructor
  */
  Date()
  {
    m_day=0;
    m_hour=0;
    m_minute=0;
    m_year=0;
    m_month=0;
  }

  /**
  * @brief constructor with arguments
  */
  Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
  {
    m_day=t_day;
    m_hour=t_hour;
    m_minute=t_minute;
    m_year=t_year;
    m_month=t_month;
  }

  /**
  * @brief constructor with a string
  */
  Date(const string &dateString)
  {
    *this=stringToDate(dateString);
  }
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int getYear(void) const
  {
    return m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void setYear(const int t_year)
  {
    m_year=t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int getMonth(void) const
  {
    return m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void setMonth(const int t_month)
  {
    m_month=t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int getDay(void) const
  {
    return m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void setDay(const int t_day)
  {
    m_day=t_day;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int getHour(void) const
  {
    return m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void setHour(const int t_hour)
  {
    m_hour=t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int getMinute(void) const
  {
    return m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void setMinute(const int t_minute)
  {
    m_minute=t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  static bool isValid(const Date &t_date)
  {
    int num[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if((t_date.getYear()%4==0&&t_date.getYear()%100!=0)||t_date.getYear()%400==0)num[1]++;
    if(t_date.getYear()>=1000&&t_date.getYear()<=9999){
      if(t_date.getMonth()>=1&&t_date.getMonth()<=12){
        if(t_date.getDay()>=1&&t_date.getDay()<=num[t_date.getMonth()-1]){
          if(t_date.getHour()>=0&&t_date.getHour()<=23){
            if(t_date.getMinute()>=0&&t_date.getMinute()<=59)return true;
            else return false;
          }
          else return false;
        }
        else return false;
      }
      else return false;
    }
    else return false;
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  static Date stringToDate(const string &t_dateString)
  {
    Date a;
    if(t_dateString.size()!=16){
      return a;
    }
    if(!(isDigit(t_dateString[0])&&isDigit(t_dateString[1])&&isDigit(t_dateString[2])&&isDigit(t_dateString[3])&&isDigit(t_dateString[5])
    &&isDigit(t_dateString[6])&&isDigit(t_dateString[8])&&isDigit(t_dateString[9])&&isDigit(t_dateString[11])&&isDigit(t_dateString[12])
    &&isDigit(t_dateString[14])&&isDigit(t_dateString[15])&&t_dateString[4]=='-'&&t_dateString[7]=='-'&&t_dateString[10]=='/'
    &&t_dateString[13]==':'))return a;
    stringstream ss;
    int y, m, d, h, mi;
    char c;
    ss << t_dateString;
    ss >> y >> c >> m >> c
       >> d >> c >> h >> c >> mi;
    return Date(y, m, d, h, mi);
  }

  /**
  * @brief convert a date to string, if the date is invalid return
  * 0000-00-00/00:00
  */
  static string dateToString(const Date &t_date)
  {stringstream ss;
            ss << t_date.getYear() << "-"
               << (t_date.getMonth()<10?"0":"")<<t_date.getMonth()<< "-"
               << (t_date.getDay() <10?"0":"")<<t_date.getDay()<< "/"
               << (t_date.getHour() <10?"0":"")<<t_date.getHour()<< ":"
               << (t_date.getMinute()<10?"0":"")<<t_date.getMinute();
            return ss.str();
  }

  /**
  *  @brief overload the assign operator
  */
  Date &operator=(const Date &t_date)
  {
    m_year=t_date.m_year;
    m_month=t_date.m_month;
    m_day=t_date.m_day;
    m_hour=t_date.m_hour;
    m_minute=t_date.m_minute;
    return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool operator==(const Date &t_date) const
  {
    if(m_year==t_date.m_year&&m_month==t_date.m_month&&m_day==t_date.m_day&&m_hour==t_date.m_hour&&m_minute==t_date.m_minute)
      return true;
    else return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool operator>(const Date &t_date) const
  {
   if(this->getYear()>t_date.getYear())return true;
    if(this->getYear()<t_date.getYear())return false;
    if(this->getYear()==t_date.getYear()){
        if(this->getMonth()>t_date.getMonth())return true;
        if(this->getMonth()<t_date.getMonth())return false;
        if(this->getMonth()==t_date.getMonth()){
            if(this->getDay()>t_date.getDay())return true;
            if(this->getDay()<t_date.getDay())return false;
            if(this->getDay()==t_date.getDay()){
                if(this->getHour()>t_date.getHour())return true;
                if(this->getHour()<t_date.getHour())return false;
                if(this->getHour()==t_date.getHour()){
                    if(this->getMinute()>t_date.getMinute())return true;
                    if(this->getMinute()<=t_date.getMinute())return false;
                }
            }
        }
    }
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool operator<(const Date &t_date) const
  {
    return !(*this>t_date)&&!(*this==t_date);
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool operator>=(const Date &t_date) const
  {
    if(!(*this<t_date))return true;
    else return false;
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool operator<=(const Date &t_date) const
  {
    if(!(*this>t_date))return true;
    else return false;
  }

 private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
};

#endif
