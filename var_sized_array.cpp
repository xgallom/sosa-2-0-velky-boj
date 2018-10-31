#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//-STRUCTURE-DECLARATIONS------------------------------------------------------

struct Query {
	int index, offset;
};

//-FUNCTION-DECLARATIONS-------------------------------------------------------

vector<vector<int>> readIndex(int indexSize);
vector<int> readOffset(int offsetSize);
vector<Query> readQueries(int queriesSize);
void processQuery(const vector<vector<int>> &index, const Query &query);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main() {
	int indexSize, queriesSize;

	cin >> indexSize >> queriesSize;

	vector<vector<int>> index = readIndex(indexSize);
	vector<Query> queries = readQueries(queriesSize);

	for(const Query &query : queries)
		processQuery(index, query);

	return 0;
}

vector<vector<int>> readIndex(int indexSize)
{
	vector<vector<int>> array;
	array.reserve(indexSize);

	while(indexSize--) {
		int offsetSize;

		cin >> offsetSize;

		array.push_back(readOffset(offsetSize));
	}

	return array;
}

vector<int> readOffset(int offsetSize)
{
	vector<int> offset;
	offset.reserve(offsetSize);

	while(offsetSize--) {
		int value;

		cin >> value;

		offset.push_back(value);
	}

	return offset;
}

vector<Query> readQueries(int queriesSize)
{
	vector<Query> queries;
	queries.reserve(queriesSize);

	while(queriesSize--) {
		Query query;

		cin >> query.index >> query.offset;

		queries.push_back(query);
	}

	return queries;
}

void processQuery(const vector<vector<int>> &index, const Query &query)
{
	cout << index[query.index][query.offset] << endl;
}
