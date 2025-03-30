/*
 * Author: Martin Nguyen
 * Description: Implementation of Space class for Minesweeper game
 * Date: 02/06/2025
 */

#include "Space.h"

/*
 * Constructor: Space
 * Description: Initializes a new space with default values
 */
Space::Space() : isMine(false), adjacentMines(0), isRevealed(false), isFlagged(false), isQuestion(false) 
{
}

/*
 * Destructor: Space
 * Description: Destroys the space object (managed by Qt)
 */
Space::~Space()
{
}

 /*
  * Function: getIsMine
  * Description: Checks if space contains a mine
  * Returns: true if space contains a mine, false otherwise
  */
bool Space::getIsMine() const
{
    return isMine;
}

 /*
  * Function: getAdjacentMines
  * Description: Gets the number of mines adjacent to this current space
  * Returns: Number of adjacent mines
  */
int Space::getAdjacentMines() const
{
    return adjacentMines;
}

 /*
  * Function: getIsRevealed
  * Description: Checks if current space has been revealed
  * Returns: true if space is revealed, false otherwise
  */

bool Space::getIsRevealed() const
{
    return isRevealed;
}

 /*
  * Function: getIsFlagged
  * Description: Checks if space is flagged
  * Returns: true if space is flagged, false otherwise
  */
bool Space::getIsFlagged() const
{
    return isFlagged;
}

 /*
  * Function: getIsQuestion
  * Description: Checks if space has a question mark
  * Returns: true if space has a question mark, false otherwise
  */
bool Space::getIsQuestion() const
{
    return isQuestion;
}

 /*
  * Function: setMine
  * Description: Sets whether this space contains a mine
  * Parameters: mine - true to place a mine, false to remove it
  */
void Space::setMine(bool mine)
{
    isMine = mine;
}

 /*
  * Function: setAdjacentMines
  * Description: Sets the number of mines adjacent to this space
  * Parameters: count - Number of adjacent mines
  */
void Space::setAdjacentMines(int count)
{
    adjacentMines = count;
}

 /*
  * Function: setRevealed
  * Description: Sets whether this space has been revealed
  * Parameters: revealed - true to reveal the space, false to hide it
  */
void Space::setRevealed(bool revealed)
{
    isRevealed = revealed;
}

 /*
  * Function: setFlagged
  * Description: Sets whether this space is flagged
  * Parameters: flagged - true to flag the space, false to remove flag
  */
void Space::setFlagged(bool flagged)
{
    isFlagged = flagged;
}

 /*
  * Function: setIsQuestion
  * Description: Sets whether this space has a question mark
  * Parameters: question - true to add question mark, false to remove it
  */
void Space::setIsQuestion(bool question)
{
    isQuestion = question;
}
