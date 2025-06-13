#ifndef _Class_H
#define _Class_H

#include<iostream>
#include<string>
#include<fstream>
using namespace std;


//................................ Creating User's Accounts .............................

struct UserData
{
    string name;
    int id;
    UserData* next;
};

class User
{
public:
    UserData* student_front, *teacher_front, *admin_front;    //start node for linked list
    int s_id, t_id, a_id, a_nodes, s_nodes, t_nodes;      //iteration for id's

    User();
    ~User();

    UserData * createUser(string name);
    UserData * userSearch(UserData* , int);
    UserData * checkUser(UserData*, int);
    void Display(UserData*);

    void userMenu();
    UserData *CreateAdmin(string , int);
    void DeleteAdmin(int );
    UserData *CreateStudent(string , int);
    void DeleteStudent(int );
    UserData *CreateTeacher(string , int);
    void DeleteTeacher(int );
};


// *********************************** Course Managing ********************************

struct Node
{
    int height;
    UserData* user;
    Node *left, *right;
    Node(UserData *);
};

class HeapNode
{
public:
    Node * user;
    int ptr;
};

class CourseMaking
{
public:
    Node *student_root, *teacher_root;
    int cs_nodes, ct_nodes;

    //For Slots
    HeapNode *arr;
    int cap, usedSize, pri;

    CourseMaking *next;
    string name;
    int id;
    User *userBase;

    CourseMaking(User *);
    ~CourseMaking();
    void AdminCourseMenu();
    void deleteAllNodes(Node* );

    int max(int a, int b);
    Node *rightRotate(Node *);
    Node *leftRotate(Node *);
    void inOrderTraversal(int, Node* );
    Node *minNode(Node* root);
    int getheight(Node*);     //user-defined functions
    int getHeightDifference(Node* );
    int getBalance(Node *);

    Node* insert(UserData* , Node* );
    Node* searchKey(UserData* , Node*);
    Node* deleteN(UserData* ,Node* );

    void heapify(int i);
    void SetAppoinments();
    void takeAppoinment(Node*);
    void deleteAppoinment(Node*);
    void checkAppoinment(Node*);
    void displayAppoinments();
    void reset();
};

// ****************************** Course linking *******************************

class Courses
{
    int total_courses;
    User *base;
public:
    CourseMaking *admin_front_link;

    Courses();
    ~Courses();

    CourseMaking* createCourses(User* userBase);
    void displayCourses();
    void deleteCourse(int );
    CourseMaking *userSearch(CourseMaking * user_front, int id);
};

// ************************************* Admin Portal *********************************

class Admin
{
public:
    User userBase;
    Courses courseLinked;
    void adminMenu();
};


class Student
{
    Admin *admin;
public:
    Student(Admin*);
    void menuDriven();
};


class Teachers
{
    Admin *admin;
public:
    Teachers(Admin*);
    void menuDriven();
};

// ******************************** Singleton ******************************

class Singleton {
    static Singleton *instance;

// Private constructor so that no objects can be created.
    Singleton();

public:
    static Singleton *getInstance();
    void writeUser(Admin* );
    void readUser(Admin* );
};

#endif