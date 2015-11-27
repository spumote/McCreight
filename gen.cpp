#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define f first
#define s second
#define next qwertyusdfgh
#define read(x) scanf("%d", &x)
#define write(x) printf("%d ", x)
#define writeln(x) printf("%d\n", x)

const int maxN = 4000;
const int maxK = 1000;

//-------------------------------------------------------------------------------------------------

int main(int argc, char * argv[]) {
	ll x;
	asm("rdtsc" : "=A"(x));
	srand(x);

	int n = rand() % maxN + 1;
	int k = rand() % maxK + 1;
	if (argc > 1)
		n = atoi(argv[1]);
	if (argc > 2)
		k = atoi(argv[2]);

	cout << k << endl;
	for (int i = 0; i < n; i++)
		cout << char('a' + rand() % 1);
	cout << endl;	
	
	return 0;
}