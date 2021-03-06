/** @file becolorlb_f.cpp
 * 
 *  @author Jon Turner
 *  @date 2015
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#include "becolor.h"
#include "List_g.h"
#include "Graph_ff.h"
#include "mflo_d.h"
#include "mflo_ffsp.h"

namespace grafalgo {

extern bool mflof(Graph_ff&, string);
extern int becolorlb_m(Graph_wd&);
void buildFlograf(Graph_wd&, int, int, Graph_ff&);

/** Compute the matching lower bound on the bounded chromatic index.
 *  @param g is a reference to a weighted digraph, where edge lengths are
 *  used to represent lower bounds on the edge colors
 */
int becolorlb_f(Graph_wd& g) {
	int bmax = 0;
	for (edge e = g.first(); e != 0; e = g.next(e)) 
		bmax = max(bmax, g.length(e));

	Graph_ff fg;
	int loC = becolorlb_m(g) - 1;
	int hiC = bmax + g.maxDegree() - 1;
	int C = (loC + hiC + 1)/2;
	while (C < hiC) {
		int k;
		for (k = bmax; k >= 1; k--) {
			buildFlograf(g, k, C, fg);
			if (!mflof(fg,"mflo_d")) {
				loC = C; break;
			}
		}
		if (k == 0) hiC = C;
		C = (loC + hiC + 1)/2;
	}
	return hiC;
}

/** Construct flow graph for determining lower bound.
 *  @param g is a weighted digraph in which the edge lengths represent
 *  lower bounds on edge colors
 *  @param k is the largest bound to consider when constructing fg;
 *  that is, only incorporate edges from g that have bounds <= k
 *  @param C is the target number of colors for lower bound computation
 *  @param fg is a flow graph with min flow requirements, in which the
 *  result is returned
 */
void buildFlograf(Graph_wd& g, int k, int C, Graph_ff& fg) {
	fg.resize(g.n()*k+2,g.M()+g.n()*k+2);
	fg.setSrc(g.n()*k+1); fg.setSnk(g.n()*k+2);
	// first, build central edges, preserving edge numbers from g
	for (edge e = g.first(); e != 0; e = g.next(e)) {
		vertex u = g.tail(e); vertex v = g.head(e);
		int b = g.length(e);
		if (b > k) continue;
		if (b == 1) fg.joinWith(u,v,e);
		else fg.joinWith(g.n()+(u-1)*(k-1)+(b-1),
				 g.n()+(v-1)*(k-1)+(b-1), e);
		fg.setCapacity(e, 1);
	}
	// now, build remaining edges
	for (vertex u = 1; u <= g.n(); u++) {
		int du = g.degree(u);
		if (g.firstOut(u) != 0) {  // u is an input
			edge e = fg.join(fg.src(), u);
			fg.setCapacity(e, k);
			fg.setFloor(e, max(0, du - (C - k)));
			if (k == 1) continue;
			vertex x = g.n()+(u-1)*(k-1)+1;
			int ecap = k-1;
			e = fg.join(u, x); fg.setCapacity(e, ecap--);
			while (x < g.n()+u*(k-1)) {
				e = fg.join(x, x+1); fg.setCapacity(e, ecap--);
				x++;
			}
		} else if (g.firstIn(u) != 0) { // u is an output
			edge e = fg.join(u, fg.snk());
			fg.setCapacity(e, k);
			fg.setFloor(e, max(0, du - (C - k)));
			if (k == 1) continue;
			vertex x = g.n()+(u-1)*(k-1)+1;
			int ecap = k-1;
			e = fg.join(x, u); fg.setCapacity(e, ecap--);
			while (x < g.n()+u*(k-1)) {
				e = fg.join(x+1, x); fg.setCapacity(e, ecap--);
				x++;
			}
		}
	}
}

} // ends namespace
