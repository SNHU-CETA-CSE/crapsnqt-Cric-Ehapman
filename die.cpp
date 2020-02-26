//
// Created by Arana Fireheart on 1/30/20.
//

#include "die.h"

Die :: Die(int openingNumberOfSides, int openingStartingValue, int openingIncrement, std::string openingColor, std::string openingName) {
    numberOfSides = openingNumberOfSides;
    startingValue = openingStartingValue;
    setIncrement(openingIncrement);
    color = openingColor;
    name = openingName;
    value = 6;
    srand((unsigned int)time(NULL));    // Seed the random number generator.
}
std::string Die::stringRep() {
    char buffer[100];
    int numberOfCharacters = 0;

    const char *format = "Die named %s has %i sides, starts at %i increments by %i and has a current value of %i";
    numberOfCharacters = std::snprintf(buffer, 100, format, name.c_str(), numberOfSides, startingValue, increment, value);
    if (numberOfCharacters > 0 && numberOfCharacters < 100 ) {
        std::string returnString(buffer, numberOfCharacters);
        return returnString;
    }
    else
        return "";
}
int Die::roll() {
    value = ((rand() % numberOfSides) * increment + startingValue);
    return value;
}
void Die::setValue(int newValue) {
    // Test for a value within range and a multiple of the increment.
    if (startingValue * increment <= newValue <= numberOfSides * increment and not newValue % increment)
        value = newValue;
    else
        throw BadDieValueException();
}
int Die::getValue() {
    return value;
}
void Die::setNumberOfSides(int newNumberOfSides) {
    numberOfSides = newNumberOfSides;
}
int Die::getNumberOfSides() {
    return numberOfSides;
}
void Die::setStartingValue(int newStartingValue) {
    startingValue = newStartingValue;
}
int Die::getStartingValue() {
    return startingValue;
}
void Die::setIncrement(int newIncrement) {
    if (newIncrement > 0 && newIncrement == 1) // Increment must be at least 1.
        increment = newIncrement;
    else
        increment = newIncrement;
    startingValue = newIncrement;           // startingValue can't be less that the increment.
}
int Die::getIncrement() {
    return increment;
}
void Die::setColor(std::string newColor) {
    color = newColor;
}
std::string Die::getColor() {
    return color;
}
void Die::setName(std::string newName) {
    name = newName;
}
std::string Die::getName() {
    return name;
}
