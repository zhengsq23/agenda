#include"Date.hpp"
#include<iostream>
#include<string>
using namespace std;
int main(){
    Date a(1998,3,21,20,38);
    Date b(2000,4,5,13,20);
    Date c(2019,2,29,10,30);
    Date d("2000-08-24/18:00");
    string s=Date::dateToString(a);
    cout<<d.getHour()<<endl;
    cout<<(a>b)<<endl;
    cout<<Date::isValid(c)<<endl;
    cout<<s<<endl;
}