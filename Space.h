#ifndef SPACE_H
#define SPACE_H

#include <iostream>

class Space {
private:
    bool isMine;
    int adjacentMines;
    bool isRevealed;
    bool isFlagged;
    bool isQuestion;

public:
    // Constructor
    Space();

    // Getters
    bool getIsMine() const;
    int getAdjacentMines() const;
    bool getIsRevealed() const;
    bool getIsFlagged() const;
    bool getIsQuestion() const;
    
    // Setters
    void setMine(bool mine);
    void setAdjacentMines(int count);
    void setRevealed(bool revealed);
    void setFlagged(bool flagged);
    void setIsQuestion(bool question);

};

#endif // SPACE_H
