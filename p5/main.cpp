/********************************
Test program for Huffman coding
*********************************/

#include <stdio.h>
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
#ifdef SKEL
#include "huffman-skel.hpp"
#else
#include "huffman.hpp"
#endif
#include <vector>
using std::vector;
#include <getopt.h>
#include <string>
using std::string;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Compute Huffman coding of data in stdin.\n\n"
"   --int           read integers instead of chars.\n"
"   --svg    FILE   Render svg of Huffman tree with graphviz.\n"
"   --help          show this message and exit.\n";

int main(int argc, char *argv[])
{
	/* locations for graphical output: */
	string tmpsvg;
	const char* tmpdot = "/tmp/csc212htree.dot";
	const char* dotcmd_fmt = "dot -Tsvg -o %s %s";
	const size_t cmdLen = 512;
	char dotcmd[cmdLen];

	// define long options
	static struct option long_opts[] = {
		{"int",     no_argument,       0, 'i'},
		{"svg",     required_argument, 0, 's'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	bool readInts = false;
	while ((c = getopt_long(argc, argv, "id:s:h", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 'i':
				readInts = true;
				break;
			case 's':
				tmpsvg = optarg;
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* check flag to see if we need to read ints or chars: */
	vector<char> data;
	vector<int> idata;
	string labels;
	int i;
	if (readInts) {
		while(cin >> i) idata.push_back(i);
		hNode<int>* inodes;
		hNode<int>* itree = huffmanEncode(&idata[0], idata.size(), inodes);
		if (tmpsvg != "")
			itree->drawDot(tmpdot);
		printLabels(itree,labels);
		delete [] inodes;
	} else {
		while(cin >> c) data.push_back(c);
		hNode<char>* nodes;
		hNode<char>* tree = huffmanEncode(&data[0], data.size(), nodes);
		if (tmpsvg != "")
			tree->drawDot(tmpdot);
		printLabels(tree,labels);
		delete [] nodes;
	}
	/* draw svg if requested: */
	if (tmpsvg != "") {
		snprintf(dotcmd,cmdLen,dotcmd_fmt,tmpsvg.c_str(),tmpdot);
		FILE* dotout = popen(dotcmd,"r");
		pclose(dotout);
	}
	return 0;
}
