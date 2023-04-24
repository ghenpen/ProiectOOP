#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>
#include <string>
//#include <utility>
#include <utility>
#include <vector>
//#include <algorithm>
class item{
protected:
    std::string name;
    int price;
    int curency;
    std::string efect;
    int value;
    /*bool bought;*/
public:
    item(const std::string &n, int p, int c, const std::string &e, int v) : name(n), efect(e){
        price = p;
        curency = c;
        value = v;
        //bought=false;
    }
    ~item() = default;
    /*[[maybe_unused]] void getBought(bool b){
        bought = b;
   }*/

    /*[[maybe_unused]] void setBought(bool b){
        bought = b;
    }*/
    [[nodiscard]] int getPrice() const{
        return price;
    }
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const item& i){
        os << "Name: " << i.name << std::endl;
        os << "Price: " << i.price << std::endl;
        os << "Curency: " << i.curency << std::endl;
        os << "Efect: " << i.efect << std::endl;
        os << "Value: " << i.value << std::endl;
        return os;
    }
    std::string getEfect(){
        return efect;
    }
    [[nodiscard]] int getValue() const{
        return value;
    }

};
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
class enemy{
protected:
    int health;
    int damage;
    int numberofunits;
public:
    enemy(int h, int d, int de){
        health = h;
        damage = d;
        numberofunits = de;
    }
    ~enemy() = default;
    void setHealth(int h){
        health = h;
    }

    /*[[maybe_unused]] void setDamage(int d){
        damage = d;
    }*/

    /*[[maybe_unused]] void setNumberOfUnits(int n){
        numberofunits = n;
    }*/
    [[nodiscard]] int getHealth() const{
        return health;
    }
    [[nodiscard]] int getDamage() const{
        return damage;
    }

   /* [[maybe_unused]] [[nodiscard]] int getNumberOfUnits() const{
        return numberofunits;
    }*/

    /*[[maybe_unused]] void defend(int damage){
        this->setHealth(this->getHealth() - damage );
    }*/
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const enemy& e){
        os << "Enemy stats:" << std::endl;
        os << "Health: " << e.health << std::endl;
        os << "Damage: " << e.damage << std::endl;
        os << "Number of Units: " << e.numberofunits << std::endl;
        return os;
    }

};

class player{
    protected:
        int health;
        int attack;
        int defense;
        std::vector<item> items;
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
        void addItem(const item& i){
            items.push_back(i);
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
            int turns1 = this->getHealth() / damage;
            int turns2 = e.getHealth() / this->getAttack();
            this->health -= std::min(turns1, turns2) * damage;
        }
        void applyItems(){
            for(int i=0; i<(int)items.size(); i++){
                if(items[i].getEfect() == "health"){
                    this->setHealth(this->getHealth() + items[i].getValue());
                }
                if(items[i].getEfect() == "attack"){
                    this->setAttack(this->getAttack() + items[i].getValue());
                }
                if(items[i].getEfect() == "defense"){
                    this->setDefense(this->getDefense() + items[i].getValue());
                }
            }
        }
        //overload << operator
        friend std::ostream& operator<<(std::ostream& os, const player& p){
            os << "Health: " << p.health << std::endl;
            os << "Attack: " << p.attack << std::endl;
            os << "Defense: " << p.defense << std::endl;
            return os;
        }

};
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

class currency{
protected:
    int money;
    int diamonds;
public:
    currency(){
        money = 0;
        diamonds = 0;
    }
    ~currency() = default;
    void setMoney(int m){
        money = m;
    }
    /*void setDiamonds(int d){
        diamonds = d;
    }*/
    [[nodiscard]] int getMoney() const{
        return money;
    }
    [[nodiscard]] int getDiamonds() const{
        return diamonds;
    }
    //overload << operator
    friend std::ostream& operator<<(std::ostream& os, const currency& c){
        os << "Money: " << c.money << std::endl;
        os << "Diamonds: " << c.diamonds << std::endl;
        return os;
    }
};

class shop {
protected:
    std::vector<item> items;
    std::vector<pet> pets;
    currency curency;
public:
    shop() {
        items.emplace_back("itemviata", 10, 1, "health", 10);
        items.emplace_back("itematac", 20, 1, "attack", 20);
        items.emplace_back("itemdefense", 30, 1, "defense", 30);
        pets.emplace_back("dog", 10, 0, 10);
        pets.emplace_back("cat", 10, 0, 10);
        pets.emplace_back("bird", 10, 0, 10);
    }

    //item(std::string n, int p, int c, std::string e, int v)
    ~shop() = default;

    void buyItem(int i, player &p) {
        if (curency.getMoney() >= items[i].getPrice()) {
            curency.setMoney(curency.getMoney() - items[i].getPrice());
            p.addItem(items[i]);
        }
    }

    void buyPet(int i, player &p) {
        if (curency.getDiamonds() >= pets[i].getPrice()) {
            curency.setMoney(curency.getDiamonds() - pets[i].getPrice());
            p.setpet(pets[i]);
        }
    }

    /*[[maybe_unused]] void sellItem(int i, player &p) {
        curency.setMoney(curency.getMoney() + items[i].getPrice());
        p.addItem(items[i]);
    }*/

    /*[[maybe_unused]] void sellPet(int i, player &p) {
        curency.setMoney(curency.getMoney() + pets[i].getPrice());
        p.setpet(pets[i]);
    }*/

    void setMoney(int m) {
        curency.setMoney(m);
    }

    /*[[maybe_unused]] void setDiamonds(int d) {
        curency.setDiamonds(d);
    }*/

    /*[[maybe_unused]] void addtocurentcy(int m, int d) {
        curency.setMoney(curency.getMoney() + m);
        curency.setDiamonds(curency.getDiamonds() + d);
    }*/

    int getMoney() {
        return curency.getMoney();
    }

    int getDiamonds() {
        return curency.getDiamonds();
    }

    //overload << operator
    friend std::ostream &operator<<(std::ostream &os, const shop &s) {
        os << "Items: " << std::endl;
        for (int i = 0; i < (int)s.items.size(); i++) {
            os << s.items[i] << std::endl;
        }
        os << "Pets: " << std::endl;
        for (int i = 0; i < (int)s.pets.size(); i++) {
            os << s.pets[i] << std::endl;
        }
        return os;
    }
};
int main() {
    srand(time(NULL));
    player p(50, 5,0);
    int enemies = 1;
    int earnedMoney = 5;
    bool game = true;
    bool win = false;
    shop s;
    while(game)
    {
    //shop
    std::cout<<"Welcome to the shop."<<std::endl;
    std::cout<<s;
    std::cout<<"You have "<<s.getMoney()<<" money and "<<s.getDiamonds()<<" diamonds."<<std::endl;
    if(s.getMoney() > 0 || s.getDiamonds() > 0)
    {
        bool leave = false;
        while(!leave) {
            std::cout << "Do you want to buy something? (1/0)" << std::endl;
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "What do you want to buy? (item/pet)" << std::endl;
                std::string choicetobuy;
                std::cin >> choicetobuy;
                if (choicetobuy == "item") {
                    std::cout << "Which item do you want to buy? (0/1/2)" << std::endl;
                    int choiceitem;
                    std::cin >> choiceitem;
                    s.buyItem(choiceitem, p);
                    p.applyItems();
                    std::cout<<"Leave shop. (1/0)"<<std::endl;
                    int choiceleave;
                    std::cin>>choiceleave;
                    if(choiceleave == 1)
                    {
                        leave = true;
                    }
                } else {
                    std::cout << "Which pet do you want to buy? (0/1/2)" << std::endl;
                    int choicepet;
                    std::cin >> choicepet;
                    s.buyPet(choicepet, p);
                    std::cout<<"Leave shop.  (1/0)"<<std::endl;
                    int choicetoleave;
                    std::cin>>choicetoleave;
                    if(choicetoleave == 1)
                    {
                        leave = true;
                    }
                }
            } else {
                std::cout << "Start the game." << std::endl;
                leave = true;
            }
        }
    }
    else{
        std::cout<<"You don't have enough money or diamonds."<<std::endl;
        std::cout<<"Start the game."<<std::endl;
    }

        int nrportals = 5;
        while(p.getHealth() > 0)
        {
            if(nrportals != 0)
            {
                std::cout<<"You've reached two portals. Choose one: "<<std::endl;
                portal portal1,portal2;
                std::cout<< portal1 << portal2;
                int choiceportal;
                std::cin>>choiceportal;
                if(choiceportal == 1)
                    portal1.take_action(p);
                else
                    portal2.take_action(p);
                std::cout<<p;
                enemy e(10, 2, enemies);
                enemies = enemies *2;
                std::cout<<"You've reached an enemy."<<std::endl;
                p.combat(e);
                if (p.getHealth() > 0) {
                    std::cout << "You've won the fight." << std::endl;
                    s.setMoney(s.getMoney() + earnedMoney);
                    std::cout << "You've earned " << earnedMoney << " money." << std::endl;
                    std:: cout << "You have " << s.getMoney() << " money." << std::endl;
                }
                else
                    win = false;
                std::cout<< p;
                nrportals--;

            }
            else{
                std::cout<<"You've won the game."<<std::endl;
                win = true;
                std::cout << "You've earned " << earnedMoney << " money." << std::endl;
                std:: cout << "You have " << s.getMoney() << " money." << std::endl;
                std::cout<<"Want to play again? (1/0)"<<std::endl;
                int choicee;
                std::cin>>choicee;
                if(choicee != 1) {
                    game = false;
                    break;
                }
                else
                    break;
            }
        }
        if(!win)
        {

            std::cout<<"You've died."<<std::endl;
            std::cout<<"Want to play again? (1/0)"<<std::endl;
            int choicee;
            std::cin>>choicee;
            if(choicee == 1)
                game = true;
            else
                game = false;
        }

    }
    return 0;
}