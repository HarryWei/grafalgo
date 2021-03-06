#include "stdinc.h"
#include "TreeMap.h"
#include "Util.h"

void basicTests() {
	int n = 13; string s;
	TreeMap map(n);
	int *perm = new int[n+1];
	Util::genPerm(n,perm);
	cout << "putting in key order\n";
	for (int i = 1; i <= n; i++) {
		map.put(i,perm[i]);
		cout << map.toString(s) << endl;
	}
	cout << "getting in key order\n";
	for (int i = 1; i <= n; i++) {
		cout << map.get(i) << " ";
	}
	cout << endl;
	cout << "changing values in key order\n";
	for (int i = 1; i <= n; i++) {
		map.put(i,randint(n+1,5*n));
		cout << map.toString(s) << endl;
	}
	cout << "getting in key order\n";
	for (int i = 1; i <= n; i++) {
		cout << map.get(i) << " ";
	}
	cout << endl;
	cout << "removing in key order\n";
	for (int i = 1; i <= n; i++) {
		map.remove(i);
		cout << map.toString(s) << endl;
	}
	cout << endl;
}


main() {
	basicTests();
}
