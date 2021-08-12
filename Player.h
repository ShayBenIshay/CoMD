#ifndef PLAYER_H_
#define PLAYER_H_

#include "Weapon.h"
#include "mtm_exceptions.h"
#include <string>
using std::string;

namespace mtm {

    enum FIGHT_RESULT {
        WON, LOST, DRAW
    };

    class Player {
        string name;
        int level;
        int strength;
    protected:
        int life;
        Weapon weapon;
        int position;
        Player(const string& name, const Weapon& weapon);
        virtual int distance(const Player& player){
            if(position < player.position) return player.position-position;
            return position-player.position;
        }

    public:
        Player(const Player& player);
        //~Player() = default;
        // virtual ~Player() throw () = default;
        //virtual ~Player() = default;
        virtual ~Player() = default;
        void nextLevel();
        bool isPlayer(const string& name) const;
        virtual void makeStep();
        virtual void addLife();
        void addStrength(int strengthToAdd);
        bool isAlive() const;
        bool weaponIsWeak(int weaponMinStrength) const;
        bool operator<(const Player& player) const;
        bool operator>(const Player& player) const;
        bool fight(Player& player);
        virtual bool canAttack(const Player& player){
            return position==player.position;
        }
        bool operator==(const Player& player) const;
        Player& operator=(const Player& player);
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
        void attack(Player& player) const;

        bool operator!=(const Player& player) const{
            return !(*this==player);
        }
        bool operator>=(const Player& player) const{
            return !(*this<player);
        }
        bool operator<=(const Player& player) const{
            return !(*this>player);
        }
    };
}

using namespace mtm;
class Wizard : public Player{
    int range;
public:
    Wizard(string const& name, const Weapon& weapon, int range = 0): Player(name, weapon),range(range) {
        if(range<0) throw InvalidParam();
        if(weapon.getTarget() == LIFE) throw IllegalWeapon();
    }
    //~Wizard() throw() override = default;
    //virtual ~Wizard() throw () override = default;
    virtual ~Wizard() throw () override = default;

    bool canAttack(const Player& player) override{
        return (distance(player)<=range && distance(player)>0);
    }

};
class Troll : public Player{
    int maxLife;
public:
    Troll(string const& name, const Weapon& weapon, int maxLife): Player(name, weapon),maxLife(maxLife) {
        if(maxLife<=0) throw InvalidParam();
    }
    virtual ~Troll() throw() override = default;
//    virtual ~Troll() throw () override = default;
    void makeStep() override {
        Player::makeStep();
        Player::makeStep();
        addLife();
    }
    void addLife() override {
        if(life>=maxLife) return;
        Player::addLife();
    }
};
class Warrior : public Player {
    bool rider;
public:
    Warrior(string const& name, const Weapon& weapon, bool rider = false): Player(name, weapon),rider(rider) {
        if (weapon.getTarget() == LEVEL) throw IllegalWeapon();
    }
    virtual ~Warrior() throw() override = default;
    //virtual ~Warrior() throw() override = default;
    void makeStep() override {
        int steps = 1;
        if (rider) {
            steps = 5;
        }
        for (int i = 0; i < steps; i++) {
            Player::makeStep();
        }
    }
};

#endif  /* PLAYER_H_ */