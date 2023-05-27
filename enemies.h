#pragma once
#include<iostream>
class enemy{
protected:
    int health;
    int damage;
    int numberofunits;
public:
    enemy(int h, int d, int de);
    ~enemy() = default;
    void setHealth(int h);
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] int getDamage() const;
    friend std::ostream& operator<<(std::ostream& os, const enemy& e){
        os << "Enemy stats:" << std::endl;
        os << "Health: " << e.health << std::endl;
        os << "Damage: " << e.damage << std::endl;
        os << "Number of Units: " << e.numberofunits << std::endl;
        return os;
    }
};


class boss: public enemy{
protected:
    int ability;
public:
    boss(int h, int d, int de, int a);
    ~boss() = default;
    void setAbility(int a);
    [[nodiscard]] int getAbility() const;

    [[maybe_unused]] void ability1();
    //overload = operator
    boss& operator=(const boss& b){
        health = b.health;
        damage = b.damage;
        numberofunits = b.numberofunits;
        ability = b.ability;
        return *this;
    }

    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const boss& b){
        os << "Boss stats:" << std::endl;
        os << "Health: " << b.health << std::endl;
        os << "Damage: " << b.damage << std::endl;
        os << "Number of Units: " << b.numberofunits << std::endl;
        os << "Ability: " << b.ability << std::endl;
        return os;
    }
};