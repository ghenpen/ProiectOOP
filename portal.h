#pragma once
#include <cstdlib>
#include "player.h"
class portal{
protected:
    int number;
    int operatie;
public:
    portal(){
        number= rand() % 100 + 1;
        operatie = rand() %2;
        if(operatie == 0)
            operatie = -1;
    }
    ~portal() = default;
    void take_action(player &p) const{
        if(operatie == 1){
            p.setHealth(p.getHealth() + number);
        }
        else{
            p.setHealth(p.getHealth() - number);
        }
    }
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const portal& p){
        if(p.operatie == 1)
            os << "+";
        else
            os << "-";
        os<<p.number<<std::endl;
        return os;
    }


};