/** @file TestUiList.cpp
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#include "UiDlist.h"
#include "Utest.h"

void basicTests() {
	int n1 = 10; UiDlist l1(n1);

	Utest::assertTrue(l1.empty(), "initial list not empty");
	string s;
	cout << "writing empty list: " << l1.toString(s) << endl;

	for (int i = 1; i <= n1; i++)
		Utest::assertTrue(!l1.member(i),
			"member returns true on empty list");

	l1.addFirst(1);
	cout << "writing one item list: " << l1.toString(s) << endl;
	Utest::assertEqual(s, "[ a ]",
		"mismatch on adding first item");
	
	Utest::assertTrue(!l1.empty(),
		"list with one item reports empty");
	Utest::assertTrue(l1.member(1),
		"member 1 not reported in list");

	for (int i = 1; i <= n1; i += 2) l1.addLast(i);
	cout << "writing longer list: " << l1.toString(s) << endl;
	Utest::assertEqual(s, "[ a c e g i ]",
		"mismatch on list [ a c e g i ]");

	Utest::assertTrue(l1.member(5),
		"member 5 not reported in list");
	Utest::assertTrue(!l1.member(4),
		"non-member 4 is reported in list");

	l1.removeFirst();
	Utest::assertEqual(l1.toString(s), "[ c e g i ]",
		"mismatch on list [ c e g i ]");
	Utest::assertTrue(!l1.member(1),
		"non-member 1 is reported in list");
	l1.removeLast();
	Utest::assertEqual(l1.toString(s), "[ c e g ]",
		"mismatch on list [ c e g ]");

	l1.remove(5); 
	Utest::assertEqual(l1.toString(s), "[ c g ]",
		"mismatch on list [ c g ]");

	l1.removeLast();
	Utest::assertEqual(l1.toString(s), "[ c ]",
		"mismatch on list [ c ]");

	Utest::assertTrue(!l1.empty(),
		"non-empty list reported as empty");

	l1.removeFirst();
	Utest::assertEqual(l1.toString(s), "[ ]", "mismatch on list [ ]");

	Utest::assertTrue(l1.empty(), "empty list reported as non-empty");

	int n2 = 27; UiDlist l2(n2);
	l2.addFirst(1); l2.addFirst(2); l2.addFirst(3);
	cout << "writing numeric list: " << l2.toString(s) << endl;
	Utest::assertEqual(l2.toString(s), "[ 3 2 1 ]",
		"mismatch on list [ 3 2 1 ]");
}

/**
 *  Unit test for UiList data structure.
 */
main() {
	cout << "running basic tests\n";
	basicTests();
	cout << "basic tests passed\n";

	// add more systematic tests for each individual method
}
