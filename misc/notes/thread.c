#include <pthread.h>

/* https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/ */

void	*my_entry_function(void *param)
{
}

int		main()
{
	 pthread_t thread0;

	 pthread_create(&thread0, NULL, my_entry_function, &parameter);
	 pthread_join(thread0, NULL);

	 return 0;
}
