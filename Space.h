/*
 * Author: Martin Nguyen
 * Description: Space class for representing individual cells in Minesweeper game
 * Date: 02/06/2025
 */

#ifndef SPACE_H
#define SPACE_H

// System/standard libraries
#include <iostream>

class Space {
private:
    // Instance variables
    bool isMine;
    int adjacentMines;
    bool isRevealed;
    bool isFlagged;
    bool isQuestion;

public:
    // Constructor and destructor
    Space();
    virtual ~Space();

    // Getters (public)
    bool getIsMine() const;
    int getAdjacentMines() const;
    bool getIsRevealed() const;
    bool getIsFlagged() const;
    bool getIsQuestion() const;
    
    // Setters (public)
    void setMine(bool mine);
    void setAdjacentMines(int count);
    void setRevealed(bool revealed);
    void setFlagged(bool flagged);
    void setIsQuestion(bool question);

};

#endif // SPACE_H
