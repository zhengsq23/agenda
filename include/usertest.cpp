#include<iostream>
#include<string>
#include"User.hpp"
using namespace std;
int main(){
    User alex("alex","12345","12342@qq.com","3382823");
    cout<<alex.getEmail()<<alex.getName()<<endl;
    User copy(alex);
    cout<<copy.getName()<<copy.getPassword()<<endl;

}