#include "PersonData.h"

void PersonData::ComputeDataValue()
{
	value = 0;
	if (!name.empty())
		value += 100;
	if (!sex.empty())
		value += 20;
	if (birthday)
		value += 20;
	if (lostday)
		value += 5;
	if (height)
		value += 20;
	if (!birthplace.first.empty())
		value += 22.5;
	if (!birthplace.second.empty())
		value += 7.5;
	if (!lostplace.first.empty())
		value += 7.5;
	if (!lostplace.second.empty())
		value += 2.5;
	if (!MayToGo.empty())
		value += 5;
	if (!information.empty())
		value += 40;
}