#ifdef WIN32
#include <Windows.h> // GetTickCount()
#else
#include <sys/time.h>
#include <stdlib.h>
#endif

// platform-abstracted tick retrieval
// Taken from the rathena project
unsigned int GetTick(void)
{
#if defined(WIN32)
	return GetTickCount();
#elif defined(ENABLE_RDTSC)
	return (unsigned int)((_rdtsc() - RDTSC_BEGINTICK) / RDTSC_CLOCK);
#elif defined(HAVE_MONOTONIC_CLOCK)
	struct timespec tval;
	clock_gettime(CLOCK_MONOTONIC, &tval);
	return tval.tv_sec * 1000 + tval.tv_nsec / 1000000;
#else
	struct timeval tval;
	gettimeofday(&tval, NULL);
	return tval.tv_sec * 1000 + tval.tv_usec / 1000;
#endif
}
