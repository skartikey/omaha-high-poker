#include "Poker.h"
#include "PokerHandHigh.h"

namespace Poker
{

	PokerHandHigh::PokerHandHigh(PokerPlayerCards a, PokerBoardCards pBoardCards)
	{
		mHandRank = 0;
		if (a.Cards() >= 2 && pBoardCards.Cards() >= 3)
		{
			PokerCardArray ar(5);
			unsigned int ar_rank = 0;
			PokerCardArray::size_type playerOneCards, playerTwoCards, pb1, pb2, pb3;
			for (playerOneCards = 0; playerOneCards < a.Cards(); playerOneCards++)
				for (ar[0] = a[playerOneCards], playerTwoCards = playerOneCards + 1; playerTwoCards < a.Cards(); playerTwoCards++)
					for (ar[1] = a[playerTwoCards], pb1 = 0; pb1 < pBoardCards.Cards(); pb1++)
						for (ar[2] = pBoardCards[pb1], pb2 = pb1 + 1; pb2 < pBoardCards.Cards(); pb2++)
							for (ar[3] = pBoardCards[pb2], pb3 = pb2 + 1; pb3 < pBoardCards.Cards(); pb3++)
							{
								ar[4] = pBoardCards[pb3];

								PokerCardSet candidate(ar);

								if (candidate.MakeStraightFlush())
									ar_rank = 9;
								else if (mHandRank <= 8 && candidate.Make4ofKind())
									ar_rank = 8;
								else if (mHandRank <= 7 && candidate.MakeFullHouse())
									ar_rank = 7;
								else if (mHandRank <= 6 && candidate.MakeFlush())
									ar_rank = 6;
								else if (mHandRank <= 5 && candidate.MakeStraight())
									ar_rank = 5;
								else if (mHandRank <= 4 && candidate.Make3ofKind())
									ar_rank = 4;
								else if (mHandRank <= 3 && candidate.MakeTwoPair())
									ar_rank = 3;
								else if (mHandRank <= 2 && candidate.MakeOnePair())
									ar_rank = 2;
								else
								{
									candidate.SortSet();
									ar_rank = 1;
								}

								if (!Cards() || ar_rank > mHandRank ||
									(ar_rank == mHandRank && candidate > mCards))
								{
									mCards = candidate.GetCards();
									mHandRank = ar_rank;
								}
							}

			mRankName = GetRankNameForHighHand(mHandRank);
		}
	}

	std::string PokerHandHigh::ToString() const // for testing
	{
		std::ostringstream oss;
		if (!mSetName.empty())
			oss << mSetName << ':';
		for (PokerCardArray::size_type i = 0; i < Cards(); i++)
		{
			oss << mCards[i];
			switch (mCards[i].GetCardSource())
			{
			case CardSource::sourceFromPlayer:
				oss << "/P";
				break;
			case CardSource::sourceFromBoard:
				oss << "/B";
				break;
			default:
				break;
			}
			if (mCards[i].HasSuit() && i < Cards() - 1)
				oss << ' ';
		}
		oss << " - Rank: " << mHandRank << "(" << mRankName << ")";
		return oss.str();
	}

	std::string PokerHandHigh::GetRankNameForHighHand(unsigned int n)
	{
		switch (n)
		{
		case 9:
			return "Straight Flush";
			break;
		case 8:
			return "4-of-a-Kind";
			break;
		case 7:
			return "Full House";
			break;
		case 6:
			return "Flush";
			break;
		case 5:
			return "Straight";
			break;
		case 4:
			return "3-of-a-Kind";
			break;
		case 3:
			return "Two Pair";
			break;
		case 2:
			return "One Pair";
			break;
		case 1:
			return "High card";
			break;
		case 0:
		default:
			return "Unknown rank";
			break;
		}
	}

} // namespace Poker