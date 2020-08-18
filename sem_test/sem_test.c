#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>  
#include <stdio.h>

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO                            (Linux-specific) */
};
 
int main(int argc, char **argv)
{
  	int semid = semget((key_t)1234, 1, 0666|IPC_CREAT);//�����ź�����  

  	if(semid < 0)
 	 {
   		 printf("failed to get semid\r\n");
   		 return -1;
  	}
  
  	union semun sem_num;
  	sem_num.val = 2;
  	semctl(semid, 0, SETALL, sem_num);               //�����ź���ֵΪ1
  
  	struct sembuf sem_p = {
      	0,      //�ź���Ԫ�����
      	-1,     //�ź�������һ�α仯��ֵ
      	0       
  	}; 
  
  	struct sembuf sem_v = {
     	 0,      //�ź���Ԫ�����
      	 1,     //�ź�������һ�α仯��ֵ
      	 0       //
  	}; 

  	pid_t pid = fork();   
  	if(pid == 0)
  	{
      	while(1)
     	{
            semop(semid, &sem_p, 1);
            printf("I am child\r\n");
            sleep(2);
            semop(semid, &sem_v, 1);
     	}
  	} 
  	else
  	{
    	while(1)
    	{
            semop(semid, &sem_p, 1);
            printf("I am father\r\n");
            sleep(2);
            semop(semid, &sem_v, 1);
    	}
  	} 
  
    return 0;      
}