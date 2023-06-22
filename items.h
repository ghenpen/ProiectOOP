#pragma once
#include <iostream>
#include "player.h"
class item{
protected:
    std::string name;
    int price;
    int curency;
public:
    explicit item(const std::string &n, int p, int c) : name(n){
        price = p;
        curency = c;
    }
    virtual ~item() = default;
    int getPrice() const {
        return price;
    }

    virtual void applyEffect(player& Player)  = 0;

    virtual item* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const item& i){
        os << "Name: " << i.name << std::endl;
        os << "Price: " << i.price << std::endl;
        os << "Curency: " << i.curency << std::endl;
        return os;
    }
};

class DefenceItems : public item
{
protected:
    double proc_buff;
public:
    DefenceItems(const std::string &n, int p, int c, double proc_buff_) : item(n,p,c)
    {
        proc_buff=proc_buff_;
    }
    virtual void applyEffect(player& Player) override
    {
        Player.setDefense(Player.getDefense()+proc_buff/100.0f*Player.getHealth());
    }
    virtual item* clone() const
    {
        return new DefenceItems(*this);
    }
};
class AttackItems : public item
{
protected:
    int buff_value;
public:
    AttackItems(const std::string &n, int p, int c, int buff_value_) : item(n,p,c)
    {
        buff_value = buff_value_;
    }
    virtual void applyEffect(player& Player) override
    {
        Player.setAttack(Player.getAttack()+buff_value);
    }
    virtual item* clone() const
    {
        return new AttackItems(*this);
    }
};
class HealthItems : public item
{
protected:
    double proc_buff;
public:
    HealthItems(const std::string &n, int p, int c, int proc_buff_) : item(n,p,c)
    {
        proc_buff = proc_buff_;
    }
    virtual void applyEffect(player& Player) override
    {
        Player.setHealth(Player.getHealth()+proc_buff/100.0f*Player.getHealth());
    }
    virtual item* clone() const
    {
        return new HealthItems(*this);
    }

};

class SpecialItems : public item
{
protected:
    std::string special_power;
public:
    SpecialItems(const std::string &n, int p, int c, const std::string &special_power_) : item(n,p,c), special_power(special_power_)
    {

    }
    virtual void applyEffect(player& Player) override
    {
        if(special_power == "Trinity")
        {
            Player.setHealth(Player.getHealth()+33.3f/100.0f*Player.getHealth());
            Player.setAttack(Player.getAttack()+33.3f/100.0f*Player.getAttack());
            Player.setDefense(Player.getDefense()+33.3f/100.0f*Player.getHealth());
        }
        else if(special_power == "Ascension")
        {
            int p = rand() % 3 + 1;
            switch (p)
            {
                case 1:
                {
                    Player.setHealth(Player.getHealth() * 2);
                    break;
                }
                case 2:
                {
                    Player.setAttack(Player.getAttack() * 2);
                    break;
                }
                default:
                {
                    Player.setDefense(Player.getDefense() * 2);
                }
            }
        }
    }
    virtual item* clone() const
    {
        return new SpecialItems(*this);
    }

};
