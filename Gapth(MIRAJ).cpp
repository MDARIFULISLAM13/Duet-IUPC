struct Dijkstra {
    const ll N=100005;
    vector<pair<ll, ll>> arr[N]; // Adjacency list
    ll dist[N];

    Dijkstra(ll n) {
        fill(dist, dist + n + 1, INF);
    }

    void add_edge(ll u, ll v, ll w) {
    arr[u].push_back({v, w});
    arr[v].push_back({u, w}); // Add reverse edge for undirected graph
    }

    void run(ll src) {
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            ll d = pq.top().first, u = pq.top().second;
            pq.pop();
            if (d > dist[u]) continue;
            for (auto &edge : arr[u]) {
                ll v = edge.first, w = edge.second;
                if (dist[v] > dist[u] + w)
                    dist[v] = dist[u] + w, pq.push({dist[v], v});
            }
        }
    }

    ll query(ll v) {
        return dist[v];
    }
};

