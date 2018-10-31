#include <bits/stdc++.h>

using namespace std;

typedef int NodeIndex;
typedef set<NodeIndex> System;
typedef list<System> Systems;
typedef Systems::iterator SystemIndex;
typedef unordered_map<NodeIndex, SystemIndex> Nodes;

SystemIndex createSystem(Nodes &nodes, Systems &systems, const System &systemValue)
{
	SystemIndex system = systems.insert(systems.end(), systemValue);

	for(NodeIndex nodeIndex : *system)
		nodes[nodeIndex] = system;

	return system;
}

SystemIndex addNodeToSystem(Nodes &nodes, SystemIndex system, NodeIndex node)
{
	nodes[node] = system;
	(*system).insert(node);

	return system;
}

SystemIndex mergeSystems(Nodes &nodes, Systems &systems, SystemIndex system1, SystemIndex system2)
{
	SystemIndex left, right;

	if((*system1).size() > (*system2).size()) {
		left = system1;
		right = system2;
	}
	else {
		left = system2;
		right = system1;
	}

	for(NodeIndex nodeIndex : *right)
		addNodeToSystem(nodes, left, nodeIndex);

	systems.erase(right);

	return left;
}

SystemIndex mergeNodesSystems(Nodes &nodes, Systems &systems, NodeIndex leftNode, NodeIndex rightNode)
{
	Nodes::iterator
			leftNodeIterator = nodes.find(leftNode),
			rightNodeIterator = nodes.find(rightNode);

	if(leftNodeIterator != nodes.end() && rightNodeIterator != nodes.end()) {
		if(leftNodeIterator->second == rightNodeIterator->second)
			return leftNodeIterator->second;
		else
			return mergeSystems(nodes, systems, leftNodeIterator->second, rightNodeIterator->second);
	}
	else if(leftNodeIterator != nodes.end())
		return addNodeToSystem(nodes, leftNodeIterator->second, rightNode);
	else if(rightNodeIterator != nodes.end())
		return addNodeToSystem(nodes, rightNodeIterator->second, leftNode);
	else
		return createSystem(nodes, systems, {leftNode, rightNode});
}

vector<int> componentsInGraph(vector<vector<int>> lines)
{
	if(!lines.size())
		return {0, 0};

	Systems systems;
	Nodes nodes;

	int systemMin, systemMax = 0;

	for(const vector<int> &line : lines) {
		NodeIndex
				leftNode = line[0],
				rightNode = line[1];

		cerr << leftNode << " -> " << rightNode << endl;
		SystemIndex mergedSystem = mergeNodesSystems(nodes, systems, leftNode, rightNode);

		int systemSize = mergedSystem->size();

		if(!systemMax || systemMin > systemSize)
			systemMin = systemSize;

		if(!systemMax || systemMax < systemSize)
			systemMax = systemSize;
	}

	return {systemMin, systemMax};
}

void writeResult(const vector<int> &result)
{
	ofstream fout(getenv("OUTPUT_PATH"));

	for(int value : result)
		fout << value << ' ';

	fout.close();
}

int main()
{
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<vector<int>> gb(n);
	for (int gb_row_itr = 0; gb_row_itr < n; gb_row_itr++) {
		gb[gb_row_itr].resize(2);

		for (int gb_column_itr = 0; gb_column_itr < 2; gb_column_itr++) {
			cin >> gb[gb_row_itr][gb_column_itr];
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	vector<int> result = componentsInGraph(gb);

	writeResult(result);

	return 0;
}
