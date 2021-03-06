/** @file ListSet.h
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#ifndef LISTSET_H
#define LISTSET_H

#include "Adt.h"

namespace grafalgo {

typedef int32_t alist;

/** Header file for data structure representing a collection of lists
 *  defined over index values 1,2,... Each index can be stored in at
 *  most one list. Lists are also numbered 1,2,...
 */
class ListSet : public Adt {
public:		ListSet(int=26,int=5);
		~ListSet();

	// common methods
	void	clear();
	void	resize(int siz) { resize(siz,siz); }
	void	resize(int,int);
	void	expand(int siz) { expand(siz,siz); }
	void	expand(int,int);
	void	copyFrom(const ListSet&);

	// access items in list
	index	next(index) const;	
	index	first(alist) const;
	index	last(alist) const;	

	// predicates
	bool	validList(index) const;
	bool	member(index) const;
	bool	empty(alist) const;

	// modifiers
	void	addLast(index, alist);
	void	addFirst(index,alist);
	index	removeFirst(alist);

	// input/output
	string  toString() const;
	string  list2string(alist) const;
private:
	int	nlst;			// lists 1..nlst
	/** header for a single list */
	struct listhdr {
		alist head, tail;
	};
	listhdr	*lh;			// array of list headers
	index	*nxt;			// next[i] is successor of i

	void	makeSpace(int,int);
	void	freeSpace();
};

/** Determine if a list number is valid.
 *  @return true if lst is a valid list number.
 */
inline bool ListSet::validList(alist lst) const {
	return 1 <= lst && lst <= nlst;
}

/** Get the first index in a list.
 *  @param lst is a list in the collection
 *  @return the first index on lst, or 0 if the list is empty
 */
inline index ListSet::first(alist lst) const {
	assert(validList(lst)); return lh[lst].head;
}

/** Get the last index in a list.
 *  @param lst is a list in the collection
 *  @return the last index on lst, or 0 if the list is empty
 */
inline index ListSet::last(alist lst) const {
	assert(validList(lst)); return lh[lst].tail;
}

/** Determine if a list is empty.
 *  @param lst is a list in the collection
 *  @return true if the list is empty, else false
 */
inline bool ListSet::empty(alist lst) const {
	assert(validList(lst)); return lh[lst].head == 0;
}

/** Determine if an index is on some list.
 *  @param i is an index
 *  @return true if the some list contains i, else false
 */
inline bool ListSet::member(index i) const {
	assert(valid(i)); return nxt[i] != -1;
}

/** Get the successor of an index.
 *  @param i is an index on some list
 *  @return the successor of i
 */
inline index ListSet::next(index i) const { assert(valid(i)); return nxt[i]; }

} // ends namespace

#endif
