#include "Space.h"

// Constructor initializes instance variables
Space::Space() : isMine(false), adjacentMines(0), isRevealed(false), isFlagged(false), isQuestion(false) {}


// Getters
bool Space::getIsMine() const {
    return isMine;
}

int Space::getAdjacentMines() const {
    return adjacentMines;
}

bool Space::getIsRevealed() const {
    return isRevealed;
}

bool Space::getIsFlagged() const {
    return isFlagged;
}

bool Space::getIsQuestion() const {
    return isQuestion;
}

// Setters
void Space::setMine(bool mine) {
    isMine = mine;
}

void Space::setAdjacentMines(int count) {
    adjacentMines = count;
}

void Space::setRevealed(bool revealed) {
    isRevealed = revealed;
}

void Space::setFlagged(bool flagged) {
    isFlagged = flagged;
}

void Space::setIsQuestion(bool question) {
    isQuestion = question;
}
