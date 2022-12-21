#include "iostream"
#include <cstdlib>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include "Products.h"
#include "Containers.h"
using namespace std;

#ifndef SUPERMARKET_MARKET_UI_H
#define SUPERMARKET_MARKET_UI_H

class MarketSystem{
public:
    vector<Containers*> wSpace;
    int lastID;

    static Products* CreateProduct(const string& type, const string& name, const string& weight, const string& date, const string& property){
        if (type == "bread"){
            auto* l = new Bread(name, weight, date, property);
            return l;
        }

        if (type == "milk"){
            auto* l = new Milk(name, weight, date, property);
            return l;
        }
        cout << "no such product \n";
    }

    int CreateContainer(const string& type){
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

    explicit MarketSystem(const string& path){
        wSpace = *new std::vector<Containers*>;
        lastID = 11111;
        std::fstream newFile;
        newFile.open(path, std::ios::in);
        if (newFile.is_open()){
            int n = 1;
            std::string curr;
            while(getline(newFile, curr)){
                if (n == 1){
                    n++;
                } else {
                    char delim = ' ';
                    std::vector<std::string> div;
                    tokenize(curr, delim, div);
                    int temp = CreateContainer(div[0]);
                    for (auto & j : wSpace) {
                        if (j->containerId == temp) {
                            for (int i = 1; i <= div.size() - 5;) {
                                j->containerSpace.push_back(CreateProduct(div[i],div[i+1],div[i+2],div[i+3],div[i+4]));
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

    static void tokenize(std::string const &str, const char delim,std::vector<std::string> &out){
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
                dt2_object->viewProducts();
            }
        }}
    void ViewShelve(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            auto* dt2_object = dynamic_cast<Shelve*>(wSpace[i]);
            if (dt2_object != nullptr)
            {
                dt2_object->viewProducts();
            }
        }}
    void ViewFreezer(){
        for (int i = 0; i < wSpace.capacity(); ++i) {
            auto* dt2_object = dynamic_cast<Freezer*>(wSpace[i]);
            if (dt2_object != nullptr)
            {
                dt2_object->viewProducts();
            }
        }
    }
};
#endif //SUPERMARKET_MARKET_UI_H
