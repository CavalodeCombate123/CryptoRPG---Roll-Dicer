#include "diceengine.h"

#include <random>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

DiceEngine::DiceEngine() {}

static std::string removeSpaces(std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c){
                return std::isspace(c);
            }), s.end());
    return s;
}

static std::string normalizeMinus(const std::string& s) {
    std::string out;
    out.reserve(s.size() * 2);
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-' && i > 0)
            out += "+-";
        else
            out += s[i];
    }
    return out;
}

RollResult DiceEngine::rollExpression(const std::string& expr) {
    // RNG (um por chamada já é ok; se quiser, dá pra manter como membro da classe)
    static thread_local std::mt19937_64 rng{ std::random_device{}() };

    auto rollOne = [&](int sides) -> int {
        if (sides <= 0) throw std::runtime_error("sides <= 0");
        std::uniform_int_distribution<int> dist(1, sides);
        return dist(rng);
    };

    RollResult result;
    result.originalExpression = expr;

    std::string cleaned = removeSpaces(expr);
    if (cleaned.empty()) throw std::runtime_error("empty");

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

        // qtd
        int q = 1;
        if (posD > 0) {
            q = std::stoi(token.substr(0, posD));
        }
        // lados
        int sides = std::stoi(token.substr(posD + 1));

        if (q <= 0) throw std::runtime_error("q <= 0");
        if (sides <= 0) throw std::runtime_error("sides <= 0");

        RollGroup g;
        g.quantity = q;
        g.sides = sides;

        for (int i = 0; i < q; i++) {
            int r = rollOne(sides);
            g.rolls.push_back(r);
            result.sumDice += r;
        }

        result.groups.push_back(g);
    }

    result.total = result.sumDice + result.modifier;

    // Texto detalhado
    std::ostringstream out;
    for (size_t i = 0; i < result.groups.size(); i++) {
        const auto& g = result.groups[i];

        out << g.quantity << "d" << g.sides << ":[";
        for (size_t j = 0; j < g.rolls.size(); j++) {
            out << g.rolls[j];
            if (j + 1 < g.rolls.size()) out << ",";
        }
        out << "]";

        if (i + 1 < result.groups.size()) out << " | ";
    }

    if (result.modifier != 0) {
        if (!result.groups.empty()) out << " | ";
        out << "mod:" << (result.modifier > 0 ? "+" : "") << result.modifier;
    }

    result.detailsText = out.str();
    result.historyLine = expr + " => " + result.detailsText +
                         " | total:" + std::to_string(result.total);

    return result;
}

