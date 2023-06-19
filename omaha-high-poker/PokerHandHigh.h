#ifndef POKER_HAND_HIGH_H // include guard
#define POKER_HAND_HIGH_H

#include "Poker.h"
#include "PokerHand.h"
#include "PokerPlayerCards.h"
#include "PokerBoardCards.h"

namespace Poker
{
    /* -------------------------------------------------------------------------------------------------------
        9 - Straight Flush: Five cards in sequence, of the same suit. (A,K,Q,J,10 is known as a Royal Flush)
        8 - Four of a Kind: Four cards of the same rank, and one side card or 'kicker'.
        7 - Full House: Three cards of the same rank, and two cards of a different, matching rank.
        6 - Flush: Five cards of the same suit.
        5 - Straight: Five cards in sequence.
        4 - Three of a kind: Three cards of the same rank, and two unrelated side cards.
        3 - Two pair: Two cards of a matching rank, another two cards of a different matching rank, and one side card.
        2 - One pair: Two cards of a matching rank, and three unrelated side cards.
        1 - High card: Any hand that does not qualify under a category listed above.
    */

    class PokerHandHigh : public PokerHand
    {
    protected:
        unsigned int mHandRank;

    public:
        PokerHandHigh(PokerPlayerCards, PokerBoardCards);
        PokerHandHigh(const PokerHandHigh &other) : mHandRank(other.mHandRank)
        {
            mRankName = other.mRankName;
            mCards = other.mCards;
            mSetName = other.mSetName;
        }

        PokerHandHigh &operator=(const PokerHandHigh &rValue)
        {
            mHandRank = rValue.mHandRank;
            mRankName = rValue.mRankName;
            mCards = rValue.mCards;
            mSetName = rValue.mSetName;
            return *this;
        }

        static std::string GetRankNameForHighHand(unsigned int);

        virtual std::string ToString() const;
        virtual unsigned int GetRank() const { return mHandRank; }
        virtual std::string ObjectSuffix() const { return std::string("Hi"); }

        virtual bool operator==(const PokerHand &rValue) const
        {
            return mHandRank == rValue.GetRank() && mCards == rValue.GetCards();
        }

        virtual bool operator>(const PokerHand &rValue) const
        {
            return mHandRank > rValue.GetRank() || (mHandRank == rValue.GetRank() && mCards > rValue.GetCards());
        }
    };
} // namespace Poker
#endif /* POKER_HAND_HIGH_H */