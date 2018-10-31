#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//-CONSTANTS-------------------------------------------------------------------

static const bool
		Horizontal = false,
		Vertical = true;

static const int
		Width = 3,
		Height = 3;

static const char
		ObstacleSymbol = '#',
		TargetSymbol   = 'e';

enum Command {
	Forward = 0,
	Right,
	Backwards,
	Left
};

//-STRUCTURE-DECLARATIONS------------------------------------------------------

struct Coords {
	int y, x;

	bool longerSide() const;

	bool operator !() const;

	friend
	Coords operator -(const Coords &l, const Coords &r);
};

typedef vector<char> Row;
typedef vector<Row> Space;

//-FUNCTION-DECLARATIONS-------------------------------------------------------

char symbolAt(const Space &space, Coords coords);

Space readSpace();

Coords findTargetDelta(const Space &space);
Command findExplorationDirection(const Space &space);
Command findTargetDirection(const Coords &delta);
Command getNextCommand(const Space &space);
void execute(Command cmd);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main() {
	int player;
	cin >> player;

	cin.get(); // newline

	Space space = readSpace();

	Command command = getNextCommand(space);

	execute(command);

	return 0;
}

char symbolAt(const Space &space, Coords coords)
{
	return space[coords.y][coords.x];
}

Space readSpace()
{
	Space space(Height);
	Coords coords;

	for(coords.y = 0; coords.y < Height; ++coords.y) {
		Row row(Width);

		for(coords.x = 0; coords.x < Width; ++coords.x) {
			row[coords.x] = cin.get();
		}

		cin.get(); // newline

		space[coords.y] = row;
	}

	for(Row row : space) {
		for(char symbol : row)
			cerr << symbol;
		cerr << endl;
	}

	return space;
}

Coords findTargetDelta(const Space &space)
{
	static const Coords position = {1, 1};
	Coords target;

	for(target.y = 0; target.y < Height; ++target.y) {
		for(target.x = 0; target.x < Width; ++target.x) {
			if(symbolAt(space, target) == TargetSymbol)
				return target - position;
		}
	}

	return {0, 0};
}

Command findExplorationDirection(const Space &space, const vector<Command> &preferedDirections)
{
	static const Coords
			ForwardCoords = {0, 1},
			RightCoords   = {1, 2},
			BackCoords    = {2, 1},
			LeftCoords    = {1, 0};

	for(Command preferedDirection : preferedDirections) {
		Coords directionCoords;

		switch(preferedDirection) {
			case Forward  : directionCoords = ForwardCoords; break;
			case Right    : directionCoords = RightCoords  ; break;
			case Backwards: directionCoords = BackCoords   ; break;
			case Left     : directionCoords = LeftCoords   ; break;
		}

		if(symbolAt(space, directionCoords) != ObstacleSymbol)
			return preferedDirection;
	}

	return Left;
}

Command findTargetDirection(const Space &space, const Coords &delta)
{
	vector<Command>
			verticalDirection,
			horizontalDirection;

	if(delta.y < 0)
		verticalDirection = {Forward, Backwards};
	else
		verticalDirection = {Backwards, Forward};

	if(delta.x < 0)
		horizontalDirection = {Left, Right};
	else
		horizontalDirection = {Right, Left};

	if(delta.longerSide() == Vertical)
		return findExplorationDirection(space, {
				verticalDirection[0], horizontalDirection[0],
				verticalDirection[1], horizontalDirection[1]
		});
	else
		return findExplorationDirection(space, {
				horizontalDirection[0], verticalDirection[0],
				horizontalDirection[1], verticalDirection[1]
		});
}

Command getNextCommand(const Space &space)
{
	Coords targetDelta = findTargetDelta(space);

	if(!targetDelta)
		return findExplorationDirection(space, {Forward, Right, Backwards, Left});

	return findTargetDirection(space, targetDelta);
}

void execute(Command cmd)
{
	string cmdStr;

	switch(cmd) {
		case Forward  : cmdStr = "UP"   ; break;
		case Right    : cmdStr = "RIGHT"; break;
		case Backwards: cmdStr = "DOWN" ; break;
		case Left     : cmdStr = "LEFT" ; break;
	}

	cout << cmdStr << endl;
}

bool Coords::longerSide() const
{
	return abs(y) >= abs(x) ? Vertical : Horizontal;
}

bool Coords::operator !() const
{
	return !y && !x;
}

Coords operator -(const Coords &l, const Coords &r)
{
	return Coords{l.y - r.y, l.x - r.x};
}
