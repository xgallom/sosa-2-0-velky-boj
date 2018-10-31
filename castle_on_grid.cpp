#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

//-CONSTANTS-------------------------------------------------------------------

static const int Invalid = -1;

static const int
		DirectionNone  = 0x0,
		DirectionRight = 0x1,
		DirectionDown  = 0x2,
		DirectionLeft  = 0x4,
		DirectionUp    = 0x8;


static const char ObstacleSymbol = 'X';

//-STRUCT-DECLARATIONS---------------------------------------------------------

typedef vector<string> Space;
typedef int Distance;
typedef int Direction;

struct Coords {
	int y, x;

	bool operator ==(const Coords &r) const;

	friend
	Coords operator +(const Coords &l, const Coords &r);
};

struct ProcessQueueEntry {
	Coords coords;
	Distance distance;
	Direction direction;
};

struct  PathMap : public vector<vector<int>> {
	explicit PathMap(Coords bounds);

	bool hasEntry(Coords coords) const;

	int &operator [](Coords coords);
	const int &operator [](Coords coords) const;
};

typedef deque<ProcessQueueEntry> ProcessQueue;

//-FUNCTION-DECLARATIONS-------------------------------------------------------

void readInput(Space &space, Coords &bounds, Coords &start, Coords &target);
void writeResult(int result);

char symbolAt(const Space &space, Coords coords);

void addProcessQueueEntry(ProcessQueue &processQueue,
						  Coords coords, Direction direction,
						  const ProcessQueueEntry &parent);
void addPathMapNode(const Space &space, Coords bounds, PathMap &pathMap,
					ProcessQueue &processQueue,
					const ProcessQueueEntry &entry);
int getMinimumMoves(const Space &space, Coords bounds, Coords start,
					Coords target);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main()
{
	Space space;
	Coords bounds, start, target;

	readInput(space, bounds, start, target);

	int result = getMinimumMoves(space, bounds, start, target);

	writeResult(result);

	return 0;
}

void readInput(Space &space, Coords &bounds, Coords &start, Coords &target)
{
	int size;
	cin >> size;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	bounds = Coords{size, size};

	space = Space(size);

	for(string &row : space)
		getline(cin, row);

	string coordsStr;
	getline(cin, coordsStr);

	vector<string> coordsStrVector = split_string(coordsStr);

	start = Coords{
			stoi(coordsStrVector[0]),
			stoi(coordsStrVector[1])
	};

	target = Coords{
			stoi(coordsStrVector[2]),
			stoi(coordsStrVector[3])
	};
}

void writeResult(int result)
{
	ofstream fout(getenv("OUTPUT_PATH"));

	fout << result << "\n";

	fout.close();
}

char symbolAt(const Space &space, Coords coords)
{
	return space[coords.y][coords.x];
}

void addProcessQueueEntry(ProcessQueue &processQueue,
						  Coords coords, Direction direction,
						  const ProcessQueueEntry &parent)
{
	ProcessQueueEntry entry = {
			coords,
			parent.distance,
			direction};

	if(parent.direction & direction)
		processQueue.push_front(entry);
	else {
		++entry.distance;
		processQueue.push_back(entry);
	}
}

void addPathMapNode(const Space &space, Coords bounds, PathMap &pathMap,
					ProcessQueue &processQueue,
					const ProcessQueueEntry &entry)
{
	const Coords
			coordsRight = entry.coords + Coords{ 0,  1},
			coordsDown  = entry.coords + Coords{ 1,  0},
			coordsLeft  = entry.coords + Coords{ 0, -1},
			coordsUp    = entry.coords + Coords{-1,  0};

	cerr << "[" << entry.coords.y << "," << entry.coords.x << "]: "
		 << entry.distance << ", " << entry.direction << endl;
	pathMap[entry.coords] = entry.distance;

	if(coordsRight.x < bounds.x &&
	   symbolAt(space, coordsRight) != ObstacleSymbol)
		addProcessQueueEntry(processQueue, coordsRight,
							 DirectionRight, entry);
	if(coordsDown.y < bounds.y &&
	   symbolAt(space, coordsDown) != ObstacleSymbol)
		addProcessQueueEntry(processQueue, coordsDown,
							 DirectionDown, entry);
	if(coordsLeft.x >= 0 &&
	   symbolAt(space, coordsLeft) != ObstacleSymbol)
		addProcessQueueEntry(processQueue, coordsLeft,
							 DirectionLeft, entry);
	if(coordsUp.y >= 0 &&
	   symbolAt(space, coordsUp) != ObstacleSymbol)
		addProcessQueueEntry(processQueue, coordsUp,
							 DirectionUp, entry);
}

int getMinimumMoves(const Space &space, Coords bounds, Coords start,
					Coords target)
{
	PathMap pathMap(bounds);

	ProcessQueue processQueue;
	processQueue.push_back(
			ProcessQueueEntry{target, 0, DirectionNone}
	);

	while(true) {
		ProcessQueueEntry entry = processQueue.front();
		processQueue.pop_front();

		if(!pathMap.hasEntry(entry.coords) ||
		   entry.distance <= pathMap[entry.coords]
				)
			addPathMapNode(space, bounds, pathMap,
						   processQueue, entry);

		if(entry.coords == start) {
			return entry.distance;
		}
	}
}

bool Coords::operator ==(const Coords &r) const
{
	return x == r.x && y == r.y;
}

Coords operator +(const Coords &l, const Coords &r)
{
	return Coords{l.y + r.y, l.x + r.x};
}

PathMap::PathMap(Coords bounds)
{
	resize(bounds.y);

	for(vector<int> &row : *this) {
		row.resize(bounds.x);

		for(int &cell : row)
			cell = Invalid;
	}
}

bool PathMap::hasEntry(Coords coords) const
{
	return (*this)[coords] != Invalid;
}

int &PathMap::operator [](Coords coords)
{
	return vector<vector<int>>::operator[](coords.y)[coords.x];
}

const int &PathMap::operator [](Coords coords) const
{
	return vector<vector<int>>::operator[](coords.y)[coords.x];
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
