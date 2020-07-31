#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#include <functional>
#include <list>
#include <memory>
#include<fstream>
#include <string>
#include<sstream>
#include "Meeting.hpp"
#include "User.hpp"
using namespace std;

class Storage {
 public:
  /**
  *   default constructor
  */
  Storage(){
    readFromFile();
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
    ifstream fin;
    fin.open("user.csv");
    if (!fin.is_open())return false;
    while(!fin.eof()){
      char a[200];
      fin>>a;
      string b(a);
       stringstream ss(b);
     string name,password,email,phone,tmp;
     int i=0;
     while (getline(ss, tmp, ',')) {
       switch(i){
         case 0:
         name=tmp;
         break;
         case 1:
         password=tmp;
         break;
         case 2:
         email=tmp;
         break;
         case 3:
         phone=tmp;
         break;
       }
       i++;
       i%=4;
     }
    name.erase(name.begin());
     name.erase(name.end()-1);
     password.erase(password.begin());
     password.erase(password.end()-1);
     email.erase(email.begin());
     email.erase(email.end()-1);
     phone.erase(phone.begin());
     phone.erase(phone.end()-1);
     User tempuser(name,password,email,phone);
     m_userList.push_back(tempuser);
    }
    fin.close();

    ifstream finm;
    finm.open("meeting.csv");
    if (!finm.is_open())return false;
    while(!finm.eof()){
      char b[200];
      finm>>b;
      string c(b);
       stringstream ss(c);
     string sponsor,participator,startdate,enddate,title,tmp;
     int j=0;
     while (getline(ss, tmp, ',')) {
       switch(j){
         case 0:
            sponsor=tmp;
            break;
        case 1:
            participator=tmp;
            break;
        case 2:
            startdate=tmp;
            break;
         case 3:
            enddate=tmp;
            break;
         case 4:
            title=tmp;
            break;

       }
       j++;
       j%=5;
     }
    sponsor.erase(sponsor.begin());
    sponsor.erase(sponsor.end()-1);
    participator.erase(participator.begin());
    participator.erase(participator.end()-1);
    startdate.erase(startdate.begin());
    startdate.erase(startdate.end()-1);
    enddate.erase(enddate.begin());
    enddate.erase(enddate.end()-1);
    title.erase(title.begin());
    title.erase(title.end()-1);
    Date date1(startdate),date2(enddate);
    vector<string> par;
    stringstream ss1(participator);
    while (getline(ss1, tmp, '&')) {
       par.push_back(tmp);
     }
    Meeting tempmeeting(sponsor,par,date1,date2,title);
    }
    finm.close();
  }

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
  bool writeToFile(void)
  {
    ofstream fin;
    fin.open("user.csv");
    list<User>::iterator i=m_userList.begin();
    while(i!=m_userList.end()){
      fin<<'"'<<(*i).getName()<<'"'<<','<<'"'<<(*i).getPassword()<<'"'<<','<<'"'<<(*i).getEmail()<<'"'<<','<<'"'<<(*i).getPhone()<<'"'<<'\n';
      i++;
    }
    fin.close();
    ofstream finm;
    finm.open("meeting.csv");
    list<Meeting>::iterator j=m_meetingList.begin();
    while(j!=m_meetingList.end()){
      string outpart;
      vector<string>::iterator k=(*j).getParticipator().begin();
      while(k!=(*j).getParticipator().end()){
        outpart+=(*k);
        outpart.append("&");
        k++;
      }
      outpart.erase(outpart.end()-1);
      finm<<'"'<<(*j).getSponsor()<<'"'<<','<<'"'<<outpart<<'"'<<','<<'"'<<Date::dateToString((*j).getStartDate())<<'"'<<','
      <<'"'<<Date::dateToString((*j).getEndDate())<<'"'<<','<<'"'<<(*j).getTitle()<<'\n';
      j++;
    }
    finm.close();

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
        m_userList.erase(i);
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
        m_meetingList.erase(i);
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
      writeToFile();
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
shared_ptr<Storage> Storage:: m_instance=nullptr;
#endif
