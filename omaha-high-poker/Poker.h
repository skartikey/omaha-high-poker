#ifndef POKER_H // include guard
#define POKER_H

#include <vector>
#include <algorithm>
#include <sstream>

namespace Poker
{
	enum class Suit
	{
		suitUnknown,
		suitDiamonds,
		suitClubs,
		suitHearts,
		suitSpades
	};
	enum class CardSource
	{
		sourceUnknown,
		sourceFromPlayer,
		sourceFromBoard
	};

} // End Namespace Poker
#endif /* POKER_H */
