#ifndef GAME_H_
#define GAME_H_

#include "Weapon.h"
#include "Player.h"
#include <algorithm>
#include "mtm_exceptions.h"
#include <vector>
#include <iostream>

#include <iostream>
#include <memory>

using namespace mtm;
//using mtm::Player;
using std::vector;

namespace mtm {

    enum GameStatus{
        INVALID_PARAM,
        NAME_ALREADY_EXISTS,
        GAME_FULL,
        NAME_DOES_NOT_EXIST,
        FIGHT_FAILED,
        ILLEGAL_WEAPON,
        SUCCESS
    };

    class Game {
        int maxPlayers;
        vector<Player*> playersArray;
    protected:
        int gameSize(){

            return (int)playersArray.size();

            /*
            int size=0;
            for( Player* player: playersArray ){
                size++;
                player->isAlive();  //need to remove
            }
            return size;
             */
        };
     public:
        explicit Game(int maxPlayer);
        ~Game(){
            for (Player* player : playersArray){
                delete player;
            }

            /*
            while(playersArray.size()>0){
                playersArray.erase(playersArray.begin());
            }
             */
        };
        GameStatus addPlayer(const string& playerName,const string& weaponName,\
        Target target,int hit_strength);
        GameStatus nextLevel(const string& playerName);

        GameStatus makeStep(const string& playerName);

        GameStatus addLife(const string& playerName);
        GameStatus addStrength(const string& playerName,int strengthToAdd);
        bool removeAllPlayersWithWeakWeapon(int weaponStrength);
        GameStatus fight(const string& playerName1,const string& playerName2);
        void removeDeadPlayer(int p1_i);
        void removeDeadPlayer(Player* player_to_remove);
        Game& operator=(const Game& game){
            if(this == &game) return *this;
            maxPlayers = game.maxPlayers;
            playersArray = game.playersArray;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os,const Game& game);
        template <class FCN>
        bool removePlayersIf(FCN& fcn){
            bool flag = false;

            for(int i=0;i<gameSize();i++) {
                for (Player *player : playersArray) {
                   if ((fcn(*player))) {
                        removeDeadPlayer(player);
                        flag = true;
                    }
                }
            }
            return flag;
        }
        void addWizard(string const& playerName,string const& weaponName,Target\
 target,int hitStrength,int range){
            //check if user already exists
            for( Player* player : playersArray){
                if( player->isPlayer(playerName) ) throw NameAlreadyExists();
            }
            //check if the game is GAME_FULL
            if(gameSize()==maxPlayers) throw GameFull();
            Weapon weapon(weaponName,target,hitStrength);
            //check if the correct player* passed to the array
            Wizard* wizard= new Wizard(playerName,weapon,range);
            playersArray.push_back(wizard);
            //delete wizard;
        }
        void addTroll(string const& playerName,string const& weaponName,Target\
 target,int hitStrength,int maxLife){
            for( Player* player : playersArray){
                if( player->isPlayer(playerName) ) throw NameAlreadyExists();
            }
            //check if the game is GAME_FULL
            if(gameSize()==maxPlayers) throw GameFull();
            Weapon weapon(weaponName,target,hitStrength);
            //check if the correct player* passed to the array
            Troll* troll= new Troll(playerName,weapon,maxLife);
            playersArray.push_back(troll);
            //delete troll;
        }
        void addWarrior(string const& playerName,string const& weaponName, Target\
 target,int hitStrength,bool rider){
            for( Player* player : playersArray){
                if( player->isPlayer(playerName) ) throw NameAlreadyExists();
            }
            //check if the game is GAME_FULL
            if(gameSize()==maxPlayers) throw GameFull();
            Weapon weapon(weaponName,target,hitStrength);
            //check if the correct player* passed to the array
            Warrior* warrior = new Warrior(playerName,weapon,rider);
            playersArray.push_back(warrior);
            //delete warrior;
        }
    };
}


#endif  /* GAME_H_ */