
#include "Glist.h"
#include "Graph.h"
#include "fastMaxdMatch.h"

namespace grafalgo {

using namespace grafalgo;

/** Find a minimum edge coloring in a bipartite graph.
 *  The algorithm used here finds a series of matchings, where each
 *  matching includes an edge incident to every max degree vertex.
 *  g1 is a reference to the graph
 *  @param color is an array indexed by edge numbers which is allocated
 *  by the caller; on return color[e] is the color assigned to edge e
 *  each list in the set defines a set of edges of the same color
 *  @return the number of colors used
 */
int ecFmatch(Graph& g1, int color[]) {
	Graph g; g.copyFrom(g1);
	Glist<edge> match(g.M());

	int c = 0;
	while (g.m() != 0) {
		c++;	// color to use next
		fastMaxdMatch(g,match);
		while (!match.empty()) {
			edge e = match.value(match.first());
			color[e] = c;
			g.remove(e);
			match.removeFirst();
		}
	}
	return c;
}

} // ends namespace
