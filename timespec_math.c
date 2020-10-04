#include <time.h>

void timespec_dif(struct timespec *a, struct timespec *b, struct timespec *result) {
    result->tv_sec = a->tv_sec - b->tv_sec;
    result->tv_nsec = a->tv_nsec - b->tv_nsec;
    if (result->tv_nsec < 0) {
        result->tv_sec++;
        result->tv_nsec += 1000000000L;
    }
}

void timespec_sum(struct timespec *a, struct timespec *b, struct timespec *result) {
    result->tv_sec  = a->tv_sec + b->tv_sec;
    result->tv_nsec = a->tv_nsec + b->tv_nsec;
    if (result->tv_nsec > 1000000000L) {
        result->tv_sec++;
        result->tv_nsec -= 1000000000L;
    }
}

//(a+1/b)*c = c*a+c/b
void timespec_mul(struct timespec *a, int b, struct timespec *result) {
	long long temp = (long long) b * 1000000000LL;
	temp = temp / result->tv_nsec;
    result->tv_sec = a->tv_sec * b;
    result->tv_sec = result->tv_sec + (temp / 1000000000LL);
    result->tv_nsec = temp % 1000000000LL;
}

//(a+1/b)/c = a/c+1/(b*c)
void timespec_div(struct timespec *a, int b, struct timespec *result) {
    long long temp = a->tv_sec % b;
    temp = (temp * 1000000000LL) / (long long) b;
    temp = temp + ((long long) a->tv_nsec * (long long) b);
    result->tv_nsec = temp % 1000000000LL;
    result->tv_sec = result->tv_sec + (temp / 1000000000LL);
}