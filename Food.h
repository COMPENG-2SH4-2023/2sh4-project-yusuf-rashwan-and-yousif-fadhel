#ifndef FOOD_H
#define FOOD_H

#include <cstdlib> // rand() and srand()
#include <ctime>

#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"

#define FOOD_COUNT                          5
#define DEFAULT_FOOD_KIND                   'o'
#define SPECIAL_FOOD_KIND1                  'x'
#define SPECIAL_FOOD_KIND2                  '$'

#define DEFAULT_FOOD_KIND_SCORE             1
#define SPECIAL_FOOD_KIND1_SCORE            10
#define SPECIAL_FOOD_KIND2_SCORE            5

#define DEFAULT_FOOD_KIND_LENGTH_PENALTY    1
#define SPECIAL_FOOD_KIND1_LENGTH_PENALTY   0
#define SPECIAL_FOOD_KIND2_LENGTH_PENALTY   10


class Player;

class Food
{
    private:
        objPosArrayList* foodBucket;

    public:
        Food(GameMechs* thisGMRef, Player* thisPLRef);
        ~Food();
        
        void generateFood(GameMechs* thisGMRef, objPosArrayList *blockOff);
        void getFoodPos(objPos &returnPos, int foodIndex);
        void consumeFood(int foodIndex, int& score, int& lengthGain);
        int foodCount() { 
             if (foodBucket == nullptr) {
                return 0;
             }
             return foodBucket->getSize();
        };
};

#endif