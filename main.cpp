#include<iostream>   //standard c++ library
#include"Class.h"    //functions header files
#include<string>
#include<fstream>
using namespace std;

int main() {
    Admin a1;     //Making instance of class Admin
    Student s1(&a1);
    Teachers t1(&a1);

    Singleton *s = s->getInstance();
    s->readUser(&a1);

    int choose = 0, check;    //variables for choosing Options
    while(choose != -1)
    {
        cout<<"\n********************* Course Management System *************************";
        if(a1.userBase.admin_front == NULL)
        {
            cin.ignore();    //ignore enter key
            cout<<"\nEnter the name of Admin: ";
            string name;
            getline(cin, name);
            int id;
            id = ++a1.userBase.a_id;

            a1.userBase.CreateAdmin(name, id);  //calling function
        }
        cout<<"\n\n1- Admin"     //display Menu Driven
              "\n2- Teacher"
              "\n3- Student"
              "\n4- Exit From System: ";
        cin>>check;
        switch(check)
        {
            case 1:
            {
                a1.adminMenu();
                break;
            }
            case 2:
            {
                t1.menuDriven();
                break;
            }
            case 3:
            {
                s1.menuDriven();
                break;
            }
            case 4:
            {
                choose = -1;
                break;
            }
            default:
                cout<<"\nInvalid Input...........";     //display if input wrong
        }
    }

    s->writeUser(&a1);
    return 0;
}