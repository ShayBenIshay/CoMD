//
// Created by pike- on 03/06/2018.
//
#include "Game.h"
#include <string.h>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

using namespace mtm;

namespace mtm {
    //constructor
    Game::Game(int maxPlayers) : maxPlayers(maxPlayers),
                                 playersArray(0){}
    //Game::~Game()=default;
    GameStatus Game::addPlayer(const string& playerName,const string& weaponName,\
 Target target,int hit_strength){
        //check if user already exists
        if(target==LEVEL) return ILLEGAL_WEAPON;

        for(Player* player : playersArray){
            if( player->isPlayer(playerName) ) return NAME_ALREADY_EXISTS;
        }

        //check if the game is GAME_FULL
        if(gameSize()==maxPlayers) return GAME_FULL;

        Weapon weapon(weaponName,target,hit_strength);
        Warrior* warrior = new Warrior(playerName,weapon,false);
        playersArray.push_back(warrior);
        return SUCCESS;
    }


    std::ostream& operator<<(std::ostream& os,const Game& game){
        //sort players array prior to printing
        vector<Player*> sortedGame(0);
        vector<Player*> copyPlayersArray(game.playersArray);
        while(!copyPlayersArray.empty()){
            //find the minimal player
            Player* minPlayer = *(copyPlayersArray.begin());
            int minIndex=0,counter=0;
            for(Player* player : copyPlayersArray){
                if(*player<*minPlayer){
                    minPlayer=player;
                    minIndex=counter;
                }
                counter++;
            }
            //insert minimal player to new sorted vector
            sortedGame.push_back(minPlayer);
            //erase the minimal player
            copyPlayersArray.erase(copyPlayersArray.begin()+minIndex);
        }
        //delete the empy vector and initial playersArray with sorted vector

        int player_index=0;
        for (Player* player : sortedGame){
            os << "player ";
            os << player_index;
            os << ": ";
            os << *player;
            os << ",";
            os << endl;
            player_index++;
        }

        return os;
    }



GameStatus Game::nextLevel(const string& playerName){
        for(Player* player : playersArray){
            if( player->isPlayer(playerName) ) {
                player->nextLevel();
                return SUCCESS;
            }
        }
        return NAME_DOES_NOT_EXIST;
    }

    GameStatus Game::makeStep(const string& playerName){
        for(Player* player : playersArray){
            if( player->isPlayer(playerName) ) {
                player->makeStep();
                return SUCCESS;
            }
        }
        return NAME_DOES_NOT_EXIST;
    }

    GameStatus Game::addLife(const string& playerName){
        for(Player* player : playersArray){
            if( player->isPlayer(playerName) ) {
                player->addLife();
                return SUCCESS;
            }
        }
        return NAME_DOES_NOT_EXIST;
    }

    GameStatus Game::addStrength(const string& playerName,int strengthToAdd){
        //validate strength and name
        if (strengthToAdd<0)    return INVALID_PARAM;
        for(Player* player : playersArray){
            if( player->isPlayer(playerName) ) {
                player->addStrength(strengthToAdd);
                return SUCCESS;
            }
        }
        return NAME_DOES_NOT_EXIST;
    }

    GameStatus Game::fight(const string& playerName1,const string& playerName2){
        //find two players
        int p1_i=-1,p2_i=-1;
        int vector_index = 0;
        for(Player* player : playersArray){
            if( player->isPlayer(playerName1) ) p1_i=vector_index;
            if( player->isPlayer(playerName2) ) p2_i=vector_index;
            vector_index++;
        }
        //return NAME_DOES_NOT_EXIST if a player is missing
       //if (p1_i==-1 || p2_i==-1)   return NAME_DOES_NOT_EXIST;
        if (p1_i==-1 || p2_i==-1)   throw NameDoesNotExist();
        //PLAYER::fight
        if (playersArray[p1_i]->fight(*playersArray[p2_i])) {
            //in case fight returned 'true', check isAlive, remove and return SUCCESS.
            if (!playersArray[p1_i]->isAlive()){
                //Remove p1 from playersArray, set pointer as nullptr, remove from memory
                removeDeadPlayer(p1_i);
            }
            if (!playersArray[p2_i]->isAlive()){
                //Remove p2 from playersArray
                removeDeadPlayer(p2_i);
            }
            return SUCCESS;
        } else {
            //in case fight returned 'false', return FIGHT_FAILED.
            return FIGHT_FAILED;
        }
    }

    void Game::removeDeadPlayer(int p_i){
        //remove player associated with p1_i index
        playersArray.erase(playersArray.begin()+p_i);//p_i or (p_i-1)
       }

    void Game::removeDeadPlayer(Player* player_to_remove){
        int player_index=0;
        for(Player* player : playersArray){
            if(player==player_to_remove){
               playersArray.erase(playersArray.begin()+player_index);
               return;
            }
            player_index++;
        }
    }

    bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength){
        bool flag=false;
        int dead_player_index=0;
        for( Player* player : playersArray){
            if( player->weaponIsWeak(weaponStrength) ){
                flag = true;
                removeDeadPlayer(player);
            }
            dead_player_index++;
        }
        return flag;
    }
}
