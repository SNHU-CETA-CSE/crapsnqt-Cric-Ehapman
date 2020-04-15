//
// Created by Arana Fireheart on 2/2/20.
//

#ifndef CRAPSSTARTER_CRAPS_H
#define CRAPSSTARTER_CRAPS_H

#include "ui_CrapsMainWindow.h"
#include "die.h"
#include <QMainWindow>

class CrapsMainWindow : public QMainWindow, private Ui::CrapsMainWindow {
Q_OBJECT

public:
    CrapsMainWindow(QMainWindow *parent = nullptr);
    void printStringRep();
    void updateUI();

private:
    Die die1, die2;
    bool firstRoll = true;
    int winsCount;
    int lossCount;
    float currentBankValue;
    int rollValue;
    int currentBet;
    int previousRoll;
    //std::string statusMessage;
    //const float payouts[];


    std::tuple<bool, float> playFirstRoll(int rollValue, float currentBank, float currentBet);
    std::tuple<bool, float> playSecondRoll(int rollValue, int previousRoll, float currentBank, float currentBet);
    float processWin(int rollValue, int rollNumber, float currentBank, float currentBet);
    float processLoss(int rollValue, int rollNumber, float currentBank, float currentBet);
    static float calculateCurrentBank(int rollValue, int rollNumber, float currentBank, float currentBet, bool wonBet);

    int processBet(float currentBank);
    //bool isInteger(const std::string & s);
    //void displayResults(float currentBank, float currentBet);


public Q_SLOTS:
    void rollButtonClickedHandler();

};
//#include "moc_craps.cpp"
#endif //CRAPSSTARTER_CRAPS_H

