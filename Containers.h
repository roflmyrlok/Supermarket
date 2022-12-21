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
    void CreateProduct(string type, string name, string weight, string date, string property){
        if (type == "bread"){
            auto* l = new Bread(name, weight, date, property);
            containerSpace.push_back(l);
            return;
        }

        if (type == "milk"){
            auto* l = new Milk(name, weight, date, property);
            containerSpace.push_back(l);
            return;
        }
        cout << "no such product \n";
    }

    virtual void viewByType(){}
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
    Shelve(int IcontainerId){
        containerId = IcontainerId;
        containerSpace = *new vector<Products*>;
    }
};

class Freezer : public Containers{
public:
    int maxTemp;
    int minTemp;
    int temp;
    Freezer(int IcontainerId){
        containerId = (IcontainerId);
        containerSpace = *new vector<Products*>;
        minTemp = -25;
        maxTemp = -5;
        temp = -13;
    }
    bool ChangeTemp(int Itemp) {
        if (temp <= maxTemp && temp >= minTemp) {
            temp = ::abs(Itemp);
            return true;
        }
        cout << "wrong temp";
        return false;
    }
};

class Refrigerator : public Containers{
public:
    Refrigerator(int IcontainerId){
        containerId = (IcontainerId);
        containerSpace = *new vector<Products*>;
        minTemp = 0;
        maxTemp = 15;
        temp = 13;
    }
    bool ChangeTemp(int Itemp) {
        if (temp <= maxTemp && temp >= minTemp) {
            temp = Itemp;
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
