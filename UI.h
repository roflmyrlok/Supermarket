#include "iostream"
#include <cstdlib>
#include <utility>
#include <vector>
#include "Products.h"
#include "Containers.h"
#include "MarketSystem.h"
#ifndef SUPERMARKET_UI_H
#define SUPERMARKET_UI_H

class UI{
public:
    enum Command { ViewAll = 1, ViewByType, NextDay, Take, Add, SetTemperature,Move};
    MarketSystem *dell;
    UI(){
        dell = new MarketSystem("conf.txt");
    }
    string InputCall(int i){
        string str;
        switch (i) {
            case 1:
                cout << "enter product Property: ";
                break;
            case 2:
                cout << "enter weight: ";
                break;
            case 3:
                cout << "Chose the command: ";
                break;
            case 4:
                cout << "enter container ID: ";
                break;
            case 41:
                cout << "enter new container ID: ";
                break;
            case 5:
                cout << "enter product name: ";
                break;
            case 6:
                cout << "enter product type: ";
                break;
            case 61:
                cout << "enter container type: ";
                break;
            case 7:
                cout << "enter product date of expire: ";
                break;
            case 8:
                cout << "enter temperature: ";
                break;
        }
        fflush(stdin);
        getline(std::cin, str);
        return str;
    }
    void StartWork(){
        while(true){
            int n;
            try {
                std::string s = InputCall(3);
                n = std::stoi(s);
                if (n < 0) throw 1;
            }
            catch (...) {
                std::cerr << "You must answer with a whole number >= 0." << std::endl;
            }
            fflush(stdin);
            if (n > 7) {
                std::cout << "The command is not implemented!" << std::endl;
            }
            system("clear");
            string productType;
            string dataEx;
            string containerID;
            string productName ;
            string weight ;
            string productProperty ;
            string temp;
            string newID;
            switch (n) {
                case ViewAll:
                    dell->ViewFreezer();
                    dell->ViewRefrigerator();
                    dell->ViewShelve();
                    break;
                case ViewByType:
                    productType = InputCall(61);
                    if (productType == "freezer"){
                        dell->ViewFreezer();
                    }
                    if (productType == "shelve"){
                        dell->ViewShelve();
                    }
                    if (productType == "refrigerator"){
                        dell->ViewRefrigerator();
                    }
                    break;
                case NextDay:
                    dataEx = InputCall(7);
                    for (int i = 0; i < dell->wSpace.capacity(); ++i) {
                        dell->wSpace[i]->dellByDate(dataEx);
                    }
                    cout << "\n";
                    break;
                case Take:
                    containerID = InputCall(4);
                    productName = InputCall(5);
                    for (auto & i : dell->wSpace) {
                        if (i->containerId == stoi(containerID)){
                            for (int j = 0; j < i->containerSpace.size(); ++j) {
                                if (i->containerSpace[j]->productName == productName){
                                    i->containerSpace.erase(i->containerSpace.begin() + j);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                case Add:
                    containerID = InputCall(4);
                    productName = InputCall(5);
                    productType = InputCall(6);
                    dataEx = InputCall(7);
                    weight = InputCall(2);
                    productProperty = InputCall(1);
                    for (auto & i : dell->wSpace) {
                        if (i->containerId == stoi(containerID)){
                            i->containerSpace.push_back(dell->CreateProduct(productType, productName, weight, dataEx, productProperty));
                        }
                    }
                    break;
                case SetTemperature:
                    containerID = InputCall(4);
                    temp = InputCall(8);
                    for (auto & i : dell->wSpace) {
                        if (i->containerId == stoi(containerID)){
                            auto* dt1_object = dynamic_cast<Freezer*>(i);
                            if (dt1_object != nullptr)
                            {
                                if (stoi(temp) < dt1_object->maxTemp && stoi(temp) > dt1_object->minTemp){
                                    dt1_object->ChangeTemp(stoi(temp));
                                }
                                break;
                            }
                            auto* dt2_object = dynamic_cast<Refrigerator*>(i);
                            if (dt2_object != nullptr)
                            {
                                dt2_object->ChangeTemp(stoi(temp));
                                break;
                            }
                        }
                    }
                    break;
                case Move:
                    containerID = InputCall(4);
                    productName = InputCall(5);
                    newID = InputCall(41);
                    for (auto & i : dell->wSpace) {
                        if (i->containerId == stoi(containerID)){
                            for (int j = 0; j < i->containerSpace.size(); ++j) {
                                if (i->containerSpace[j]->productName == productName){
                                    auto* dt1_object = dynamic_cast<Bread*>(i->containerSpace[j]);
                                    if (dt1_object != nullptr)
                                    {
                                        productType = "bread";
                                    }
                                    auto* dt2_object = dynamic_cast<Bread*>(i->containerSpace[j]);
                                    if (dt2_object != nullptr)
                                    {
                                        productType = "milk";
                                    }
                                    dataEx = i->containerSpace[j]->expDate;
                                    weight = i->containerSpace[j]->productWeight;
                                    productProperty = i->containerSpace[j]->Property();
                                    i->containerSpace.erase(i->containerSpace.begin() + j);
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    for (auto & i : dell->wSpace) {
                        if (i->containerId == stoi(newID)){
                            i->containerSpace.push_back(dell->CreateProduct(productType, productName, weight, dataEx, productProperty));
                        }
                    }
                    break;
            }
        }
    }
};

#endif //SUPERMARKET_UI_H
