#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

struct vertex {
	vector<vertex*> alist;
	string name;
	vertex(string s) : name(s){}
};

class Graph {
public:
	typedef map<string, vertex*>gmap;
	gmap agraph;
	void add_vertex(const string&);
	void add_edge(const string& form, const string& to);
	bool check_connected();
	void DFS(string, vector<vertex*>&);
};

void Graph::add_vertex(const string& name) {
	gmap::iterator iter = agraph.find(name);
	if (iter == agraph.end())
	{
		vertex* x;
		x = new vertex(name);
		agraph[name] = x;
		return;
	}
	cout << "\nDuplicate vertex key: " << name;
}

void Graph::add_edge(const string& from, const string& to) {
	vertex* f = (agraph.find(from)->second);
	vertex* t = (agraph.find(to)->second);
	f->alist.push_back(t);
	t->alist.push_back(f);
}

void Graph::DFS(string source, vector<vertex*>& visited) {
	vertex* v = agraph.find(source)->second;
	visited.push_back(v);
	for (auto iter = v->alist.begin(); iter != v->alist.end(); iter++) {
		if (find(visited.begin(), visited.end(), *iter) == visited.end()) DFS((*iter)->name, visited);
	}
}

bool Graph::check_connected() {
	vector<vertex*> visited;
	DFS(agraph.begin()->first, visited);
	return (visited.size() == agraph.size());
}

