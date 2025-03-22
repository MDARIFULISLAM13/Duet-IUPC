
struct DSU {
    vector<ll> parent;
    // passing array just in function(ll arr[]), in call(arr)
    DSU(ll n) {
        parent.resize(n);
        for (ll i = 0; i < n; i++) parent[i] = i; // make all them own there p
    }
    int path(ll v) {
        if (parent[v] == v) return v;
        return parent[v] = path(parent[v]);  // Path compression
    }
    void connect(ll u, ll v) {
        parent[path(u)] = path(v);  // Union by root
    }
    bool query(ll u, ll v) {
        return path(u) == path(v); // ans are the p same 
    }
};

struct BIT {
    vector<ll> bit;
    ll n;  

    BIT(ll n) {
        this->n = n;
        bit.assign(n + 1, 0); // 1-based indexing
    }

    void update(ll ind, ll val) {
        ind++;  // Convert 0-based index to 1-based
        while (ind <= n) {
            bit[ind] += val;
            ind += ind & -ind;
        }
    }

    ll query(ll ind) {
        ll sum = 0;
        while (ind > 0) {
            sum += bit[ind];
            ind -= ind & -ind;
        }
        return sum;
    }

    ll query_range(ll l, ll r) {  // reminder removing front part
        return query(r) - query(l);
    }
};

struct SegmentTree {
    vector<ll> a, seg;

    SegmentTree(ll n) {
        a.resize(n);
        seg.resize(4 * n);
    }

    void build(ll i, ll s, ll e) {  // Function to build the segment tree
        if (s == e) { seg[i] = a[s]; return;}
        ll mid = s + (e - s) / 2;
        build(2 * i + 1, s, mid); 
        build(2 * i + 2, mid + 1, e);
        seg[i] = max(seg[2 * i + 1], seg[2 * i + 2]); 
    }


    ll query(ll l, ll r, ll i, ll s, ll e) {     // Query function to get the maximum in the range [l, r]
        if (s >= l && e <= r) { return seg[i]; }
        if (s > r || e < l) { return -1e18;}
        ll mid = s + (e - s) / 2;
        ll left = query(l, r, 2 * i + 1, s, mid);  
        ll right = query(l, r, 2 * i + 2, mid + 1, e); 
        return max(left, right); 
    }


    void update(ll ind, ll val, ll i, ll s, ll e) {  // Update function to set the value at index ind
        if (s == e) { a[ind] = val;  seg[i] = val;  return; }
        ll mid = s + (e - s) / 2;
        if (ind <= mid) { update(ind, val, 2 * i + 1, s, mid); }
        else { update(ind, val, 2 * i + 2, mid + 1, e); }
        seg[i] = max(seg[2 * i + 1], seg[2 * i + 2]);  
    }
};

