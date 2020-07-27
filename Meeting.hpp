#ifndef MEETING_H
#define MEETING_H

#include <vector>
#include<string>
#include<iostream>
#include "Date.hpp"
using namespace std;
class Meeting {
 public:
  /**
  * @brief default constructor
  */
  Meeting() = default;

  /**
  *   @brief constructor with argument
  */
  Meeting(const string &t_sponsor,const vector<string> &t_participator,
          const Date &t_startTime, const Date &t_endTime,const string &t_title)
        {
                m_sponsor=t_sponsor;
                m_participators=t_participator;
                m_startDate=t_startTime;
                m_title=t_title;
                m_endDate=t_endTime;
        }

  /**
  * @brief copy constructor of left value
  */
  Meeting(const Meeting &t_meeting)
  {
        m_sponsor=t_meeting.m_sponsor;
        m_participators=t_meeting.m_participator;
        m_startDate=t_meeting.m_startDate;
        m_title=t_meeting.m_title;
        m_endDate=t_meeting.m_endDate;
  }

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
  string getSponsor(void) const
  {
        return m_sponsor;
  }

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
  void setSponsor(const string &t_sponsor)
  {
        m_sponsor=t_sponsor;
  }

  /**
  * @brief  get the participators of a meeting
  * @return return a string vector indicate participators
  */
  vector<string> getParticipator(void) const
  {
        return m_participators;
  }

  /**
  *   @brief set the new participators of a meeting
  *   @param the new participators vector
  */
  void setParticipator(const vector<string> &t_participators)
  {
        m_participators=t_participators;
  }

  /**
  * @brief add a new participator to the meeting
  * @param the new participator
  */
  void addParticipator(const string &t_participator)
  {
        m_participators.push_back(t_participator);
  }

  /**
  * @brief remove a participator of the meeting
  * @param the participator to be removed
  */
  void removeParticipator(const string &t_participator)
  {
        int i=m_participators.begin();
        while(i<=m_participators.end()){
                if(m_participators[i]==t_participator)m_participators.erase(i);
                else i++;
        }
  }

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
  Date getStartDate(void) const
  {
        return m_startDate;
  }

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
  void setStartDate(const Date &t_startTime)
  {
        m_startDate=t_startTime;
  }

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
  Date getEndDate(void) const
  {
        return m_endDate;
  }

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
  void setEndDate(const Date &t_endTime)
  {
        m_endDate=t_endTime;
  }

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
 string getTitle(void) const
 {
        return m_title;
 }

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
  void setTitle(const string &t_title)
  {
        m_title=t_title;
  }

  /**
  * @brief check if the user take part in this meeting
  * @param t_username the source username
  * @return if the user take part in this meeting
  */
  bool isParticipator(const string &t_username) const
  {
        int i=m_participators.begin();
        while(i<=m_participators.end()){
                if(m_participators[i]==t_username)return true;
                else i++;
        }
        return false;
  }

 private:
  string m_sponsor;
  vector<string> m_participators;
  Date m_startDate;
  Date m_endDate;
  string m_title;
};

#endif
