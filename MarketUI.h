#include "iostream"
#include <cstdlib>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include "Products.h"
#include "Containers.h"
using namespace std;

#ifndef SUPERMARKET_MARKETUI_H
#define SUPERMARKET_MARKETUI_H

class MarketSystem{
public:
    vector<Containers*> wSpace;
    int containersN;
    int lastID;
    MarketSystem(string path){
        wSpace = *new std::vector<Containers*>;
        lastID = 11111;
        std::fstream newFile;
        newFile.open(path, std::ios::in);
        if (newFile.is_open()){
            int n = 1;
            std::string curr;
            while(getline(newFile, curr)){
                if (n == 1){
                    containersN = stoi(curr);
                    n++;
                } else {
                    char delim = ' ';
                    std::vector<std::string> div;
                    tokenize(curr, delim, div);
                    int temp = CreateContainer(div[0]);
                    for (auto & j : wSpace) {
                        if (j->containerId == temp) {
                            for (int i = 1; i <= div.size() - 5;) {
                                j->CreateProduct(div[i],div[i+1],div[i+2],div[i+3],div[i+4]);
                                i += 5;
                            }
                        }
                    }
                    lastID++;
                }
            }
            newFile.close();
        }
    }
    int CreateContainer(string type){
        lastID++;
        if (type == "freezer"){
            auto* l = new Freezer(lastID);
            wSpace.push_back(l);
            return l->containerId;
        }

        if (type == "refrigerator"){
            auto* l = new Refrigerator(lastID);
            wSpace.push_back(l);
            return l->containerId;
        }

        if (type == "shelve"){
            auto* l = new Shelve(lastID);
            wSpace.push_back(l);
            return l->containerId;
        }
        return 0;
    }
    void tokenize(std::string const &str, const char delim,std::vector<std::string> &out){
        std::stringstream ss(str);
        std::string s;
        while (std::getline(ss, s, delim)) {
            out.push_back(s);
        }
    }

    void ViewRefrigerator(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            auto* dt2_object = dynamic_cast<Refrigerator*>(wSpace[i]);
            if (dt2_object != nullptr)
            {
                cout << "Refrigerator: " << endl;
                for (auto & j : dt2_object->containerSpace) {
                    cout << j->productName + ", ";
                }
                cout << endl;
            }
        }}
    void ViewShelve(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            auto* dt2_object = dynamic_cast<Shelve*>(wSpace[i]);
            if (dt2_object != nullptr)
            {
                cout << "Shelve: " << endl;
                for (auto & j : dt2_object->containerSpace) {
                    cout << j->productName + ", ";
                }
                cout << endl;
            }
        }}
    void ViewFreezer(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            auto* dt2_object = dynamic_cast<Freezer*>(wSpace[i]);
            if (dt2_object != nullptr)
            {
                cout << "Freezer: " << endl;
                for (auto & j : dt2_object->containerSpace) {
                    cout << j->productName + ", ";
                }
                cout << endl;
            }
        }
    }
};


class MarketUI{
public:
    enum Command { ViewAll = 1, ViewByType, NextDay, Take, Add, SetTemperature,Move};
    MarketUI(){
        MarketSystem dell = *new MarketSystem("conf.txt");
        while(true){
            int n;
            try {
                std::string s;
                std::cout << "Chose the command: ";
                getline(std::cin, s);
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
            if (n == ViewAll) {
                dell.ViewFreezer();
                dell.ViewRefrigerator();
                dell.ViewShelve();
            }
            if (n == ViewByType){
                std::cout << "enter type: ";
                string type;
                getline(std::cin,type);
                if (type == "freezer"){
                    dell.ViewFreezer();
                }
                if (type == "shelve"){
                    dell.ViewShelve();
                }
                if (type == "refrigerator"){
                    dell.ViewRefrigerator();
                }
            }
            if (n == NextDay){
                string date;
                cout << "enter date: ";
                getline(std::cin, date);
                for (int i = 0; i < dell.wSpace.capacity(); ++i) {
                    dell.wSpace[i]->dellByDate(date);
                }
                cout << "\n";
            }
            if (n == Take){
                string containerID;
                string productName;
                cout << "enter container ID: ";
                getline(std::cin, containerID);
                cout << "enter product name: ";
                getline(std::cin, productName);
                for (int i = 0; i < dell.wSpace.size(); ++i) {
                    if (dell.wSpace[i]->containerId == stoi(containerID)){
                        for (int j = 0; j < dell.wSpace[i]->containerSpace.size(); ++j) {
                            if (dell.wSpace[i]->containerSpace[j]->productName == productName){
                                dell.wSpace[i]->containerSpace.erase(dell.wSpace[i]->containerSpace.begin() + j);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            if (n == Add){
                string containerID;
                string productName;
                string productType;
                string dataEx;
                string weight;
                string productProperty;
                cout << "enter container ID: ";
                getline(std::cin, containerID);
                cout << "enter product name: ";
                getline(std::cin, productName);
                cout << "enter product type: ";
                getline(std::cin, productType);
                cout << "enter product date of expire: ";
                getline(std::cin, dataEx);
                cout << "enter product weight: ";
                getline(std::cin, weight);
                cout << "enter product property: ";
                getline(std::cin, productProperty);
                for (int i = 0; i < dell.wSpace.size(); ++i) {
                    if (dell.wSpace[i]->containerId == stoi(containerID)){
                        dell.wSpace[i]->CreateProduct(productType, productName, weight, dataEx, productProperty);
                    }
                }
            }
            if (n == SetTemperature){
                string containerID;
                string temp;
                cout << "enter container ID: ";
                getline(std::cin, containerID);
                cout << "enter product temperature: ";
                getline(std::cin, temp);
                for (int i = 0; i < dell.wSpace.size(); ++i) {
                    if (dell.wSpace[i]->containerId == stoi(containerID)){
                        auto* dt1_object = dynamic_cast<Freezer*>(dell.wSpace[i]);
                        if (dt1_object != nullptr)
                        {
                            cout << "We've found an object of type refrigerator" << endl;
                            if (stoi(temp) < dt1_object->maxTemp && stoi(temp) > dt1_object->minTemp){
                                dt1_object->ChangeTemp(stoi(temp));
                            }
                            break;
                        }
                        auto* dt2_object = dynamic_cast<Refrigerator*>(dell.wSpace[i]);
                        if (dt2_object != nullptr)
                        {
                            cout << "We've found an object of type refrigerator" << endl;
                            dt2_object->ChangeTemp(stoi(temp));
                            break;
                        }
                    }
                }
            }
            if (n == Move){
                string containerID;
                string productName;
                string productType;
                string dataEx;
                string weight;
                string productProperty;
                cout << "enter container ID: ";
                getline(std::cin, containerID);
                cout << "enter product name: ";
                getline(std::cin, productName);
                for (int i = 0; i < dell.wSpace.size(); ++i) {
                    if (dell.wSpace[i]->containerId == stoi(containerID)){
                        for (int j = 0; j < dell.wSpace[i]->containerSpace.size(); ++j) {
                            if (dell.wSpace[i]->containerSpace[j]->productName == productName){
                                dataEx = dell.wSpace[i]->containerSpace[j]->expDate;
                                weight = dell.wSpace[i]->containerSpace[j]->productWeight;
                                productProperty = dell.wSpace[i]->containerSpace[j]->Property();
                                dell.wSpace[i]->containerSpace.erase(dell.wSpace[i]->containerSpace.begin() + j);
                                break;
                            }
                        }
                        break;
                    }
                }
                string newContainerID;
                cout << "enter new container ID: ";
                getline(std::cin, newContainerID);
                for (int i = 0; i < dell.wSpace.size(); ++i) {
                    if (dell.wSpace[i]->containerId == stoi(newContainerID)){
                        dell.wSpace[i]->CreateProduct(productType, productName, weight, dataEx, productProperty);
                    }
                }
            }

        }
    }
};
#endif //SUPERMARKET_MARKETUI_H
