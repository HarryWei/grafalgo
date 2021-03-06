/** @file copyGraph.cpp
 * 
 *  @author Jon Turner
 *  @date 2011
 *  This is open source software licensed under the Apache 2.0 license.
 *  See http://www.apache.org/licenses/LICENSE-2.0 for details.
 */

#include "stdinc.h"
#include "Adt.h"
#include "Graph_w.h"
#include "Graph_wd.h"
#include "Graph_wf.h"
#include "Graph_g.h"

using namespace grafalgo;

/** usage: copyGraph type
 * 
 *  Copy a graph of specified type from stdin to stdout.
 *  Why you ask? To test input and output operators, of course.
 *  We also do an assignment in between input and output,
 *  in order to test the assignment operator.
 * 
 *  The allowed values of type are graph, wgraph,
 *  digraph, wdigraph, flograph, wflograph.
 */
int main(int argc, char *argv[]) { 

	if (argc != 2) Util::fatal("usage: copyGraph type");

	if (strcmp(argv[1],"ugraph") == 0) {
		Graph g; cin >>g; Graph g1;
		g1.copyFrom(g); cout << g1;
	} else if (strcmp(argv[1],"wgraph") == 0) {
		Graph_w wg; cin >> wg; Graph_w wg1;
		wg1.copyFrom(wg); cout << wg1;
	} else if (strcmp(argv[1],"digraph") == 0) {
		Graph_d dig; cin >> dig; Graph_d dig1;
		dig1.copyFrom(dig); cout << dig1;
	} else if (strcmp(argv[1],"wdigraph") == 0) {
		Graph_wd wdig; cin >> wdig; Graph_wd wdig1;
		wdig1.copyFrom(wdig); cout << wdig1;
	} else if (strcmp(argv[1],"flograph") == 0) {
		Graph_f fg; cin >> fg; Graph_f fg1;
		fg1.copyFrom(fg); cout << fg1.toString();
	} else if (strcmp(argv[1],"wflograph") == 0) {
		Graph_wf wfg; cin >> wfg; Graph_wf wfg1;
		wfg1.copyFrom(wfg); cout << wfg1;
	} else if (strcmp(argv[1],"groupgraph") == 0) {
		Graph_g gg; cin >> gg; Graph_g gg1;
		gg1.copyFrom(gg); cout << gg1;
	} else {
		Util::fatal("usage: copyGraph type");
	}
}
