/*
	分支定界求解最路线
	by enginning
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#define Bound  1500
#define Length 50

using namespace std;
void load_matrix(string filename, vector<vector<int>> &matrix)
{
	vector<int> tmp;
	string line;
	ifstream in(filename);
	regex pat_regex("[[:digit:]]+");
	while (getline(in, line))
	{
		for (sregex_iterator it(line.begin(), line.end(), pat_regex), end_it; it != end_it; ++it)
		{
			tmp.push_back(stoi(it->str()));
		}
		matrix.push_back(tmp);
		tmp.clear();
	}
}

void floyd(vector<vector<int>> &graph, vector<vector<int>> &graph2, vector<vector<int>> &Path)
{
	int count = graph.size();
	for (int k = 0; k < count; k++)
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++)
			{
				if (graph[i][j]>graph[i][k] + graph[k][j]){
					graph[i][j] = graph[i][k] + graph[k][j];
					graph2[i][j] = graph2[i][k] + graph2[k][j];
					Path[i][j] = k;
				}
			}
}

void print(int start, int end, vector<vector<int>> &Path)
{
	int mid = Path[start][end];
	if (mid == end)
	{
		cout << start + 1 << "->";
		return;
	}
	print(start, mid, Path);
	print(mid, end, Path);
}

int main(int argc, char const *argv[])
{
	vector<vector<int>> dist, cost, Path; //存储距离，花费，路径
	int MAX = 9999;
	time_t start = clock();
	//读取数据
	string dist_filename = "m1.txt", cost_filename = "m2.txt";
	vector<vector<int>> mindist, mincost;
	load_matrix(dist_filename, dist);
	load_matrix(cost_filename, cost);

	vector<int> temp;
	for (int i = 0; i < Length; i++)
		temp.push_back(i);
	for (int i = 0; i < Length; i++)
		Path.push_back(temp);
	//使用floyed算法更新任意两点间的最短距离，同时记录花费和路径
	floyd(dist, cost, Path);		

	int mid, cost_a;
	for (int i = 1; i < Length - 1; i++)
	{
		if (dist[0][i] + dist[i][Length - 1] < MAX && cost[0][i] + cost[i][Length - 1] < Bound)
		{
			MAX = dist[0][i] + dist[i][Length - 1];
			cost_a = cost[0][i] + cost[i][Length - 1];
			mid = i;
		}
	}
	//打印路径
	cout << "by eng 190115" << "\nFinal result:" << "\nBest path: [";
	print(0, mid, Path);
	print(mid, Length - 1, Path);
	cout << Length << "]" <<endl;
	//打印花费
	cout << "Minimum distance:" << MAX << "\nMinimum cost:" << cost_a << endl;
	cout << "Time cost:" << (clock() - start) / double(CLOCKS_PER_SEC) << "s" << endl;
	system("pause");
	return 0;
}
