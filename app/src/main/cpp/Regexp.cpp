#include "Regexp.h"

StatePtr_t Regexp::createState(bool isFinal)
{
    return StatePtr_t(new State(isFinal));
}

void Regexp::addEpsilonTransition(StatePtr_t from, StatePtr_t to)
{
    from->addEpsilonTransition(to);
}

void Regexp::addTransition(StatePtr_t from, StatePtr_t to, char symbol)
{
    from->setTransition(symbol, to);
}

/*
  Construct an NFA that recognizes only the empty string.
*/
NFA_t Regexp::fromEpsilon()
{
    StatePtr_t start = createState(false);
    StatePtr_t end = createState(true);
    addEpsilonTransition(start, end);
    return std::make_pair(start, end);
}

/*
   Construct an NFA that recognizes only a sequence of symbols with any length.
*/
NFA_t Regexp::fromAsterisk()
{
    StatePtr_t start = createState(false);
    StatePtr_t middle = createState(false);
    StatePtr_t end = createState(true);
    addTransition(start, middle, '?');
    addEpsilonTransition(middle, start);
    addEpsilonTransition(middle, end);
    return std::make_pair(start, end);
}

/*
  Construct an NFA that recognizes symbol.
*/
NFA_t Regexp::fromSymbol(char symbol)
{
    StatePtr_t start = createState(false);
    StatePtr_t end = createState(true);
    addTransition(start, end, symbol);
    return std::make_pair(start, end);
}

/*
   Concatenates two NFAs.
*/
NFA_t Regexp::concat(NFA_t& first, NFA_t& second)
{
    first.second->addEpsilonTransition(second.first);
    first.second->setFinal(false);
    return std::make_pair(first.first, second.second);
}

NFA_t Regexp::toNFA(const std::string& str)
{
    if (str.empty()) {
        return fromEpsilon();
    }

    std::vector<std::pair<StatePtr_t, StatePtr_t>> nfas;

    for (int i = 0; i < str.size(); ++i) {
        char token = str[i];
        if (token == '*') {
            nfas.push_back(fromAsterisk());
        }
        else {
            nfas.push_back(fromSymbol(token));
        }
    }

    for (int i = 0; i < nfas.size() - 1; ++i) {
        concat(nfas[i], nfas[i + 1]);
    }

    return nfas[0];
}

void Regexp::addNextState(StatePtr_t state, std::vector<StatePtr_t> & nextStates, std::vector<StatePtr_t>& visited)
{
    std::vector<StatePtr_t>& states = state->getEpsilonTransition();

    if (states.size()) {
        for (std::vector<StatePtr_t>::iterator iter = states.begin(); iter != states.end(); ++iter) {
            if (std::find(visited.begin(), visited.end(), *iter) == visited.end()) {
                visited.push_back(*iter);
                addNextState(*iter, nextStates, visited);
            }
        }
    }
    else {
        nextStates.push_back(state);
    }
}

bool Regexp::search(NFA_t& nfa, const std::string& word)
{
    std::vector<StatePtr_t> currentStates;
    std::vector<StatePtr_t> visited;
    addNextState(nfa.first, currentStates, visited);

    for (int i = 0; i < word.size(); ++i) {
        char symbol = word[i];
        std::vector<StatePtr_t> nextStates;

        for (int i = 0; i < currentStates.size(); ++i) {
            StatePtr_t nextState = currentStates[i]->transition(symbol);
            if (nextState) {
                visited.clear();
                addNextState(nextState, nextStates, visited);
            }
        }
        currentStates = nextStates;
    }

    for (int i = 0; i < currentStates.size(); ++i) {
        if (currentStates[i]->isFinal()) return true;
    }
    return false;
}
