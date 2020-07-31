#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H
#include <functional>
#include <list>
#include <memory>
#include<fstream>
#include <string>
#include<sstream>
#include "Storage.hpp"
using namespace std;
class AgendaService {
 public:
  /**
   * constructor
   */
  AgendaService()
  {
    startAgenda();
  }

  /**
   * destructor
   */
  ~AgendaService()
  {
    quitAgenda();
  }

  /**
   * check if the username match password
   * @param userName the username want to login
   * @param password the password user enter
   * @return if success, true will be returned
   */
  bool userLogIn(const string &userName, const string &password)
  {
    auto filter = [userName, password](const User& user) {
      return user.getName() == userName && user.getPassword() == password;
    };
    list<User> ans=m_storage->queryUser(filter);
    if(ans.size())return true;
    else return false;
  }

  /**
   * regist a user
   * @param userName new user's username
   * @param password new user's password
   * @param email new user's email
   * @param phone new user's phone
   * @return if success, true will be returned
   */
  bool userRegister(const string &userName, const string &password,const string &email, const string &phone)
  {
    auto filter = [userName, password,email,phone](const User& user) {
      return user.getName() == userName ;
    };
    list<User> ans=m_storage->queryUser(filter);
    if(ans.size()==0){
      User a(userName,password,email,phone);
      m_storage->createUser(a);
      return true;
    }
    else return false;
  }

  /**
   * delete a user
   * @param userName user's username
   * @param password user's password
   * @return if success, true will be returned
   */
  bool deleteUser(const string &userName, const string &password)
  {
    auto filter = [userName, password](const User& user) {
      return user.getName() == userName && user.getPassword() == password;
    };
    if(m_storage->deleteUser(filter)){
      deleteAllMeetings(userName);
      return true;
    }
    else return false;
  }

  /**
   * list all users from storage
   * @return a user list result
   */
  list<User> listAllUsers(void) const
  {
    auto filter = [](const User& user) {
      return true;
    };
    return m_storage->queryUser(filter);
  }

  /**
   * create a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @param startData the meeting's start date
   * @param endData the meeting's end date
   * @return if success, true will be returned
   */
  bool createMeeting(const string &userName, const string &title,const string &startDate, const string &endDate,const vector<string> &participator)
  {
    auto filter = [userName,title,startDate,endDate,participator](const Meeting &meeting) {
      return meeting.getTitle()==title;
    };
    Date sdate(startDate),edate(endDate);
    if(sdate>=edate||!Date::isValid(sdate)||!Date::isValid(edate))return false;
    bool is_valid_sponsor=false,temp;
    for(auto i=listAllUsers().begin();i!=listAllUsers().end();i++){
      if(userName==(*i).getName())is_valid_sponsor=true;
    }
    if (!is_valid_sponsor)return false;//举办者是否有效
    for(auto j=participator.begin();j!=participator.end();j++){
      temp=false;
      for(auto i=listAllUsers().begin();i!=listAllUsers().end();i++){
        if((*j)==(*i).getName())temp=true;
      }
      if(!temp)return false;
    }//参与者是否有效
    list<Meeting> sponmeeting=meetingQuery(userName,startDate,endDate);
    if(sponmeeting.size()>0&&!(sponmeeting.front().getEndDate()==sdate)
    &&!(sponmeeting.front().getStartDate()==edate))return false;//举办者是否在该时间有其他会议
    for(auto j=participator.begin();j!=participator.end();j++){
      temp=true;
      for(auto i=listAllMeetings(*j).begin();i!=listAllMeetings(*j).end();i++){
        if(((*i).getEndDate()<=edate&&(*i).getEndDate()>sdate)||((*i).getStartDate()<edate&&(*i).getStartDate()>=sdate))temp=false;
      }
      if(!temp)return false;
    }//参与者是否在该时间有其他会议
    if(m_storage->queryMeeting(filter).size()==0)
    {
      Meeting meeting(userName,participator,sdate,edate,title);
      m_storage->createMeeting(meeting);
    }//创建会议，无主题重复，人员均有效，时间合法，开始早于结束，所有人员在该时间无其他会议
    else return false;
  }
  /**
   * add a participator to a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool addMeetingParticipator(const string &userName,const string &title,const string &participator)
  {
    auto filter=[userName,title,participator](const User &user){
      return userName==user.getName();
    };
    if(m_storage->queryUser(filter).size()<=0)return false;//参与者是否存在
    if(meetingQuery(userName,title).size()>0){  //会议是否存在
      Meeting tmp=*(meetingQuery(userName,title).begin());
      list<Meeting> partmeeting=meetingQuery(participator,Date::dateToString(tmp.getStartDate()),Date::dateToString(tmp.getEndDate()));
      if(partmeeting.size()==0||partmeeting.front().getStartDate()==tmp.getEndDate()||partmeeting.front().getEndDate()==tmp.getStartDate())
      {
        tmp.addParticipator(participator);
        return true;
      }    //参与者是否有空
    }
    return false;
  }

  /**
   * remove a participator from a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool removeMeetingParticipator(const string &userName,const string &title,const string &participator)
  {
    if(meetingQuery(userName,title).size()>0){
      Meeting tmp=*(meetingQuery(userName,title).begin());
      for(auto i=tmp.getParticipator().begin();i!=tmp.getParticipator().end();i++)
      {
        if((*i)==participator){
          tmp.getParticipator().erase(i);
          return true;
        }
      }
      return false;
    }
  }

  /**
   * quit from a meeting
   * @param userName the current userName. no need to be the sponsor
   * @param title the meeting's title
   * @return if success, true will be returned
   */
  bool quitMeeting(const string &userName, const string &title)
  {
    auto filter = [title](const Meeting &meeting) {
      return meeting.getTitle()==title;
    };
    if(m_storage->queryMeeting(filter).size()==0)return false;
    Meeting tmpmeeting=*(m_storage->queryMeeting(filter).begin());
    vector<string> tmpparticipator=tmpmeeting.getParticipator();
    for(auto j=tmpparticipator.begin();j!=tmpparticipator.end();j++){
      if((*j)==userName){
        tmpparticipator.erase(j);
        return true;
      }
     }
    return false;
  }

  /**
   * search a meeting by username and title
   * @param uesrName the sponsor's userName
   * @param title the meeting's title
   * @return a meeting list result
   */
  list<Meeting> meetingQuery(const string &userName,const string &title) const
  {
    list<Meeting> ans;
    auto filter = [userName,title](const Meeting &meeting) {
      return meeting.getTitle()==title&&meeting.getSponsor()==userName;
    };
    if(m_storage->queryMeeting(filter).size()==0){
      return ans;
    }
    ans=m_storage->queryMeeting(filter);
    return ans;

  }
  /**
   * search a meeting by username, time interval
   * @param uesrName the sponsor's userName
   * @param startDate time interval's start date
   * @param endDate time interval's end date
   * @return a meeting list result
   */
  list<Meeting> meetingQuery(const string &userName,const string &startDate, const string &endDate) const
  {
    Date sdate(startDate),edate(endDate);
    auto filter=[userName,sdate,edate](const Meeting &meeting){
      if(meeting.getSponsor()==userName){
        if((meeting.getStartDate()<=edate&&meeting.getStartDate()>=sdate)||(meeting.getEndDate()<=edate&&meeting.getEndDate()>=sdate))
        return true;
      }
      return false;
    };
    return m_storage->queryMeeting(filter);
  }

  /**
   * list all meetings the user take part in
   * @param userName user's username
   * @return a meeting list result
   */
  list<Meeting> listAllMeetings(const string &userName) const
  {
    auto filter=[](const Meeting &meeting){
      return true;
    };
    list<Meeting> tmp= m_storage->queryMeeting(filter),ans;
    for(auto i=tmp.begin();i!=tmp.end();i++){
      for(auto j=(*i).getParticipator().begin();j!=(*i).getParticipator().end();j++){
        if((*j)==userName){
          ans.push_back(*i);
        }
      }
    }
    return ans;
  }

  /**
   * list all meetings the user sponsor
   * @param userName user's username
   * @return a meeting list result
   */
  list<Meeting> listAllSponsorMeetings(const string &userName) const
  {
    auto filter = [userName](const Meeting &meeting) {
      return meeting.getSponsor()==userName;
    };
    return m_storage->queryMeeting(filter);
  }

  /**
   * list all meetings the user take part in and sponsor by other
   * @param userName user's username
   * @return a meeting list result
   */
  list<Meeting> listAllParticipateMeetings(const string &userName) const
  {
    list<Meeting> a= listAllMeetings(userName);
    list<Meeting> b=listAllSponsorMeetings(userName);
    a.splice(a.begin(), b);
    return a;
  }

  /**
   * delete a meeting by title and its sponsor
   * @param userName sponsor's username
   * @param title meeting's title
   * @return if success, true will be returned
   */
  bool deleteMeeting(const string &userName, const string &title)
  {
    auto filter = [userName,title](const Meeting &meeting) {
      return meeting.getSponsor()==userName&&meeting.getTitle()==title;
    };
    m_storage->deleteMeeting(filter);
    return m_storage->deleteMeeting(filter)>0;
  }

  /**
   * delete all meetings by sponsor
   * @param userName sponsor's username
   * @return if success, true will be returned
   */
  bool deleteAllMeetings(const string &userName)
  {
    auto filter = [userName](const Meeting &meeting) {
      return meeting.getSponsor()==userName;
    };
    m_storage->deleteMeeting(filter);
    return m_storage->deleteMeeting(filter)>0;
  }

  /**
   * start Agenda service and connect to storage
   */
  void startAgenda(void)
  {
    m_storage=Storage::getInstance();
  }

  /**
   * quit Agenda service
   */
  void quitAgenda(void)
  {
    m_storage->sync();
  }

 private:
  shared_ptr<Storage> m_storage;
};


#endif
