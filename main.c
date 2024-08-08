#include <stdio.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	struct timeval tv;
	struct timezone tz;


	gettimeofday(&tv, &tz);

	printf("seecons: %ld, microseconds %ld\n", tv.tv_sec, tv.tv_usec );
	return (0);
}
