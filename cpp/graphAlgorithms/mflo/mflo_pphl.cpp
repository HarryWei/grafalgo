/** \file mflo_pphl.cpp
 *
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#include "mflo_pphl.h"

namespace grafalgo {

/** Find maximum flow in a flow graph using the highest-label-first
 *  variant of the preflow-push algorithm.
 *  @param g1 is a reference to the flow graph
 *  @param batch is a boolean which determines if the algorithm uses
 *  batch relabeling (batch=true) or incremental relabeling (batch=false)
 */
mflo_pphl::mflo_pphl(Graph_f& g1, bool batch) : mflo_pp(g1) {
	// ubVec[d] is an unbalanced vertex with a distance label of d
	// or 0 if there is no unbalanced vertex with a distance label of d
	// unbal partitions the vertices into circular lists, where all
	// vertices on the same list are unbalanced and have the same
	// distance label; balanced vertices each form singleton lists
	ubVec = new int[2*g->n()];
	unbal = new Dlists(g->n());
	top = 0;
	for (int i = 0; i < 2*g->n(); i++) ubVec[i] = 0;

	if (batch) maxFlowBatch();
	else maxFlowIncr();
}

/** Add an unbalanced vertex to the vector of lists of such vertices.
 *  @param u is the unbalanced vertex to be added to the list of
 *  of unbalanced vertices with the same distance label as u
 */
void mflo_pphl::addUnbal(vertex u) {
	if (ubVec[d[u]] == u || !unbal->singleton(u)) return;
	ubVec[d[u]] = unbal->join(ubVec[d[u]],u);
	top = max(top,d[u]);
}

/** Remove and return an unbalanced vertex with the largest distance label.
 *  @return an unbalanced vertex u that has a maximum distance label;
 *  u is also removed from the data structure that tracks unbalanced
 *  vertices, so if it remains unbalanced after being processed,
 *  it must be added back
 */
vertex mflo_pphl::removeUnbal() {
	if (top == 0) return 0;
	vertex u = ubVec[top]; 
	ubVec[top] = unbal->remove(u,ubVec[top]);
	while (top > 0 && ubVec[top] == 0) top--;
	return u;
}

} // ends namespace
