#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(),v.end()
#define mod1 1000000007LL
#define YES cout<<"YES"<<nline
#define NO cout<<"NO"<<nline
#define mod2 998244353LL
#define ll long long
#define lld long double
#define ull unsigned long long
#define nline "\n"
#define maxbit(n) 31-__builtin_clz(n)
#define maxbitll(n) 63-__builtin_clzll(n)
#define minbit(n) __builtin_ctz(n) 
#define minbitll(n) __builtin_ctzll(n) 
#define bits(n) __builtin_popcount(n)
#define bitsll(n) __builtin_popcountll(n)
mt19937_64 rng((long long) chrono::steady_clock::now().time_since_epoch().count());
int rand(int L, int R){return L > R ? R : uniform_int_distribution<int>(L, R)(rng);}

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(deque <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(deque <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}


vector<int> randomPerm(int N){
	vector<int> P(N);
	for (int i = 0; i < N; i++) P[i] = i + 1;
	shuffle(P.begin(), P.end(), rng);
	return P;
}
vector<pair<int, int>> randomTree(int N){
	assert(1 <= N <= (int)1e7);
	vector<pair<int, int>> edges;
	auto nodes = randomPerm(N);
	for (int i = 1; i < N; i++) edges.push_back({nodes[i], nodes[rand(0, i - 1)]});
	return edges;
}
vector<pair<int, int>> longchainTree(int N){
	assert(1 <= N <= (int)1e7);
	vector<pair<int, int>> edges;
	auto nodes = randomPerm(N);
	for (int i = 1; i < N; i++) edges.push_back({nodes[i], nodes[rand(max(0,i-N/100-1), i - 1)]});
	return edges;
}
vector<pair<int, int>> binaryTree(int N){
	assert(1 <= N and N <= (int)1e7);
	auto nodes = randomPerm(N);
	vector<pair<int, int>> edges;
	for (int i = 1; i < N; i++){
		int p = (i + 1) >> 1;
		edges.push_back({nodes[i], nodes[p - 1]});
	}
	return edges;
}
vector<pair<int, int>> linearTree(int N){
	assert(1 <= N and N <= (int)1e7);
	auto nodes = randomPerm(N);
	vector<pair<int, int>> edges;
	for (int i = 1; i < N; i++) edges.push_back({nodes[i], nodes[i - 1]});
	return edges;
}
vector<pair<int, int>> startTree(int N){
	assert(1 <= N and N <= (int)1e7);
	auto nodes = randomPerm(N);
	vector<pair<int, int>> edges;
	int med = rand(0, N - 1);
	for (int i = 0; i < N; i++) if (i != med) edges.push_back({nodes[i], nodes[med]});
	return edges;
}
vector<pair<int, int>> anyTree(int N, string s = ""){
	int id = rand(0, 4);
	if (s == "BINARY" or (s == "" and id == 0)) return binaryTree(N);
	if (s == "LINEAR" or (s == "" and id == 1)) return linearTree(N);
	if (s == "STAR" or (s == "" and id == 2)) return startTree(N);
    if (s == "LONGCHAIN" or (s == "" and id == 3)) return longchainTree(N);
	return randomTree(N);
}

vector<pair<int, int>> testcaseTree(int t,int n){
	if(t==0){
        return linearTree(n);
    }
    if(t==1){
        return binaryTree(n);
    }
    if(t<4){
        return randomTree(n);
    }
    if(t<=6){
        return startTree(n);
    }
    return longchainTree(n);
}

long long int mod=1e9+7;

template <class T,class U,class X>
T modpow(T base, X exp, U modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

void dfs(int v,int p,vector<vector<int>>&adj,map<pair<int,int>,int>&mp,vector<int>&ans){
	if(p!=-1){
		ans[v]=(ans[p]*1LL*mp[{p,v}])%mod;
	}
	for(auto u:adj[v]){
		if(u!=p){
			dfs(u,v,adj,mp,ans);
		}
	}
}
 
vector<int> solve (int n, vector<vector<int> > relations) {
	vector<vector<int>>adj(n);
	map<pair<int,int>,int>mp;
	vector<int>ans(n,1);
	for(int i=0;i<n-1;i++){
		adj[relations[i][0]-1].push_back(relations[i][1]-1);
		adj[relations[i][1]-1].push_back(relations[i][0]-1);
		mp[{relations[i][0]-1,relations[i][1]-1}]=relations[i][2];
		mp[{relations[i][1]-1,relations[i][0]-1}]=modpow(relations[i][2]*1LL,mod-2LL,mod);
	}
	dfs(0,-1,adj,mp,ans);
	return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(9) << fixed;
    // freopen("haircut.in", "r", stdin);
	// freopen("haircut.out", "w", stdout);

    //then make a mersenne twister engine
    std::mt19937 engine(rng());
    //then the easy part... the distribution
    std::uniform_int_distribution<int> dist0(1, int(1e5));
    std::uniform_int_distribution<int> dist1(90000, int(1e5));
    std::uniform_int_distribution<int> dist2(int(150), int(200));
    std::uniform_int_distribution<int> dist3(int(1), int(1e9));
    std::uniform_int_distribution<int> dist4(int(-1e9), -1);
    std::uniform_int_distribution<long long> dist5(1LL,1e14*1LL);

    //then just generate the integer like this:
    for (int tc=0;tc<10;tc++) {
        string inputFileName = "in0"+to_string(tc)+".txt";
        string outputFileName = "out0"+to_string(tc)+".txt";
        string infilename = "in"+to_string(tc)+".txt";
        string outfilename = "out"+to_string(tc)+".txt";
        // string infilename=to_string(tc+1)+".txt";
        // Create and open input file
        // ifstream cii(infilename);
        // ifstream cio(outfilename);
        ofstream coi(inputFileName);
        ofstream coo(outputFileName);

        // vector<string>S;
        std::uniform_int_distribution<int> distn(max(1,(tc)*20000),(tc+1)*20000);
        int n=distn(engine);
        vector<int>rn(n);
        for(int i=0;i<n;i++){
            rn[i]=dist3(engine);
        }
        sort(all(rn));
        int lst=0;
        vector<vector<int>>queries;
        for(int i=0;i<n;i++){
            std::uniform_int_distribution<int> distr(1,2);
            int type=distr(engine);
            if(type==1){
                int x=dist3(engine);
                queries.push_back({type,rn[lst],x});
            }
            else{
                int txx=distr(engine);
                if(txx==1){
                    int l=dist3(engine);
                    int r=dist3(engine);
                    if(l>r){
                        swap(l,r);
                    }
                    queries.push_back({type,l,r});
                }
                else{
                    int txy=distr(engine);
                    if(txy==1)
                        queries.push_back({type, 1, 10000000});
                    else
                        queries.push_back({type, 1, 1000000000});
                }
            }
        }

        vector<long long>v={0};
        vector<long long>pre={0};
        vector<long long>ans;
        for(int i=0;i<n;i++){
            if(queries[i][0]==1){
                if(queries[i][1]==v.back()){
                    pre[pre.size()-1]+=queries[i][2];
                }
                else{
                    v.push_back(queries[i][1]);
                    pre.push_back(pre[pre.size()-1]+queries[i][2]*1LL);
                }
            }
            else{
                int up= lower_bound(v.begin(),v.end(),queries[i][2]*1LL)-v.begin();
                int lo= lower_bound(v.begin(),v.end(),queries[i][1]*1LL)-v.begin();
                lo--;
                if(up==int(v.size()) || v[up]>queries[i][2]){
                    up--;
                }
                ans.push_back(pre[up]-pre[lo]);
            }
        }
        coi<<n<<nline;
        for(int i=0;i<n;i++){
            coi<<queries[i][0]<<" "<<queries[i][1]<<" "<<queries[i][2]<<nline;
        }
        for(int i=0;i<ans.size();i++){
            coo<<ans[i]<<" ";
        }

        // ll l,r,k;
        // cii>>l>>r>>k;
        // vector<ll>v(k);
        // for(int i=0;i<k;i++){
        //     cii>>v[i];
        // }
        // vector<ll>ans(k);
        // for(int i=0;i<k;i++){
        //     cio>>ans[i];
        // }
        // coi<<l<<nline;
        // coi<<r<<nline;
        // coi<<k<<nline;
        // for(int i=0;i<k;i++){
        //     coi<<v[i];
        //     if(i!=k-1){
        //         coi<<" ";
        //     }
        //     else{
        //         coi<<nline;
        //     }
        // }
        // for(int i=0;i<k;i++){
        //     coo<<ans[i];
        //     if(i!=k-1){
        //         coo<<" ";
        //     }
        //     else{
        //         coo<<nline;
        //     }
        // }

        // uniform_int_distribution<int> distn(1,100);
        // ll k=distn(engine);
        // ll n,m;
        // uniform_int_distribution<int>distx(tc*10000,(tc+1)*10000);
        // n=distx(engine);
        // m=distx(engine);
        // coi<<n<<nline;
        // coi<<m<<nline;
        // coi<<k<<nline;
        // vector<int>v;
        // for(int i=0;i<n;i++){
        //     int y=dist3(engine);
        //     // string y;
        //     // cii>>y;
        //     v.push_back(y);
        //     coi<<y;
        //     if(i!=n-1){
        //         coi<<" ";
        //     }
        //     else{
        //         coi<<nline;
        //     }
        // }
        // vector<pair<int,int>>vp;
        // for(int i=0;i<m;i++){
        //     std::uniform_int_distribution<int> distc(int(1), int(n));
        //     int l=distc(engine);
        //     int r=distc(engine);
        //     if(r<l){
        //         swap(l,r);
        //     }
        //     vp.push_back({l,r});
        //     coi<<l<<" "<<r<<nline;
        // }
        // vector<int>pre(n+1,0);
        // for(int i=0;i<n;i++){
        //     pre[i+1]=pre[i]^(v[i]%(k+1));
        // }
        // for(int i=0;i<m;i++){
        //     int l=vp[i].first;
        //     int r=vp[i].second;
        //     coo<<int((pre[r]^pre[l-1])>0);
        //     if(i!=m-1){
        //         coo<<" ";
        //     }
        //     else{
        //         coo<<nline;
        //     }
        // }
        
        // cii.close();
        // cio.close();
        coo.close();
        coi.close();
    }

    return 0;
}
