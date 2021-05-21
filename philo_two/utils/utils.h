#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define NUM_OF_ARGS 5

typedef long long unsigned	t_llu;

typedef t_llu				t_msec;

typedef struct s_args
{
	size_t					ph_num;
	t_msec					die_time;
	t_msec					eat_time;
	t_msec					sleep_time;
	size_t					must_eat_n;
}							t_args;

/*
** === Utility functions ===
*/
int							ft_isdigit(int c);
int							ft_isspace(int c);
size_t						ft_strlen(const char *s);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nmemb, size_t size);
int							init_start_of_simulation(void);
t_msec						get_current_time_ms(void);
t_msec						str_to_msec(const char *str, int *error);
int							error(const char *msg);
int							parse_args(int argc, char *argv[], t_args *pargs);
int							destroy_threads(pthread_t *threads, \
								size_t thread_num);

#endif