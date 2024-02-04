#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define MSGSIZE 256
typedef struct{
	long m_type;
	char m_data[MSGSIZE];
}mq;

void binaryStr(int n, char str[]);
void octalStr(int n, char str[]);
void hexaStr(int n, char str[]);

int main()
{ 
	int n;
	int mqid = msgget((key_t) 1234,0666| IPC_CREAT);
	mq m1,m2,m3;
	printf("Enter the Integer: ");
	scanf("%d",&n);
	char binStr[MSGSIZE],octStr[MSGSIZE],hexStr[MSGSIZE];
	
	binaryStr(n,binStr);
	octalStr(n,octStr);
	hexaStr(n,hexStr);
	
	printf("Binary Representation of %d: %s\n",n,binStr);
	printf("Octal Representation of %d: %s\n",n,octStr);
	printf("Hexadecimal Representation of %d: %s\n",n,hexStr);
	
	m1.m_type = 2;
	m2.m_type = 8;
	m3.m_type = 16;
	
	strcpy(m1.m_data,binStr);
	strcpy(m2.m_data,octStr);
	strcpy(m3.m_data,hexStr);
	
	msgsnd(mqid,&m1,256,0);
	msgsnd(mqid,&m2,256,0);
	msgsnd(mqid,&m3,256,0);
	
	return 0;
}

void binaryStr(int n, char str[]){
	int i=0;
	char str2[MSGSIZE];
	while(n>0){
		str2[i] = (n%2 + '0');
		n = n/2;
		i++;
	}
	str2[i++] = '\0';
	int length = strlen(str2)-1;
	int j = 0;
	while(length >= 0){
		str[j] = str2[length];
		length--;
		j++;
	}
	str[j++] = '\0';
}

void octalStr(int n, char str[]){
	int i=0;
	char str2[MSGSIZE];
	while(n>0){
		str2[i] = (n%8 + '0');
		n = n/8;
		i++;
	}
	str2[i++] = '\0';
	int length = strlen(str2)-1;
	int j = 0;
	while(length >= 0){
		str[j] = str2[length];
		length--;
		j++;
	}
	str[j++] = '\0';
}

void hexaStr(int n, char str[]){
	int i=0;
	char str2[MSGSIZE];
	while(n>0){
		int x = n%16;
		if(x<10){
			str2[i] = (x + '0');
		}
		else{
			str2[i] = (char) (x+55);
		}
		n = n/16;
		i++;
	}
	str2[i++] = '\0';
	int length = strlen(str2)-1;
	int j = 0;
	while(length >= 0){
		str[j] = str2[length];
		length--;
		j++;
	}
	str[j++] = '\0';
}
