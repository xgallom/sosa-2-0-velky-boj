#include<iostream>
#include<vector>
using namespace std;

//-CONSTANTS-------------------------------------------------------------------

static const bool
		Horizontal = false,
		Vertical = true;

static const char
		TargetSymbol = 'd';

enum Command {
	Clean = 0,
	Right,
	Down,
	Left,
	Up
};

//-STRUCTURE-DECLARATIONS------------------------------------------------------

struct Coords {
	int y, x;

	bool longerSide() const;
	int manhattan() const;

	bool operator ==(const Coords &r) const;
	bool operator < (const Coords &r) const;

	bool operator ! () const;

	friend
	Coords operator -(const Coords &l, const Coords &r);
};

//-FUNCTION-DECLARATIONS-------------------------------------------------------

Coords readPosition();
vector<string> readSpace();

void execute(Command cmd);
Coords closestTargetDelta(const Coords &position, const vector<string> &space);
Command nextMove(const Coords &position, const vector<string> &space);

//-MAIN------------------------------------------------------------------------

int main()
{
	Coords position = readPosition();
	vector<string> space = readSpace();

	Command nextCmd = nextMove(position, space);

	execute(nextCmd);

	return 0;
}

Coords readPosition()
{
	Coords position;
	cin >> position.y >> position.x;

	return position;
}

vector<string> readSpace()
{
	vector<string> space;

	for(int i = 0; i < 5; ++i) {
		string row;
		cin >> row;

		space.push_back(row);
	}

	return space;
}

//-IMPLEMENTATION--------------------------------------------------------------

void execute(Command cmd)
{
	string cmdStr;

	switch(cmd) {
		case Clean: cmdStr = "CLEAN"; break;
		case Right: cmdStr = "RIGHT"; break;
		case Down : cmdStr = "DOWN" ; break;
		case Left : cmdStr = "LEFT" ; break;
		case Up   : cmdStr = "UP"   ; break;
	}

	cout << cmdStr << endl;
}

Coords closestTargetDelta(const Coords &position, const vector<string> &space)
{
	const Coords boundary = {
			static_cast<int>(space.size()),
			static_cast<int>(space.size())
	};

	Coords smallestDelta;

	Coords target;
	for(target.y = 0; target.y < boundary.y; ++target.y) {
		for(target.x = 0; target.x < boundary.x; ++target.x) {
			if(space[target.y][target.x] == TargetSymbol) {
				Coords delta = target - position;

				if(!target || delta < smallestDelta)
					smallestDelta = delta;
			}
		}
	}

	return smallestDelta;
}

Command nextMove(const Coords &position, const vector<string> &space)
{
	Coords targetDelta = closestTargetDelta(position, space);

	Command directionCommand;

	if(!targetDelta)
		directionCommand = Clean;
	else if(targetDelta.longerSide() == Vertical)
		directionCommand = targetDelta.y < 0 ? Up : Down;
	else
		directionCommand = targetDelta.x < 0 ? Left : Right;

	return directionCommand;
}

//-STRUCT-IMPLEMENTATION-------------------------------------------------------

bool Coords::longerSide() const
{
	return abs(x) < abs(y) ? Vertical : Horizontal;
}

int Coords::manhattan() const
{
	return abs(y) + abs(x);
}

bool Coords::operator ==(const Coords &r) const
{
	return y == r.y && x == r.x;
}

bool Coords::operator <(const Coords &r) const
{
	return manhattan() < r.manhattan();
}

bool Coords::operator !() const
{
	return !y && !x;
}

Coords operator -(const Coords &l, const Coords &r)
{
	return Coords{l.y - r.y, l.x - r.x};
}
