/* Main program for project 6. */
#include <cstdio>
#include <string>
using std::string;
#include <getopt.h>
#include <stdlib.h> /* atoi function. */

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"General options:\n"
"   -i,--in     FILE   read graph from FILE.\n"
"   -o,--out    FILE   use FILE for output.\n"
"   --undir            interpret edge list as an undirected graph.\n"
"   -h,--help          show this message and exit.\n"
"Traversal / search options:\n"
"   --bfs              perform breadth-first search.\n"
"   --dfs              perform depth-first search.\n"
"   --components       compute connected components.\n"
"   --source      NUM  source vertex for traversal/search.\n"
"   --path-to     NUM  find a shortest path to vertex NUM.\n";

/* NOTE: here is a little more detail on what these options are
 * supposed to do:
 * --bfs should explore the connected component containing the source
 *   vertex, and label each vertex with its distance from the source.
 * --dfs should label each vertex with the "discovery" time and the
 *   "finish" time.  See your book for details.
 * --components will traverse the entire graph and write the number of
 *   connected components to stdout.  If --out is specified, it should
 *   also write a dot file of the graph illustrating the components.
 * --path-to should print the length of a shortest path from the source
 *   to the destination (the argument to --path-to), and if --out is
 *   given, it should highlight the actual path in the dot file.
 *
 * NOTE: in all of the above cases, the output should be in dot format,
 * written to the file specified with --out.  In particular, if none of
 * the traversal / search options are given, the program should just
 * convert the input file to dot format and write it.
 * */

int main(int argc, char *argv[]) {
	// define long options
	int undirected = 0;
	static struct option long_opts[] = {
		{"in",         required_argument, 0, 'i'},
		{"out",        required_argument, 0, 'o'},
		{"undir",      no_argument,       &undirected, 1},
		{"help",       no_argument,       0, 'h'},
		{"bfs",        no_argument,       0, 'b'},
		{"dfs",        no_argument,       0, 'd'},
		{"components", no_argument,       0, 'c'},
		{"source",     required_argument, 0, 's'},
		{"path-to",    required_argument, 0, 'p'},
		{0,0,0,0}
	};
	// process options:
	char c;
	string inFile, outFile;
	int source = 0;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hi:o:bdcs:p:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 'i':
				inFile = optarg;
				break;
			case 'o':
				outFile = optarg;
				break;
			case 'b':
				/* TODO... */
				break;
			case 'd':
				/* TODO... */
				break;
			case 'c':
				/* TODO... */
				break;
			case 's':
				source = atoi(optarg);
				break;
			case 'p':
				/* TODO... */
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	return 0;
}
