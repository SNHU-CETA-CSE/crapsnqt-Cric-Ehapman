#include <iostream>
#include <stdio.h>
//#include <QApplication>
//#include <QWidget>
//#include <QGridLayout>
//#include <QPushButton>
//#include <QLabel>
//#include <QPixmap>

#include "die.h"
#include "craps.h"
#include "ui_CrapsMainWindow.h"
#include <sstream>
#include <iomanip>

CrapsMainWindow :: CrapsMainWindow(QMainWindow *parent):
// Build a GUI window with two dice.

        firstRoll { true },
        winsCount { 0 },
        lossCount { 0 },
        currentBankValue { 100 },
        currentBet{ 0 },
        previousRoll { 0 }
//statusMessage { "" },
//payouts {0.0, 0.0, 1.0, 1.0, 2.0, 1.5, 1.2, 1.0, 1.2, 1.5, 2.0, 1.0, 1.0}

{
    setupUi(this);

    QObject::connect(rollButton, SIGNAL(clicked()), this, SLOT(rollButtonClickedHandler()));
}
void CrapsMainWindow::printStringRep() {
    // String representation for Craps.
    char buffer[25];
    int length =  sprintf(buffer, "Die1: %i\nDie2: %i\n", die1.getValue(), die2.getValue());
    printf("%s", buffer);
}
void CrapsMainWindow::updateUI() {
//    printf("Inside updateUI()\n");

//Stream in the bank value
    std::stringstream updatedBank;
    updatedBank << std::fixed << std::setprecision(2) << currentBankValue;
    std::string updatedBankString = updatedBank.str();

    std::string die1ImageName = ":/dieImages/" + std::to_string(die1.getValue());
    std::string die2ImageName = ":/dieImages/" + std::to_string(die2.getValue());
    die1UI->setPixmap(QPixmap(QString::fromStdString(die1ImageName)));
    die2UI->setPixmap(QPixmap(QString::fromStdString(die2ImageName)));
    currentBankValueUI->setText("$" + QString::fromStdString(updatedBankString));
    winsCountUI->setText(QString::fromStdString(std::to_string(winsCount)));
    lossCountUI->setText(QString::fromStdString(std::to_string(lossCount)));
    if (currentBankValue <= 0){
        rollButton->setEnabled(false);
        rollButton->setText(QString::fromStdString("BANKRUPT!"));
    }

}

void CrapsMainWindow::rollButtonClickedHandler() {
    bool rollCompleted = false;
    float localBank = currentBankValue;
    rollValue =  die1.roll() + die2.roll();
    currentBet = processBet(currentBankValue);
    if (currentBet > currentBankValue){
        statusUI->setText("Not enough money!");
    } else {
        if (firstRoll) {
            currentRollUI->setText("1");
            rollingForUI->setText("Waiting...");
            statusUI->setText("Waiting...");
            // Play the game as if it was the first roll
            std::cout << "This is the first roll\n";
            std::tie(rollCompleted, localBank) = playFirstRoll(rollValue, currentBankValue, currentBet);
            if (rollCompleted) {
                firstRoll = true;
                rollCompleted = false;
                currentBankValue = localBank;
            } else {
                previousRoll = rollValue;
                firstRoll = false;
                rollCompleted = false;
                rollValueUI->setText(QString::fromStdString(std::to_string(previousRoll)));

                rollButton->setText(QString::fromStdString("ROLL AGAIN!"));
            }
        } else {
            // Play the game if one of first roll values is eligible for a second roll
            std::cout << "This is the second roll\n";
            currentRollUI->setText("2");
            std::tie(rollCompleted, localBank) = playSecondRoll(rollValue, previousRoll, currentBankValue, currentBet);
            if (rollCompleted) {
                previousRoll = rollValue;
                firstRoll = true;
                rollCompleted = false;
                currentBankValue = localBank;
                rollValueUI->setText(QString::fromStdString(std::to_string(previousRoll)));
                rollButton->setText(QString::fromStdString("ROLL!"));
            }
        }
        printStringRep();
        updateUI();
    }
}

inline bool isInteger(const std::string & s) {      //Function to check whether or not the
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    char * p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

int CrapsMainWindow::processBet(float currentBankValue) {   //method to handle the users bet
    int attemptedBet;
    attemptedBet = userBetUI->value();
    if (float(attemptedBet) <= currentBankValue) {
        return attemptedBet;
    } else {
        return attemptedBet;
    }
}

std::tuple<bool, float>  CrapsMainWindow::playFirstRoll(int rollValue, float currentBank, float currentBet){
    std::cout << rollValue << "\n";
    switch (rollValue) {
        case 7:
        case 11: {
            rollValueUI->setText(QString::fromStdString(std::to_string(rollValue)));
            currentBank = processWin(rollValue, 1, currentBank, currentBet);
            return std::make_tuple(true, currentBank);
        }
        case 2:
        case 3:
        case 12: {
            rollValueUI->setText(QString::fromStdString(std::to_string(rollValue)));
            currentBank = processLoss(rollValue, 1, currentBank, currentBet);
            return std::make_tuple(true, currentBank);
        }
        default: {
            rollingForUI->setText(QString::fromStdString(std::to_string(rollValue)));
            return std::make_tuple(false, currentBank);
        }
    }
};

std::tuple<bool, float>  CrapsMainWindow::playSecondRoll(int rollValue, int previousRoll,  float currentBank, float currentBet){
    if (rollValue == previousRoll) {
        return std::make_tuple(true, processWin(rollValue, 2, currentBank, currentBet));
    } else {
        return std::make_tuple(true, processLoss(rollValue, 2, currentBank, currentBet));
    }
};