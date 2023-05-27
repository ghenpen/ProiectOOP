#pragma once
#include "pet.h"
#include "exceptii.h"
#include "enemies.h"
class player{
protected:
    int health;
    int attack;
    int defense;
    pet equippedpet;
public:
    player(int h, int a, int de){
        health = h;
        attack = a;
        defense = de;
    }
    ~player() = default;
    void setHealth(int h){
        health = h;
    }
    void setAttack(int a){
        attack = a;
    }
    void setDefense(int de){
        defense = de;
    }
    void setpet(const pet& p){
        equippedpet = p;
    }
    [[nodiscard]] int getHealth() const{
        return health;
    }
    [[nodiscard]] int getAttack() const{
        return attack;
    }
    [[nodiscard]] int getDefense() const{
        return defense;
    }
    void combat(enemy e){
        int damage = e.getDamage() - this->getDefense();
        if(damage==0) throw DivisionByZero("damage is zero in player");
        int turns1 = this->getHealth() / damage;
        if(this->getAttack()==0) throw DivisionByZero("player attack is zero");
        int turns2 = e.getHealth() / this->getAttack();
        this->health -= std::min(turns1, turns2) * damage;
    }
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const player& p){
        os << "Health: " << p.health << std::endl;
        os << "Attack: " << p.attack << std::endl;
        os << "Defense: " << p.defense << std::endl;
        return os;
    }


};