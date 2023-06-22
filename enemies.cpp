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
