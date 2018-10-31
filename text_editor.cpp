#include <bits/stdc++.h>
using namespace std;

//-CONSTANTS-------------------------------------------------------------------

enum OperationId {
	Append = 1,
	Delete,
	Print,
	Undo
};

//-CLASS-DECLARATIONS----------------------------------------------------------

class Data;

//-OPERATION-INTERFACE
class Operation {
public:
	explicit Operation(bool addToHistory);
	virtual ~Operation() = default;

	virtual void execute(Data &data) = 0;
	virtual void undo(Data &data);

	bool addToHistory() const;

private:
	bool m_addToHistory;
};

//-DATA-CLASS
class Data {
public:
	string &data();

	void execute(unique_ptr<Operation> operation);
	void undoLast();

private:
	string m_data;
	stack<unique_ptr<Operation>> m_operationHistory;
};

//-OPERATIONS
class AppendOperation : public Operation {
public:
	AppendOperation(string str);

	void execute(Data &data) final;
	void undo(Data &data) final;

private:
	string m_str;
};

class DeleteOperation : public Operation {
public:
	DeleteOperation(int size);

	void execute(Data &data) final;
	void undo(Data &data) final;

private:
	int m_size;
	string m_str;
};

class PrintOperation : public Operation {
public:
	PrintOperation(int pos);

	void execute(Data &data) final;

private:
	int m_pos;
};

class UndoOperation : public Operation {
public:
	UndoOperation();

	void execute(Data &data) final;
};

//-FUNCTION-DECLARATIONS-------------------------------------------------------

unique_ptr<Operation> readOperation(string line);
void executeOperations(Data &data);

//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main() {
	Data data;

	executeOperations(data);

	return 0;
}

unique_ptr<Operation> readOperation(string line)
{
	stringstream ss(line);

	int operationId;

	ss >> operationId;
	ss.ignore(numeric_limits<streamsize>::max(), ' ');

	Operation *operation;

	switch(operationId) {
		case Append: {
			string data;
			getline(ss, data);

			operation = new AppendOperation(data);
			break;
		}

		case Delete: {
			int deleteSize;
			ss >> deleteSize;

			operation = new DeleteOperation(deleteSize);
			break;
		}

		case Print: {
			int printPosition;
			ss >> printPosition;

			operation = new PrintOperation(printPosition);
			break;
		}

		case Undo:
			operation = new UndoOperation();
	}

	return unique_ptr<Operation>(operation);
}

void executeOperations(Data &data)
{
	int operationsSize;
	cin >> operationsSize;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while(operationsSize--) {
		string line;
		getline(cin, line);

		data.execute(readOperation(line));
	}
}

//-MEMBER-FUNCTION-DEFINITIONS-------------------------------------------------

Operation::Operation(bool addToHistory)
		: m_addToHistory(addToHistory)
{}

void Operation::undo(Data &)
{}

bool Operation::addToHistory() const
{
	return m_addToHistory;
}

string &Data::data()
{
	return m_data;
}

void Data::execute(unique_ptr<Operation> operation)
{
	operation->execute(*this);
	cerr << m_data << endl;

	if(operation->addToHistory())
		m_operationHistory.push(move(operation));
}

void Data::undoLast()
{
	m_operationHistory.top()->undo(*this);
	m_operationHistory.pop();
}

AppendOperation::AppendOperation(string str)
		: Operation(true)
		, m_str(move(str))
{}

void AppendOperation::execute(Data &data)
{
	data.data().append(m_str);
}

void AppendOperation::undo(Data &data)
{
	string &dataStr = data.data();

	dataStr.erase(dataStr.end() - m_str.size(), dataStr.end());
}

DeleteOperation::DeleteOperation(int size)
		: Operation(true)
		, m_size(size)
{}

void DeleteOperation::execute(Data &data)
{
	string &dataStr = data.data();

	string::iterator eraseBegin = dataStr.end() - m_size,
			eraseEnd = dataStr.end();


	m_str = string(eraseBegin, eraseEnd);

	dataStr.erase(eraseBegin, eraseEnd);
}

void DeleteOperation::undo(Data &data)
{
	data.data().append(m_str);
}

PrintOperation::PrintOperation(int pos)
		: Operation(false)
		, m_pos(pos - 1) // Indexing from 0
{}

void PrintOperation::execute(Data &data)
{
	cout << data.data()[m_pos] << endl;
}

UndoOperation::UndoOperation()
		: Operation(false)
{}

void UndoOperation::execute(Data &data)
{
	data.undoLast();
}
