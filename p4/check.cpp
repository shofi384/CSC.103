#include <stdio.h>
#include <fstream>
using std::ofstream;
using std::endl;

#include <iostream>
using std::cerr;

#include <string.h>
#include <string>
using std::string;

#include "searchTree.h"
using namespace csc212;

#ifndef DEBUG
#define DEBUG 0
#endif
#define dbgprint(fmt,...) \
	do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while(0)

/*Pseudo-pseudorandom number generation*/
const unsigned long rmax[2] = {65267,65147};
unsigned long rstate[2] = {33333,55555};
unsigned long rfac[2] = {33333,55555};
void setseed(unsigned long s);
unsigned long rnd();
const unsigned long nSeeds = 20;
unsigned int seeds[nSeeds];
unsigned long sIndx;

unsigned int nextSeed();
void initSeeds(unsigned int ms);
void normalizeLines(std::string& s);
int compareOutput();

int main(void)
{
	/*
	* copyST
	* operator=
	* searchST
    * maxST
	* minST
    * removeST
    * clearST
	* postOrderST
	* inOrderST
    * numLeaves
	* sizeST
	*/

	std::ofstream fout("output"); //should overwrite whatever file is currently there.
	
	//initialize srand with a fixed secret that will determine the sequence of test input.
	initSeeds(0xc3706baa);

	unsigned long i;
	size_t testIndx=0;
	unsigned long n;

	dbgprint("test %lu : size\n", testIndx++);
	Tree T;
	n = rnd() % 50 + 50;
	for(i=0; i<n; i++)
	{
		T.insert(rnd()%50);
		if((i%20)==0)
			fout << T.size() << " ";
	}
	fout << "@";

	dbgprint("test %lu : copyST/operator=\n", testIndx++);
	Tree U;
	U = T;
	fout << U << " @";

	dbgprint("test %lu : search\n", testIndx++);
	Tree T2; //don't know if clear works, so we'll keep allocating new trees.
	for(i=0; i<50; i++)
		T2.insert(rnd()%50);
	for(i=0; i<100; i++)
	{
		if(T2.search(rnd()%100))
			fout << "1";
		else
			fout << "0";
	}
	fout << " @";

	dbgprint("test %lu : max\n", testIndx++);
	Tree T3;
	for(i=0; i<10; i++)
		T3.insert(rnd()%20);
	fout << T3.max() << " ";
	for(i=0; i<10; i++)
		T3.insert(rnd()%30);
	fout << T3.max() << " ";
	for(i=0; i<10; i++)
		T3.insert(rnd()%40);
	fout << T3.max() << " ";
	for(i=0; i<10; i++)
		T3.insert(rnd()%50);
	fout << T3.max() << " ";
	for(i=0; i<10; i++)
		T3.insert(rnd()%60);
	fout << T3.max() << " @";

	dbgprint("test %lu : min\n", testIndx++);
	Tree T4;
	for(i=0; i<10; i++)
		T4.insert(rnd()%30+50);
	fout << T4.min() << " ";
	for(i=0; i<10; i++)
		T4.insert(rnd()%40+40);
	fout << T4.min() << " ";
	for(i=0; i<10; i++)
		T4.insert(rnd()%50+30);
	fout << T4.min() << " ";
	for(i=0; i<10; i++)
		T4.insert(rnd()%40+20);
	fout << T4.min() << " ";
	for(i=0; i<10; i++)
		T4.insert(rnd()%30);
	fout << T4.min() << " @";


	dbgprint("test %lu : remove\n", testIndx++);
	Tree T5;
	for(i=0; i<100; i++)
		T5.insert(rnd()%100);
	for(i=0; i<100; i++)
	{
		T5.remove(rnd()%100);
		if((i%20)==0)
			fout << T5 << endl;
	}
	fout << " @";

	dbgprint("test %lu : inorder\n", testIndx++);
	Tree T6;
	for(i=0; i<100; i++)
		T6.insert(rnd()%100);
	T6.inOrder(&fout);
	fout << " @ ";

	dbgprint("test %lu : postorder\n", testIndx++);
	T6.postOrder(&fout);
	fout << " @ ";

	dbgprint("test %lu : numleaves\n", testIndx++);
	Tree T7;
	n = rnd() % 50 + 50;
	for(i=0; i<n; i++)
	{
		T7.insert(rnd()%50);
		if((i%20)==0)
			fout << T7.numLeaves() << " ";
	}
	fout << "@";

	dbgprint("test %lu : clear\n", testIndx++);
	Tree T8;
	for(i=0; i<100; i++)
		T8.insert(rnd()%50);

	T8.clear();
	unsigned long a,b;
	a = rnd();
	b = rnd();
	n = (T8.size()==0)?a:b;
	fout << n << " @";

	fout.close();
	compareOutput();
	return 0;
}

unsigned int nextSeed()
{
	return seeds[sIndx = (sIndx+1)%nSeeds];
}

void initSeeds(unsigned int ms)
{
	sIndx = 0;
	setseed(ms);
	for(unsigned long i=0; i<nSeeds; i++)
		seeds[i] = rnd();
}
int compareOutput()
{
	char* sout, *out;
	FILE* fsout = fopen("soutput","r");
	if(fsout == 0) {
		printf( "File \"soutput\" not found.\n");
		return 1;
	}
	FILE* fout = fopen("output","r");
	if (fout == 0) {
		printf( "File \"output\" not found.\n");
		return 1;
	}

	unsigned long ssize,osize;
	fseek(fsout,0,SEEK_END);
	ssize = ftell(fsout);
	fseek(fsout,0,SEEK_SET);
	fseek(fout,0,SEEK_END);
	osize = ftell(fout);
	fseek(fout,0,SEEK_SET);
	sout = new char[ssize+1];
	out = new char[osize+1];
	fread(sout,1,ssize,fsout);
	fread(out,1,osize,fout);
	fclose(fsout);
	fclose(fout);
	/* make sure they are c-strings: */
	sout[ssize] = 0;
	out[osize] = 0;
	/* now tokenize and compare. */

	char* token;
	std::string answers[256]; /* official answers */
	std::string results[256]; /* submitted answers */
	char delims[] = "@";
	token = strtok(sout,delims);
	unsigned long nAnswers=0,j=0;
	while(token) {
		answers[nAnswers] = token;
		normalizeLines(answers[nAnswers++]);
		token = strtok(0,delims);
	}
	token = strtok(out,delims);
	while(token && j<nAnswers) {
		results[j] = token;
		normalizeLines(results[j++]);
		token = strtok(0,delims);
	}

	/* compare and print report */
	unsigned long nRight=0;
	for (j = 0; j < nAnswers; j++) {
		if(answers[j] == results[j])
			nRight++;
		else
			printf("\ntest %lu failed:\nshould be:\t%s\nbut got:\t%s\n",
					j, answers[j].c_str(), results[j].c_str());
	}
	printf("\n******** Results ********\n   %lu out of %lu correct.\n",
			nRight, nAnswers);
	printf("*************************\n");

	delete[] sout;
	delete[] out;
	return 0;
}
void setseed(unsigned long s)
{
	rstate[0] = ((s&0xFFFF)*33333) % rmax[0];
	rstate[1] = (((s>>16)^(s&0xFFFF))*55555) % rmax[1];
	for (unsigned long i = 0; i < 2; i++) {
		if(rstate[i]%2 == 0) ++rstate[i];
		rfac[i] = rstate[i];
	}
}
unsigned long rnd()
{
	for (unsigned long i = 0; i < 2; i++) {
		rstate[i] = (rstate[i]*rfac[i])%rmax[i];
	}
	return rstate[0] | (rstate[1] << 16);
}
void normalizeLines(std::string& s)
{
	size_t pos = 0;
	std::string creturn = "\r";
	while ((pos = s.find(creturn,pos)) != std::string::npos) {
		s.erase(pos,creturn.length());
	}
}
