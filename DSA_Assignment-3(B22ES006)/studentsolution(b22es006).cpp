#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;
//const int M = 263;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    PhoneRecord(const string& name, const string& org, const vector<string>& phoneNumbers)
        : name(name), organisation(org), phoneNumbers(phoneNumbers) {}

    string getName() const{
        return name;
    }
    string getOrganisation() const{
        return organisation;
    }
    vector<string> getPhoneNumbers() const{
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    const PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    HashTableRecord(int key, const PhoneRecord* record)
        : key(key),element(record), next(nullptr) {}

    int getKey() const{
        return key;
    }
    const PhoneRecord* getRecord() const{
         return element; 
    }
    HashTableRecord* getNext() const{
        return next;
    }
    void setNext(HashTableRecord* nxt){
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord** hashTable;

public:
    PhoneBook() {
        hashTable = new HashTableRecord*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }
    // Add your own implementation for hashing
    long long computeHash(const string& strng) {
    const long long p = 1000000007;
    const long  x = 263;
    const int m = 263;
    long long hash = 0;
    long long x_pow = 1;

    for (char c : strng) {
        hash = (hash+(c*x_pow)%p)%p;
        x_pow = (x_pow*x)%p;
    }
    return (hash+p)%p;
    }

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record) {
    string fullName = record->getName();
    vector<string> nameWords;
    string word;
    for (char ch : fullName) {
        if (ch == ' ') {
            if (!word.empty()) {
                nameWords.push_back(word);
                word.clear();
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) {
        nameWords.push_back(word);
    }
    for (size_t i = 0; i < nameWords.size(); ++i) {
         int key = computeHash(nameWords[i]);
        HashTableRecord* newRecord = new HashTableRecord(key, record);
        int slot = key % HASH_TABLE_SIZE;
        if (hashTable[slot] == nullptr) {
            hashTable[slot] = newRecord;
        } else {
            HashTableRecord* current = hashTable[slot];
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newRecord);
        }
    }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName) {
    vector<PhoneRecord*> matchingRecords = fetchContacts(searchName);
    if (matchingRecords.empty()) {
        cout<<"Chla"<<endl;
        return false;
    }
    PhoneRecord* selectedRecord = matchingRecords[0];
    bool contactDeleted = false;
    for (int i = 0; i <HASH_TABLE_SIZE; ++i) {
        HashTableRecord* current = hashTable[i];
        HashTableRecord* prev = nullptr;

        while (current != nullptr) {
            if (current->getRecord() == selectedRecord) {
                if (current->getRecord() == selectedRecord) {
                    if (prev != nullptr) {
                        prev->setNext(current->getNext());
                    } else {
                        hashTable[i] = current->getNext();
                    }
                    delete current;
                    contactDeleted = true;
                }
            }
            prev = current;
            current = current->getNext();
        }
    }
    return contactDeleted;
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query) {
    vector<string> queryWords;
    string word;
    for (char ch : *query) {
        if (ch == ' ') {
            if (!word.empty()) {
                queryWords.push_back(word);
                word.clear();
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) {
        queryWords.push_back(word);
    }
    unordered_map<const PhoneRecord*, int> recordCount;
    for (const string& word : queryWords) {
        int key = computeHash(word);
        int slot = key % HASH_TABLE_SIZE;
        HashTableRecord* current = hashTable[slot];
        while (current != nullptr) {
            const PhoneRecord* record = current->getRecord();
            recordCount[record]++;
            current = current->getNext();
        }
    }
    vector<pair<PhoneRecord*, int>> sortedRecords;
    for (const auto& entry : recordCount) {
        PhoneRecord* key = const_cast<PhoneRecord*>(entry.first);
        int value = entry.second;
        pair<PhoneRecord*, int> pairToAdd = make_pair(key, value);
        sortedRecords.push_back(pairToAdd);
    }
    sort(sortedRecords.begin(), sortedRecords.end(), [](const auto& a, const auto& b) {    return a.second > b.second;
    });
    vector<PhoneRecord*> result;
    for (const auto& entry : sortedRecords) {
        result.push_back(entry.first);
    }
    return result;
    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const {
    int count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        HashTableRecord* current = hashTable[i];
        while (current != nullptr) {
            if (current->getRecord() == record) {
                count++;
            }
            current = current->getNext();
        }
    }
    return count;
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file " << filename <<endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string name, organization, phoneNumber;
        vector<string> phoneNumbers;

        if (getline(lineStream, name, ',')) {
            while (getline(lineStream, phoneNumber, ',')) {
                phoneNumbers.push_back(phoneNumber);
            }

            if (getline(lineStream, organization, ',')) {

            } 
            else {
                organization = "Unknown Organization";
            }

            PhoneRecord* record = new PhoneRecord(name, organization, phoneNumbers);
            addContact(record);
        }
    }
    inputFile.close();
}

    // Destructor
    ~PhoneBook(){
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            HashTableRecord* current = hashTable[i];
            while (current != nullptr) {
                HashTableRecord* tmp = current;
                current = current->getNext();
                delete tmp;
            }
        }
        delete[] hashTable;
    }
};
// int main(void) {
//     // Your test cases and program logic can go here.
//     return 0;
//}