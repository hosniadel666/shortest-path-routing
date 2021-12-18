#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

vector<int> cost;
vector<vector<pair<int, int>>> v;
map<int, char> m;

void apply_dijsktra(int nodes);
int load_input(std::string path);

int main()
{
  int nodes = load_input("./input.txt");

  apply_dijsktra(nodes);

  for (int i = 0; i < 15; i++)
  {
    if (cost[i] == 1e9)
    {
      cout << "\033[1;31"
           << "mImpossible router " << m[0] << " to reach router " << m[i]
           << "\033[0m\n";
    }
    else
    {

      cout << "Cost from router " << m[0] << " to router " << m[i] << " is " << cost[i] << endl;
    }
  }
  return 0;
}
int load_input(std::string path)
{
  int nodes;
  std::fstream newfile;
  std::string input;

  newfile.open(path, std::ios::in);
  if (newfile.is_open())
  {
    getline(newfile, input);
    nodes = stoi(input);
    v.clear();
    v.resize(nodes);

    for (int i = 0; i < nodes; i++)
    {
      m[i] = 'A' + i;
    }

    while (getline(newfile, input))
    {
      int arr[3], index = 0;

      std::string word;
      std::stringstream iss(input);

      while (iss >> word)
      {
        arr[index] = stoi(word);
        index++;
      }

      v[arr[0]].push_back(make_pair(arr[1], arr[2]));
      v[arr[1]].push_back(make_pair(arr[0], arr[2]));
    }

    newfile.close();
  }
  return nodes;
}

void apply_dijsktra(int nodes)
{
  priority_queue<pair<int, int>> q;
  q.push(make_pair(0, 0));

  for (int i = 1; i <= nodes; i++)
    cost.push_back(1e9);

  cost[0] = 0;
  while (q.size())
  {
    int cst = -1 * q.top().first, u = q.top().second;
    q.pop();

    if (cost[u] < cst)
      continue;

    for (int i = 0; i < v[u].size(); i++)
    {
      int d = v[u][i].first;
      int c = v[u][i].second;
      if (cst + c < cost[d])
      {
        cost[d] = cst + c;
        q.push(make_pair(-cost[d], d));
      }
    }
  }
}

