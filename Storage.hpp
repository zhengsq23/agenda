#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#include <functional>
#include <list>
#include <memory>
#include <string>
#include "Meeting.hpp"
#include "User.hpp"
using namespace std;

class Storage {
 private:
  /**
  *   default constructor
  */
  Storage(){
    readFromFile("agenda.data");
  }

  /**
  *   disallow the copy constructor and assign operator
  */
  Storage(const Storage &t_another) = delete;
  void operator=(const Storage &t_another) = delete;

  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
  bool readFromFile(void)
  {

  }

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
  bool writeToFile(void)
  {

  }

 public:
  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  static shared_ptr<Storage> getInstance(void)
  {
    if (m_instance == nullptr)
                shared_ptr<Storage> m_instance= make_shared<Storage>();
    return m_instance;
  }

  /**
  *   destructor
  */
  ~Storage()
  {}

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void createUser(const User &t_user)
  {
    m_userList.push_back(t_user);
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  list<User> queryUser(function<bool(const User &)> filter) const
  {
    list<User> answerList;
    for(auto i=m_userList.begin();i!=m_userList.end();i++){
      if(filter(*i))answerList.push_back(*i);
    }
    return answerList;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int updateUser(function<bool(const User &)> filter,function<void(User &)> switcher)
  {
    int ans=0;
    for(auto i=m_userList.begin();i!=m_userList.end();i++){
      if(filter(*i)){
        switcher(*i);
        ans++;
      }
    }
    return ans;
  }

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int deleteUser(function<bool(const User &)> filter)
  {
    int ans=0;
    for(auto i=m_userList.begin();i!=m_userList.end();i++){
      if(filter(*i))
      { ans++;
        m_userList.push_back(*i);
      }
    }
    return ans;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void createMeeting(const Meeting &t_meeting)
  {
    m_meetingList.push_back(t_meeting);
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  list<Meeting> queryMeeting(function<bool(const Meeting &)> filter) const
  {
    list<Meeting> answerList;
    for(auto i=m_meetingList.begin();i!=m_meetingList.end();i++){
      if(filter(*i))answerList.push_back(*i);
    }
    return answerList;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int updateMeeting(function<bool(const Meeting &)> filter,function<void(Meeting &)> switcher)
  {
    int ans=0;
    for(auto i=m_meetingList.begin();i!=m_meetingList.end();i++){
      if(filter(*i)){
        switcher(*i);
        ans++;
      }
    }
    return ans;
  }

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int deleteMeeting(function<bool(const Meeting &)> filter)
  {
    int ans=0;
    for(auto i=m_meetingList.begin();i!=m_meetingList.end();i++){
      if(filter(*i))
      { ans++;
        m_meetingList.push_back(*i);
      }
    }
    return ans;
  }

  /**
  * sync with the file
  */
  bool sync(void)
  {
    if(m_dirty){
      writeToFile("agenda.data");
      m_dirty=0;
    }
    return true;
  }

 private:
  static shared_ptr<Storage> m_instance;
  list<User> m_userList;
  list<Meeting> m_meetingList;
  bool m_dirty;
};

#endif
