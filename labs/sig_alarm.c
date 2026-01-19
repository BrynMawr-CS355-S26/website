#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

int checkerror(int v, const char* msg)
{
    if (v < 0)
    {
        perror(msg);
        exit(0);
    }
    return v;
}

struct timeval tstart;

void sig_alarm(int signum)
{
  printf("triggered...\n");
  sleep(5);
  struct timeval tend;
  gettimeofday(&tend, NULL);
  float dt = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Process received alarm signal. Elapsed time = %.2f\n", dt);
}

int main()
{
  struct sigaction sa;
  //sigemptyset(&sa.sa_mask);
  sigfillset(&sa.sa_mask); 
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = sig_alarm;
  checkerror(sigaction(SIGALRM, &sa, NULL), "sigaction");
  
  struct itimerval v;
  v.it_interval.tv_sec = 1;
  v.it_interval.tv_usec = 0;
  v.it_value.tv_sec = 1;
  v.it_value.tv_usec = 0;
  checkerror(setitimer(ITIMER_REAL, &v, NULL), "settimer");
  
  gettimeofday(&tstart, NULL);
  while(1) pause();
  return 0;
}
