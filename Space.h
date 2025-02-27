#ifndef SPACE_H
#define SPACE_H

#include <iostream>

class Space {
    private:
        bool isMine;
        int adjacentMines;
        bool isRevealed;
        bool isFlagged;

    public:
        // Constructor
        Space();

        // Getters
        bool getIsMine() const;
        int getAdjacentMines() const;
        bool getIsRevealed() const;
        bool getIsFlagged() const; 

        // Setters
        void setMine(bool mine);
        void setAdjacentMines(int count);
        void reveal();
        void toggleFlag();

};

#endif // SPACE_H
