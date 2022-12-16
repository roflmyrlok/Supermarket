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
    vector<Containers> wSpace;
    int containersN;
    int lastID;
    MarketSystem(string path){
        wSpace = *new std::vector<Containers>;
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
                    for (int j = 0; j < wSpace.capacity(); ++j) {
                        if (wSpace[j].containerId == temp) {
                            for (int i = 1; i < div.capacity() - 5;) {
                                wSpace[j].CreateProduct(div[i],div[i+1],div[i+2],div[i+3],div[i+4]);
                                i += 5;
                            }
                            break;
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
            Freezer l = *new Freezer(lastID);
            wSpace.push_back(l);
            return l.containerId;
        }

        if (type == "refrigerator"){
            Refrigerator l = *new Refrigerator(lastID);
            wSpace.push_back(l);
            return l.containerId;
        }

        if (type == "shelve"){
            Shelve l = *new Shelve(lastID);
            wSpace.push_back(l);
            return l.containerId;
        }

    }
    void tokenize(std::string const &str, const char delim,std::vector<std::string> &out){
        std::stringstream ss(str);
        std::string s;
        while (std::getline(ss, s, delim)) {
            out.push_back(s);
        }
    }

    void ViewAll(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            wSpace[i].viewByType("freezer");
        }
        for (int i = 0; i < wSpace.capacity(); ++i) {
            wSpace[i].viewByType("shelve");
        }
        for (int i = 0; i < wSpace.capacity(); ++i) {
            wSpace[i].viewByType("refrigerator");
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
                dell.ViewAll();
            }
            if (n == ViewByType){
                string type;
                cout << "enter type: ";
                getline(std::cin, type);
                for (int i = 0; i < dell.wSpace.capacity(); ++i) {
                    dell.wSpace[i].viewByType(type);
                }
                cout << "\n";
            }
            if (n == NextDay){
                string date;
                cout << "enter date: ";
                getline(std::cin, date);
                for (int i = 0; i < dell.wSpace.capacity(); ++i) {
                    dell.wSpace[i].dellByDate(date);
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
                    if (dell.wSpace[i].containerId == stoi(containerID)){
                        for (int j = 0; j < dell.wSpace[i].containerSpace.size(); ++j) {
                            if (dell.wSpace[i].containerSpace[j].productName == productName){
                                dell.wSpace[i].containerSpace.erase(dell.wSpace[i].containerSpace.begin() + j);
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
                    if (dell.wSpace[i].containerId == stoi(containerID)){
                        dell.wSpace[i].CreateProduct(productType, productName, weight, dataEx, productProperty);
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
                    if (dell.wSpace[i].containerId == stoi(containerID)){
                        if (stoi(temp) < dell.wSpace[i].maxTemp && stoi(temp) > dell.wSpace[i].minTemp){
                            dell.wSpace[i].temp = stoi(temp);
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
                    if (dell.wSpace[i].containerId == stoi(containerID)){
                        for (int j = 0; j < dell.wSpace[i].containerSpace.size(); ++j) {
                            if (dell.wSpace[i].containerSpace[j].productName == productName){
                                productType = dell.wSpace[i].containerSpace[j].type;
                                dataEx = dell.wSpace[i].containerSpace[j].expDate;
                                weight = dell.wSpace[i].containerSpace[j].productWeight;
                                productProperty = dell.wSpace[i].containerSpace[j].Property();
                                dell.wSpace[i].containerSpace.erase(dell.wSpace[i].containerSpace.begin() + j);
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
                    if (dell.wSpace[i].containerId == stoi(newContainerID)){
                        dell.wSpace[i].CreateProduct(productType, productName, weight, dataEx, productProperty);
                    }
                }
            }

        }
    }
};
#endif //SUPERMARKET_MARKETUI_H
