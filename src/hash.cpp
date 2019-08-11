#include "hash.h"
#include <iostream>
using namespace std;

unsigned int calculateHash(string mystring)
{
	if (mystring.size() > 8) return 0;
	
	unsigned long long pass = 0;
	for(unsigned int i=0; i<mystring.size(); i++){
		pass *= 128;
		pass += int(mystring[i]);
	}

	unsigned int w[4];
	for(unsigned int i=0; i<4; i++){
		w[4-1-i] = pass % 65521;
		pass /= 65521;
	}

	return (45912 * w[0] + 35511 * w[1] + 65169 * w[2] + 4625 * w[3]) % 65521;
}