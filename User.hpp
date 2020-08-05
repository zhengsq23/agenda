#ifndef USER_H
#define USER_H

#include <initializer_list>
#include <string>
using namespace std;
class User {
 public:
  /**
  * @brief the default constructor
  */
  User() = default;

  /**
  * constructor with arguments
  */
  User(const std::string &t_userName, const std::string &t_userPassword,
       const std::string &t_userEmail, const std::string &t_userPhone)
     {
          m_name=t_userName;
          m_password=t_userPassword;
          m_email=t_userEmail;
          m_phone=t_userPhone;
     }

  /**
  * @brief copy constructor
  */
  User(const User &t_user)
  {
       m_email=t_user.m_email;
       m_name=t_user.m_name;
       m_password=t_user.m_password;
       m_phone=t_user.m_phone;
  }

  /**
  * @brief get the name of the user
  * @return   return a string indicate the name of the user
  */
  string getName() const
  {
       return m_name;
  }

  /**
  * @brief set the name of the user
  * @param   a string indicate the new name of the user
  */
  void setName(const string &t_name)
  {
       m_name=t_name;
  }

  /**
  * @brief get the password of the user
  * @return   return a string indicate the password of the user
  */
  string getPassword() const
  {
       return m_password;
  }

  /**
  * @brief set the password of the user
  * @param   a string indicate the new password of the user
  */
  void setPassword(const string &t_password)
  {
       m_password=t_password;
  }

  /**
  * @brief get the email of the user
  * @return   return a string indicate the email of the user
  */
  string getEmail() const
  {
       return m_email;
  }

  /**
  * @brief set the email of the user
  * @param   a string indicate the new email of the user
  */
  void setEmail(const std::string &t_email)
  {
       m_email=t_email;
  }

  /**
  * @brief get the phone of the user
  * @return   return a string indicate the phone of the user
  */
  string getPhone() const
  {
       return m_phone;
  }

  /**
  * @brief set the phone of the user
  * @param   a string indicate the new phone of the user
  */
  void setPhone(const std::string &t_phone)
  {
       m_phone=t_phone;
  }

 private:
  string m_name;
  string m_password;
  string m_email;
  string m_phone;
};

#endif
