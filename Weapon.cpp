//
// Created by pike- on 03/06/2018.
//
#include "Weapon.h"
#include <string.h>
#include "stdbool.h"
#include <iostream>

//using std::string;
//using std::cerr;
using std::cout;
using std::endl;

namespace mtm {
    Weapon::Weapon(const string& name,Target target,int hit_strength) : name(name),
                                                                      target(target),
                                                                      hitStrength(hit_strength){
    }
    //copy constructor
    Weapon::Weapon(const Weapon& weapon) : name(weapon.name),
                                           target(weapon.target),
                                           hitStrength(weapon.hitStrength) {
    }

    Target Weapon::getTarget() const{
        return this->target;
    }

    int Weapon::getHitStrength() const{
        return this->hitStrength;
    }

    int Weapon::getValue() const{
        //check target to int
        Target target =this->getTarget();
        return (target+1)*this->hitStrength;
    }

    bool Weapon::operator==(const Weapon weapon) const{
        return this->getValue()==weapon.getValue();
    }

    bool Weapon::operator!=(const Weapon weapon) const{
        return this->getValue()!=weapon.getValue();
    }

    bool Weapon::operator<(const Weapon weapon) const{
        return this->getValue()<weapon.getValue();
    }

    bool Weapon::operator>(const Weapon weapon) const{
        return this->getValue()>weapon.getValue();
    }

    Weapon& Weapon::operator=(const Weapon& weapon){
        if(this == &weapon) return *this;
        name = weapon.name;
        target=weapon.target;
        hitStrength=weapon.hitStrength;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os , const Weapon& weapon){
        os << "{weapon name: ";
        os << weapon.name;
        os << ", weapon value:";
        os <<weapon.getValue();
        os << "}";
        return os;
    }
}
