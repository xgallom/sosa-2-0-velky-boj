#include <bits/stdc++.h>

using namespace std;

//-CONSTANTS-------------------------------------------------------------------

typedef long int Index;

//-FUNCTION-DECLARATIONS-------------------------------------------------------
vector<int> readData();
void writeResult(Index result);

void getBoundaries(const vector<int> &data, Index &first, Index &last);

Index getLeftIndex(const vector<int> &data, Index index, Index first);
Index getRightIndex(const vector<int> &data, Index index, Index last);

Index getIndexProductLeftRight(const vector<int> &data, Index index,
							   Index first, Index last);
Index getIndexProductRightLeft(const vector<int> &data, Index index,
							   Index first, Index last);
Index getIndexProduct(const vector<int> &data, Index index,
					  Index first, Index last);

Index getMaxIndexProduct(const vector<int> &data);

vector<string> split_string(string input_string);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main()
{
	vector<int> data = readData();

	Index result = getMaxIndexProduct(data);

	writeResult(result);

	return 0;
}

vector<int> readData()
{
	int dataSize;
	cin >> dataSize;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string dataStr;
	getline(cin, dataStr);

	vector<string> strVector = split_string(dataStr);

	vector<int> data;
	data.reserve(dataSize);

	for(const string &str : strVector)
		data.push_back(stoi(str));

	return data;
}

void writeResult(Index result)
{
	ofstream fout(getenv("OUTPUT_PATH"));

	fout << result << endl;

	fout.close();
}

void getBoundaries(const vector<int> &data, Index &first, Index &last)
{
	first = 0;
	last = data.size() - 1;

	while(first < last && data[first] <= data[first + 1])
		++first;

	while(last > first && data[last] <= data[last - 1])
		--last;
}

Index getLeftIndex(const vector<int> &data, const Index index, const Index first)
{
	Index leftIndex = index - 1;

	while(data[leftIndex] <= data[index]) {
		if(leftIndex == first)
			return 0;

		--leftIndex;
	}

	return leftIndex + 1;
}

Index getRightIndex(const vector<int> &data, const Index index,
					const Index last)
{
	Index rightIndex = index + 1;

	while(data[rightIndex] <= data[index]) {
		if(rightIndex == last)
			return 0;

		++rightIndex;
	}

	return rightIndex + 1;
}

Index getIndexProductLeftRight(const vector<int> &data, const Index index,
							   const Index first, const Index last)
{
	Index leftIndex, rightIndex;

	leftIndex = getLeftIndex(data, index, first);

	if(leftIndex)
		rightIndex = getRightIndex(data, index, last);
	else
		return 0;

	if(rightIndex)
		return leftIndex * rightIndex;

	return 0;
}

Index getIndexProductRightLeft(const vector<int> &data, const Index index,
							   const Index first, const Index last)
{
	Index leftIndex, rightIndex;

	rightIndex = getRightIndex(data, index, last);

	if(rightIndex)
		leftIndex = getLeftIndex(data, index, first);
	else
		return 0;

	if(leftIndex)
		return leftIndex * rightIndex;

	return 0;
}

Index getIndexProduct(const vector<int> &data, const Index index,
					  const Index first, const Index last)
{
	if(index < (last - first) >> 1)
		return getIndexProductLeftRight(data, index, first, last);
	else
		return getIndexProductRightLeft(data, index, first, last);
}

Index getMaxIndexProduct(const vector<int> &data)
{
	Index first, last;

	getBoundaries(data, first, last);

	Index maxIndexProduct = 0;

	for(Index index = first + 1; index < last; ++index) {
		Index indexProduct = getIndexProduct(data, index, first, last);

		if(indexProduct > maxIndexProduct)
			maxIndexProduct = indexProduct;
	}

	return maxIndexProduct;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
#include <bits/stdc++.h>

using namespace std;

//-CONSTANTS-------------------------------------------------------------------

typedef long int Index;

//-FUNCTION-DECLARATIONS-------------------------------------------------------
vector<int> readData();
void writeResult(Index result);

void getBoundaries(const vector<int> &data, Index &first, Index &last);

Index getLeftIndex(const vector<int> &data, Index index, Index first);
Index getRightIndex(const vector<int> &data, Index index, Index last);

Index getIndexProductLeftRight(const vector<int> &data, Index index,
							   Index first, Index last);
Index getIndexProductRightLeft(const vector<int> &data, Index index,
							   Index first, Index last);
Index getIndexProduct(const vector<int> &data, Index index,
					  Index first, Index last);

Index getMaxIndexProduct(const vector<int> &data);

vector<string> split_string(string input_string);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main()
{
	vector<int> data = readData();

	Index result = getMaxIndexProduct(data);

	writeResult(result);

	return 0;
}

vector<int> readData()
{
	int dataSize;
	cin >> dataSize;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string dataStr;
	getline(cin, dataStr);

	vector<string> strVector = split_string(dataStr);

	vector<int> data;
	data.reserve(dataSize);

	for(const string &str : strVector)
		data.push_back(stoi(str));

	return data;
}

void writeResult(Index result)
{
	ofstream fout(getenv("OUTPUT_PATH"));

	fout << result << endl;

	fout.close();
}

void getBoundaries(const vector<int> &data, Index &first, Index &last)
{
	first = 0;
	last = data.size() - 1;

	while(first < last && data[first] <= data[first + 1])
		++first;

	while(last > first && data[last] <= data[last - 1])
		--last;
}

Index getLeftIndex(const vector<int> &data, const Index index, const Index first)
{
	Index leftIndex = index - 1;

	while(data[leftIndex] <= data[index]) {
		if(leftIndex == first)
			return 0;

		--leftIndex;
	}

	return leftIndex + 1;
}

Index getRightIndex(const vector<int> &data, const Index index,
					const Index last)
{
	Index rightIndex = index + 1;

	while(data[rightIndex] <= data[index]) {
		if(rightIndex == last)
			return 0;

		++rightIndex;
	}

	return rightIndex + 1;
}

Index getIndexProductLeftRight(const vector<int> &data, const Index index,
							   const Index first, const Index last)
{
	Index leftIndex, rightIndex;

	leftIndex = getLeftIndex(data, index, first);

	if(leftIndex)
		rightIndex = getRightIndex(data, index, last);
	else
		return 0;

	if(rightIndex)
		return leftIndex * rightIndex;

	return 0;
}

Index getIndexProductRightLeft(const vector<int> &data, const Index index,
							   const Index first, const Index last)
{
	Index leftIndex, rightIndex;

	rightIndex = getRightIndex(data, index, last);

	if(rightIndex)
		leftIndex = getLeftIndex(data, index, first);
	else
		return 0;

	if(leftIndex)
		return leftIndex * rightIndex;

	return 0;
}

Index getIndexProduct(const vector<int> &data, const Index index,
					  const Index first, const Index last)
{
	if(index < (last - first) >> 1)
		return getIndexProductLeftRight(data, index, first, last);
	else
		return getIndexProductRightLeft(data, index, first, last);
}

Index getMaxIndexProduct(const vector<int> &data)
{
	Index first, last;

	getBoundaries(data, first, last);

	Index maxIndexProduct = 0;

	for(Index index = first + 1; index < last; ++index) {
		Index indexProduct = getIndexProduct(data, index, first, last);

		if(indexProduct > maxIndexProduct)
			maxIndexProduct = indexProduct;
	}

	return maxIndexProduct;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
