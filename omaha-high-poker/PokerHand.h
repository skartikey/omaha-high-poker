#ifndef POKER_HAND_H // include guard
#define POKER_HAND_H

#include "Poker.h"
#include "PokerCardSet.h"
namespace Poker
{
    class PokerHand : public PokerCardSet // Abstract Class
    {
    protected:
        std::string mRankName;

    public:
        std::string GetRankName() const { return mRankName; }

        virtual bool operator==(const PokerHand &rValue) const
        {
            return qualified() && rValue.qualified() && mCards == rValue.mCards;
        }

        virtual bool operator>(const PokerHand &rValue) const
        {
            return qualified() && rValue.qualified() && mCards > rValue.mCards;
        }

        virtual bool qualified() const { return Cards() == 5; }
        virtual unsigned int GetRank() const { return 0; }

        virtual std::string ObjectSuffix() const = 0;
    };
} // namespace Poker
#endif /* POKER_HAND_H */