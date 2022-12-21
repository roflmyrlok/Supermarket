#include "iostream"
#include <cstdlib>
#include <utility>
#include <vector>
#include "Products.h"
using namespace std;

#ifndef SUPERMARKET_CONTAINERS_H
#define SUPERMARKET_CONTAINERS_H

class Containers {
public:
    int containerId;
    vector<Products*> containerSpace;
    virtual void viewProducts(){
        cout << containerId;
        cout << ": " << endl;
        for (auto & j : containerSpace) {
            cout << j->productName + " ";
        }
        cout << endl;
    }
    void dellByDate(const string& date){
        int i = 0;
        int j = containerSpace.size();
        int dell = 0;
        while(i < j) {
            string lDate = containerSpace[i - dell]->expDate;
            int day = stoi(lDate.substr(0,2));
            int cDay = stoi(date.substr(0,2));
            int month = stoi(lDate.substr(3,2));
            int cMonth = stoi(date.substr(3,2));
            if(cMonth > month){
                containerSpace.erase(containerSpace.begin() + i - dell);
                dell ++;
            } else if (cMonth == month && cDay >= day){
                containerSpace.erase(containerSpace.begin() + i - dell);
                dell++;
            }
            i++;
        }
    }
};

class Shelve : public Containers{
public:
    explicit Shelve(int IContainerId){
        containerId = IContainerId;
        containerSpace = *new vector<Products*>;
    }
};

class Freezer : public Containers{
public:
    int maxTemp;
    int minTemp;
    int temp;
    explicit Freezer(int IContainerId){
        containerId = (IContainerId);
        containerSpace = *new vector<Products*>;
        minTemp = -25;
        maxTemp = -5;
        temp = -13;
    }
    bool ChangeTemp(int ITemp) {
        if (temp <= maxTemp && temp >= minTemp) {
            temp = ::abs(ITemp);
            return true;
        }
        cout << "wrong temp";
        return false;
    }
};

class Refrigerator : public Containers{
public:
    explicit Refrigerator(int IContainerId){
        containerId = (IContainerId);
        containerSpace = *new vector<Products*>;
        minTemp = 0;
        maxTemp = 15;
        temp = 13;
    }
    bool ChangeTemp(int ITemp) {
        if (temp <= maxTemp && temp >= minTemp) {
            temp = ITemp;
            return true;
        }
        cout << "wrong temp";
        return false;
    }

    int maxTemp;
    int minTemp;
    int temp;
};

#endif //SUPERMARKET_CONTAINERS_H
