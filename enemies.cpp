#include "enemies.h"

enemy::enemy(int h, int d, int de){
    health = h;
    damage = d;
    numberofunits = de;
}


void enemy::setHealth(int h){
    health = h;
}

[[nodiscard]] int enemy::getHealth() const{
    return health;
}

[[nodiscard]] int enemy::getDamage() const {
    return damage;
}


boss::boss(int h, int d, int de, int a): enemy(h, d, de){
    ability = a;
}

void boss::setAbility(int a){
    ability = a;
}

[[nodiscard]] int boss::getAbility() const {
    return ability;
}

[[maybe_unused]] void boss::ability1(){
    this->setHealth(this->getHealth() +10 );
}