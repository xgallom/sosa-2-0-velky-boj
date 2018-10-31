#include <bits/stdc++.h>

using namespace std;


//-CONSTANTS-------------------------------------------------------------------

static const char
//-TAGS-parsing----------------------------------------------------------------
		NotFoundString[] = "Not Found!",
		LongStringDelim = '\"',
		WordEndDelim = ' ',
		TagStartDelim = '<',
		TagEndDelim = '>',
		LineEndDelim = '\n',
		StringEndDelim = '\0',
		PropertyAssignDelim = '=',
		TagCloseDelim = '/',

//-QUERY-parsing---------------------------------------------------------------
		QueryPropertyDelim = '~',
		QueryTagsDelim = '.';

//-TAGS-property-parsing-------------------------------------------------------
static const array<char, 3> PropertiesEndDelims = {
		TagEndDelim,
		LineEndDelim,
		StringEndDelim
};


//-CLASS-DECLARATIONS----------------------------------------------------------

class Tag;

typedef unordered_map<string, string> Properties;
typedef unordered_map<string, unique_ptr<Tag>> Tags;

//-TAGS-INTERFACE-class-TagInterface-------------------------------------------
class TagInterface {
public:
	virtual ~TagInterface() = default;

	virtual string property(const string &key) const = 0;
	virtual const TagInterface *tag(const string &key) const = 0;
};

//-TAGS-IMPLEMENTATION-class-Tag-----------------------------------------------
class Tag : public TagInterface {
	Tag(Tag *parent = nullptr, Properties properties = Properties());
public:
	string property(const string &key) const final;
	const TagInterface *tag(const string &key) const final;

	Tag *parent() const;

	Tag *addTag(const string &name, const Properties &properties);

	static unique_ptr<Tag> CreateRoot();

private:
	Tag *m_parent;
	Properties m_properties;
	Tags m_tags;
};

//-TAGS-IMPLEMENTATION-class-InvalidTag----------------------------------------
class InvalidTag : public TagInterface {
	InvalidTag() = default;

public:
	string property(const string &key) const final;
	const TagInterface *tag(const string &key) const final;

	static const TagInterface *SharedInstance();
};


//-FUNCTION-DECLARATIONS-------------------------------------------------------

//-function-templates----------------------------------------------------------
template<typename T, typename U>
bool in(const T &value, const U &collection)
{
	for(const auto &entry : collection) {
		if(entry == value)
			return true; // found
	}

	return false; // not found
}

//-CONSOLE-input/output--------------------------------------------------------
vector<string> readLines(int count);
void writeResult(const vector<string> &result);

//-TAGS-character-parsing------------------------------------------------------
char parseChar(string::const_iterator &index,
			   const string::const_iterator &end);
char peekChar(string::const_iterator &index,
			  const string::const_iterator &end);
string parseWord(string::const_iterator &index,
				 const string::const_iterator &end);

//-TAGS-property-parsing-------------------------------------------------------
pair<string, string> parseProperty(string::const_iterator &index,
								   const string::const_iterator &end);
Properties parseProperties(string::const_iterator &index,
						   const string::const_iterator &end);

//-TAGS-tag-parsing------------------------------------------------------------
Tag *parseTag(string::const_iterator &index,
			  const string::const_iterator &end,
			  Tag *tagHead);

//-TAGS-line-parsing-----------------------------------------------------------
Tag *parseLine(const string &line, Tag *tag);

//-TAGS-tree-generating--------------------------------------------------------
unique_ptr<const TagInterface> generateTree(const vector<string> &data);

//-QUERY-parsing/execution-----------------------------------------------------
vector<string> split(const string &str, char delim);
vector<string> parseQueries(const vector<string> &queries,
							const TagInterface *tagRoot);


//-FUNCTION-DEFINITIONS--------------------------------------------------------

int main()
{
	int dataCount, queryCount;
	cin >> dataCount >> queryCount;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	const auto tags = readLines(dataCount);
	const auto tagRoot = generateTree(tags);

	const auto queries = readLines(queryCount);
	const auto result = parseQueries(queries, tagRoot.get());

	writeResult(result);

	return 0;
}

//-CONSOLE-input/output--------------------------------------------------------

vector<string> readLines(int count)
{
	vector<string> lines(static_cast<size_t>(count));

	for(auto &line : lines)
		getline(cin, line);

	return lines;
}

void writeResult(const vector<string> &result)
{
	for(const auto &line : result)
		cout << line << endl;
}

//-TAGS-character-parsing------------------------------------------------------

char parseChar(string::const_iterator &index,
			   const string::const_iterator &end)
{
	if(index != end)
		return *index++;

	return StringEndDelim;
}

char peekChar(string::const_iterator &index,
			  const string::const_iterator &end)
{
	if(index != end)
		return *index;

	return StringEndDelim;
}

string parseWord(string::const_iterator &index,
				 const string::const_iterator &end)
{
	string word;

	auto started = false, longMode = false;

	while(true) {
		const auto c = parseChar(index, end);

		switch(c) {
			case LongStringDelim:
				if(started && longMode)
					return word; // end of string
				else {
					longMode = true; // start of string
					started = true;
				}
				break;

			case WordEndDelim:
			case TagEndDelim:
				if(started) {
					if(longMode)
						word.push_back(c); // part of string
					else
						return word; // end of word
				}
				break;

			case LineEndDelim:
			case StringEndDelim:
				return word; // end of line

			case TagStartDelim:
			case PropertyAssignDelim:
			case TagCloseDelim:
				if(started)
					word.push_back(c); // part of word
				break;

			default:
				word.push_back(c); // part of word
				started = true;
				break;
		}
	}
}

//-TAGS-property-parsing-------------------------------------------------------

pair<string, string> parseProperty(string::const_iterator &index,
								   const string::const_iterator &end)
{
	const auto name  = parseWord(index, end);
	const auto value = parseWord(index, end);

	return make_pair(name, value);
}

Properties parseProperties(string::const_iterator &index,
						   const string::const_iterator &end)
{
	Properties properties;

	while(!in(peekChar(index, end), PropertiesEndDelims))
		properties.emplace(parseProperty(index, end)); // ! end of properties

	return properties;
}

//-TAGS-tag-parsing------------------------------------------------------------

Tag *parseTag(string::const_iterator &index,
			  const string::const_iterator &end,
			  Tag *tagHead)
{
	if(peekChar(index, end) == TagCloseDelim)
		return tagHead->parent(); // closing tag
	else {
		const auto tagName = parseWord(index, end);
		const auto properties = parseProperties(index, end);

		return tagHead->addTag(tagName, properties); // opening tag
	}
}

//-TAGS-line-parsing-----------------------------------------------------------

Tag *parseLine(const string &line, Tag *headTag)
{
	const auto end = line.cend();
	auto index = line.cbegin();

	if(parseChar(index, end) == TagStartDelim)
		return parseTag(index, end, headTag); // valid line
	else
		return headTag; // invalid line
}

//-TAGS-tree-generating--------------------------------------------------------

unique_ptr<const TagInterface> generateTree(const vector<string> &lines)
{
	auto rootTag = Tag::CreateRoot();

	auto headTag = rootTag.get();

	for(const auto &line : lines)
		headTag = parseLine(line, headTag);

	return rootTag;
}

//-QUERY-parsing/execution-----------------------------------------------------

vector<string> split(const string &str, char delim)
{
	vector<std::string> tokens;
	string token;
	istringstream tokenStream(str);

	while(getline(tokenStream, token, delim))
		tokens.push_back(token);

	return tokens;
}

vector<string> parseQueries(const vector<string> &queries,
							const TagInterface *tagRoot)
{
	vector<string> data;

	for(const auto &query : queries) {
		const auto tagsAndProperty = split(query, QueryPropertyDelim);

		const auto tags = split(tagsAndProperty[0], QueryTagsDelim);

		auto tag = tagRoot;
		for(const auto &tagName : tags)
			tag = tag->tag(tagName);

		data.push_back(tag->property(tagsAndProperty[1]));
	}

	return data;
}


//-TAGS-IMPLEMENTATION-class-Tag-----------------------------------------------

Tag::Tag(Tag *parent, Properties properties)
		: m_parent(parent)
		, m_properties(properties)
{}

string Tag::property(const string &key) const
{
	const auto property = m_properties.find(key);
	if(property != m_properties.cend())
		return property->second;

	return NotFoundString;
}

const TagInterface *Tag::tag(const string &key) const
{
	const auto tag = m_tags.find(key);
	if(tag != m_tags.cend())
		return tag->second.get();

	return InvalidTag::SharedInstance();
}

Tag *Tag::parent() const
{
	return m_parent;
}

Tag *Tag::addTag(const string &name, const Properties &properties)
{
	auto newTag = new Tag(this, properties);

	m_tags[name] = unique_ptr<Tag>(newTag);

	return newTag;
}

unique_ptr<Tag> Tag::CreateRoot()
{
	return unique_ptr<Tag>(new Tag);
}


//-TAGS-IMPLEMENTATION-class-InvalidTag----------------------------------------

const TagInterface *InvalidTag::SharedInstance()
{
	static const InvalidTag instance;

	return &instance;
}

string InvalidTag::property(const string &key) const
{
	return NotFoundString;
}

const TagInterface *InvalidTag::tag(const string &key) const
{
	return SharedInstance();
}
