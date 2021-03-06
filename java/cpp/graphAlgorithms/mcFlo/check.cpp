// usage: check
//
// Check reads a Wflograph from stdin, with a flow and checks
// that its a legal maximum flow and has a minimum cost.
//

#include "stdinc.h"
#include "Wflograph.h"
#include "UiList.h"

main() {
	vertex u,v,w; edge e; int s;
	Wflograph wfg; wfg.read(cin);

	// Check that capacity constraints are respected.
	for (e = 1; e <= wfg.m(); e++) {
		u = wfg.tail(e); v = wfg.head(e);
		if (wfg.f(u,e) < 0)
			printf("Negative flow on edge %d=(%d,%d)\n",e,u,v);
		if (wfg.f(u,e) > wfg.cap(u,e))
			printf("Flow exceeds capacity on edge %d=(%d,%d)\n",
				e,u,v);
	}

	// Make sure each vertex is balanced.
	for (u = 2; u < wfg.n(); u++) { 
		s = 0;
		for (e = wfg.firstAt(u); e != 0; e = wfg.nextAt(u,e)) {
			if (u == wfg.head(e))
				s += wfg.f(wfg.tail(e),e);
			else
				s -= wfg.f(u,e);
		}
		if (s != 0)
			printf("Vertex %d is not balanced\n",u);
	}

	// Check that there is no augmenting path.
	int *d = new int[wfg.n()+1];
	for (u = 1; u <= wfg.n(); u++) d[u] = wfg.n();
	d[1] = 0;
	UiList q(wfg.n()); q.addLast(1);
	while (!q.empty()) {
		u = q.first(); q.removeFirst();
		for (e = wfg.firstAt(u); e != 0; e = wfg.nextAt(u,e)) {
			v = wfg.mate(u,e);
			if (wfg.res(u,e) > 0 && d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				q.addLast(v);
			}
		}
	}
	if (d[wfg.n()] < wfg.n()) printf("Not a maximum flow\n");

	// Check that there are no negative cost cycles in residual graph.
	int** cst = new int*[wfg.n()+1];
	for (u = 1; u <= wfg.n(); u++) {
		cst[u] = new int[wfg.n()+1];
	}
	for (u = 1; u <= wfg.n(); u++) {
		for (v = 1; v <= wfg.n(); v++) {
			if (u == v) cst[u][v] = 0;
			else cst[u][v] = BIGINT;
		}
	}
	for (u = 1; u <= wfg.n(); u++) {
		for (e = wfg.firstAt(u); e != 0; e = wfg.nextAt(u,e)) {
			v = wfg.mate(u,e);
			if (wfg.res(u,e) > 0)
				cst[u][v] = min(cst[u][v],wfg.cost(u,e));
		}
	}
	for (v = 1; v <= wfg.n(); v++) {
		if (cst[v][v] < 0) {
			printf("Vertex %2d on a negative cost cycle\n",v);
			exit(0);
		}
		for (u = 1; u <= wfg.n(); u++) {
			for (w = 1; w <= wfg.n(); w++) {
				if (cst[u][v] != BIGINT && cst[v][w] != BIGINT
				    && cst[u][w] > cst[u][v] + cst[v][w]) {
					cst[u][w] = cst[u][v] + cst[v][w];
				}
			}
		}
	}
}
