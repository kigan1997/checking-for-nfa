/*
C program to check a string input is accepted by a NFA or not.
Created by - Akash Banerjee(Third Year,IT,510816010)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexA(char symbol[],char ip)
{
	for(int i=0;i<strlen(symbol);i++)
		if(symbol[i]==ip)
			return i;
	return -1;
}


//recurssive function to check a string
int check(int state,int symbolN,int* (*nfa)[symbolN],char * input,char * symbol,int i,int endN,int* end){
	int n = indexA(symbol,input[i++]),isFinal = 0,j;
	if(n==-1) return -1;
	int * nextstate = nfa[state][n];
	int x=nextstate[0];
	if(x==0) return 0;

	for(j=1;j<=x;j++){
		if(input[i]!='\0') 
			isFinal = check(nextstate[j],symbolN,nfa,input,symbol,i,endN,end);
		else
			for (int k = 0; k < endN; k++)
				if(nextstate[j]==end[k])
				{
					isFinal = 1;
					break;
				}
		if(isFinal == 1)
			break;
	}
	return isFinal;
}

int main(void)
{
	int stateN,symbolN,outN,i,j,k;
	printf("Enter # of states and # of symbols:");
	scanf("%d%d",&stateN,&symbolN);
	char symbol[symbolN],repeat;
	printf("Enter symbol set:");
	scanf("%s",symbol);
	printf("Enter table:\n");
	int *nfa[stateN][symbolN];
	for(i=0;i<stateN;i++)
		for(j=0;j<symbolN;j++){
			printf("Enter # of output state for %d state & %c symbol:\n",i,symbol[j] );
			scanf("%d",&outN);
			nfa[i][j] = (int *)malloc((outN+1) * sizeof(int));
			nfa[i][j][0] = outN;
			printf("Enter output states:\n");
			for(k=1;k<=outN;k++)
				scanf("%d",&nfa[i][j][k]);
			}	
	int start,endN;
	printf("Enter starting state:");
	scanf("%d",&start);
	printf("Enter # of final states:");
	scanf("%d",&endN);
	int end[endN];
	printf("Enter final states:");
	for(i=0;i<endN;i++)
		scanf("%d",&end[i]);
	char input[100];
	do{
	printf("Enter a input string:");
	scanf("%s",input);

	/*
	//
	//This portion is for checking a string is accepted by a DFA or not
	//

	for(i=0;i<strlen(input);i++)
	{
		int n=indexA(symbol,input[i]);
		if(n==-1)
		{
			printf("wrong input\n");
			goto lable;
		}
		start=dfa[start][n];
	}*/
	/*start=check(start,symbolN,dfa,input,symbol,0);
	//printf("%d\n",start);
	for(i=0;i<endN;i++)
	{
		if(start==end[i])
		{
			printf("Accepted\n");
			break;
		}
	}	
	if(i==endN)
		printf("Not accepted\n");*/
	

	if(check(start,symbolN,nfa,input,symbol,0,endN,end))
		printf("Accepted by NFA\n");
	else
		printf("Not accepted by NFA\n");
	lable:printf("Want to repaet?(y/n):");
	scanf("%s",&repeat);
	}while(repeat=='y');
	
}
