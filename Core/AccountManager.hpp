#pragma once

#include <cinttypes>

#include <iostream>
#include <fstream>
#include <ostream>

class AccountManager {
public:
    static void Init();
    static void Terminate();
    static void PrintInfo();

    static double GetBalance() { return m_balance; }

    // balance modifiers
    static void AddToBalance(double amount) {
        m_balance += amount;
        if(amount > m_greatestWin)
            m_greatestWin = amount;
        if(amount < m_greatestLoss)
            m_greatestLoss = amount;
    }
private:
    static double m_balance, m_greatestWin, m_greatestLoss;
};
