#include "Poker.h"
#include "PlayingCard.h"

namespace Poker
{

	PlayingCard::PlayingCard(const std::string &r)
	{
		mRank = 0;
		mSuit = Suit::suitUnknown;
		if (!r.length() || r.length() > 2)
			return;

		if (isdigit(r[0]))
		{
			mRank = atoi(r.substr(0, 1).c_str());
			if (mRank == 1)
				mRank = 0;
		}
		else
		{
			switch (tolower(r[0]))
			{
			case 't':
				mRank = 10;
				break;
			case 'j':
				mRank = 11;
				break;
			case 'q':
				mRank = 12;
				break;
			case 'k':
				mRank = 13;
				break;
			case 'a':
				mRank = 14;
				break;
			}
		}

		if (r.length() == 2)
		{
			switch (tolower(r[1]))
			{
			case 'd':
				mSuit = Suit::suitDiamonds;
				break;
			case 'c':
				mSuit = Suit::suitClubs;
				break;
			case 'h':
				mSuit = Suit::suitHearts;
				break;
			case 's':
				mSuit = Suit::suitSpades;
				break;
			case '*':
				mSuit = Suit::suitUnknown;
				break;
			}
		}
	}

	std::string PlayingCard::ToString() const
	{
		std::ostringstream oss;
		if (empty())
			oss << "##";
		else
		{
			if (mRank >= 2 && mRank <= 9)
				oss << mRank;
			else
			{
				switch (mRank)
				{
				case 10:
					oss << 'T';
					break;
				case 11:
					oss << 'J';
					break;
				case 12:
					oss << 'Q';
					break;
				case 13:
					oss << 'K';
					break;
				case 1:
				case 14:
					oss << 'A';
					break;
				}
			}

			switch (mSuit)
			{
			case Suit::suitDiamonds:
				oss << 'd';
				break;
			case Suit::suitClubs:
				oss << 'c';
				break;
			case Suit::suitHearts:
				oss << 'h';
				break;
			case Suit::suitSpades:
				oss << 's';
				break;
			default:
				break;
			}
		}
		return oss.str();
	}

} // End Namespace Poker