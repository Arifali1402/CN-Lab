// For Binary
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define MSGSIZE 512
typedef struct{
	long m_type;
	char m_data[MSGSIZE];
}mq;

int main(){
	int mqid = msgget((key_t) 1234,0666);
	mq msg1;
	msgrcv(mqid,&msg1,sizeof(msg1),2,0);
	printf("Binary Representation: %s\n",msg1.m_data);
	//msgctl(1234,IPC_RMID,NULL);
	return 0;
}
