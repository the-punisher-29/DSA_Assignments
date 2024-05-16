#include<bits/stdc++.h>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName(){
        return studentName;
    }
    void set_studentName(string Name){
        studentName=Name;
    }
    string get_rollNumber(){
        return rollNumber;
    }
    void set_rollNumber(string rollnum){
        rollNumber=rollnum;
    }
};

class Node{
private:
	Node* next;
	StudentRecord* element;
public:
    Node* get_next(){
        return next;
    }
    StudentRecord* get_element(){
        return element;
    }
    void set_next(Node* value){
        next=value;
    }
    void set_element(StudentRecord* student){
        element=student;
    }
};

class Entity {
private:
    string name;
    Node* iterator;

public:
    string get_name(){
        return name;
    }
    void set_name(string Name){
        name=Name;
    }
    Node* get_iterator(){
        return iterator;
    }
    void set_iterator(Node* iter){
        iterator=iter;
    }
};

vector<vector<string>> data;

vector<string> getdata(string str) {
    vector<string> result;
    string temp = "";
    int start;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '[') {
            start = i + 1;
            temp = "";
            break;
        }
        if (str[i] == ',') {
            result.push_back(temp);
            temp = "";
            continue;
        }
        temp += str[i];
    }

    string holder = "";
    for (int i = start; i < str.size(); ++i) {
        if (str[i] == ']') {
            holder += temp;
            start = i + 2;
            temp = "";
            break;
        }
        if (str[i] == ',') {
            holder += temp + '|';
            temp = "";
            continue;
        }
        temp += str[i];
    }

    result.push_back(holder.substr(0, holder.size()));
    holder = "";

    result.push_back(str.substr(start, 2));
    start += 4;

    for (int i = start; i < str.size(); ++i) {
        if (str[i] == ']') {
            holder += temp;
            start = i + 2;
            temp = "";
            break;
        }
        if (str[i] == ',') {
            holder += temp + '|';
            temp = "";
            continue;
        }
        temp += str[i];
    }

    result.push_back(holder.substr(0, holder.size()));
    
    return result;
}

vector<StudentRecord> students;

class LinkedList :
public Entity {
    // Implement LinkedList members here
    public:
void add_student(StudentRecord student) {
    students.push_back(student);
    Node* newNode = new Node();
    newNode->set_element(&students.back());

    Node* current = get_iterator();
    while (current->get_next() != NULL) {
        current = current->get_next();
    }

    current->set_next(newNode);
}

void delete_student(string studentName) {
    Node* current = get_iterator();

    if (current->get_element()->get_studentName() == studentName) {
        set_iterator(current->get_next());
        return;
    }

    while (current->get_next() != NULL && current->get_next()->get_element()->get_studentName() != studentName) {
        current = current->get_next();
    }

    if (current->get_next() != NULL) {
        current->set_next(current->get_next()->get_next());
    }
}

};

vector<LinkedList> EntityArray;

void createEntityArray(string str, int size, vector<vector<string>> data, int index) {
    Node *head = new Node();
    Node *current;
    head->set_element(&students[0]);
    head->set_next(NULL);
    current = head;

    for (int i = 0; i < size; ++i) {
        if (data[i][index].find(str) != string::npos) {
            Node *newNode = new Node();
            newNode->set_element(&students[i]);
            current->set_next(newNode);
            current = current->get_next();
        }
    }

    head = head->get_next();
    LinkedList linkedList;
    linkedList.set_iterator(head);
    linkedList.set_name(str);
    EntityArray.push_back(linkedList);
}


void read_input_file(string Details){
    ifstream file;
    file.open(Details,ios::in);
    vector<vector<string>>data;
    if(!file.is_open()){
        std::cerr<<"Error in opening the file:"<<Details<<std::endl;
    }
    string l;
    while(getline(file,l)){
        data.push_back(getdata(l));
    }
    file.close();
    for(int i=0;i<data.size();++i){
        StudentRecord sr;
        sr.set_studentName(data[i][0]);
        sr.set_rollNumber(data[i][0]);
        students.push_back(sr);
    }
    vector <string> hos={"G1","G2","G3","G4","G5","G6"};
    vector <string> bnh{"CSE","EE","AI","ES"};
    vector <string> sub{"DSA","PRML","SNA","Maths"};
    vector <string> clb{"Music","Robotics","Programming","Dance","Toastmasters"};
    //  array<string,6> hos[]{"G1","G2","G3","G4","G5","G6"};
    //  array<string,4> bnh[]{"CSE","EE","AI","ES"};
    //  array<string,4> sub[]{"DSA","PRML","SNA","Maths"};
    //  array<string,5> clb[]{"Music","Robotics","Programming","Dance","Toastmasters"};
    //  auto it=hos.begin();
     for (int i=0;i<hos.size();++i){
         createEntityArray(hos[i],data.size(),data,4);
     }
     for (int i=0;i<bnh.size();++i){
         createEntityArray(bnh[i],data.size(),data,2);
     }
     for (int i=0;i<sub.size();++i){
         createEntityArray(sub[i],data.size(),data,3);
     }
     for (int i=0;i<clb.size();++i){
         createEntityArray(clb[i],data.size(),data,5);
     }
}

