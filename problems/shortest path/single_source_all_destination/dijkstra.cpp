int v;
vector<pari<int, int>> adj[MAX_V]; // <pos, edge_dist>

vector<int> dijkstra(int src)
{
  vector<int> dist<v, INF>;
  dist[src] = 0;
  priority_queue<pair<int, int>> pq;
  pq.push(make_pari(0, src));
  
  while (!pq.empty())
  {
    int cur_dist = -pq.top().first;
    int cur_pos = pq.top().second;
    pq.pop();
    
    if (dist[cur_pos] < cur_dist) continue;
    
    for (int i = 0; i < adj[cur_pos].size(); i++)
    {
        int next_pos = adj[cur_pos][i].first;
        int next_dist = cur_dist+ adj[cur_pos][i].second;
        if (next_dist < dist[next_pos])
        {
          dist[next_pos] = next_dist;
          pq.push(make_pair(-next_dist, next_pos));
        }
    }
    return dist;
  }
}
