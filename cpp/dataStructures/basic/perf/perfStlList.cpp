#include "stdinc.h"
#include <list>
#include "Util.h"

void perfTest(int n) {
	list<int> lst(n);
	int perm[n+1];
	Util::genPerm(n,perm);

	cout << "perfTest " << n << endl;

	uint32_t t0 = Util::getTime();
	for (int i = 0; i < n; i++) lst.push_back(i);
	uint32_t t1= Util::getTime();
	double addBack = ((double) t1 - (double) t0)/n;
	cout << "appending to end: " << addBack << " us per operation\n";

	t0= Util::getTime();
	for (int i = 0; i < n; i++) lst.pop_front();
	t1= Util::getTime();
	double removeFront = ((double) t1 - (double) t0)/n;
	cout << "removing from front: " << removeFront << " us per operation\n";

	t0 = Util::getTime();
	for (int i = 0; i < n; i++) lst.push_back(1+perm[i]);
	t1= Util::getTime();
	double addBackRand = ((double) t1 - (double) t0)/n;
	cout << "appending to end in random order: " << addBack
	     << " us per operation\n";

	t0= Util::getTime();
	for (int i = 1; i <= n; i++) lst.pop_front();
	t1= Util::getTime();
	removeFront = ((double) t1 - (double) t0)/n;
	cout << "removing from front: " << removeFront << " us per operation\n";

	list<int>::iterator p;
	if (n <= 10000) {
		for (int i = 0; i < n; i++) lst.push_back(1+perm[i]);
		t0= Util::getTime();
		for (int i = 1; i <= n; i++) { lst.remove(i); }
		t1= Util::getTime();
		double removeByValue = ((double) t1 - (double) t0)/n;
		cout << "removing by value: " << removeByValue
		     << " us per operation\n";
	}

	for (int i = 0; i < n; i++) lst.push_back(1+perm[i]);
	int sum = 0;
	t0= Util::getTime();
	for (p = lst.begin(); p != lst.end(); p++) sum += *p;
	t1= Util::getTime();
	double sumInOrder = ((double) t1 - (double) t0)/n;
	cout << "summing in order: " << sumInOrder << " us per operation "
	     << sum << "\n";

	cout << endl;
}

main() {
	perfTest(100);
	perfTest(1000);
	perfTest(10000);
	perfTest(100000);
	perfTest(1000000);
}
