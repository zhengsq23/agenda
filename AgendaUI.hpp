#ifndef AGENDAUI_H
#define AGENDAUI_H

#include <iostream>
#include <string>
#include<list>
#include<vector>
#include "AgendaService.hpp"
using namespace std;
class AgendaUI {
 public:
  AgendaUI()
  {
    startAgenda();
  }
  void OperationLoop(void)
  {
       string operation;
      do {
          cout << "________________________________Agenda________________________________\n"
               << "Action :\n"
               << "l   - log in Agenda by user name and password\n"
               << "r   - register an Agenda account\n"
               << "q   - quit Agenda\n"
               << "______________________________________________________________________\n"
               << "\n" << "Agenda : ~$ ";
          cin >> operation;
          switch(operation[0]) {
              case 'l':
                  userLogIn();
                  break;
              case 'r':
                  userRegister();
                  break;
              case 'q':
                  quitAgenda();
                  break;
              default:
                  break;
          }
      } while(operation[0] != 'q');
  }
  

 private:
  /**
   * constructor
   */
  void startAgenda(void)
  {
    m_agendaService.startAgenda();
  }

  /**
   * catch user's operation
   * @return the operation
   */
  string getOperation()
  {
    cout << "________________________________Agenda________________________________\n"
                 << "Action :\n"
                 << "o   - log out Agenda\n"
                 << "dc  - delete Agenda account\n"
                 << "lu  - list all Agenda user\n"
                 << "cm  - create a meeting\n"
                 << "la  - list all meetings\n"
                 << "las - list all sponsor meetings\n"
                 << "lap - list all participate meetings\n"
                 << "qm  - query meeting by title\n"
                 << "qt  - query meeting by time interval\n"
                 << "dm  - delete meeting by title\n"
                 << "da  - delete all meetings\n"
                 << "______________________________________________________________________\n"
                 << "\n" << "Agenda@" << m_userName << " :# ";
    string ans;
    cin>>ans;
    return ans;
  }

  /**
   * execute the operation
   * @return if the operationloop continue
   */
  bool executeOperation(const string &t_operation)
  {
    if(t_operation=="o"){
      userLogOut();
      return false;
    }
    if(t_operation=="dc"){
      deleteUser();
      return false;
    }
    if(t_operation=="lu"){
      listAllUsers();
      return true;
    }
    if(t_operation=="cm"){
      createMeeting();
      return true;
    }
    if(t_operation=="amp"){
      addMeetingParticipator();
      return true;
    }
    if(t_operation=="rmp"){
      removeMeetingParticipator();
      return true;
    }
    if(t_operation=="rqm"){
      quitMeeting();
      return true;
    }
     if(t_operation=="la"){
      listAllMeetings();
      return true;
    }
     if(t_operation=="las"){
      listAllSponsorMeetings();
      return true;
    }
     if(t_operation=="lap"){
      listAllParticipateMeetings();
      return true;
    }
     if(t_operation=="qm"){
      queryMeetingByTitle();
      return true;
    }
     if(t_operation=="qt"){
      queryMeetingByTimeInterval();
      return true;
    }
     if(t_operation=="dm"){
      deleteMeetingByTitle();
      return true;
    }
     if(t_operation=="da"){
      deleteAllMeetings();
      return true;
    }
    return true;
  }

  /**
   * user Login
   */
  void userLogIn(void)
  {
    string userName, password;
    cout << "[log in] [username] [password]\n" << "[log in] ";
    cin >> userName >> password;
    if (m_agendaService.userLogIn(userName, password)) {
        m_userName = userName;
        m_userPassword = password;
        cout << "[log in] succeed!\n";
        while(executeOperation(getOperation()));
    }
    else {
        cout << "[log in] Password error or user doesn't exist\n";
    }
  }

  /**
   * user regist
   */
  void userRegister(void)
  {
    string userName, password, email, phone;
    cout << "[register] [username] [password] [email] [phone]\n"<< "[register] ";
    cin >> userName >> password >> email >> phone;
    if (m_agendaService.userRegister(userName, password, email, phone)) {
        m_userName= userName;
        m_userPassword = password;
        cout << "[register] succeed!\n";
        while(executeOperation(getOperation()));
    }
    else {
        cout << "This username has been registered\n";
    }
  }

  /**
   * user logout
   */
  void userLogOut(void)
  {
    m_userName.clear();
    m_userPassword.clear();
  }

  /**
   * quit the Agenda
   */
  void quitAgenda(void)
  {
    quitAgenda();
  }

  /**
   * delete a user from storage
   */
  void deleteUser(void)
  {
    m_agendaService.deleteUser(m_userName,m_userPassword);
    cout<<"[delete agenda account] succeed!\n";
    userLogOut();
  }

  /**
   * list all users from storage
   */
  void listAllUsers(void)
  {
    cout<<"[list all users]\n";
    printUsers(m_agendaService.listAllUsers());
  }

  /**
   * user create a meeting with someone else
   */
  void createMeeting(void)
  {
    string title, participator, startDate, endDate;
    cout << "[create meeting] [the number of participators]\n"<<"[create meeting] ";
    int num;
    cin>>num;
    vector<string> ans;
    for(int i=0;i<num;i++){
      cout << "[create meeting] [please enter the participator "<<i<<" ]\n"<<"[create meeting] ";
      string par;
      cin>>par;
      ans.push_back(par);
    }
    cout<<"[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n" << "[create meeting] ";
    cin >> title >> startDate >> endDate;
    if (m_agendaService.createMeeting(m_userName, title,  startDate, endDate,ans)) {
        cout << "[create meeting] succeed!\n";
    }
    else {
        cout << "[create meeting] error!\n";
    }
  }
  /**
   * sponsor add a participator to the meeting
   */
  void addMeetingParticipator(void)
  {
    cout<<"[add participator] [meeting title] [participator username]\n"<<"[add participator] ";
    string title,participator;
    cin>>title>>participator;
    if(m_agendaService.addMeetingParticipator(m_userName,title,participator))
      cout<<"[add participator] succeed!\n";
    else cout<<"[add participator] error!\n";
  }

  /**
   * sponsor add a participator to the meeting
   */
  void removeMeetingParticipator(void)
  {
    cout<<"[remove participator] [meeting title] [participator username]\n"<<"[remove participator] ";
    string title,participator;
    cin>>title>>participator;
    if(m_agendaService.removeMeetingParticipator(m_userName,title,participator))
    cout<<"[remove participator] succeed!\n";
    else cout<<"[remove participator] error!\n";
  }

  /**
   * user quit from meeting
   */
  void quitMeeting(void)
  {
    cout<<"[quit meeting] [meeting title]\n"<<"[quit meeting] ";
    string title;
    cin>>title;
    if(m_agendaService.quitMeeting(m_userName,title))
    cout<<"[quit meeting] succeed!\n";
    else cout<<"[quit meeting] error!\n";

  }

  /**
   * list all meetings from storage
   */
  void listAllMeetings(void)
  {
    cout<<"[list all meetings]\n";
    printMeetings(m_agendaService.listAllMeetings(m_userName));
  }

  /**
   * list all meetings that this user sponsored
   */
  void listAllSponsorMeetings(void)
  {
    cout<<"[list all sponsor meetings]\n";
    printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
  }

  /**
   * list all meetings that this user take part in
   */
  void listAllParticipateMeetings(void)
  {
    cout<<"[list all participate meetings]\n";
    printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
  }

  /**
   * search meetings by title from storage
   */
  void queryMeetingByTitle(void)
  {
    string title;
    cout << "[query meeting] [title]\n"<< "[query meeting] ";
    cin >> title;
    printMeetings(m_agendaService.meetingQuery(m_userName, title));
  }

  /**
   * search meetings by timeinterval from storage
   */
  void queryMeetingByTimeInterval(void)
  {
     string startDate, endDate;
      cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n"
           << "[query meetings] ";
      cin >> startDate >> endDate;
      cout<<"[query  meetings]\n";
      printMeetings(m_agendaService.meetingQuery(m_userName, startDate, endDate));
  }

  /**
   * delete meetings by title from storage
   */
  void deleteMeetingByTitle(void)
  {
    string title;
    cout << "[delete meeting] [title]\n"<< "[delete meeting] ";
    cin >> title;
    if (m_agendaService.deleteMeeting(m_userName, title)) {
        cout << "[delete meeting by title] succeed!\n";
    }
    else {
        cout << "[delete meeting by title] error!\n";
    }
  }

  /**
   * delete all meetings that this user sponsored
   */
  void deleteAllMeetings(void)
  {
    m_agendaService.deleteAllMeetings(m_userName);
     cout << "[delete all meetings] succeed!\n";
  }

  /**
   * show the meetings in the screen
   */
  void printMeetings(const list<Meeting> &t_meetings)
  {
    cout << "title\t" << "sponsor\t" << "participator\t"<< "start time\t" << "end time\n";
    for (auto itr =t_meetings.begin(); itr != t_meetings.end(); itr++) {
        cout << itr->getTitle() << "\t"
             << itr->getSponsor() << "\t"
             << Date::dateToString(itr->getStartDate()) << "\t"
             << Date::dateToString(itr->getEndDate()) << "\n";
    }
  }
  void printUsers(std::list<User> users) {
            cout << "name\t" << "email\t" << "phone\n";
            for (auto itr = users.begin(); itr != users.end(); itr++) {
                cout << itr->getName() << "\t"
                     << itr->getEmail()<< "\t"
                     << itr->getPhone()<< "\n";
            }
        }
  // dates
  std::string m_userName;
  std::string m_userPassword;
  AgendaService m_agendaService;
};

#endif
