#include <stdio.h>
#include <stdlib.h>

enum Query {
	Push = 1,
	Pop,
	Print
};

struct Entry {
	int value;
	struct Entry *next;
};

struct Maximum {
	struct Entry *entry;
	struct Maximum *next;
};

struct Stack {
	struct Entry *values;
	struct Maximum *maximums;
};

static struct Entry ZeroEntry = {
		0, NULL
};

static struct Maximum ZeroMaximum = {
		&ZeroEntry,
		NULL
};

static struct Stack Stack = {
		&ZeroEntry,
		&ZeroMaximum
};

struct Entry *createEntry(int value)
{
	struct Entry
			*newHead = (struct Entry *) malloc(sizeof(struct Entry));

	newHead->value = value;
	newHead->next = Stack.values;
	Stack.values = newHead;

	return newHead;
}

void pushEntry(struct Entry *entry)
{
	struct Maximum
			*newHead = (struct Maximum *) malloc(sizeof(struct Maximum));

	newHead->entry = entry;
	newHead->next = Stack.maximums;
	Stack.maximums = newHead;
}

void addEntry(int value)
{
	struct Entry *entry = createEntry(value);

	if(entry->value > Stack.maximums->entry->value)
		pushEntry(entry);
}

void deleteEntry()
{
	struct Entry *oldHead = Stack.values;

	Stack.values = oldHead->next;

	free(oldHead);
}

void popEntry()
{
	struct Maximum *oldHead = Stack.maximums;

	Stack.maximums = oldHead->next;

	free(oldHead);
}

void removeEntry(void)
{
	if(Stack.maximums->entry == Stack.values)
		popEntry();

	deleteEntry();
}

int main(void)
{
	int count;
	scanf("%d", &count);

	while(count--) {
		int query;
		scanf("%d", &query);

		switch(query) {
			case Push: {
				int value;
				scanf("%d", &value);

				addEntry(value);

				break;
			}

			case Pop:
				removeEntry();
				break;

			case Print:
				printf("%d\n", Stack.maximums->entry->value);
				break;
		}
	}

	return 0;
}
