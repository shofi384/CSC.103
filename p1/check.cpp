#include <stdio.h>
#include <string.h> /* tokenization stuff */
#include <string>
using std::string;

#include "queue.h"
using namespace csc212;

#ifndef DEBUG
#define DEBUG 0
#endif
#define dbgprint(msg) \
	do { if (DEBUG) fprintf(stderr, "%s", msg); } while(0)
#define dumpqueue(q) \
	do { if (DEBUG) q->print(stderr); } while(0)
#define log(op) do { dbgprint("---  "#op"  ---\n"); op; dumpqueue(q); } while(0)
/* XXX above assumes queue is named "q". */
#define R rnd() % 16

/* Pseudo-pseudorandom number generation */
const unsigned long rmax[2] = {65267,65147};
unsigned long rstate[2] = {33333,55555};
unsigned long rfac[2] = {33333,55555};
void setseed(unsigned long s);
unsigned long rnd();

const unsigned long maxIterations = 100; /* detect infinite loops */
const unsigned long nSeeds = 20;
unsigned int seeds[nSeeds];
unsigned long sIndx;

unsigned int nextSeed();
void initSeeds(unsigned int ms);
void normalizeLines(std::string& s);
int compareOutput();

int main()
{
	FILE* fout = fopen("output","wb");
	initSeeds(0xb72b3f69);

	csc212::queue* q = new csc212::queue;
	unsigned long i,count,elt;

	dbgprint("test0: basic push operations\n");
	for(i=0; i<q->getCapacity(); i++)
		log(q->push(R));
	q->print(fout); fprintf(fout, "@\n");

	dbgprint("test1: basic pop operations\n");
	for(i=0; i<q->getSize(); i++) {
		log(elt=q->pop());
		fprintf(fout, "%lu ",elt);
	}
	fprintf(fout, "@\n");

	/* now switch to a new queue to make the tests more disjoint
	 * NOTE: if you ever run a test which may have a number of calls to
	 * rnd() which is not constant, then you should reset the seed to avoid
	 * synchronization issues. */
	setseed(nextSeed());
	delete q;
	q = new csc212::queue;

	dbgprint("test2: circular operations\n");
	for(i=0; i<q->getCapacity(); i++)
		log(q->push(R));
	for(i=0; i<q->getCapacity()/2; i++)
		log(q->pop());
	q->print(fout); fprintf(fout, "@\n");

	setseed(nextSeed());
	dbgprint( "test3: more circular operations\n");
	for(i=0; i<2*q->getCapacity()+3; i++) {
		log(q->push(R));
		log(q->pop());
	}
	q->print(fout); fprintf(fout, "@\n");

	setseed(nextSeed());
	dbgprint("test4: getSize\n");
	delete q;
	q = new csc212::queue;

	for(i=0; i<q->getCapacity(); i++)
		log(q->push(R));
	for(i=0; i<q->getCapacity()/2; i++)
		log(q->pop());
	for(i=0; i<10; i++) {
		log(q->pop());
		fprintf(fout, "%lu ",q->getSize());
		log(q->push(R));
	}
	log(q->pop());
	log(q->pop());
	fprintf(fout, "%lu @\n",q->getSize());

	setseed(nextSeed());
	dbgprint("test5: getBack\n");
	delete q;
	q = new csc212::queue;
	log(q->push(R));
	log(q->push(R));
	fprintf(fout, "%lu @\n",q->getBack());

	setseed(nextSeed());
	dbgprint("test6: isFull\n");
	int full = rnd();
	int notfull = rnd();
	if(q->isFull())
		fprintf(fout, "%i ",full);
	else
		fprintf(fout, "%i ",notfull);

	count = 0;
	while(q->isFull() == false && count++ < maxIterations)
		log(q->push(R));
	q->print(fout); fprintf(fout, "@\n");

	setseed(nextSeed());
	dbgprint("test 7: erase\n");
	q->erase();
	int empty = rnd();
	int notempty = rnd();
	if(q->isEmpty())
		fprintf(fout, "%i ",empty);
	else
		fprintf(fout, "%i ",notempty);
	fprintf(fout, "@\n");

	fclose(fout);
	delete q;
	/* check the output with the solution: */
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

