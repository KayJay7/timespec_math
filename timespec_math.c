#include <time.h>

void timespec_dif(const struct timespec *a, const struct timespec *b, struct timespec *result);
void timespec_sum(const struct timespec *a, const struct timespec *b, struct timespec *result);
void timespec_mul(const struct timespec *a,  int b, struct timespec *result);
void timespec_div(const struct timespec *a,  int b, struct timespec *result);

void timespec_dif(const struct timespec *a, const struct timespec *b, struct timespec *result) {
    result->tv_sec = a->tv_sec - b->tv_sec;
    result->tv_nsec = a->tv_nsec - b->tv_nsec;
    if (result->tv_nsec < 0) {
        result->tv_sec--;
        result->tv_nsec += 1000000000L;
    }
}

void timespec_sum(const struct timespec *a, const struct timespec *b, struct timespec *result) {
    result->tv_sec  = a->tv_sec + b->tv_sec;
    result->tv_nsec = a->tv_nsec + b->tv_nsec;
    if (result->tv_nsec > 1000000000L) {
        result->tv_sec++;
        result->tv_nsec -= 1000000000L;
    }
}

//(a+b/1E9)*c = c*a+cb/1E9
void timespec_mul(const struct timespec *a, int b, struct timespec *result) {
	long long temp = (long long) b * (long long) a->tv_nsec;
    result->tv_sec = (a->tv_sec * b) + (temp / 1000000000LL);
    result->tv_nsec = temp % 1000000000LL;
}

//(a+b/1E9)/c = a/c+b/cE9
void timespec_div(const struct timespec *a, int b, struct timespec *result) {
    long long temp = (((long long) (a->tv_sec % b) * 1000000000LL) + (long long) a->tv_nsec) / (long long) b;
    result->tv_sec = (a->tv_sec / b) + (temp / 1000000000LL);
    result->tv_nsec = temp % 1000000000LL;
}