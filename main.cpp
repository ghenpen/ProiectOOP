#include <iostream>
#include <ctime>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "items.h"
#include "portal.h"


class OwnedStuff
{
protected:
    std::vector<item*> owned_items;
    static int update_status;
public:
    OwnedStuff()
    {
        owned_items.clear();
        update_status = 0;
    }
    void add_item(std::shared_ptr<item>ptr)
    {
        owned_items.push_back(ptr.get()->clone());
    }
    void update(player &p)
    {
        for(int i = update_status ; i< (int) owned_items.size() ; i++)
            owned_items[i]->applyEffect(p);
        update_status = owned_items.size() - 1;
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
int OwnedStuff::update_status;
class shop{
protected:
    std::vector<std::shared_ptr<item>> items;
    std::vector<pet> pets;
    currency curency;
public:

    shop() {
        std::shared_ptr<item> temp;
        temp = std::shared_ptr<item>(std::make_shared<AttackItems>(AttackItems("Sabie",10,1,15)));
        items.push_back(temp);
        std::shared_ptr<item> a;
        a = std::shared_ptr<item>(std::make_shared<DefenceItems>(DefenceItems("Scut",20,1,10)));
        items.push_back(a);
        std::shared_ptr<item> b;
        b = std::shared_ptr<item>(std::make_shared<HealthItems>(HealthItems("Potiune",10,1,20)));
        items.push_back(b);
    }

    //item(std::string n, int p, int c, std::string e, int v)
    ~shop() = default;

    void buyItem(int i, player &p) {
        if (curency.getMoney() >= items[i].getPrice()) {
            curency.setMoney(curency.getMoney() - items[i].getPrice());
            p.addItem(items[i]);
        }
        os.update(p);
    }

    void buyPet(int i, player &p) {
        if (curency.getDiamonds() >= pets[i].getPrice()) {
            curency.setMoney(curency.getDiamonds() - pets[i].getPrice());
            p.setpet(pets[i]);
        }
    }

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
        os << "Items: " << s.items.size() << std::endl;
        for (int i = 0; i < (int)s.items.size(); i++){
            os << *(s.items[i].get()) << std::endl;
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
    OwnedStuff os;
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
            try{
                std::cout << "Do you want to buy something? (1/0)" << std::endl;
                int choice;
                std::cin >> choice;
               if(choice != 1 && choice != 0) throw InputError("Player input incorrect");
                if (choice == 1) {
                    std::cout << "What do you want to buy? (item/pet)" << std::endl;
                    std::string choicetobuy;
                    std::cin >> choicetobuy;
                    if(choicetobuy != "item" && choicetobuy != "pet") throw InputError("Player input incorrect");
                    if (choicetobuy == "item") {
                     std::cout << "Which item do you want to buy? (0/1/2)" << std::endl;
                        int choiceitem;
                        if(choiceitem != 1 && choiceitem != 0 && choiceitem != 2) throw InputError("Player input incorrect");
                     std::cin >> choiceitem;
                        s.buyItem(choiceitem, p, os);
                        std::cout<<"Leave shop. (1/0)"<<std::endl;
                     int choiceleave;
                     std::cin>>choiceleave;
                        if(choiceleave != 1 && choiceleave != 0) throw InputError("Player input incorrect");
                     if(choiceleave == 1)
                        {
                         leave = true;
                     }
                    } else {
                        std::cout << "Which pet do you want to buy? (0/1/2)" << std::endl;
                     int choicepet;
                        if(choicepet != 1 && choicepet != 0 && choicepet != 2) throw InputError("Player input incorrect");
                     std::cin >> choicepet;
                     s.buyPet(choicepet, p);
                     std::cout<<"Leave shop.  (1/0)"<<std::endl;
                     int choicetoleave;
                        if(choicetoleave != 1 && choicetoleave != 0) throw InputError("Player input incorrect");
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
            catch(Error &e)
            {
                std::cout<<e.what()<<'\n';
            }
        }
    }
    else{
        std::cout<<"You don't have enough money or diamonds."<<std::endl;
        std::cout<<"Start the game."<<std::endl;
    }

        int nrportals = 5;
        while(p.getHealth() > 0) {
            try {
                if (nrportals != 0) {
                    std::cout << "You've reached two portals. Choose one: " << std::endl;
                    portal portal1, portal2;
                    std::cout << portal1 << portal2;
                    int choiceportal = 1;
                    std::cin >> choiceportal;
                    if (choiceportal == 1)
                        portal1.take_action(p);
                    else
                        portal2.take_action(p);
                    std::cout << p;
                    enemy e(10, 2, enemies);
                    enemies = enemies * 2;
                    std::cout << "You've reached an enemy." << std::endl;
                    try {
                        p.combat(e);
                    }
                    catch (Error &e) {
                        std::cout << e.what() << '\n';
                    }
                    if (p.getHealth() > 0) {
                        std::cout << "You've won the fight." << std::endl;
                        s.setMoney(s.getMoney() + earnedMoney);
                        std::cout << "You've earned " << earnedMoney << " money." << std::endl;
                        std::cout << "You have " << s.getMoney() << " money." << std::endl;
                    } else
                        win = false;
                    std::cout << p;
                    nrportals--;

                } else {
                    std::cout << "You've won the game." << std::endl;
                    win = true;
                    std::cout << "You've earned " << earnedMoney << " money." << std::endl;
                    std::cout << "You have " << s.getMoney() << " money." << std::endl;
                    std::cout << "Want to play again? (1/0)" << std::endl;
                    int choicee = 0;
                    if(choicee != 1 && choicee != 0) throw InputError("Player input incorrect");
                    std::cin >> choicee;
                    if (choicee != 1) {
                        game = false;
                        break;
                    } else
                        break;
                }
            }
            catch(Error &e)
            {
                std::cout<<e.what()<<'\n';
            }
        }
        if(!win)
        {

            std::cout<<"You've died."<<std::endl;
            std::cout<<"Want to play again? (1/0)"<<std::endl;
            int choicee=0;
            if(choicee != 1 && choicee != 0) throw InputError("Player input incorrect");
            std::cin>>choicee;
            if(choicee == 1)
                game = true;
            else
                game = false;
        }

    }
    return 0;
}