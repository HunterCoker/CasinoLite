#include "AccountManager.hpp"

#include <sstream>

#define ACCOUNTFILE "account.lite"

double AccountManager::m_balance = 100.0,
       AccountManager::m_greatestWin = 0.0,
       AccountManager::m_greatestLoss = 0.0;

void AccountManager::Init() {
    try {
        std::ifstream ifstream;
        ifstream.open(ACCOUNTFILE);

        // no file to open implies starting a new account
        if (ifstream.fail()) {
            std::cout << "< New Account Created >\n"
                         "\tstarting balance : $100.00\n";
            return;
        }

        double* refs[] = {
                &m_balance,
                &m_greatestWin,
                &m_greatestWin
        };

        std::stringstream sstream;
        sstream << ifstream.rdbuf();
        std::string s;

        for (auto ref : refs) {
            sstream >> s;
            *ref = std::stod(s);
        }

        ifstream.open(ACCOUNTFILE);
    }
    catch(std::fstream::failure& e) {
        std::cerr << "error :: failed to read account file" << std::endl;
    }
}

void AccountManager::PrintInfo() {
    std::cout << "balance:\t" << m_balance << '\n'
              << "greatest win:\t" << m_greatestWin << '\n'
              << "greatest loss:\t" << m_greatestLoss << '\n'
              << std::endl;
}

void AccountManager::Terminate() {
    try {
        std::ofstream ofstream;
        ofstream.open(ACCOUNTFILE);

        double* refs[] = {
                &m_balance,
                &m_greatestWin,
                &m_greatestWin
        };

        for (auto ref : refs)
            ofstream << *ref << '\n';

        ofstream.close();
    }
    catch(std::fstream::failure& e) {
        std::cerr << "error :: failed to write to account file" << std::endl;
    }
}
