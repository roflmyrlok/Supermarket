#include "iostream"
#include <cstdlib>
#include <utility>
using namespace std;

#ifndef SUPERMARKET_PRODUCTS_H
#define SUPERMARKET_PRODUCTS_H


class Products {
public:
    string productName;
    string productWeight;
    string expDate;
    string type;
    Products(string name, string weight, string date){
        productName = std::move(name);
        productWeight = std::move(weight);
        expDate = std::move(date);
    }

    virtual string Property(){
        return "";
    }
};

class Bread: public Products{
    string colour;
public:
    Bread(string name, string weight, string expDate, string iColour) : Products( std::move(name), std::move(weight), std::move(expDate)){
        type = "bread";
        colour = iColour;
    }
    string Property() override{
        return colour;
    }
};

class Milk: public Products{
    string fatPercentage;
public:
    Milk(string name, string weight, string expDate, string iFat) : Products( std::move(name), std::move(weight), std::move(expDate)){
        type = "milk";
        fatPercentage = iFat;
    }
    string Property() override{
        return fatPercentage;
    }
};


#endif //SUPERMARKET_PRODUCTS_H
