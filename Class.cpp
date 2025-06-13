#include "Class.h"      //headers files
#include<iostream>      //standard c++ library
#include<string>
#include<fstream>
using namespace std;


//****************TASK 1*****************

User::User() {
    student_front = NULL;
    teacher_front = NULL;
    admin_front = NULL;
    s_id = t_id = a_id = a_nodes = s_nodes = t_nodes = 0;
}

User::~User() {         //delete all dynamic allocated nodes
    while(student_front != NULL)
    {
        UserData* temp = student_front;
        student_front = student_front->next;
        delete temp;
    }

    while(admin_front != NULL)
    {
        UserData* temp = admin_front;
        admin_front = admin_front->next;
        delete temp;
    }

    while(teacher_front != NULL)
    {
        UserData* temp = teacher_front;
        teacher_front = teacher_front->next;
        delete temp;
    }
}

Node::Node(UserData *temp)
{
    user = temp;
    left = right = NULL;
    height = 0;
}

void User::userMenu() {
    int choose = 0, check;    //variables for choosing Options
    while(choose != -1)
    {
        cout<<"\n*********************** Account Management Portal *********************"
              "\n\n1- Create Admin"     //display Menu Driven
              "\n2- Delete Admin"
              "\n3- Display All Admins"
              "\n4- Create Student"
              "\n5- Delete Student"
              "\n6- Display All Students"
              "\n7- Create Teacher"
              "\n8- Delete Teacher"
              "\n9- Display All Teachers"
              "\n10- Return to Admin Portal: ";
        cin>>check;
        switch(check)
        {
            case 1:
            {
                cin.ignore();    //ignore enter key
                cout<<"\nEnter the name of Admin: ";
                string name;
                getline(cin, name);
                int id;
                id = ++a_id;

                UserData *temp = CreateAdmin(name, id);  //calling function
                cout<<"\nAccount Created Successfully, "<<temp->name<<" id is: "<<temp->id;
                break;
            }
            case 2:
            {
                cout<<"\nEnter the id: ";
                int id;
                cin>>id;
                DeleteAdmin(id);
                if(checkUser(admin_front, id) == NULL)
                    choose = -1;
                break;
            }
            case 3:
            {
                cout<<"\nDisplaying ALL Admins.......";
                Display(admin_front);
                break;
            }
            case 4:
            {
                cin.ignore();
                cout<<"\nEnter the name of Student: ";
                string name;
                getline(cin, name);
                int id;
                id = ++s_id;

                UserData *temp = CreateStudent(name, id);  //calling function
                cout<<"\nAccount Created Successfully, "<<temp->name<<" id is: "<<temp->id;
                break;
            }
            case 5:
            {
                if(s_nodes == 0)
                    cout<<"\nNo Account Created yet.............";
                else
                {
                    cout<<"\nEnter the id: ";
                    int id;
                    cin>>id;
                    DeleteStudent(id);
                }
                break;
            }
            case 6:
            {
                if(s_nodes == 0)
                    cout<<"\nNo Student to Show..........";
                else {
                    cout << "\nDisplaying ALL Students.......";
                    Display(student_front);
                }
                break;
            }
            case 7:
            {
                cin.ignore();
                cout<<"\nEnter the name of Teacher: ";
                string name;
                getline(cin, name);
                int id;
                id = ++t_id;

                UserData *temp = CreateTeacher(name, id);  //calling function
                cout<<"\nAccount Created Successfully, "<<temp->name<<" id is: "<<temp->id;
                break;
            }
            case 8:
            {
                if(t_nodes == 0)
                    cout<<"\nNo Account Created yet.............";
                else
                {
                    cout<<"\nEnter the id: ";
                    int id;
                    cin>>id;
                    DeleteTeacher(id);
                }
                break;
            }
            case 9:
            {
                if(t_nodes == 0)
                    cout<<"\nNo Teacher to Show..........";
                else {
                    cout << "\nDisplaying ALL Teachers.......";
                    Display(teacher_front);
                }
                break;
            }
            case 10:
            {
                choose = -1;
                break;
            }
            default:
                cout<<"\nInvalid Input...........";     //display if input wrong
        }
    }
}

void User::Display(UserData *front) {
    int count = 0;     //counter for sr no.
    cout<<"\nSr no.\t| ID\t| Names";
    while(front != NULL)
    {
        cout<<endl<<++count<<"\t| "<<front->id<<"\t| "<<front->name;
        front = front->next;
    }
}

UserData *User::createUser(string name) {
    UserData*temp = new UserData;      //create new admin
    temp->next = NULL;
    temp->name = name;

    return temp;
}

UserData *User::userSearch(UserData * user_front, int id) {
    UserData* user_prev = user_front;      //Save deleted node previous node

    if(user_front->next->next == NULL)      //Case for if only two Node
    {
        if(user_front->next->id == id)
            return user_prev;
        else
            return NULL;    //Null if Id Node Found
    }
    else{                //Case if More than two Node
        user_front = user_front->next;
        while(user_front->id != id)
        {
            if(user_front->next != NULL)
            {
                user_prev = user_front;     //Previous Update
                user_front = user_front->next;
            }
            else
            {
                return NULL;
            }
        }
        return user_prev;
    }
}

UserData *User::checkUser(UserData * user, int id) {
    if(user->id == id )    //Case if id found at front
    {
        return user;
    }
    else if(user->next == NULL)     //Case if id not found at front
        return NULL;
    else
    {
        UserData* temp = userSearch(user, id);    //Return Previous deleted Node or Null if not found id
        if(temp == NULL)
            return NULL;
        else
        {
            UserData* prev = temp->next;   //Node to be deleted
            return prev;
        }
    }
}

UserData* User::CreateAdmin(string name, int id) {
    UserData* temp = createUser(name);   //calling create User function
    a_nodes++;
    temp->id = id;      //assign admin data
    temp->name = name;

    if(admin_front == NULL)
        admin_front = temp;
    else
    {
        UserData* curr = admin_front;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = temp;
    }

    return temp;
}

void User::DeleteAdmin(int id) {
    if(admin_front->id == id)    //Case if id found at front
    {
        UserData* temp = admin_front;
        admin_front = admin_front->next;
        delete temp;
        cout<<"\nAccount Deleted Successfully.........";
    }
    else if(admin_front->next == NULL)     //Case if id not found at front
    {
        cout<<"\nAlas! Id Not Found..............";
        return;
    }
    else
    {
        UserData* temp = userSearch(admin_front, id);    //Return Previous deleted Node or Null if not found id
        if(temp == NULL)
        {
            cout<<"\nAlas! Id Not Found..............";
            return;
        }
        else
        {
            UserData* del = temp->next;   //Node to be deleted
            if(temp->next->next == NULL)     //Case for if delete last Node
                temp->next = NULL;
            else
                temp->next = temp->next->next;
            delete del;
            cout<<"\nAccount Deleted Successfully.........";
        }
    }
    a_nodes--;
}

UserData* User::CreateStudent(string name, int id) {
    UserData* temp = createUser(name);   //calling create User function
    s_nodes++;
    temp->id = id;      //assign admin data
    temp->name = name;

    if(student_front == NULL)
        student_front = temp;
    else
    {
        UserData* curr = student_front;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = temp;
    }
    return temp;
}

void User::DeleteStudent(int id) {
    if(student_front->id == id)    //Case if id found at front
    {
        UserData* temp = student_front;
        student_front = student_front->next;
        delete temp;
        cout<<"\nAccount Deleted Successfully.........";
    }
    else if(student_front->next == NULL)     //Case if id not found at front
    {
        cout<<"\nAlas! Id Not Found..............";
        return;
    }
    else
    {
        UserData* temp = userSearch(student_front, id);    //Return Previous deleted Node or Null if not found id
        if(temp == NULL)
        {
            cout<<"\nAlas! Id Not Found..............";
            return;
        }
        else
        {
            UserData* del = temp->next;   //Node to be deleted
            if(temp->next->next == NULL)     //Case for if delete last Node
                temp->next = NULL;
            else
                temp->next = temp->next->next;
            delete del;
            cout<<"\nAccount Deleted Successfully.........";
        }
    }
    s_nodes--;
}

UserData* User::CreateTeacher(string name, int id) {
    UserData* temp = createUser(name);   //calling create User function
    t_nodes++;
    temp->id = id;      //assign admin data
    temp->name = name;

    if(teacher_front == NULL)
        teacher_front = temp;
    else
    {
        UserData* curr = teacher_front;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = temp;
    }
    return temp;
}

void User::DeleteTeacher(int id) {
    if(teacher_front->id == id)    //Case if id found at front
    {
        UserData* temp = teacher_front;
        teacher_front = teacher_front->next;
        delete temp;
        cout<<"\nAccount Deleted Successfully.........";
    }
    else if(teacher_front->next == NULL)     //Case if id not found at front
    {
        cout<<"\nAlas! Id Not Found..............";
        return;
    }
    else
    {
        UserData* temp = userSearch(teacher_front, id);    //Return Previous deleted Node or Null if not found id
        if(temp == NULL)
        {
            cout<<"\nAlas! Id Not Found..............";
            return;
        }
        else
        {
            UserData* del = temp->next;   //Node to be deleted
            if(temp->next->next == NULL)     //Case for if delete last Node
                temp->next = NULL;
            else
                temp->next = temp->next->next;
            delete del;
            cout<<"\nAccount Deleted Successfully.........";
        }
    }
    t_nodes--;
}

//****************TASK 2*****************

void CourseMaking::heapify(int i) { //definition of user defined function of class
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if(left<cap && arr[left].ptr > arr[largest].ptr)
        largest = left;
    if(right<cap && arr[right].ptr > arr[largest].ptr)
        largest = right;
    if(largest != i)
    {
        HeapNode *temp = new HeapNode;

        temp->ptr = arr[i].ptr;
        temp->user = arr[i].user;
        arr[i].ptr = arr[largest].ptr;
        arr[i].user = arr[largest].user;
        arr[largest].ptr = arr[i].ptr;
        arr[largest].user = arr[i].user;

        delete temp;
        heapify(largest);
    }
}

void CourseMaking::SetAppoinments() {
    delete [] arr;
    cout<<"\nEnter No. of SLots : ";
    cin>>cap;
    arr = new HeapNode[cap];
}

void CourseMaking::takeAppoinment(Node * a) {
    pri++;
    arr[usedSize].ptr = pri;
    arr[usedSize].user = a;
    usedSize++;

    for(int i = usedSize/2 - 1; i>=0; i--)
        heapify(i);
}

void CourseMaking::deleteAppoinment(Node* ) {

}

void CourseMaking::AdminCourseMenu() {
    cout<<"\n.......................... "<<name<< " ( "<<id<<" ) Managing ..........................";        //display string
    int choose1, data;        //declaring variable

    do {
        cout<<"\n\n1- Add Students"     //display string
              "\n2- Remove Students"
              "\n3- Insert Teachers"
              "\n4- Delete Teachers"
              "\n5- Display All Students"
              "\n6- Display All Teachers"
              "\n7- Exit from Course Manager: ";
        cin>>choose1;        //taking input from user

        switch (choose1)
        {
            case 1:
            {
                cout << "\nEnter the Student ID: ";        //display string
                cin >> data;
                UserData* temp = userBase->checkUser(userBase->student_front, data);
                if(temp == NULL)
                    cout<<"\nId Not Found...........";
                else if(searchKey(temp, student_root) == NULL) {
                    student_root = insert(temp ,student_root);
                    cs_nodes++;
                    cout<<"\n"<<temp->name<<" ("<<temp->id<<") Added Successfully.......";
                }
                else
                    cout<<"\n' "<<data<<" ' is Already in Course";
                break;
            }
            case 2:
            {
                if(cs_nodes==0)
                    cout<<"\nTree is Empty: ";        //display string
                else
                {
                    cout<<"\nEnter the id: ";
                    cin>>data;        //taking input from user
                    UserData* temp = userBase->checkUser(userBase->student_front, data);
                    if(temp == NULL)
                        cout<<"\nId Not Found...........";
                    else if(searchKey(temp, student_root) == NULL)
                        cout<<"\nKey not Found.....";
                    else
                    {
                        student_root = deleteN(temp,student_root);    //calling user-defined function of class
                        cs_nodes--;
                        cout<<"\n"<<temp->name<<" ("<<temp->id<<") Deleted Completely.......";        //display string
                    }
                }
                break;
            }
            case 3:
            {
                cout << "\nEnter the Teacher ID: ";        //display string
                cin >> data;
                UserData* temp = userBase->checkUser(userBase->teacher_front, data);
                if(temp == NULL)
                    cout<<"\nId Not Found...........";
                else if(searchKey(temp, teacher_root) == NULL) {
                    teacher_root = insert(temp ,teacher_root);
                    ct_nodes++;
                    cout<<"\n"<<temp->name<<" ("<<temp->id<<") Added Successfully.......";
                }
                else
                    cout<<"\n' "<<data<<" ' is Already in Course";
                break;
            }
            case 4:
            {
                if(ct_nodes==0)
                    cout<<"\nTree is Empty: ";        //display string
                else
                {
                    cout<<"\nEnter the id: ";
                    cin>>data;        //taking input from user
                    UserData* temp = userBase->checkUser(userBase->teacher_front, data);
                    if(temp == NULL)
                        cout<<"\nId Not Found...........";
                    else if(searchKey(temp, teacher_root) == NULL)
                        cout<<"\nKey not Found.....";
                    else
                    {
                        teacher_root = deleteN(temp,teacher_root);    //calling user-defined function of class
                        ct_nodes--;
                        cout<<"\n"<<temp->name<<" ("<<temp->id<<") Deleted Completely.......";        //display string
                    }
                }
                break;
            }
            case 5:
            {
                if(cs_nodes==0)
                    cout<<"\nNo, Student assign in this course yet.......";        //display string
                else
                {
                    int count = 0;     //counter for sr no.
                    cout<<"\nSr no.\t| ID\t| Names";
                    inOrderTraversal(count, student_root);
                }
                break;
            }
            case 6:
            {
                if(ct_nodes==0)
                    cout<<"\nNo, Teachers assign in this course yet.......";        //display string
                else
                {
                    int count = 0;     //counter for sr no.
                    cout<<"\nSr no.\t| ID\t| Names";
                    inOrderTraversal(count, teacher_root);
                }
                break;
            }
            case 7:
            {
                choose1=22;      //initialize to specific value to exit from code
                break;
            }
            default:
                cout<<"\nInvalid Input,Please Try Again\n";        //display string
        }
    }
    while(!(choose1==22));
}

CourseMaking::CourseMaking(User *userBase) {
    student_root = teacher_root = NULL;
    next = NULL;
    id = cs_nodes = ct_nodes = cap = usedSize = pri = 0;
    this->userBase = userBase;
}

CourseMaking::~CourseMaking() {
    deleteAllNodes(student_root);
    deleteAllNodes(teacher_root);
    student_root = teacher_root = NULL;
}

int CourseMaking::max(int a, int b) {
    if(a>b)
        return a;
    else
        return b;
}

Node * CourseMaking::minNode(Node* root)
{
    Node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

int CourseMaking::getheight(Node *root) {
    return (root == NULL)? 0:root->height;
}
int CourseMaking::getBalance(Node *root)
{
    if (root == NULL)
        return 0;
    return getHeightDifference(root);
}
int CourseMaking::getHeightDifference(Node *root) {
    return getheight(root->left) - getheight(root->right);
}

Node* CourseMaking :: insert(UserData* temp ,Node* root )
{
    if (root == NULL) {
        Node *temp1 = new Node(temp);
        return temp1;
    }
    if (temp->id < root->user->id)
        root->left = insert(temp, root->left);
    else if (temp->id > root->user->id)
        root->right = insert(temp ,root->right );
    else
        return root;
    root->height = max(getheight(root->left),getheight(root->right)) + 1;

    int balance = getBalance(root);
    if (balance < -1 && temp->id > root->right->user->id) // right right
        return leftRotate(root);
    if (balance > 1 && temp->id < root->left->user->id) //left left
        return rightRotate(root);
    if (balance < -1 && temp->id < root->right->user->id) // right left
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    if (balance > 1 && temp->id > root->left->user->id) // left right
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

Node* CourseMaking::deleteN(UserData* user, Node* root)
{
    if (root == NULL)
        return root;
    if ( user->id < root->user->id )
        root->left = deleteN(user ,root->left);
    else if( user->id > root->user->id )
        root->right = deleteN(user ,root->right);
    else
    {
        if( (root->right == NULL) || (root->left == NULL) )    //node no children
        {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node* temp = minNode(root->right); //node with two children
            root->user = temp->user;
            root->right = deleteN(temp->user ,root->right);
        }
    }
    if (root == NULL) //node one child
        return root;
    root->height = 1 + max(getheight(root->left),getheight(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) //left left
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) //left right
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)      //right right
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)     //right left
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* CourseMaking :: leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getheight(x->left), getheight(x->right)) +
                1;
    y->height = max(getheight(y->left),getheight(y->right)) +
                1;
    return y;
}
Node * CourseMaking::rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getheight(y->left), getheight(y->right)) +
                1;
    x->height = max(getheight(x->left), getheight(x->right)) +
                1;
    return x;
}

Node *CourseMaking::searchKey(UserData* data, Node* root) {
    if(root == NULL)
        return NULL;
    else if(data->id == root->user->id)
        return root;
    else if(data->id < root->user->id)
        return searchKey(data, root->left);
    else
        return searchKey(data, root->right);
}

void CourseMaking::inOrderTraversal(int count, Node *root) {
    if(root == NULL)
        return;
    inOrderTraversal(count, root->left);
    cout<<endl<<++count<<"\t| "<<root->user->id<<"\t| "<<root->user->name;
    inOrderTraversal(count, root->right);
}

void CourseMaking::deleteAllNodes(Node* root) {
    if(root!=NULL) {
        deleteAllNodes(root->left);
        deleteAllNodes(root->right);
        delete root;
    }
}

Courses::Courses() {
    admin_front_link = NULL;
    total_courses = 0;
}

Courses::~Courses() {
    while (admin_front_link != NULL)
    {
        CourseMaking* temp = admin_front_link;
        admin_front_link = admin_front_link->next;
        delete temp;
    }
}

CourseMaking* Courses::createCourses(User *userBase) {
    CourseMaking*temp = new CourseMaking(userBase);      //create new admin
    temp->next = NULL;
    cout<<"\nEnter the course name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    temp->name = name;
    cout<<"\nEnter "<<name<<" id: ";
    cin>>temp->id;

    total_courses++;

    if(admin_front_link == NULL)
        admin_front_link = temp;
    else
    {
        CourseMaking* curr = admin_front_link;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = temp;
    }
    return temp;
}

CourseMaking *Courses::userSearch(CourseMaking * user_front, int id) {
    CourseMaking* user_prev = user_front;      //Save deleted node previous node

    if(user_front->next->next == NULL)      //Case for if only two Node
    {
        if(user_front->next->id == id)
            return user_prev;
        else
            return NULL;    //Null if Id Node Found
    }
    else{                //Case if More than two Node
        user_front = user_front->next;
        while(user_front->id != id)
        {
            if(user_front->next != NULL)
            {
                user_prev = user_front;     //Previous Update
                user_front = user_front->next;
            }
            else
            {
                return NULL;
            }
        }
        return user_prev;
    }
}

void Courses::deleteCourse(int id) {

    if(admin_front_link->id == id)    //Case if id found at front
    {
        CourseMaking* temp = admin_front_link;
        admin_front_link = admin_front_link->next;
        delete temp;
        cout<<"\nCourse Deleted Successfully.........";
    }
    else if(admin_front_link->next == NULL)     //Case if id not found at front
    {
        cout<<"\nAlas! Id Not Found..............";
        return;
    }
    else
    {
        CourseMaking* temp = userSearch(admin_front_link, id);    //Return Previous deleted Node or Null if not found id
        if(temp == NULL)
        {
            cout<<"\nAlas! Id Not Found..............";
            return;
        }
        else
        {
            CourseMaking* del = temp->next;   //Node to be deleted
            if(temp->next->next == NULL)     //Case for if delete last Node
                temp->next = NULL;
            else
                temp->next = temp->next->next;
            delete del;
            cout<<"\nAccount Deleted Successfully.........";
        }
    }
    total_courses--;
}

void Courses::displayCourses() {
    CourseMaking* temp = admin_front_link;
    int count = 0;     //counter for sr no.
    cout<<"\nSr no.\t| ID\t| Course Names";
    while(temp != NULL)
    {
        cout<<endl<<++count<<"\t| "<<temp->id<<"\t| "<<temp->name;
        temp = temp->next;
    }
}

void Admin::adminMenu() {
    cout<<"\n\n**************************** Admin Portal **************************";

    int choose = 0, check;    //variables for choosing Options
    UserData* temp;
    do
    {
        cout<<"\nEnter your Id: ";
        cin>>check;
        cin.get();

        temp = userBase.checkUser(userBase.admin_front, check);

        if(temp == NULL)
            cout<<"\nAlas! Id Not Found.......";
        else
        {
            cout<<"\nEnter your Name: ";
            string name;
            getline (cin, name);

            if(temp != NULL && temp->name != name)
                cout<<"\nName is Incorrect..........";
            else
                break;
        }

        cout<<"\n\n1- Want to Try Again"
              "\n2- Return to Main Menu: ";
        cin>>check;

        if(check == 2)
            choose = -1;

    }while(choose != -1);      //check for user id

    while(choose != -1)     //admin portal main menu
    {
        cout<<"\n\n*************************** Hello "<<temp->name<<" *****************************";
        cout<<"\n\n1- Choose '1' to Create/Delete User"     //display Menu Driven
              "\n2- Create Course"
              "\n3- Delete Courses"
              "\n4- Changing in Courses"
              "\n5- Display Courses"
              "\n6- Exit From Portal: ";
        cin>>check;
        switch(check)
        {
            case 1:
            {
                userBase.userMenu();
                if(userBase.checkUser(userBase.admin_front, temp->id) == NULL)   //check if admin exit or not
                    choose = -1;
                break;
            }
            case 2:
            {
                CourseMaking*temp = courseLinked.createCourses(&userBase);
                cout<<"\n"<<temp->name<<" ("<<temp->id<<") course created Successfully...";
                temp->AdminCourseMenu();
                break;
            }
            case 3:
            {
                if(courseLinked.admin_front_link == NULL)
                    cout<<"\nNo, course Formed yet........";
                else {
                    int id;
                    cout << "\nEnter the Id of Course: ";
                    cin >> id;
                    courseLinked.deleteCourse(id);
                }
                break;
            }
            case 4:
            {
                if(courseLinked.admin_front_link == NULL)
                    cout<<"\nNo, course Formed yet........";
                else
                {
                    courseLinked.displayCourses();
                    int id;
                    cout<<"\nEnter the Id of Course: ";
                    cin>>id;
                    CourseMaking * curr = courseLinked.admin_front_link;;
                    while (curr!=NULL) {
                        if (curr->id == id)
                            break;
                        curr=curr->next;
                    }
                    if(curr==NULL)
                        cout<<"\nWrong Id!";
                    else
                        curr->AdminCourseMenu();
                }
                break;
            }
            case 5:
            {
                if(courseLinked.admin_front_link == NULL)
                    cout<<"\nNo, course Formed yet........";
                else
                {
                    courseLinked.displayCourses();
                }
                break;
            }
            case 6:
            {
                choose = -1;
                break;
            }
            default:
                cout<<"\nInvalid Input...........";     //display if input wrong
        }
    }
}

Student::Student(Admin * admin) {
    this->admin = admin;
}

void Student::menuDriven() {
    cout<<"\n\n**************************** Student Portal **************************";

    int choose = 0, check;    //variables for choosing Options
    UserData* temp;
    CourseMaking* node;
    do
    {
        cout<<"\nEnter your Id: ";
        cin>>check;
        cin.get();

        temp = admin->userBase.checkUser(admin->userBase.student_front, check);

        if(temp == NULL)
            cout<<"\nAlas! Id Not Found.......";
        else
        {
            cout<<"\nEnter your Name: ";
            string name;
            getline (cin, name);

            if(temp != NULL && temp->name != name)
                cout<<"\nName is Incorrect..........";
            else
                break;
        }

        cout<<"\n\n1- Want to Try Again"
              "\n2- Return to Main Menu: ";
        cin>>check;

        if(check == 2)
            choose = -1;

    }while(choose != -1);      //check for user id

    if(choose != -1)     //show student courses in which he enrolled
    {
        int count = 0, in;
        while(admin->courseLinked.admin_front_link->next!=NULL)
        {
            Node* node1 = admin->courseLinked.admin_front_link->searchKey(temp, admin->courseLinked.admin_front_link->student_root);
            if(node1 != NULL)
            {
                count++;
                cout<<endl<<count<<"- "<<admin->courseLinked.admin_front_link->name;
            }
            admin->courseLinked.admin_front_link = admin->courseLinked.admin_front_link->next;
        }
        do{
            cout<<"\nSelect Course: ";
            cin>>in;
        }while((in<=0)  && (in >count));

        if(count == 0)
            cout<<"\n "<<temp->name<<" does not enllored in any course.";
        else
        {
            count = 0;
            while(admin->courseLinked.admin_front_link->next!=NULL)
            {
                count++;
                if(in == count)
                    node = admin->courseLinked.admin_front_link;
                admin->courseLinked.admin_front_link = admin->courseLinked.admin_front_link->next;
            }
        }
    }

    while(choose != -1)     //admin portal main menu
    {
        cout<<"\n\n*************************** Hello "<<temp->name<<" *****************************";
        cout<<"\n\n1- Make a slot"     //display Menu Driven
              "\n2- Delete a slot"
              "\n3- Msg on group"
              "\n4- Delete Msg"
              "\n5- Display Msg's"
              "\n6- Exit From Portal: ";
        cin>>check;
        switch(check)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                break;
            }
            case 7:
            {
                choose = -1;
                break;
            }
            default:
                cout<<"\nInvalid Input...........";     //display if input wrong
        }
    }
}


Teachers::Teachers(Admin *admin) {
    this->admin = admin;
}

void Teachers::menuDriven() {
    cout<<"\n\n**************************** Teacher Portal **************************";

    int choose = 0, check;    //variables for choosing Options
    UserData* temp;
    CourseMaking* node;
    do
    {
        cout<<"\nEnter your Id: ";
        cin>>check;
        cin.get();

        temp = admin->userBase.checkUser(admin->userBase.teacher_front, check);

        if(temp == NULL)
            cout<<"\nAlas! Id Not Found.......";
        else
        {
            cout<<"\nEnter your Name: ";
            string name;
            getline (cin, name);

            if(temp != NULL && temp->name != name)
                cout<<"\nName is Incorrect..........";
            else
                break;
        }

        cout<<"\n\n1- Want to Try Again"
              "\n2- Return to Main Menu: ";
        cin>>check;

        if(check == 2)
            choose = -1;

    }while(choose != -1);      //check for user id

    if(choose != -1)     //show student courses in which he enrolled
    {
        int count = 0, in;
        while(admin->courseLinked.admin_front_link->next!=NULL)
        {
            Node* node1 = admin->courseLinked.admin_front_link->searchKey(temp, admin->courseLinked.admin_front_link->student_root);
            if(node1 != NULL)
            {
                count++;
                cout<<endl<<count<<"- "<<admin->courseLinked.admin_front_link->name;
            }
            admin->courseLinked.admin_front_link = admin->courseLinked.admin_front_link->next;
        }
        do{
            cout<<"\nSelect Course: ";
            cin>>in;
        }while((in<=0)  && (in >count));

        if(count == 0)
            cout<<"\n "<<temp->name<<" does not enrolled in any course.";
        else
        {
            count = 0;
            while(admin->courseLinked.admin_front_link->next!=NULL)
            {
                count++;
                if(in == count)
                    node = admin->courseLinked.admin_front_link;
                admin->courseLinked.admin_front_link = admin->courseLinked.admin_front_link->next;
            }
        }
    }

    while(choose != -1)     //admin portal main menu
    {
        cout<<"\n\n*************************** Hello "<<temp->name<<" *****************************";
        cout<<"\n\n1- Change appointment slot"     //display Menu Driven
              "\n2- Add students in course"
              "\n3- Msg on group"
              "\n4- Delete Msg"
              "\n5- Display Msg's"
              "\n6- Exit From Portal: ";
        cin>>check;
        switch(check)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                break;
            }
            case 7:
            {
                choose = -1;
                break;
            }
            default:
                cout<<"\nInvalid Input...........";     //display if input wrong
        }
    }
}

Singleton *Singleton::instance = 0;

Singleton::Singleton() {

}

Singleton *Singleton::getInstance() {
    if (!instance)
        instance = new Singleton;
    return instance;
}

void Singleton::writeUser(Admin* a) {
    ofstream out("User.txt");

    //FOR Admins
    out<<a->userBase.a_id<<" " <<a->userBase.a_nodes<<"\n";      // save max id's
    UserData* curr = a->userBase.admin_front;
    while (curr != NULL)
    {
        out<<curr->id<<"\n"<<curr->name<<"\n";     //save data
        curr = curr->next;
    }

    //For Students
    out<<a->userBase.s_id<<" " <<a->userBase.s_nodes<<"\n";      // save max id's
    curr = a->userBase.student_front;
    while (curr != NULL)
    {
        out<<curr->id<<"\n"<<curr->name<<"\n";     //save data
        curr = curr->next;
    }

    //For Teacher
    out<<a->userBase.t_id<<" " <<a->userBase.t_nodes<<"\n";      // save max id's
    curr = a->userBase.teacher_front;
    while (curr != NULL)
    {
        out<<curr->id<<"\n"<<curr->name<<"\n";     //save data
        curr = curr->next;
    }

    out.close();
}

void Singleton::readUser(Admin * a) {
    ifstream in("User.txt");

    //For Admins Saving Data
    int a_id, n_nodes, id;
    string name;
    in>> a_id>>n_nodes;     //getting data
    in.ignore();

    for(int i=0; i<n_nodes; i++)
    {
        in>>id;
        in.ignore();
        getline(in, name);
        a->userBase.CreateAdmin(name, id);
    }

    a->userBase.a_id = a_id;
    a->userBase.a_nodes = n_nodes;

    //For Students
    a_id = n_nodes = 0;
    in>> a_id>>n_nodes;     //getting data
    in.ignore();

    for(int i=0; i<n_nodes; i++)
    {
        in>>id;
        in.ignore();
        getline(in, name);
        a->userBase.CreateStudent(name, id);
    }

    a->userBase.s_id = a_id;
    a->userBase.s_nodes = n_nodes;

    //FOR Teachers
    a_id = n_nodes = 0;
    in>> a_id>>n_nodes;     //getting data
    in.ignore();

    for(int i=0; i<n_nodes; i++)
    {
        in>>id;
        in.ignore();
        getline(in, name);
        a->userBase.CreateTeacher(name, id);
    }

    a->userBase.t_id = a_id;
    a->userBase.t_nodes = n_nodes;

    in.close();
}
