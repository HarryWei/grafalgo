/** @file List.h
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#ifndef LIST_H
#define LIST_H

#include "Adt.h"

namespace grafalgo {

/** Data structure representing a list of indexes.
 *
 *  An index is a postive integer in 1..n where n is an upper
 *  bound on the size of the list. An index can appear on a list
 *  at most once. Index-based lists are handy in contexts where we
 *  need a common "handle" for a piece of data in several different
 *  data structures. They are also compact, efficient and support
 *  constant-time membership tests (based on the index).
 *
 *  Note: List has several no virtual members, so should not be used
 *  in contexts requiring polymorphic types.
 */
class List : public Adt {
public:		List();
		List(int);
		List(const List&);
		List(List&&);
		~List();

	void	resize(int);
	void	expand(int);

	// operators
	List&	operator=(const List&);
	List&	operator=(List&&);
	bool	operator==(const List&);

	// methods to access items
	index 	get(position) const;
	index	next(index) const;
	index	first() const;
	index	last() const;
	int	length() const;

	// predicates
	bool	empty() const;
	bool	member(index) const;
	bool	isConsistent() const;
	
	// modifiers
	virtual void insert(index,index);
	void	addFirst(index);
	void	addLast(index);
	void	removeFirst();
	void	removeNext(index);
	void	clear();

	// input/output
	string	toString() const;
	friend istream& operator>>(istream&, List&);

protected:
	bool	autoExpand;		///< if true, list expands to handle
					///< larger index values
private:
	int	len;			///< number of elements in list
	index	head;			///< first index in list
	index	tail;			///< last index in list
	index	*succ;			///< succ[i] is successor of i in list

	// managing dynamic storage
        void    makeSpace();   
	void	freeSpace();

	void	init();
	void	copyContents(const List&);
};

/** Get the next index in a list.
 *  @param i is an index on the list
 *  @return the index that follows i, or 0 if there is no next index
 */
inline index List::next(index i) const {
	assert(member(i)); return succ[i];
}

/** Get first index on list.
 *  @return the first index on the list or 0 if the list is empty
 */
inline index List::first() const { return head; }

/** Get the last index on list.
 *  @return the last index on the list or 0 if the list is empty
 */
inline index List::last() const { return tail; }

/** Test if list is empty.
 *  @return true if list is empty, else false.
 */
inline bool List::empty() const { return first() == 0; }

/** Determine the length of the list.
 *  @return the number of items in the list.
 */
inline int List::length() const { return len; }

/** Test if an index is in the list.
 *  @param i is an index
 *  @return true if i is in the list, else false
 */
inline bool List::member(index i) const {
	assert(valid(i)); return succ[i] != -1;
}

/** Add index to the front of the list.
 *  @param index to be added.
 */
inline void List::addFirst(index i) { insert(i,0); }

/** Add index to the end of the list.
 *  @param index to be added.
 */
inline void List::addLast(index i) { insert(i,last()); }

/** Remove the first index in the list.
 */
inline void List::removeFirst() { removeNext(0); }

} // ending namespace

#endif

