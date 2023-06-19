#ifndef POKER_PLAYER_CARDS_H // include guard
#define POKER_PLAYER_CARDS_H

#include "Poker.h"
#include "PokerCardSet.h"
namespace Poker
{
    class PokerPlayerCards : public PokerCardSet
    {
    public:
        PokerPlayerCards() {}
        PokerPlayerCards(const std::string &s) : PokerCardSet(s)
        {
            for (PokerCardArray::iterator pos = mCards.begin(); pos != mCards.end(); ++pos)
                pos->SetAsFromPlayer();
        }
    };
} // namespace Poker
#endif /* POKER_PLAYER_CARDS_H */