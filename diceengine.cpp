#include "diceengine.h"

#include <random>
#include <sstream>
#include <algorithm>

DiceEngine::DiceEngine() {}

class CryptoDice {
private:
    std::random_device rd;

public:
    int roll(int sides) {
        unsigned int limit = rd.max() - (rd.max() % (unsigned int)sides);
        unsigned int x;
        do { x = rd(); } while (x >= limit);
        return (int)(x % (unsigned int)sides) + 1;
    }
};

static std::string removeSpaces(std::string s) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

static std::string normalizeMinus(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-' && i > 0)
            out += "+-";
        else
            out += s[i];
    }
    return out;
}

RollResult DiceEngine::rollExpression(const std::string& expr) {
    CryptoDice dice;
    RollResult result;
    result.originalExpression = expr;

    std::string cleaned = removeSpaces(expr);
    std::string normalized = normalizeMinus(cleaned);

    std::stringstream ss(normalized);
    std::string token;

    while (std::getline(ss, token, '+')) {
        if (token.empty()) continue;

        auto posD = token.find('d');
        if (posD == std::string::npos)
            posD = token.find('D');

        // Modificador fixo
        if (posD == std::string::npos) {
            result.modifier += std::stoi(token);
            continue;
        }

        int q = 1;
        if (posD > 0)
            q = std::stoi(token.substr(0, posD));

        int sides = std::stoi(token.substr(posD + 1));

        RollGroup g;
        g.quantity = q;
        g.sides = sides;

        for (int i = 0; i < q; i++) {
            int r = dice.roll(sides);
            g.rolls.push_back(r);
            result.sumDice += r;
        }

        result.groups.push_back(g);
    }

    result.total = result.sumDice + result.modifier;

    // Montar texto detalhado
    std::ostringstream out;
    for (size_t i = 0; i < result.groups.size(); i++) {
        const auto& g = result.groups[i];

        out << g.quantity << "d" << g.sides << ":[";
        for (size_t j = 0; j < g.rolls.size(); j++) {
            out << g.rolls[j];
            if (j + 1 < g.rolls.size())
                out << ",";
        }
        out << "]";

        if (i + 1 < result.groups.size())
            out << " | ";
    }

    if (result.modifier != 0) {
        if (!result.groups.empty())
            out << " | ";
        out << "mod:" << (result.modifier > 0 ? "+" : "") << result.modifier;
    }

    result.detailsText = out.str();
    result.historyLine =
        expr + " => " + result.detailsText +
        " | total:" + std::to_string(result.total);

    return result;
}
