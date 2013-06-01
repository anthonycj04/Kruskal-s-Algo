#include <iostream>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

class Graph{
private:
	unordered_map<string, int> edges;
	unordered_set<char> vertices;
public:
	void insertEdge(char start, char end, int weight){
		vertices.insert(start);
		vertices.insert(end);
		string string1, string2;
		if (edges.find(string1.append(1, start).append(1, end)) == edges.end() && 
			edges.find(string2.append(1, end).append(1, start)) == edges.end())
			edges.insert(make_pair(string1, weight));
	}

	unordered_set<char> getVertices(){
		return vertices;
	}

	unordered_map<string, int> getEdges(){
		return edges;
	}
};

typedef struct _Node{
	int rank;
	char parent;
} Node;

class DisjointSet{
private:
	unordered_map<char, Node> nodes;
public:
	void makeSet(char c){
		if (nodes.find(c) == nodes.end()){
			Node node;
			node.rank = 0;
			node.parent = c;
			nodes.insert(make_pair(c, node));
		}
	}

	char findSet(char x){
		auto nodeX = nodes.find(x);
		if (nodeX != nodes.end()){
			if (nodeX->second.parent != x){
				nodeX->second.parent = findSet(nodeX->second.parent);
				return nodeX->second.parent;
			}
			else
				return x;
		}
		else{
			cout << "error in findSet" << endl;
			exit(1);
		}
		return '@';
	}

	void link(char x, char y){
		auto nodeX = nodes.find(x);
		auto nodeY = nodes.find(y);
		if (nodeX != nodes.end() && nodeY != nodes.end()){
			if (nodeX->second.rank > nodeY->second.rank)
				nodeY->second.parent = x;
			else{
				nodeX->second.parent = y;
				if (nodeX->second.rank == nodeY->second.rank)
					nodeY->second.rank++;
			}
		}
		else{
			cout << "error in link" << endl;
			exit(1);
		}
	}

	void dUnion(char u, char v){
		link(findSet(u), findSet(v));
	}
};

void kruskal(Graph graph){
	DisjointSet disjointSet;
	unordered_set<string> minimumSpanningTree;
	for (auto it = graph.getVertices().begin(); it != graph.getVertices().end(); it++)
		disjointSet.makeSet(*it);
	multimap<int, string> tempMap;
	for (auto it = graph.getEdges().begin(); it != graph.getEdges().end(); it++)
		tempMap.insert(make_pair(it->second, it->first));
	for (auto it = tempMap.begin(); it != tempMap.end(); it++){
		char char1 = it->second.c_str()[0];
		char char2 = it->second.c_str()[1];
		if (disjointSet.findSet(char1) != disjointSet.findSet(char2)){
			string tempString;
			minimumSpanningTree.insert(tempString.append("(").append(1, char1).append(", ").append(1, char2).append(")"));
			disjointSet.dUnion(char1, char2);
		}
	}
	for (auto it = minimumSpanningTree.begin(); it != minimumSpanningTree.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main(){
	cout << "Kruskal's algorithm for graph in lecture" << endl;
	Graph G1;
	G1.insertEdge('a', 'b', 10);
	G1.insertEdge('a', 'c', 12);
	G1.insertEdge('b', 'c', 9);
	G1.insertEdge('b', 'd', 8);
	G1.insertEdge('c', 'e', 3);
	G1.insertEdge('c', 'f', 1);
	G1.insertEdge('d', 'e', 7);
	G1.insertEdge('d', 'g', 8);
	G1.insertEdge('d', 'h', 5);
	G1.insertEdge('e', 'f', 3);
	G1.insertEdge('f', 'h', 6);
	G1.insertEdge('g', 'h', 9);
	G1.insertEdge('g', 'i', 2);
	G1.insertEdge('h', 'i', 11);
	kruskal(G1);

	cout << "Kruskal's algorithm for graph in book" << endl;
	Graph G2;
	G2.insertEdge('a', 'b', 4);
	G2.insertEdge('a', 'h', 8);
	G2.insertEdge('b', 'c', 8);
	G2.insertEdge('b', 'h', 11);
	G2.insertEdge('c', 'd', 7);
	G2.insertEdge('c', 'f', 4);
	G2.insertEdge('c', 'i', 2);
	G2.insertEdge('d', 'e', 9);
	G2.insertEdge('d', 'f', 14);
	G2.insertEdge('e', 'f', 10);
	G2.insertEdge('f', 'g', 2);
	G2.insertEdge('g', 'h', 1);
	G2.insertEdge('g', 'i', 6);
	G2.insertEdge('h', 'i', 7);
	kruskal(G2);

	return 0;
}

/*
MST-KRUSKAL(G, w)
	A = NULL
	foreach vertex v in G.V
		MAKE-SET(v)
	sort the edges of G.E into nondecreasing order by w
	foreach (u, v) taken from the sorted list
		if (FIND-SET(u) != FIND-SET(v))
			A = A + {(u, v)}
			UNION(u, v)
	return A
*/
/*
Kruskal's algorithm for graph in lecture
(c, f) (g, i) (c, e) (d, h) (f, h) (b, d) (d, g) (a, b)
Kruskal's algorithm for graph in book
(g, h) (c, i) (f, g) (a, b) (c, f) (c, d) (a, h) (d, e)
*/ 
