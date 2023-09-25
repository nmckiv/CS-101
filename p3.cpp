#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

void ContactList::copyInfo(const ContactList &src) {
    for (Contact *curr = src.headContactList; curr != nullptr; curr = curr->next) {
        for (Info *currInfo = curr->headInfoList; currInfo != nullptr; currInfo = currInfo->next) {
            addInfo(curr->first, curr->last, currInfo->name, currInfo->value);
        }
    }
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    if (headContactList == nullptr) {
        return false;
    }
    else {
        Contact *curr = headContactList;
        while(curr->first != first || curr->last != last) {
            if (curr->next == nullptr) {
                return false;
            }
            else {
                curr = curr->next;
            }
        }

             os << "Contact name: " << first << " " << last << endl;
             for (Info *currInfo = curr->headInfoList; currInfo != nullptr; currInfo = currInfo->next) {
                os << "      " << currInfo->name << " | " << currInfo->value << endl;
             }
             

             return true;
        
    }

}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {
    Contact *curr = headContactList;
    for (int x = 0; x < count; x++) {
        os << "Contact name: " << curr->first << " " << curr->last << endl;
             for (Info *currInfo = curr->headInfoList; currInfo != nullptr; currInfo = currInfo->next) {
                os << "      " << currInfo->name << " | " << currInfo->value << endl;
             }
        curr = curr->next;
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    Contact *newContact = new Contact(first, last);
    if (headContactList == nullptr) {
        headContactList = newContact;
        count++;
        return true;
    }
    else {
    Contact *curr = headContactList;
    while(curr->first != first || curr->last != last ) {
        if (curr->next == nullptr) {
            curr->next = newContact;
            count++;
            return true;
        }
        else {
            curr = curr->next;
        }
    }
    }
    return false;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {

    if (headContactList == nullptr) {
        return false;
    }
    else {
        Contact *curr = headContactList;
        while (curr->first != first || curr->last != last) {
        if (curr->next == nullptr) {
            return false;
        }
        curr = curr->next;
    }

    if (curr->headInfoList == nullptr) {
        Info *newInfo = new Info(infoName, infoVal);
        curr->headInfoList = newInfo;
        return true;
    }
    else {
        Info *currInfo = curr->headInfoList;
        while (currInfo->next != nullptr) {
            if (currInfo->name == infoName) {
                currInfo->value = infoVal;
                return true;
            }
            currInfo = currInfo->next;
        }
        if (currInfo->name == infoName) {
                currInfo->value = infoVal;
                return true;
            }
        Info *newInfo = new Info(infoName, infoVal);
        currInfo->next = newInfo;
        return true;
    }
    }
    return false;
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrderedFirstName(std::string first, std::string last, int index) {
    int indexToAdd = index;
    Contact *curr = headContactList;
    for (int x = 0; x < index; x++) {
        curr = curr->next;
    }
    while (curr->first < first && curr->last == last) {
        if (curr->next == nullptr) {
            addContact(first, last);
            return true;
        }
        curr = curr->next;
        indexToAdd++;
    }
    if (curr->first == first) {
        return false;
    }
    Contact *prev = headContactList;
    Contact *next = headContactList->next;
    for (int x = 0; x < indexToAdd - 1; x++) {
        prev = prev->next;
        next = next->next;
    }
    if (indexToAdd == 0) {
        headContactList = new Contact(first, last, headContactList);
        count++;
        return true;
    }
    prev->next = new Contact(first, last, next);
    count++;
    return true;
}

bool ContactList::addContactOrdered(std::string first, std::string last) {
    int currIndex = 0;//Index of the contact the new contact must be placed ahead of
    Contact *curr = headContactList;
    if (headContactList == nullptr) {
        addContact(first, last);
        return true;
    }
    while (curr->last < last) {
        if (curr->next == nullptr) {
            addContact(first, last);
            return true;
        }
        curr = curr->next;
        currIndex++;
    }
    if (curr->last == last) {
        return addContactOrderedFirstName(first, last, currIndex);
    }
    Contact *prev = headContactList;
    Contact *next = headContactList->next;
    for (int x = 0; x < currIndex - 1; x++) {
        prev = prev->next;
        next = next->next;
    }
    if (currIndex == 0) {
        headContactList = new Contact(first, last, headContactList);
        count++;
        return true;
    }
    prev->next = new Contact(first, last, next);
    count++;
    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact *curr = headContactList;
    int currIndex = 0;
    while(curr->last != last || curr->first != first) {
        if (curr->next == nullptr) {
            return false;
        }
        curr = curr->next;
    }
    Info *currInfo = curr->headInfoList;
    if (currInfo == nullptr) {
        addInfo(curr->first, curr->last, infoName, infoVal);
        return true;
    }
    while (currInfo->name < infoName) {
        if (currInfo->next == nullptr) {
            addInfo(curr->first, curr->last, infoName, infoVal);
            return true;
        }
        currInfo = currInfo->next;
        currIndex++;
    }
    if (currInfo->name == infoName) {
        currInfo->value = infoVal;
        return true;
    }
    if (currIndex == 0) {
        curr->headInfoList = new Info(infoName, infoVal, curr->headInfoList);
        return true;
    }
    Info *prev = curr->headInfoList;
    for (int x = 0; x < currIndex - 1; x++) {
        prev = prev->next;
    }
    prev->next = new Info(infoName, infoVal, prev->next);
    return true;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    if (headContactList == nullptr) {
        return false;
    }
    int indexToRemove = 0;
    Contact *curr = headContactList;
    //If the first element in the list must be removed
    if (headContactList->first == first && headContactList->last == last) {
        while (curr->headInfoList != nullptr) {
            removeInfo(first, last, curr->headInfoList->name);
        }
    headContactList = curr->next;
    delete curr;
    count--;
    return true;
    }

    while (curr->first != first || curr->last != last) {
        if (curr->next == nullptr) {
            return false;//Contact is not in the list
        }
        curr = curr->next;
        indexToRemove++;
    }
    Contact *prevRemove = headContactList;
    Contact *postRemove = headContactList->next->next;
    for (int x = 0; x < indexToRemove - 1; x++) {
        prevRemove = prevRemove->next;
        postRemove = postRemove->next;
    }
    while (curr->headInfoList != nullptr) {
        removeInfo(first, last, curr->headInfoList->name);
        }
    prevRemove->next = postRemove;
    

    
    delete curr;
    count--;
    return true;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list{}
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {

    Contact *curr = headContactList;
    if (curr == nullptr) {
        return false;
    }

    while (curr->last != last || curr->first != first) {

        if (curr->next == nullptr) {
            return false;
        }
        curr = curr->next;
    }    

    Info *currInfo = curr->headInfoList;
    int indexToRemove = 0;
    //If the info list is empty
    if (currInfo == nullptr) {
        return false;
    }
    //If the first element in the list must be removed
    if (currInfo->name == infoName) {
        curr->headInfoList = currInfo->next;
        delete currInfo;
        return true;
    }
    while (currInfo->name != infoName) {
        if (currInfo->next == nullptr) {
            return false;
        }
        currInfo = currInfo->next;
        indexToRemove++;
    }
    Info *prevRemove = curr->headInfoList;
    Info *postRemove = curr->headInfoList->next->next;
    for (int x = 0; x < indexToRemove - 1; x++) {
        prevRemove = prevRemove->next;
        postRemove = postRemove->next;
    }
    prevRemove->next = postRemove;
    delete currInfo;
    return true;

    // Info *prevCurrInfo = curr->headInfoList;
    // Info *nextCurrInfo;
    // bool iterated = false;
    // while (currInfo->name != infoName) {
    //     if (iterated) {
    //         prevCurrInfo = prevCurrInfo->next;
    //     }
    //     if (currInfo->next == nullptr) {
    //         return false;
    //     }
    //     currInfo = currInfo->next;
    //    iterated = true;
    // }
    // if (!iterated) {
    //     curr->headInfoList = currInfo->next;
    //     delete currInfo;
    //     return true;
    // }
    // nextCurrInfo = currInfo->next;
    // delete currInfo;
    // prevCurrInfo->next = nextCurrInfo;
    // return true;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {

    while (headContactList != nullptr) {
            removeContact(headContactList->first, headContactList->last);
        }
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {
    this->headContactList = nullptr;
    this->count = 0;
    for (Contact *srcCurr = src.headContactList; srcCurr != nullptr; srcCurr = srcCurr->next) {
        addContact(srcCurr->first, srcCurr->last);
    }
    copyInfo(src);
} 

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {
    while (headContactList != nullptr) {
            removeContact(headContactList->first, headContactList->last);
        }
    this->count = 0;
    for (Contact *srcCurr = src.headContactList; srcCurr != nullptr; srcCurr = srcCurr->next) {
        addContact(srcCurr->first, srcCurr->last);
    }
    copyInfo(src);
    }
    return *this;
}
