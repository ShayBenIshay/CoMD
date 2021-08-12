#ifndef WEAPON_H_
#define WEAPON_H_

//#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace mtm {

    enum Target {
        LEVEL, STRENGTH, LIFE
    };

    class Weapon {
        string name;
        Target target;
        int hitStrength;

    public:
        Weapon(const string& name, Target target,int hit_strength);
        Weapon(const Weapon& weapon);
        ~Weapon() = default;
        Target getTarget() const;
        int getHitStrength() const;
        int getValue() const;
        bool operator==(Weapon weapon) const;
        bool operator!=(Weapon weapon) const;
        bool operator<(Weapon weapon) const;
        bool operator>(Weapon weapon) const;
        Weapon& operator=(const Weapon& weapon);
        friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);

        bool operator>=(const Weapon& weapon) const{
            return !(*this<weapon);
        }
        bool operator<=(const Weapon& weapon) const{
            return !(*this>weapon);
        }
    };
}

#endif  /*WEAPON_H_ */