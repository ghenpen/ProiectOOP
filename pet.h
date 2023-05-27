#pragma once
#include<iostream>

class pet{
protected:
    std::string name;
    int price{};
    int curency{};
    int damage{};
    bool bought{};
public:
    pet()=default;
    pet(const std::string &n, int p, int c, int d): name(n){
        price = p;
        curency = c;
        damage = d;
        bought=false;
    }
    ~pet() = default;

    /*[[maybe_unused]] static int getDamage(int damage){
        return damage;
    }*/
    [[nodiscard]] int getPrice() const{
        return price;
    }

    /*[[maybe_unused]] void getBought(bool b){
        bought = b;
    }*/
    //copy constructor
    pet(const pet& p):name(p.name), price(p.price), curency(p.curency), damage(p.damage), bought(p.bought){}
    //overload = operator
    pet& operator=(const pet& p){
        name = p.name;
        price = p.price;
        curency = p.curency;
        damage = p.damage;
        bought = p.bought;
        return *this;
    }
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const pet& p){
        os << "Name: " << p.name << std::endl;
        os << "Price: " << p.price << std::endl;
        os << "Curency: " << p.curency << std::endl;
        os << "Damage: " << p.damage << std::endl;
        return os;
    }

};
