const ll N=4e5+5;
bool prim[N];
void seive() {  //  N*log^2(n)
    memo(prim, 0); 
    prim[0] = prim[1] = 1;
    for(ll i=2; i*i<=N; i++) {
        if(!prim[i]) {
            for(ll j=i*i; j<=N; j+=i)
                prim[j]=1; 
        }
    }
}

const int N = 1e8 + 5;
bitset<N> is_prime;//  N*log^2(n)
void sieve(int n) {// Optimized Sieve
    is_prime.set();
    is_prime[0] = is_prime[1] = false; 
    for (int i = 4; i <= n; i += 2) is_prime[i] = false; 
    for (int i = 3; i * i <= n; i += 2) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                is_prime[j] = false;
            }
        }
    }
}

using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) 
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}
bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) { // to find prime in k(log^2 n)
    if (n < 2) return false; 
    if (n % 2 == 0) return (n == 2);
    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    vector<u64> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};// k
    for (u64 a : bases) {
        if (a >= n) break;  // Skip if base is greater than n
        if (check_composite(n, a, d, s)) return false;
    }
    return true;
}

const int N = 1e7 + 5;
vector<int> primes;// all primes
int spf[N]; // Smallest Prime Factor for all number
void linearSieve(int n) {// O(n) wow
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {  // i is prime
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || p * i > n) break;
            spf[p * i] = p;
        }
    }
}

vector<int> getFactors(int x) {// long (x)
    vector<int> factors;// only use if spf is there 
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}

vector<bool> is_prime;
void segmentedSieve(ll L,ll R) {
    ll lim = sqrt(R) + 1;// O(sqrt(R)+(R-L)log^2(R);
    vector<bool> mark(lim + 1, true);
    vector<ll> primes;
    for (ll i = 2; i <= lim; i++) {
    if (mark[i]) {
    primes.push_back(i);
    for (ll j = i * i; j <= lim; j += i) mark[j]=0;
    }}
    vector<bool> is_prime(R - L + 1,1);
    for (ll p:primes) {
        for (ll j = max(p * p, (L + p - 1) / p * p); j <= R; j += p) {
            is_prime[j - L] = 0;
        }
    }
    if (L == 1) is_prime[0] = 0;
    // for (ll i = 0; i < R - L + 1; i++) {
    //     if (is_prime[i]) cout << i + L << "\n";
    // }
}
//segmentedSieve(10, 100);  // Finds all primes between 10 and 100


