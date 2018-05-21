/*WAP to implement a Regular expression. The program should
read a RE through a file and should check whether a string
given from the console is acceptable by the given RE or not*/
#include <iostream>
#include <fstream>
#include<string>
using namespace std;
int main()
{
	ifstream infile;
	infile.open("fAutomata.txt");
	int initial,i=0,k=0,l=0,nf,nr,nc;
	char ch;
	int automata[100][100],final[100];
	string rline;
	infile.get(ch);
	initial=(int)ch-48;
	getline(infile,rline);
	int j=0;
	int len;
	cout<<initial<<"\n";
	i=0;
	while(getline(infile,rline))
	{
		len=rline.size();
		k=0;
		for(j=0;j<len;j++)
		{
			if(l==0)
			{
				if(rline[j]!=',')
				{
					final[k]=rline[j]-'0';
					k++;
				}
				i=-1;
				nf=k;
			}
			else
			{
			
				if(rline[j]!=' ')
				{
					if(rline[j]=='-')
						automata[i][k]=-1;
					else
						automata[i][k]=rline[j]-'0';
					cout<<automata[i][k]<<" ";
					k++;
				}
			}
		}
		l=1;
		cout<<"\n";
		i++;
	}
	string inputVal;
	int inputvalIndex;
	while(1)
	{
		cout<<"Enter the string\n";
		cin>>inputVal;
		i=0;
		j=initial;k=0;
		int result;
		while(inputVal[i]!='\0')
		{
			inputvalIndex=inputVal[i]-'a';
			result= automata[j][inputvalIndex];
			j=result;
			if(j==-1)
			break;
			i++;
		}
		int flag=0;
		for(i=0;i<nf;i++)
		{
			if(j==-1)
			break;
			if(j==final[i])
			flag=1;
		}
		if(flag==1)
			cout<<"accept\n";
		else
			cout<<"reject\n";
	}
	return 0;
}
