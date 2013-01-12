/** @file Wdigraph.h
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#ifndef WDIGRAPH_H
#define WDIGRAPH_H

#include "Digraph.h"

namespace grafalgo {

/** Data structure for directed graph with edge lengths.
 *
 *  Wdigraph size (number of vertices and max number of edges) must
 *  be specified when a Wdigraph object is instantiated.
 *  Edges can be added and removed from the graph.
 *  Methods are provided to facilitate graph traversal,
 *  either by iterating through all edges of the graph
 *  or all edges incident to a specific vertex.
 */
class Wdigraph : public Digraph {
public:		Wdigraph(int=1,int=1);
		~Wdigraph();
	
	void	resize(int, int);
	void	resize(int numv) { resize(numv, numv); }
	void	expand(int, int);
	void	expand(int numv) { expand(numv, max(numv,m())); }
	virtual void copyFrom(const Wdigraph&);

	// methods for accessing/changing length
        int     length(edge) const;
        void    setLength(edge,int);

	// create a string representation
        string&	edge2string(edge, string&) const;
        string&	toDotString(string&) const;

	void randLength(int, int); 

private:
	int	*len;			///< len[e] is length of edge e

	void makeSpace(int,int);
	void freeSpace();
	bool	readAdjList(istream&);
        string&	adjList2string(vertex,string&) const;

	Wdigraph& operator=(const Wdigraph&);
};

/** Get the length of an edge.
 *  @param e is the edge of interest
 *  @return the length of e
 */
inline int Wdigraph::length(edge e) const {
	assert(0 <= e && e <= maxEdge); return len[e];
}

/** Set the length of an edge.
 *  @param e is the edge of interest
 *  @param lng is the desired length
 */
inline void Wdigraph::setLength(edge e, int lng) {
	assert(0 <= e && e <= maxEdge); len[e] = lng;
}

} // ends namespace

#endif
