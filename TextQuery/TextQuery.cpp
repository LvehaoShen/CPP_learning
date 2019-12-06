#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map> 
#include<set>
#include<fstream>
#include<memory>
#include<sstream>
using namespace std;
string make_plural(int i, string str1, string str2);
void runQueries(ifstream& infile);
using line_no = vector<string>::size_type;
class QueryResult;
class TextQuery {
public:	
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult {
friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>>f) :
		sought(s), lines(p), file(f) {};

private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;
};
ostream& print(ostream& os, const QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s");
	for (auto num : *qr.lines)
		os << "\t(line" << num + 1 << ")"
		<< *(qr.file->begin() + num) << endl;
	return os;
}

TextQuery::TextQuery(ifstream& is) :file(new vector<string>)
{
	string text;
	while (getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			auto& lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}
QueryResult
TextQuery::query(const string& sought) const
{
	static shared_ptr<set<line_no>> nodata(new set <line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
int main()
{
	ifstream infile("data.txt");
	runQueries(infile);
	return 0;
}
void runQueries(ifstream& infile)
{
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
	return;
}
string make_plural(int i, string str1, string str2)
{
	if (i == 1)
		return str1;
	else
		return str1 + str2;
}
