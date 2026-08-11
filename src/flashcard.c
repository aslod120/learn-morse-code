#include "bitbyte.h"

#define DECK_LENGTH 36
#define BASE_BOX2_REPEATING 3
#define BASE_BOX3_REPEATING 4
#define BASE_BOX4_REPEATING 10

// this will hold the flashcard data that the user will be tested on
// this will be based off the Leitner system https://en.wikipedia.org/wiki/Leitner_system

int box1[DECK_LENGTH]; // where all the cards start out
int box1Length;

int box2[DECK_LENGTH]; // cards we get wrong that we need to review more
int box2Length;

int box3[DECK_LENGTH]; // cards we are getting right but still need to be repeated
int box3Length;

int box4[DECK_LENGTH]; // cards we don't need to review as much
int box4Length;

int currentBox;
int box2RepeatingFactor;
int box3RepeatingFactor;
int box4RepeatingFactor;

// when a card is correctly guessed, it is moved to the next box in the line.
// if a card is incorrectly guessed, it is moved to box 1 for review.
// for every X cards in box 1, present a card from box 2 for review.
// for every X cards from box 2, present a card from box 3 for review

void flashcard_init()
{
    box1Length = 26; // all cards are in box 1
    box2Length = 0;
    box3Length = 0;
    box4Length = 0;
    currentBox = 1;
    box2RepeatingFactor = 0;
    box3RepeatingFactor = 0;
    box4RepeatingFactor = 0;

    // initialize the reference indexes in box 1
    for(int i = 0; i < box1Length; i++)
    {
        box1[i] = i;
    }

}

void flashcard_debug(float size)
{
    DrawText("1: ", 0, 0, size, GREEN);
    DrawText("2: ", 0, 20, size, GREEN);
    DrawText("3: ", 0, 40, size, GREEN);
    DrawText("4: ", 0, 60, size, GREEN);
    for(int i = 0; i < box1Length; i++)
    {
        DrawText(TextFormat("%c ", box1[i] + 'A'), (i + 1) * 20, 0, size, GREEN);
    }
    for(int i = 0; i < box2Length; i++)
    {
        DrawText(TextFormat("%c ", box2[i] + 'A'), (i + 1) * 20, 20, size, GREEN);
    }
    for(int i = 0; i < box3Length; i++)
    {
        DrawText(TextFormat("%c ", box3[i] + 'A'), (i + 1) * 20, 40, size, GREEN);
    }
    for(int i = 0; i < box4Length; i++)
    {
        DrawText(TextFormat("%c ", box4[i] + 'A'), (i + 1) * 20, 60, size, GREEN);
    }
}

void flashcard_shuffle(int deck[], int length)
{
    int temp = 0;
    int randNum = 0;
    for(int i = 0; i < length - 1; i++)
    {
        randNum = GetRandomValue(i + 1, length - 1);
        temp = deck[i];
        deck[i] = deck[randNum];
        deck[randNum] = temp;
    }
}

void flashcard_shuffleDeck(int boxNumber)
{
    if(boxNumber == 1)
    {
        flashcard_shuffle(box1, box1Length);
    }
    if(boxNumber == 2)
    {
        flashcard_shuffle(box2, box2Length);
    }
    if(boxNumber == 3)
    {
        flashcard_shuffle(box3, box3Length);
    }
    if(boxNumber == 4)
    {
        flashcard_shuffle(box4, box4Length);
    }
}

int flashcard_dequeue(int boxNum)
{
    // returns the letter from the front of the queue
    int returnNum = 0;
    if(boxNum == 1 && box1Length > 0)
    {
        box1Length--;
        returnNum = box1[box1Length];
    }
    else if(boxNum == 2 && box2Length > 0)
    {
        box2Length--;
        returnNum = box2[box2Length];
    }
    else if(boxNum == 3 && box3Length > 0)
    {
        box3Length--;
        returnNum = box3[box3Length];
    }
    else if(boxNum == 4 && box4Length > 0)
    {
        box4Length--;
        returnNum = box4[box4Length];
    }

    if(returnNum < 26) // it's a letter
    {
        returnNum += 'A';
    }
    else // it's a number
    {
        if(returnNum == 34)
        {
            returnNum = '0';
        }
        else
        {
            returnNum += '1';
        }
    }

    return returnNum;
}

// move a card to the back of the array to pull later
int flashcard_queue(int boxNum, int card)
{
    if(isalpha(card)) // it's a letter
    {
        card = toupper(card);
        card -= 'A';
    }
    else // it's a number
    {
        if(card == '0')
        {
            card = 34;
        }
        else
        {
            card -= '1';
        }
    }

    if(boxNum == 1 && box1Length < DECK_LENGTH)
    {
        for(int i = box1Length; i > 0; i--)
        {
            box1[i] = box1[i - 1];
        }
        box1[0] = card;
        box1Length++;
        return 1;
    }

    if(boxNum == 2 && box2Length < DECK_LENGTH)
    {
        for(int i = box2Length; i > 0; i--)
        {
            box2[i] = box2[i - 1];
        }
        box2[0] = card;
        box2Length++;
        return 1;
    }

    if(boxNum == 3 && box3Length < DECK_LENGTH)
    {
        for(int i = box3Length; i > 0; i--)
        {
            box3[i] = box3[i - 1];
        }
        box3[0] = card;
        box3Length++;
        return 1;
    }

    if(boxNum == 4 && box4Length < DECK_LENGTH)
    {
        for(int i = box4Length; i > 0; i--)
        {
            box4[i] = box4[i - 1];
        }
        box4[0] = card;
        box4Length++;
        return 1;
    }

    // box number out of range or box full
    return -1;
}

int flashcard_boxLength(int boxNum)
{
    if(boxNum == 1)
    {
        return box1Length;
    }
    if(boxNum == 2)
    {
        return box2Length;
    }
    if(boxNum == 3)
    {
        return box3Length;
    }
    if(boxNum == 4)
    {
        return box4Length;
    }
    // not a valid boxnum
    return 0;
}

// returns true is correct and false if incorrect
bool flashcard_processAnswer(char userInput, char answer)
{
    if(isalpha(userInput))
    {
        userInput = toupper(userInput);
        //printf("%c : %f\n", answer, GetTime());
        // determine if the user pressed the same key as the one in the queue
        if(userInput == answer)
        {
            // player got it right, put it in the next box
            if(currentBox == 1 || currentBox == 2)
            {
                // put it in box 3
                flashcard_queue(3, answer);
            }
            else if(currentBox == 3)
            {
                // put it in box 4
                flashcard_queue(4, answer);
            }
            else
            {
                // leave it in the last box
                flashcard_queue(4, answer);
            }
            return true;
        }
        else
        {
            // got it wrong, put it in box 2 for review
            flashcard_queue(2, answer);
        }
    }
    // returns false if incorrect answer, or the answer isn't a letter/number
    return false;
}

char flashcard_getCard()
{
    currentBox = 1;
    box2RepeatingFactor++;
    // box 2 is the review box if the user gets the flashcard wrong
    if(box2RepeatingFactor % BASE_BOX2_REPEATING == 0)
    {
        currentBox = 2;
        box3RepeatingFactor++;
        if(box3RepeatingFactor % BASE_BOX3_REPEATING == 0)
        {
            currentBox = 3;
            box4RepeatingFactor++;
            if(box4RepeatingFactor % BASE_BOX4_REPEATING == 0)
            {
                currentBox = 4;
            }
        }
    }
    // fallback to make sure we are choosing a box with actual stuff in it
    for(int i = 0; i < 4 && flashcard_boxLength(currentBox) <= 0; i++, currentBox++)
    {
        if(currentBox > 4){currentBox = 1;}
    }
    // if all else fails
    if(flashcard_boxLength(currentBox) == 0)
    {
        return 0;
    }

    return flashcard_dequeue(currentBox);
}