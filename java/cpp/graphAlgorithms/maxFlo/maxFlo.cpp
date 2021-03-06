// usage: maxFlo method
//
// MaxFlo reads a flograph from stdin, computes a maximum flow
// using the method specified by the argument and then prints the
// flograph with the max flow.
//

#include "stdinc.h"
#include "Flograph.h"
#include "maxCap.h"
#include "capScale.h"
#include "shortPath.h"
#include "dinic.h"
#include "dinicDtrees.h"
#include "prePush.h"
#include "ppFifo.h"
#include "ppHiLab.h"

main(int argc, char *argv[]) {
	int floVal;
	Flograph fg; fg.read(cin);

	if (argc != 2) fatal("usage: maxFlo method");

	if (strcmp(argv[1],"maxCap") == 0)
		maxCap(fg,floVal);
	else if (strcmp(argv[1],"capScale") == 0)
		capScale(fg,floVal);
	else if (strcmp(argv[1],"shortPath") == 0)
		shortPath(fg,floVal);
	else if (strcmp(argv[1],"dinic") == 0)
		dinic(fg,floVal);
	else if (strcmp(argv[1],"dinicDtrees") == 0)
		dinicDtrees(fg,floVal);
	else if (strcmp(argv[1],"ppFifo") == 0)
		ppFifo(fg,floVal,false);
	else if (strcmp(argv[1],"ppFifoBatch") == 0)
		ppFifo(fg,floVal,true);
	else if (strcmp(argv[1],"ppHiLab") == 0)
		ppHiLab(fg,floVal,false);
	else if (strcmp(argv[1],"ppHiLabBatch") == 0)
		ppHiLab(fg,floVal,true);
	else
		fatal("maxFlo: undefined method");

	string s;
	cout << fg.toString(s) << "total flow of " << floVal << endl;
	exit(0);
}
