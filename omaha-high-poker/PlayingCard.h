#ifndef PLAYING_CARD_H // include guard
#define PLAYING_CARD_H

#include "Poker.h"
namespace Poker
{
    class PlayingCard
    {
    protected:
        unsigned int mRank; // A=1(low),2,3,4,5,6,7,8,9,T=10,J=11,Q=12,K=13,A=14(high)
        Suit mSuit;         // d,c,h,s

    public:
        PlayingCard() : mRank(0), mSuit(Suit::suitUnknown) {}
        PlayingCard(const std::string &);
        PlayingCard(const PlayingCard &other) : mRank(other.mRank), mSuit(other.mSuit) {}

        PlayingCard &operator=(const PlayingCard &rValue)
        {
            mRank = rValue.mRank;
            mSuit = rValue.mSuit;
            return *this;
        }

        virtual bool operator==(const PlayingCard &rValue) const { return mRank == rValue.mRank && mSuit == rValue.mSuit; }
        virtual bool operator!=(const PlayingCard &rValue) const { return mRank != rValue.mRank || mSuit != rValue.mSuit; }
        virtual std::string ToString() const;

        unsigned int GetCardRank() const { return mRank; }
        Suit GetSuit() const { return mSuit; }
        bool empty() const { return mRank ? false : true; }
    };

    inline std::ostream &operator<<(std::ostream &out, const PlayingCard &c) { return out << c.ToString(); }
} // namespace Poker
#endif /* PLAYING_CARD_H */