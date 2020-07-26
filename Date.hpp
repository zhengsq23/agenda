#ifndef DATE_H
#define DATE_H

#include <initializer_list>
#include <string>
using namespace std; 
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
    string year=dateString.substr(0,4);
    string month=dateString.substr(5,2);
    string day=dateString.substr(8,2);
    string hour=dateString.substr(11,2);
    string minute=dateString.substr(14,2);
    m_year=year[0]*1000+year[1]*100+year[2]*10+year[3];
    m_month=month[0]*10+month[1];
    m_day=day[0]*10+day[1];
    m_hour=hour[0]*10+hour[1];
    m_minute=minute[0]*10+minute[1];
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
    else return false
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  static Date stringToDate(const string &t_dateString)
  {
    Date a;
    a.Date();
    for(int i=0;i<4;i++){
      a.m_year=a.m_year*10+t_dateString[i];
    }
    for(int i=5;i<7;i++){
      a.m_month=a.m_month*10+t_dateString[i];
    }
    for(int i=8;i<10;i++){
      a.m_day=a.m_day*10+t_dateString[i];
    }
    for(int i=11;i<13;i++){
      a.m_hour=a.m_hour*10+t_dateString[i];
    }
    for(int i=14;i<16;i++){
      a.m_minute=a.m_minute*10+t_dateString[i];
    }
    return a;

  }

  /**
  * @brief convert a date to string, if the date is invalid return
  * 0000-00-00/00:00
  */
  static string dateToString(const Date &t_date)
  {
    string time;
    for(int i=3;i>=0;i--){
        time[i]=m_year%10;
        m_year/=10;
    }
    time[4]='-';
    time[5]=m_month/10;
    time[6]=m_month%10;
    time[7]='-';
    time[8]=m_day/10;
    time[9]=m_day%10;
    time[10]='/';
    time[11]=m_hour/10;
    time[12]=m_hour%10;
    time[13]=':';
    time[14]=m_minute/10;
    time[15]=m_minute%10;
    return time;
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
    if(m_year==t_date.m_year&&m_month=t_date.m_month&&m_day=t_date.m_day&&m_hour=t_date.m_hour&&m_minute=t_date.m_minute)
      return true;
    else return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool operator>(const Date &t_date) const
  {
   return getYear() > t_date.getYear() ? true :
                   getMonth() > t_date.getMonth() ? true :
                   getDay() > t_date.getDay() ? true :
                   getHour() > t_date.getHour() ? true : false;
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
