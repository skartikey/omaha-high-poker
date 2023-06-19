#include "Poker.h"
#include "PokerCardSet.h"

namespace Poker
{

	PokerCardSet::PokerCardSet(const std::string &s)
	{
		std::string::size_type pos1 = s.find(":"), pos2;
		if (pos1 == std::string::npos)
			pos1 = 0;
		else
			mSetName = s.substr(0, pos1++);

		while (pos1 < s.length() && (pos2 = s.find("-", pos1)) != std::string::npos)
		{
			mCards.push_back(s.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 1;
		}
		mCards.push_back(s.substr(pos1));
	}

	std::string PokerCardSet::ToString() const
	{
		std::ostringstream oss;
		if (!mSetName.empty())
			oss << mSetName << ':';
		for (PokerCardArray::size_type i = 0; i < Cards(); i++)
		{
			oss << mCards[i];
			if (mCards[i].HasSuit() && i < Cards() - 1)
				oss << '-';
		}
		return oss.str();
	}

	bool PokerCardSet::MakeStraightFlush() // rank: 9
	{
		if (Cards() != 5 || !AllCardsOfTheSameSuit())
			return false;

		SortSet();
		if (InConsecutiveOrder())
			return true;

		if (mCards[0].GetCardRank() == 14)
		{
			PokerCardArray old(mCards);
			mCards[0].AceToLowestCard();
			MoveFirstCardToTheEnd();
			if (InConsecutiveOrder())
				return true;
			mCards = old;
		}
		return false;
	}

	bool PokerCardSet::Make4ofKind() // rank: 8
	{
		if (Cards() != 5)
			return false;

		SortSet();
		if (mCards[0].GetCardRank() != mCards[1].GetCardRank())
			MoveFirstCardToTheEnd();

		return mCards[0].GetCardRank() == mCards[1].GetCardRank() &&
			   mCards[0].GetCardRank() == mCards[2].GetCardRank() &&
			   mCards[0].GetCardRank() == mCards[3].GetCardRank();
	}

	bool PokerCardSet::MakeFullHouse() // rank: 7
	{
		if (Cards() != 5)
			return false;

		SortSet();

		if (mCards[0].GetCardRank() == mCards[1].GetCardRank() &&
			mCards[0].GetCardRank() == mCards[2].GetCardRank() &&
			mCards[3].GetCardRank() == mCards[4].GetCardRank())
			return true;

		if (mCards[0].GetCardRank() == mCards[1].GetCardRank() &&
			mCards[2].GetCardRank() == mCards[3].GetCardRank() &&
			mCards[2].GetCardRank() == mCards[4].GetCardRank())
		{
			MoveFirstCardToTheEnd();
			MoveFirstCardToTheEnd();
			return true;
		}
		return false;
	}

	bool PokerCardSet::MakeFlush() // rank: 6
	{
		if (Cards() == 5 && AllCardsOfTheSameSuit())
		{
			SortSet();
			return InConsecutiveOrder() ? false : true;
		}
		return false;
	}

	bool PokerCardSet::MakeStraight() // rank: 5
	{
		if (Cards() != 5 || AllCardsOfTheSameSuit())
			return false;

		SortSet();
		if (InConsecutiveOrder())
			return true;

		if (mCards[0].GetCardRank() == 14)
		{
			PokerCardArray old(mCards);
			mCards[0].AceToLowestCard();
			MoveFirstCardToTheEnd();
			if (InConsecutiveOrder())
				return true;
			mCards = old;
		}
		return false;
	}

	bool PokerCardSet::Make3ofKind() // rank: 4
	{
		if (Cards() != 5)
			return false;

		SortSet();
		PokerCardArray::iterator it = adjacent_find(mCards.begin(), mCards.end());
		if (it == mCards.end())
			return false;

		while (mCards[0].GetCardRank() != mCards[1].GetCardRank())
			MoveFirstCardToTheEnd();

		if (mCards[0].GetCardRank() == mCards[1].GetCardRank() &&
			mCards[0].GetCardRank() == mCards[2].GetCardRank() &&
			mCards[3].GetCardRank() != mCards[4].GetCardRank())
		{
			sort(mCards.begin() + 3, mCards.end(), std::greater<PokerCard>());
			return true;
		}
		return false;
	}

	bool PokerCardSet::MakeTwoPair() // rank: 3
	{
		if (Cards() != 5)
			return false;
		SortSet();

		PokerCardArray::iterator it = adjacent_find(mCards.begin(), mCards.end());
		if (it == mCards.end())
			return false;

		while (mCards[0].GetCardRank() != mCards[1].GetCardRank())
			MoveFirstCardToTheEnd();

		if (mCards[2].GetCardRank() == mCards[3].GetCardRank() &&
			mCards[2].GetCardRank() != mCards[4].GetCardRank() &&
			mCards[2].GetCardRank() != mCards[0].GetCardRank())
			return true;

		if (mCards[3].GetCardRank() == mCards[4].GetCardRank() &&
			mCards[2].GetCardRank() != mCards[3].GetCardRank() &&
			mCards[2].GetCardRank() != mCards[0].GetCardRank())
		{
			std::swap(mCards[2], mCards[4]);
			return true;
		}
		return false;
	}

	bool PokerCardSet::MakeOnePair() // rank: 2
	{
		if (Cards() != 5)
			return false;
		SortSet();

		PokerCardArray::iterator it = adjacent_find(mCards.begin(), mCards.end());
		if (it == mCards.end())
			return false;

		while (mCards[0].GetCardRank() != mCards[1].GetCardRank())
			MoveFirstCardToTheEnd();

		PokerCardArray t(mCards);
		if (distance(t.begin(), unique(t.begin(), t.end())) == 4)
		{
			sort(mCards.begin() + 2, mCards.end(), std::greater<PokerCard>());
			return true;
		}
		return false;
	}
}