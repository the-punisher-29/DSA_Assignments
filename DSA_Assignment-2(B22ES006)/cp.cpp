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

// Helper function to process a part of the string and add it to the result vector
void process_string(string& str, int& start, vector<string>& result, char delimiter) {
    string temp = "";
    string holder = "";
    for (int i = start; i < str.size(); ++i) {
        if (str[i] == ']') {
            holder += temp;
            start = i + 2;
            temp = "";
            break;
        }
        if (str[i] == ',') {
            holder += temp + delimiter;
            temp = "";
            continue;
        }
        temp += str[i];
    }
    result.push_back(holder.substr(0, holder.size()));
}

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

    // Process parts of the string and add them to the result vector
    process_string(str, start, result, '|');
    result.push_back(str.substr(start, 2));
    start += 4;
    process_string(str, start, result, '|');

    return result;
}


vector<StudentRecord> students;

class LinkedList :
public Entity {
    // Implement LinkedList members here
    public:

// Helper function to create a new node
Node* create_new_node(StudentRecord* student) {
    Node* newNode = new Node();
    newNode->set_element(student);
    return newNode;
}

// Helper function to find the last node in the list
Node* find_last_node() {
    Node* current = get_iterator();
    while (current->get_next() != NULL) {
        current = current->get_next();
    }
    return current;
}

void add_student(StudentRecord student) {
    // Add the student to the list
    students.push_back(student);

    // Create a new node and set its element to the last student added
    Node* newNode = create_new_node(&students.back());

    // Find the last node in the list and link the new node to it
    Node* lastNode = find_last_node();
    lastNode->set_next(newNode);
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

// Helper function to find the start index of the string after trimming leading spaces
int find_start_index(string s) {
    for(int i=0; i<s.size(); i++){
        if(s[i]!=' '){
            return i;
        }
    }
    return 0;
}

// Helper function to find the end index of the string after trimming trailing spaces
int find_end_index(string s) {
    for(int i=s.size()-1; i>=0; i--){
        if(s[i]!=' '){
            return i;
        }
    }
    return s.size()-1;
}

string trim(string s){
    // Find the start and end indices after trimming spaces
    int start = find_start_index(s);
    int end = find_end_index(s);

    // Return the trimmed string
    return s.substr(start, end-start+1);
}

// Helper function to add a string to the result vector
void add_to_result(vector<string>& result, string& y) {
    result.push_back(y);
    y = "";
}

vector<string> split(string s){
    vector<string> result;
    string y = "";
    for(int i=0; i<s.size(); i++){
        if(s[i] == '|'){
            add_to_result(result, y);
            continue;
        }
        y += s[i];
    }
    add_to_result(result, y);
    return result;
}



// Helper function to create a new node
Node* create_new_node(StudentRecord* student) {
    Node* newNode = new Node();
    newNode->set_element(student);
    return newNode;
}

// Helper function to add a node to the list
void add_node_to_list(Node*& current, StudentRecord* student) {
    Node* newNode = create_new_node(student);
    current->set_next(newNode);
    current = current->get_next();
}

void createEntityArray(string str, int size, vector<vector<string>> data, int index) {
    Node *head = new Node();
    head->set_element(&students[0]);
    head->set_next(NULL);
    Node *current = head;

    for (int i = 0; i < size; ++i) {
        if (data[i][index].find(str) != string::npos) {
            add_node_to_list(current, &students[i]);
        }
    }

    head = head->get_next();
    LinkedList linkedList;
    linkedList.set_iterator(head);
    linkedList.set_name(str);
    EntityArray.push_back(linkedList);
}

void read_input_file(string filename){
    ifstream file;
    file.open(filename,ios::in);
    vector <vector <string> > data;
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return ;
    }
    
    string line;
    while (getline(file, line)) {
        data.push_back(getdata(line));
    }
    file.close();
    
    for(int i=0;i<data.size();i++){
        StudentRecord x;
        x.set_studentName(data[i][0]);
        x.set_rollNumber(data[i][1]);
        students.push_back(x);
    }

    set <string> demo;
    for(int i=0;i<data.size();i++){
        demo.insert(trim(data[i][4]));
    }

vector<string> hostels;
vector<string> branches;
vector<string> courses;
vector<string> clubs;

// Extract unique values for hostels, branches, courses, and clubs
for (const auto& row : data) {
    hostels.push_back(row[4]);
    branches.push_back(row[2]);

    vector<string> courseTokens = split(row[3]);
    courses.insert(courses.end(), courseTokens.begin(), courseTokens.end());

    vector<string> clubTokens = split(row[5]);
    clubs.insert(clubs.end(), clubTokens.begin(), clubTokens.end());
}

// Remove duplicates by using set
set<string> uniqueHostels(hostels.begin(), hostels.end());
set<string> uniqueBranches(branches.begin(), branches.end());
set<string> uniqueCourses(courses.begin(), courses.end());
set<string> uniqueClubs(clubs.begin(), clubs.end());

// Clear the original vectors
hostels.clear();
branches.clear();
courses.clear();
clubs.clear();

// Convert back to vectors
hostels.assign(uniqueHostels.begin(), uniqueHostels.end());
branches.assign(uniqueBranches.begin(), uniqueBranches.end());
courses.assign(uniqueCourses.begin(), uniqueCourses.end());
clubs.assign(uniqueClubs.begin(), uniqueClubs.end());

// Create entity arrays
for (const string& hostel : hostels) {
    createEntityArray(hostel, data.size(), data, 4);
}

for (const string& course : courses) {
    createEntityArray(course, data.size(), data, 3);
}

for (const string& club : clubs) {
    createEntityArray(club, data.size(), data, 5);
}

for (const string& branch : branches) {
    createEntityArray(branch, data.size(), data, 2);
}
return;

}

