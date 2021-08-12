//
// Created by pike- on 03/06/2018.
//
#include "Player.h"
#include <string.h>
#include "stdbool.h"
#include <iostream>

//using std::cerr;
//using std::cin;
using std::cout;
using std::endl;
using namespace mtm;


namespace mtm {
    //constructor
    Player::Player(const string& name, const Weapon& weapon) :
                                                            name(name),level(1),strength(1),
                                                            life(1), weapon(weapon), position(0)
                                                             {}
    //copy constructor
    Player::Player(const Player& player) : name(player.name),
                                           level(player.level),
                                           strength(player.strength),
                                           life(player.life),
                                           weapon(player.weapon),
                                           position(player.position) {
      //  strcpy(this->name,player.name);
    }

    void Player::nextLevel(){
        level++;
    }

    bool Player::isPlayer(const string& nameCheck) const{
        return name==nameCheck;
    }

    void Player::makeStep(){
        position++;
    }

    void Player::addLife(){
        life++;
    }

    void Player::addStrength(int strengthToAdd){
        strength+=strengthToAdd;
    }

    bool Player::isAlive() const{
        return (life>0 && strength>0 && level>0);
    }

    bool Player::weaponIsWeak(int weaponMinStrength) const{
        return weapon.getValue() < weaponMinStrength;
    }

    bool Player::operator<(const Player& player) const{
        return name<player.name;
    }

    bool Player::operator>(const Player& player) const{
        return name>player.name;
    }

    bool Player::operator==(const Player& player) const {
        return (this->name == player.name && this->level == player.level \
 && this->life == player.life && this->strength == player.strength\
 && this->weapon == player.weapon && this->position == player.position);
    }

    Player& Player::operator=(const Player& player){
        if(this == &player) return *this;
        name = player.name;
        level = player.level;
        life = player.life;
        strength = player.strength;
        weapon = player.weapon;
        position = player.position;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Player& player){
        os << "{player name: ";
        os << player.name;
        os << ", weapon: ";
        os << player.weapon;
        os << "}";
        return os;
    }
    bool Player::fight(Player& player){
        if (player.weapon==weapon) return false;
        //variables to represent the players ability to attack
        bool player1 = canAttack(player);
        bool player2 = player.canAttack(*this);
        //in case both players cant attack return false
        if(!player1 && !player2) return false;
        //in case both players can attack; compare the weapons to determine who attacks
        if(player1 && player2){
            player.weapon>weapon ? player.attack(*this) : attack(player);
        }
        //in case player 1 can attack and player 2 can't; attack player 2
        if(!player1 && player2){
            //player.attack(*this); //this is according to our rules
            //below is according to hnoon rules
            if (player.weapon>weapon){
                player.attack(*this);
            } else return false;
        }
        //in case player 2 can attack and player 1 can't; attack player 1
        if(player1 && !player2){
            //attack(player);  /this is according to our rules
            //below is according to hnoon rules
            if (player.weapon<weapon){
                attack(player);
            } else return false;
        }
        return true;
    }


    void Player::attack(Player& player) const{
        //fork 3 options for weapon targets, for each, check if Negative value.
        if(weapon.getTarget() == LEVEL){
            player.level-=this->weapon.getHitStrength();
            if(player.level < 0) player.level=0;
        }
        if(weapon.getTarget() == STRENGTH){
            player.strength-=this->weapon.getHitStrength();
            if(player.strength < 0) player.strength=0;
        }
        if(weapon.getTarget() == LIFE) {
            player.life-=this->weapon.getHitStrength();
            if(player.life < 0) player.life=0;
        }

    }


    //end of namespace mtm
}