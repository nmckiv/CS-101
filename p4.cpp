#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
        this->id = id;
        this->first = first;
        this-> last = last;
        this-> email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
    }
};

class HashTable {
    public:
    vector<vector<Person>> buckets;
    HashTable(int size) {
        for (int x = 0; x < size; x++) {
            vector<Person> people;
            people.push_back(*(new Person("X", "X", "X", "X", "X", "X", "X", "X")));
            buckets.push_back(people);
        }
    }
    void printHashTable() {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            for (long unsigned int y = 0; y < buckets.at(x).size(); y++) {
                {
                    cout << buckets.at(x).at(y).id << "\t" << buckets.at(x).at(y).first << "\t" << buckets.at(x).at(y).last << "\t" << buckets.at(x).at(y).email << "\t" << buckets.at(x).at(y).phone << "\t" << buckets.at(x).at(y).city << "\t" << buckets.at(x).at(y).state << "\t" << buckets.at(x).at(y).postalCode << "\t\t||\t\t" << flush;
                }
            }
            cout << endl;
        }
    }
    void store(Person person, string key, string keyType) {
        int size = buckets.size();
        int index = djb2(key) % size;
        int probeCount = 0;
        if (keyType == "Id") {
            while (buckets.at(index).at(0).id != "X" && buckets.at(index).at(0).id != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).id == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "FirstName") {
        while (buckets.at(index).at(0).first != "X" && buckets.at(index).at(0).first != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).first == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "LastName") {
        while (buckets.at(index).at(0).last != "X" && buckets.at(index).at(0).last != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).last == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "Email") {
        while (buckets.at(index).at(0).email != "X" && buckets.at(index).at(0).email != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).email == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "Phone") {
        while (buckets.at(index).at(0).phone != "X" && buckets.at(index).at(0).phone != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).phone == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "City") {
        while (buckets.at(index).at(0).city != "X" && buckets.at(index).at(0).city != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).city == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "State") {
        while (buckets.at(index).at(0).state != "X" && buckets.at(index).at(0).state != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).state == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
        else if (keyType == "PostalCode") {
            while (buckets.at(index).at(0).postalCode != "X" && buckets.at(index).at(0).postalCode != key) {
            probeCount++;
            index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
        }
        if (buckets.at(index).at(0).postalCode == "X") {buckets.at(index).pop_back();}
        buckets.at(index).push_back(person);
        return;
        }
    }
    void print(string keyType) {
        if (keyType == "Id") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).id << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "FirstName") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).first << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "LastName") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).last << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "Email") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).email << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "Phone") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).phone << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "City") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).city << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "State") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).state << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
        else if (keyType == "PostalCode") {
        for (long unsigned int x = 0; x < buckets.size(); x++) {
            if (buckets.at(x).at(0).id != "X") {
                cout << x << ": " << buckets.at(x).at(0).postalCode << " (" << buckets.at(x).size() << ")," << endl;
            }
        }
        return;
        }
    }
    void printAllKey(string key, string keyType) {
        int size = buckets.size();
        int index = djb2(key) % size;
        int probeCount = 0;
        if (keyType == "Id") {
            while (buckets.at(index).at(0).id != key) {
                if (buckets.at(index).at(0).id == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "FirstName") {
            while (buckets.at(index).at(0).first != key) {
                if (buckets.at(index).at(0).first == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "LastName") {
            while (buckets.at(index).at(0).last != key) {
                if (buckets.at(index).at(0).last == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "Email") {
            while (buckets.at(index).at(0).email != key) {
                if (buckets.at(index).at(0).email == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "Phone") {
            while (buckets.at(index).at(0).phone != key) {
                if (buckets.at(index).at(0).phone == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "City") {
            while (buckets.at(index).at(0).city != key) {
                if (buckets.at(index).at(0).city == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "State") {
            while (buckets.at(index).at(0).state != key) {
                if (buckets.at(index).at(0).state == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
        else if (keyType == "PostalCode") {
            while (buckets.at(index).at(0).postalCode != key) {
                if (buckets.at(index).at(0).postalCode == "X") {
                    cout << "No results" << endl;
                    return;
                }
                probeCount++;
                index = ((djb2(key) % size) + probeCount + probeCount * probeCount) % size;
            }
            cout << "Id" << "," << "FirstName" << "," << "LastName" << "," << "Email" << "," << "Phone" << "," << "City" << "," << "State" << "," << "PostalCode" << endl;
            for (long unsigned int x = 0; x < buckets.at(index).size(); x++) {
                cout << buckets.at(index).at(x).id << "," << buckets.at(index).at(x).first << "," << buckets.at(index).at(x).last << "," << buckets.at(index).at(x).email << "," << buckets.at(index).at(x).phone << "," << buckets.at(index).at(x).city << "," << buckets.at(index).at(x).state << "," << buckets.at(index).at(x).postalCode << endl;
            }
            return;
        }
    }
};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    HashTable hashTable = *(new HashTable(tableSize));

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table

    int tokenCount;
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    string line, token;
    getline(file, line); // consume header line

    while (getline(file, line)) {
        tokenCount = 0;
        istringstream iss(line);
        while (getline(iss, token, '\t')) {
            tokenCount++;
            if (tokenCount % 8 == 1) {id = token;}
            else if (tokenCount % 8 == 2){first = token;}
            else if (tokenCount % 8 == 3){last = token;}
            else if (tokenCount % 8 == 4){email = token;}
            else if (tokenCount % 8 == 5){phone = token;}
            else if (tokenCount % 8 == 6){city = token;}
            else if (tokenCount % 8 == 7){state = token;}
            else if (tokenCount % 8 == 8 || tokenCount % 8 == 0){postalCode = token;}
            // cout << token << "\t";
        }
        if (key == "Id") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), id, "Id");
        }
        else if (key == "FirstName") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), first, "FirstName");
        }
        else if (key == "LastName") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), last, "LastName");
        }
        else if (key == "Email") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), email, "Email");
        }
        else if (key == "Phone") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), phone, "Phone");
        }
        else if (key == "City") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), city, "City");
        }
        else if (key == "State") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), state, "State");
        }
        else if (key == "PostalCode") {
            hashTable.store(*(new Person(id, first, last, email, phone, city, state, postalCode)), postalCode, "PostalCode");
        }    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            hashTable.print(key);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
            hashTable.printAllKey(val, key);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
