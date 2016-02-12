#include <stdio.h>
#include <fstream>
using std::ofstream;
using std::endl;

#include <iostream>
using std::cout;
using std::cerr;

#include <string.h>
#include <string>
using std::string;

#include "list.h"
using namespace csc212;

#ifndef DEBUG
#define DEBUG 0
#endif
#define dbgprint(msg) \
	do { if (DEBUG) fprintf(stderr, "%s", msg); } while(0)
#define dumplist(l) \
	do { if (DEBUG) cerr << #l": " << l; } while(0)
#define log(op,l) do { op; dumplist(l); dbgprint("---  "#op"\n"); } while(0)
#define R rnd() % 10

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
void fillRandom(list& L, unsigned long n, unsigned long k);
void normalizeLines(std::string& s);
int compareOutput();

int main(void)
{
	/* here's what we need to test:
	 * operator==
     * insert
     * remove
     * length
     * merge
     * intersection
	 */

	std::ofstream fout("output");
	initSeeds(0x23948bd2);

	list l;
	unsigned long i;
	unsigned long n,a,b;
	dbgprint("test 0: length\n");
	n = rnd() % 20;
	for(i=0; i<n; i++)
		log(l.insert(R),l);
	fout << l.length() << " @\n";

	dbgprint("test1: operator==\n");
	list c(l);
	a = rnd();
	b = rnd();
	fout << ((c == l)?a:b) << " @";

	dbgprint("test2: operator==2\n");
	for(i=0; i<10; i++) {
		fillRandom(l,3,2);
		fillRandom(c,3,2);
		fout << ((c == l)?a:b) << " ";
	}
	fout << " @\n";

	dbgprint("test3: insert\n");
	l.clear();
	setseed(nextSeed());
	for(i=0; i<20; i++)
		log(l.insert(rnd()%30),l);
	fout << l << " @\n";

	dbgprint("test4: insert2\n");
	l.clear();
	c.clear();
	for(i=0; i<5; i++) {
		log(l.insert(i),l);
		log(c.insert(4-i),c);
	}
	fout << l << endl << c << " @\n";

	dbgprint("test5: remove\n");
	l.clear();
	setseed(nextSeed());
	for(i=0; i<15; i++)
		log(l.insert(R),l);

	log(l.remove(0),l);
	log(l.remove(1),l);
	log(l.remove(2),l);
	log(l.remove(3),l);
	fout << l << endl;
	log(l.remove(9),l);
	log(l.remove(8),l);
	log(l.remove(7),l);
	log(l.remove(6),l);
	fout << l << " @\n";

	dbgprint("test6: remove2\n");
	l.clear();
	for(i=0; i<15; i++)
		log(l.insert(R),l);

	log(l.remove(5),l);
	log(l.remove(6),l);
	log(l.remove(7),l);
	fout << l << " @\n";

	dbgprint("test7: merge\n");
	l.clear();
	c.clear();
	list m;
	for(i=0; i<15; i++) {
		log(l.insert(rnd()%20),l);
		log(c.insert(rnd()%20),c);
	}
	log(m.merge(l,c),m);
	fout << m << " @\n";

	dbgprint("test8: merge2\n");
	m.clear();
	l.clear();
	c.clear();
	for(i=0; i<15; i++) {
		log(l.insert(R),l);
		log(c.insert(R),c);
	}
	log(l.remove(R),l);
	log(l.remove(R),l);
	log(m.merge(l,c),m);
	fout << m << " @\n";

	dbgprint("test9: intersect\n");
	l.clear();
	c.clear();
	for(i=0; i<15; i++) {
		log(l.insert(rnd()%20),l);
		log(c.insert(rnd()%20),c);
	}
	log(m.intersection(l,c),m);
	fout << m << " @\n";

	dbgprint("test10: intersect2\n");
	m.clear();
	l.clear();
	c.clear();
	for(i=0; i<15; i++) {
		log(l.insert(R),l);
		log(c.insert(R),c);
	}
	log(l.remove(R),l);
	log(l.remove(R),l);
	log(m.intersection(l,c),m);
	fout << m << " @\n";

	fout.close();
	compareOutput();
	return 0;
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
void fillRandom(list& L, unsigned long n, unsigned long k)
{
	L.clear();
	for (unsigned long i = 0; i < n; i++) {
		L.insert(rnd()%k);
	}
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
