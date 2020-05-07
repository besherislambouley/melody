/*
 * first we build a graph , connect every two melodies by an edge if you can change from one to another 
 * we use floyd warshall to fill dis[i][j] between every ( i , j ) -> the minimum length of a path between them 
 * now I'll explain a none 100 points solution then we will try to improve it 
 * suppose dp [i][j] -> you are at the i'th postion and you are playing the j'th note , when you are moving from postion i -> i+1 you try to change the current note to one of the notes with dis [ current note ] [ new note ] = 1 , or stay at the same note , this solution costs O ( LN^2 ) 
 * now we notice that we dont need to memorise what the current note is if you always make sure that Ord [i] = j 
 * that means instead of moving from the i'th postion to the i+1 you can just choose the next note and jump to the first occurrence after i such that Ord [ new i ] = j & dis [ Ord[i] ][j] <= new i - i 
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int N , M , Sz , G ;
vi Ord , Occur [109] ;
string s [109] ;
int dis [109][109] ;
int Check ( string a , string b ) {
	int Cost = 0 ;
	for ( int i = 0 ; i < Sz ; i ++ ) {
		Cost += ( a [i] != b [i] ) ;
	}
	return ( Cost <= G ) ;
}
int nxt ( int Who , int Id ) {
	int Idx = lb ( Occur [Who] .begin() , Occur [Who] .end() , Id ) - Occur [Who] .begin() ;
	if ( Idx == Occur [Who] .size() ) return -1 ;
	return Occur [Who][Idx] ;
}
int Dp [100009] ;
int Bt ( int Pos ) { 
	if ( Pos == M ) return 0 ;
	int &Ret = Dp [Pos] ;
	if ( Ret != -1 ) return Ret ;
	Ret = Bt ( M ) + M - Pos - 1  ;
	for ( int i = 0 ; i < N ; i ++ ) {
		int Id = nxt ( i , Pos + max ( 1 , dis [ Ord [Pos] ][i] ) ) ;
		if ( Id == -1 ) C ;
		Ret = min ( Ret , Bt ( Id ) + Id - Pos - 1 ) ;
	}
	return Ret ;
}
void find ( int st , int en , int x ) {
	while ( st != en ) {
		for ( int i = 0 ; i < N ; i ++ ) {
			if ( dis [i][en] == dis [st][en] - 1 && dis [st][i] == 1 ) {
				st = i ;
				break ;
			}
		}
		cout << st + 1 << " "  ; 
		x -- ;
	}
	for ( int i = 0 ; i < x ; i ++ ) cout << en + 1 << " " ;
	
}
void Path ( int Pos ) {
	if ( Pos == M ) return ;
	int Ans = Bt ( Pos ) ;
	int Ret1= Bt ( M ) + M - Pos - 1 ;
	if ( Ret1 == Ans ) {
		for ( int i = 0 ; i < M - Pos - 1 ; i ++ ) cout << Ord [Pos] + 1 << " " ;
		Path ( M ) ;
		return ;
	}
	for ( int i = 0 ; i < N ; i ++ ) {
		int Id = nxt ( i , Pos + max ( 1 , dis [ Ord [Pos] ][i] ) ) ;
		if ( Id == -1 ) C ;
		int Ret2 = Bt ( Id ) + Id - Pos - 1 ;
		if ( Ret2 == Ans ) {
			find ( Ord [Pos] , i , Id - Pos ) ;
			Path ( Id ) ;
			return ;
		}
	}
}
int main () {
	mem ( Dp , -1 ) ;
	cin >> N >> Sz >> G ;
	for ( int i = 0 ; i < N ; i ++ ) cin >> s [i] ;
	for ( int i = 0 ; i < N ; i ++ ) {
		for ( int j = 0 ; j < N ; j ++ ) {
			if ( i == j ) C ;
			dis [i][j] = 1e9 ; 
		}
	}
	for ( int i = 0 ; i < N ; i ++ ) {
		for ( int j = 0 ; j < N ; j ++ ) {
			if ( i == j ) C ;
			if ( Check ( s [i] , s [j] ) ) {
				dis [i][j] = 1 ;
			}
		}
	}
	for ( int k = 0 ; k < N ; k ++ ) {
		for ( int i = 0 ; i < N ; i ++ ) {
			for ( int j = 0 ; j < N ; j ++ ) {
				dis [i][j] = min ( dis [i][j] , dis [i][k] + dis [k][j] ) ;
			}
		}
	}
	cin >> M ;
	Ord .resize ( M ) ;
	for ( int i = 0 ; i < M ; i ++ ) {
		cin >> Ord [i] , Ord [i] -- ;
		Occur [ Ord [i] ] .pb ( i ) ;
	}
	pi Mn = { 1e9 , 1e9 }  ;
	for ( int i = 0 ; i < N ; i ++ ) {
		int Id = nxt ( i , 0 ) ;
		if ( Id == -1 ) C ; 
		Mn = min ( Mn , { Bt ( Id ) + Id , i } ) ;
	}
	cout << Mn.fi << endl ; 
	int Id = nxt ( Mn.se , 0 ) ;
	for ( int i = 0 ; i <= Id ; i ++ ) cout << Mn.se + 1 << " " ;
	Path ( Id ) ;
	cout << endl ; 
}
