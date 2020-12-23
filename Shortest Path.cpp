#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
int Max_Distance = 1000001;
class Path {
public:
	int from;
	vector<int> to;
	vector<int> weight;
	Path() :from(0) {}
	Path(int _from) :from(_from) {}
};
class Node {
public:
	int data;
	int predecessor;
	int distance;
	bool status;
	Node() :data(0), predecessor(0), distance(0), status(true) {}
	Node(int _data, int _predecessor, float _distance) :data(_data), predecessor(_predecessor), distance(_distance), status(true) {}
};
class Dijkstra {
private:
	vector<Path> path;
	vector<Node> qu;
	bool exist(const vector<Node>& qu, int key) {
		for (int i = 0; i < qu.size(); ++i) {
			if (qu[i].data == key) return true;
		}
		return false;
	}
	int check(const vector<Path>& path, int key) {
		for (int i = 0; i < path.size(); ++i) {
			if (path[i].from == key)return i;
		}
		return -1;
	}
	void goPath(int index, int to, int _weight) {
		for (int i = 0; i < qu.size(); ++i) {
			if (qu[i].data == to && qu[i].status) {
				if ((qu[index].distance + _weight) < qu[i].distance) {
					qu[i].predecessor = qu[index].data;
					qu[i].distance = qu[index].distance + _weight;
				}
				return;
			}
		}
	}
	int getMin() {
		int index;
		int min = Max_Distance;
		for (int i = 0; i < qu.size(); ++i) {
			if (qu[i].status && qu[i].distance < min) {
				min = qu[i].distance;
				index = i;
			}
		}
		if (min != Max_Distance)	return index;
		return -1;
	}
public:
	Dijkstra() {}
	void addEdge(int _from, int _to, float _weight) {
		int index = check(path, _from);
		if (index == -1) {
			Path temp;
			temp.from = _from;
			temp.to.push_back(_to);
			temp.weight.push_back(_weight);
			path.push_back(temp);
		}
		else {
			path[index].to.push_back(_to);
			path[index].weight.push_back(_weight);
		}
		Node Ntemp;
		if (!exist(qu, _from)) {
			Ntemp.data = _from;
			Ntemp.distance = Max_Distance;
			Ntemp.predecessor = -1;
			qu.push_back(Ntemp);
		}
		if (!exist(qu, _to)) {
			Ntemp.data = _to;
			Ntemp.distance = Max_Distance;
			Ntemp.predecessor = -1;
			qu.push_back(Ntemp);
		}
	}
	void execute(int begin) {
		for (int i = 0; i < path.size(); ++i) {		//find the first time
			if (path[i].from == begin) {
				int index;
				for (int j = 0; j < qu.size(); ++j) {
					if (qu[j].data == path[i].from) {
						qu[j].status = false;
						qu[j].distance = 0;
						index = j;
						break;
					}
				}
				for (int j = 0; j < path[i].to.size(); ++j) {
					goPath(index, path[i].to[j], path[i].weight[j]);
				}
			}
			break;
		}
		bool flag = true;
		while (flag) {
			flag = false;
			int index = getMin();
			if (index != -1) {
				flag = true;
				qu[index].status = false;
				for (int i = 0; i < path.size(); ++i) {
					if (path[i].from == qu[index].data) {
						for (int j = 0; j < path[i].to.size(); ++j) {
							goPath(index, path[i].to[j], path[i].weight[j]);
						}
						break;
					}
				}
			}
		}
	}
	void print(int end) {
		vector<int> a;
		int b;
		for (int i = 0; i < qu.size(); ++i) {
			if (qu[i].data == end) {
				b = qu[i].distance;
				break;
			}
		}
		for (int i = 0; i < qu.size(); ++i) {
			if (qu[i].data == end) {
				a.push_back(end);
				end = qu[i].predecessor;
				if (end == -1) {
					break;
				}
				else i = -1;
			}
		}
		printf("%d", a[a.size() - 1]);
		for (int i = a.size() - 2; i >= 0; --i) {
			printf(" %d", a[i]);
		}
		printf("\n%d", b);
	}
};
int main(void) {
	int m, n, begin, end;
	cin >> m >> n >> begin >> end;
	Dijkstra graph;
	int from, to;
	float weight;
	for (int i = 0; i < n; ++i) {
		cin >> from >> to >> weight;
		graph.addEdge(from, to, weight);
	}
	graph.execute(begin);
	graph.print(end);
	return 0;
}
