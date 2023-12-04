#include "Food.h"
#include <iostream>

Food::Food(GameMechs* thisGMRef, Player* thisPLRef)
{
    foodBucket = new objPosArrayList();
    // foodPos.setObjPos(-1, -1, 'O'); // Initialize food outside of the game board (not displayed).
}

Food::~Food()
{
    delete foodBucket;
    foodBucket = nullptr;
}

void Food::generateFood(GameMechs* thisGMRef, objPosArrayList *blockOff)
{
    srand(time(NULL));
    
    if (foodBucket->getSize() <= 0){
        // These will hold flags for the purpose of generating new special foods.
        bool specialFood1 = true;
        bool specialFood2 = true;
        while (foodBucket->getSize() < FOOD_COUNT) {
            bool found;
            objPos newFoodPos;
            do {
                found = true;
                newFoodPos.x = 1 + rand() % (thisGMRef->getBoardSizeX() - 2); // Default x-range = [0, 29], foodPos.x = [1, 28]
                newFoodPos.y = 1 + rand() % (thisGMRef->getBoardSizeY() - 2); // Default y-range = [0, 14], foodPos.y = [1, 13]
                if (blockOff != nullptr) {
                    // Make sure the random position for the new food does not overlap with the snake
                    for (int i = 0; i < blockOff->getSize(); i++) {
                        objPos o;
                        blockOff->getElement(o, i);
                        if (o.x == newFoodPos.x && o.y == newFoodPos.y) {
                            found = false;
                            break;
                        }
                    }
                }
                if (foodBucket != nullptr) {
                    // Make sure the random position for the new food does not overlap with existing food
                    // in the bucket.
                    for (int i = 0; i < foodBucket->getSize(); i++) {
                        objPos existedFoodPos;
                        foodBucket->getElement(existedFoodPos, i);
                        if (existedFoodPos.x == newFoodPos.x && existedFoodPos.y == newFoodPos.y) {
                            found = false;
                            break;
                        }
                    }
                }
            } while (!found);
            // We may want to generate all foods of default kind,
            // or up to two of special food kinds. Predictability is boring.
            int generateRandomSpecialFood;
            generateRandomSpecialFood = rand() % 2;
            // Randomize the probability of having special food,
            // provided they are not already generated in this iteration.
            if (specialFood1 && generateRandomSpecialFood) {
               specialFood1 = false;
               newFoodPos.symbol = SPECIAL_FOOD_KIND1;
            } else if (specialFood2 && generateRandomSpecialFood) {
               specialFood2 = false;
               newFoodPos.symbol = SPECIAL_FOOD_KIND2;
            } else {
              newFoodPos.symbol = DEFAULT_FOOD_KIND;
            }
            foodBucket->insertHead(newFoodPos);
        }
    }
}

void Food::getFoodPos(objPos &returnPos, int foodIndex)
{
    if ((foodIndex >= 0) && (foodIndex < foodBucket->getSize())){
        foodBucket->getElement(returnPos, foodIndex);
    }
}

void Food::consumeFood(int foodIndex, int& score, int& lengthGain)
{
    score = 0;
    if ((foodIndex >= 0) && foodIndex < foodBucket->getSize()) {
        objPos food; 
        foodBucket->getElement(food, foodIndex);
        // Score and length gain penalty are subject to the food type being consumed.
        switch (food.symbol)
        {
            case SPECIAL_FOOD_KIND1:
                score = SPECIAL_FOOD_KIND1_SCORE;
                lengthGain = SPECIAL_FOOD_KIND1_LENGTH_PENALTY;
                break;
            case SPECIAL_FOOD_KIND2:
                score = SPECIAL_FOOD_KIND2_SCORE;
                lengthGain = SPECIAL_FOOD_KIND2_LENGTH_PENALTY;
                break; 
            default:
                score = DEFAULT_FOOD_KIND_SCORE;
                lengthGain = DEFAULT_FOOD_KIND_LENGTH_PENALTY;
                break;
        }
        // We need to remove the consumed food from our food bucket.
        // Once all foods in the bucket are consumed, a new batch will be generated.
        for (int i = foodIndex; i < foodBucket->getSize() - 1; i++){
            foodBucket->getElement(food, i+1);
            foodBucket->setElement(food, i);
        }
        foodBucket->removeTail();
    }   
}