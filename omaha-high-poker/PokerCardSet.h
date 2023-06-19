#ifndef POKER_CARD_SET_H // include guard
#define POKER_CARD_SET_H

#include "Poker.h"
#include "PokerCard.h"
namespace Poker
{
    class PokerCardSet
    {
    protected:
        PokerCardArray mCards;
        std::string mSetName;

    private:
        static bool notQualifyForLow8(PokerCard c) { return !c.IsLow8(); }

    public:
        PokerCardSet() {}
        PokerCardSet(const PokerCardArray &ar) : mCards(ar) {}
        PokerCardSet(const std::string &);
        PokerCardSet(const PokerCardSet &other) : mCards(other.mCards), mSetName(other.mSetName) {}

        ~PokerCardSet() {}

        virtual std::string ToString() const;
        unsigned int Cards() const { return mCards.size(); }

        std::string GetName() const { return mSetName; }
        void SetName(std::string &s) { mSetName = s; }

        const PokerCardArray &GetCards() const { return mCards; }
        const PokerCard &operator[](PokerCardArray::size_type i) const { return mCards[i]; }

        PokerCardSet &operator=(const PokerCardSet &rValue)
        {
            mCards = rValue.mCards;
            mSetName = rValue.mSetName;
            return *this;
        }

        PokerCardSet &operator+(const PokerCardSet &rValue)
        {
            mCards.insert(mCards.end(), rValue.mCards.begin(), rValue.mCards.end());
            return *this;
        }

        bool operator==(const PokerCardSet &rValue) const { return Cards() == rValue.Cards() && mCards == rValue.mCards; }
        bool operator>(const PokerCardSet &rValue) const { return Cards() == rValue.Cards() && mCards > rValue.mCards; }
        bool operator<(const PokerCardSet &rValue) const { return Cards() == rValue.Cards() && mCards < rValue.mCards; }

        void SortSet() { sort(mCards.begin(), mCards.end(), std::greater<PokerCard>()); }

        bool InConsecutiveOrder() const
        {
            PokerCardArray::const_iterator first = mCards.begin(), next = mCards.begin();
            ++next;
            while (next != mCards.end())
            {
                if (first->GetCardRank() - next->GetCardRank() != 1)
                    return false;
                ++first;
                ++next;
            }
            return true;
        }

        bool AllCardsOfTheSameSuit() const
        {
            if (Cards() < 2)
                return true;
            Suit s = mCards[0].GetSuit();
            for (PokerCardArray::size_type i = 1; i < Cards(); i++)
                if (s != mCards[i].GetSuit())
                    return false;
            return true;
        }

        void MakeLow8()
        {
            for (PokerCardArray::iterator pos = mCards.begin(); pos != mCards.end(); ++pos)
                pos->transformForLow8();

            PokerCardArray::iterator it = remove_if(mCards.begin(), mCards.end(), PokerCardSet::notQualifyForLow8);
            sort(mCards.begin(), it);
            mCards.resize(distance(mCards.begin(), unique(mCards.begin(), it)));
        }

        void MoveFirstCardToTheEnd()
        {
            PokerCard c = mCards[0];
            for (PokerCardArray::size_type i = 1; i < Cards(); i++)
                mCards[i - 1] = mCards[i];
            mCards[Cards() - 1] = c;
        }

        bool MakeStraightFlush();
        bool Make4ofKind();
        bool MakeFullHouse();
        bool MakeFlush();
        bool MakeStraight();
        bool Make3ofKind();
        bool MakeTwoPair();
        bool MakeOnePair();
    };

    inline std::ostream &operator<<(std::ostream &out, const PokerCardSet &cs) { return out << cs.ToString(); }
} // namespace Poker
#endif /* POKER_CARD_SET_H */