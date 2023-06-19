#ifndef POKER_CARD_H // include guard
#define POKER_CARD_H

#include "Poker.h"
#include "PlayingCard.h"
namespace Poker
{
    class PokerCard : public PlayingCard
    {
    protected:
        CardSource mSource;

    public:
        PokerCard() : PlayingCard(), mSource(CardSource::sourceUnknown) {}
        PokerCard(std::string r) : PlayingCard(r), mSource(CardSource::sourceUnknown) {}

        PokerCard(const PokerCard &other) : PlayingCard(other), mSource(other.mSource) {}

        PokerCard &operator=(const PokerCard &rValue)
        {
            mRank = rValue.mRank;
            mSuit = rValue.mSuit;
            mSource = rValue.mSource;
            return *this;
        }

        void transformForLow8()
        {
            mSuit = Suit::suitUnknown;
            if (mRank == 14)
                mRank = 1;
        }
        void AceToLowestCard()
        {
            if (mRank == 14)
                mRank = 1;
        }

        void SetAsFromPlayer() { mSource = CardSource::sourceFromPlayer; }
        void SetAsFromBoard() { mSource = CardSource::sourceFromBoard; }
        CardSource GetCardSource() const { return mSource; }

        bool IsLow8() const { return mRank <= 8; }
        bool HasSuit() const { return mSuit != Suit::suitUnknown; }

        virtual bool operator==(const PokerCard &rValue) const { return mRank == rValue.mRank; }
        virtual bool operator!=(const PokerCard &rValue) const { return mRank != rValue.mRank; }
        virtual bool operator>(const PokerCard &rValue) const { return mRank > rValue.mRank; }
        virtual bool operator<(const PokerCard &rValue) const { return mRank < rValue.mRank; }
        virtual bool operator>=(const PokerCard &rValue) const { return mRank >= rValue.mRank; }
        virtual bool operator<=(const PokerCard &rValue) const { return mRank <= rValue.mRank; }
    };

    using PokerCardArray = std::vector<PokerCard>;
} // namespace Poker
#endif /* POKER_CARD_H */