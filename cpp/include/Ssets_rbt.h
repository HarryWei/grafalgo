/*  @file Ssets_rbt.h
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#ifndef SSETS_RBT_H
#define SSETS_RBT_H

#include "Ssets.h"

namespace grafalgo {

/** Balanced binary search trees class.
 *  Represents a collection of balanced BSTs, defined on indexes 1..n.
 *  Each BST represents a "sorted set" and the sets partition the
 *  underlying index set (so each index value appears in exactly one set).
 *
 *  Inherits some methods from the SortedSets class.
 */
class Ssets_rbt : public Ssets {
public:
		Ssets_rbt(int=26);
		~Ssets_rbt();

	// common methods
	void	clear();
	void	resize(int);
	void	expand(int);
	void	copyFrom(const Ssets_rbt&);

	bool	insert(index,bst&);
	void	remove(index,bst&);
	bst	join(bst,index,bst);
protected:
	int	*rvec;			///< rvec[x] is the "rank" of node x

	void	swap(index,index);
	void	rebalance1(index);
	void	rebalance2(index, index);
	string	node2string(index) const;

	void	makeSpace();
	void	freeSpace();
	void	init();
};

} // ends namespace

#endif
