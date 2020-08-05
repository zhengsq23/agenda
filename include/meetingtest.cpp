#include<iostream>
#include<string>
#include"Meeting.hpp"
#include"Date.hpp"
using namespace std;
int main(){
    string s="jhon";
    vector<string> name;
    name.push_back(s);
    Date date1(1998,2,24,5,10);
    Date date2(2000,3,13,4,20);
    Meeting a("alex",name,date1,date2,"math");
    a.addParticipator("Amy");
    a.addParticipator("king");
    cout<<a.isParticipator("jhon")<<a.isParticipator("jf")<<endl;
    a.removeParticipator("jhon");
     cout<<a.isParticipator("jhon");
}