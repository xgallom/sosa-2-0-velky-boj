#include <bits/stdc++.h>

using namespace std;

//-FUNCTION-DECLARATIONS-------------------------------------------------------

set<int> readSet(int count);
void printResult(int result);

bool iterate(const set<int>::const_iterator &stand, set<int>::const_iterator *walk,
			 const set<int>::const_iterator &end, int range);
int hackerlandRadioTransmitters(set<int> data, int range);

//-MAIN------------------------------------------------------------------------

int main()
{
	int count, range;
	cin >> count >> range;

	set<int> data = readSet(count);

	int result = hackerlandRadioTransmitters(data, range);

	printResult(result);

	return 0;
}

//-FUNCTION-DEFINITIONS--------------------------------------------------------

set<int> readSet(int count)
{
	set<int> set;

	while(count--) {
		int value;

		cin >> value;

		set.insert(value);
	}

	return set;
}

void printResult(int result)
{
	ofstream fout(getenv("OUTPUT_PATH"));

	fout << result << "\n";

	fout.close();
}

bool iterate(const set<int>::const_iterator &stand, set<int>::const_iterator *walk,
			 const set<int>::const_iterator &end, int range)
{
	while(*stand >= **walk - range) {
		if(++(*walk) == end) {
			return false;
		}
	}

	return true;
}

int hackerlandRadioTransmitters(set<int> data, int range)
{
	if(!data.size())
		return 0;

	int count = 0;

	set<int>::const_iterator
			lastCovered = data.cbegin(),
			firstUncovered = data.cbegin(),
			end = data.cend();

	bool isRunning = true;
	while(isRunning) {
		isRunning = iterate(firstUncovered, &lastCovered, end, range);

		firstUncovered = lastCovered;
		--lastCovered;
		++count;

		if(isRunning)
			isRunning = iterate(lastCovered, &firstUncovered, end, range);
	}

	return count;
}

