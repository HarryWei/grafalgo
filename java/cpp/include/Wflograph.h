/** @file Wflograph.h
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#ifndef WFLOGRAPH_H
#define WFLOGRAPH_H

#include "stdinc.h"
#include "Util.h"
#include "Flograph.h"

typedef int flow;
typedef int floCost;

/** Class representing a weighted flow graph.
 *  Used in min cost flow problems.
 *  Inherits many methods from the Flograph class and adds methods
 *  for dealing with edge costs.
 */
class Wflograph : public Flograph {
public:		Wflograph(int=26,int=100,int=1,int=2);
		Wflograph(const Wflograph&);
		virtual ~Wflograph();

	virtual void resize(int,int);	
	virtual void reset();	
        void virtual copyFrom(const Wflograph&);

	virtual edge join(vertex,vertex);

	floCost	cost(vertex,edge) const;
	void	setCost(edge,floCost);
	void	randCost(floCost,floCost);

	virtual bool readEdge(istream&);
	virtual string& edge2string(edge,string&) const; 
	string& toDotString(string&) const;

protected:
	floCost	*cst;				///< cst[e] is cost of e

	// various helper methods
        void    makeSpace(int,int);    		
        void    freeSpace();    	
	void    virtual shuffle(int*, int*);

private:
	Wflograph& operator=(const Wflograph&); 
};

/** Return cost of an edge.
 *  @param v is a vertex
 *  @param e is an edge that is incident to v
 *  @return the cost of e in the direction from v to mate(v)
 */
inline flow Wflograph::cost(vertex v, edge e) const { 
	assert(1 <= v && v <= n() && 1 <= e && e <= m());
	return tail(e) == v ? cst[e] : -cst[e];
}

/** Set the cost of an edge.
 *  @param e is an edge
 *  @param c is a new cost to be assigned to e
 */
inline void Wflograph::setCost(edge e, floCost c) { 
	assert(1 <= e && e <= m());
	cst[e] = c;
}

#endif
