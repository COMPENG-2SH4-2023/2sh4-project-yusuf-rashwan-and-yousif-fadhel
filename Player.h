#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Food;

class Player
{
    public:
        enum Dir {STOP, UP, LEFT, DOWN, RIGHT};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();
        int getDir();

        bool isFoodConsumed(int &lengthGain);
        void increasePlayerLength(int weightGain);

    private:
        objPosArrayList* playerPosList;      
        enum Dir myDir;
        
        void advanceObjectPos(objPos &obj);
        bool IsSnakeSucidal(objPos& nextHeadPos);

        // To refer to GameMechs and Food
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
};

#endif