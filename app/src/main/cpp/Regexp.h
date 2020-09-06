#ifndef ANALYZERAPP_REGEXP_H
#define ANALYZERAPP_REGEXP_H

#include <string>
#include <vector>
#include <memory>

class State;
typedef std::shared_ptr<State> StatePtr_t;

class State
{
    bool mIsFinal;
    std::pair <char, StatePtr_t> mTransition;
    std::vector<StatePtr_t> mEpsilonTransitions;
public:
    State(bool isFinal)
    {
        mIsFinal = isFinal;
    }

    bool isFinal()
    {
        return mIsFinal;
    }

    void setFinal(bool isFinal)
    {
        mIsFinal = isFinal;
    }

    void addEpsilonTransition(StatePtr_t state)
    {
        mEpsilonTransitions.push_back(state);
    }

    std::vector<StatePtr_t> & getEpsilonTransition()
    {
        return mEpsilonTransitions;
    }

    void setTransition(char sym, StatePtr_t state)
    {
        mTransition.first = sym;
        mTransition.second = state;
    }

    StatePtr_t transition(char symbol) {
        if (mTransition.first == '?' || mTransition.first == symbol)
        {
            return mTransition.second;
        }
        else return nullptr;
    }
};

typedef std::pair<StatePtr_t, StatePtr_t> NFA_t;

class Regexp
{

private:
    StatePtr_t createState(bool isFinalState);
    void addEpsilonTransition(StatePtr_t from, StatePtr_t to);
    void addTransition(StatePtr_t from, StatePtr_t to, char symbol);
    NFA_t fromEpsilon();
    NFA_t fromSymbol(char symbol);
    NFA_t fromAsterisk();
    NFA_t concat(NFA_t& first, NFA_t& second);
    void addNextState(StatePtr_t state, std::vector<StatePtr_t>& nextStates, std::vector<StatePtr_t>& visited);

public:
    NFA_t toNFA(const std::string& str);
    bool search(NFA_t & nfa, const std::string& word);
};

#endif //ANALYZERAPP_REGEXP_H
