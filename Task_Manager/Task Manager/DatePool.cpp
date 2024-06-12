#include "DatePool.h"


int DatePool::find(const Date& d) const
{
	for (int i = 0; i < capacity; i++) {
		if (d == dates[i] && !isFree(i)) {
			return i;
		}
	}
	return -1;
}

bool DatePool::isFree(unsigned index) const
{
	return referenceCounts[index] == 0;
}

unsigned DatePool::getFreeIndex() const
{
	for (int i = 0; i < capacity; i++) {
		if (referenceCounts[i] == 0) return i;
	}
}

void DatePool::resize(unsigned newCap)
{
	Date* tempDates = new Date[newCap];
	int* tempReferences = new int[newCap] {0};

	for (int i = 0; i < capacity; i++) {
		tempDates[i] = dates[i];
		tempReferences[i] = referenceCounts[i];
	}

	capacity = newCap;
		
	delete[] dates;
	delete[] referenceCounts;
	dates = tempDates;
	referenceCounts = tempReferences;
}

void DatePool::free()
{
	delete[] dates;
	delete[] referenceCounts;
}

const Date* DatePool::getDate(const String& date, const String& taskName)
{
	Date temp(date);
	int index = find(temp);

	if (index != -1) {

		dates[index].addName(taskName); // the duplicate check is here

		referenceCounts[index]++;

		return &dates[index];
	}

	if (count == capacity) resize(capacity * 2);
	index = getFreeIndex();

	dates[index] = temp;
	count++;

	dates[index].addName(taskName);
	referenceCounts[index]++;

	return &dates[index];
}

void DatePool::removeDate(const Date& date, const String& taskName)
{
	for (int i = 0; i < capacity; i++) {
		if (date == dates[i] && referenceCounts[i]!=0) {
			referenceCounts[i]--;

			dates[i].removeName(taskName);

			if (!referenceCounts[i]) {
				count--;
			}
		}
	}
}

DatePool& DatePool::getInstance()
{
	static DatePool instance;
	return instance;
}

DatePool::~DatePool()
{
	free();
}

DatePool::DatePool() {
	capacity = 4;
	dates = new Date[capacity];
	referenceCounts = new int[capacity] {0};
}
