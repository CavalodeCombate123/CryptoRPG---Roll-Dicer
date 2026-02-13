#ifndef DICEENGINE_H
#define DICEENGINE_H

#include <string>
#include <vector>

struct RollGroup {
    int quantity;
    int sides;
    std::vector<int> rolls;
};

struct RollResult {
    std::string originalExpression;
    std::vector<RollGroup> groups;
    int modifier = 0;
    int sumDice = 0;
    int total = 0;

    std::string detailsText;
    std::string historyLine;
};

class DiceEngine {
public:
    DiceEngine();
    RollResult rollExpression(const std::string& expr);
};

#endif
