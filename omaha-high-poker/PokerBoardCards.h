#ifndef POKER_BOARD_CARDS_H // include guard
#define POKER_BOARD_CARDS_H

#include "Poker.h"
#include "PokerCardSet.h"
namespace Poker
{
    class PokerBoardCards : public PokerCardSet
    {
    public:
        PokerBoardCards() {}
        PokerBoardCards(const std::string &s) : PokerCardSet(s)
        {
            for (PokerCardArray::iterator pos = mCards.begin(); pos != mCards.end(); ++pos)
                pos->SetAsFromBoard();
        }
    };
} // namespace Poker
#endif /* POKER_BOARD_CARDS_H */