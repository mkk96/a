/*WAP to verify whether a given CFG is suitable for LL(1) parsing or not.*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
int num_of_productions;
vector<string> productions;
vector<char> terminals;
vector<char> nonTerminals;
vector<string> newProductions;
vector<string> deterministicProductions;
int isInTerminal(char c)
{
	if(find(terminals.begin(),terminals.end(),c)!=terminals.end())
	{
		return 1;
	}
	return 0;
}
int isInNonTerminal(char c)
{
	if(find(nonTerminals.begin(),nonTerminals.end(),c)!=nonTerminals.end())
	{
		return 1;
	}
	return 0;
}
int isTerminal(char tem)
{
	if(tem>='A' && tem<='Z')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int prepareListOfCharacter()
{
	for(int i=0;i<productions.size()-1;i++)
	{
		string tempString=productions[i];
		int tempStringLen = tempString.length();
		for(int j=0;j<tempStringLen;j++)
		{
			char t = tempString[j];
			if(!(t==' '))
			{
				if(isInNonTerminal(t)||isInTerminal(t))
				{
					continue;
				}
				else
				{
					if(isTerminal(t))
					{
						terminals.push_back(t);
					}
					else
					{
						nonTerminals.push_back(t);
					}
				}
			}
		}
	}
	return 1;
}
int readProductions()
{
	string fileName ="";
	cout<<"Enter File Name : ";
	cin>>fileName;
	cout<<endl;
	ifstream input(fileName.c_str());
	string tempString;
	input>>num_of_productions;
	getline(input, tempString, '\n');
	while (getline(input, tempString, '\n')) 
	{
		productions.push_back(tempString);
	}
	cout<<"DATA FROM INPUT FILE BEGINS: "<<endl;
	cout<<"Num Of Productions : "<<num_of_productions<<endl;
	for(int i=0;i<productions.size()-1;i++)
	{
		cout<<productions[i]<<endl;
	}
	cout<<"DATA FROM INPUT FILE ENDS: "<<endl<<endl;
	prepareListOfCharacter();
	cout<<"\nAll The Terminals : ";
	for(int i=0;i<terminals.size();i++)
	{
		cout<<terminals[i]<<" ";
	}
	cout<<"\nAll The Non Terminals : ";
	for(int i=0;i<nonTerminals.size();i++)
	{
		cout<<nonTerminals[i]<<" ";
	}
	cout<<"\n";
	return 1;
}
char nonTermGen()
{
	char nonTerm = 'A';
	while(true)
	{
		if(isInNonTerminal(nonTerm))
		{
			nonTerm += 1;
		}
		else
		{
			return nonTerm;
		}
		if(nonTerm==('Z'+1))
		{
			return '$';
		}
	}
}
int isLeftRecursive(char c)
{
	for(int j=0;j<productions.size();j++)
	{
		string tempString = productions[j];
		if(tempString[0]==c)
		{
			if(!isInNonTerminal(tempString[2]))
			{
				newProductions.push_back(tempString);
			}
			else
			{
				if(tempString[2]==c)
				{
				return 1;
				}
				else
				{
					newProductions.push_back(tempString);
				}
			}
		}
		else
		{
		}
	}
	return 0;
}
int rectifyLeftRecursion(char c)
{
	char newNonTerm = nonTermGen();
	if(newNonTerm=='$')
	{
		cout<<"Ran Out Of Non Terminals To Assign. Too Many Left Recursive Entries.";
		exit;
	}
	vector<string> beta;
	for(int k=0;k<productions.size();k++)
	{
		if(productions[k][0]==c)
		{
			if(productions[k][2]!=c)
			{
				beta.push_back(productions[k]);
			}
		}
	}
	for(int k=0;k<beta.size();k++)
	{
		string betaProduction = beta[k]+newNonTerm;
		if(!isInNonTerminal(newNonTerm))
		{
			nonTerminals.push_back(newNonTerm);
		}
		newProductions.push_back(betaProduction);
	}
	for(int j=0;j<productions.size();j++)
	{
		if(productions[j][0]==c)
		{
			string tempString = productions[j];
			if(tempString[2]==c)
			{
				string alpha = tempString.substr(3);
				string alphaProduction = "";
				alphaProduction += newNonTerm;
				alphaProduction += (" "+alpha);
				alphaProduction += newNonTerm;
				if(!isInNonTerminal(newNonTerm))
				{
					nonTerminals.push_back(newNonTerm);
				}
				newProductions.push_back(alphaProduction);
			}
		}
	}
	string epsilonProduction = "";
	epsilonProduction += newNonTerm;
	epsilonProduction += " #";
	newProductions.push_back(epsilonProduction);
	terminals.push_back(newNonTerm);
	return 1;
}
int printFinalGrammar()
{
	cout<<"\nFINAL LEFT RECURSION FREE GRAMMAR IS : "<<endl;
	for(int i=0;i<newProductions.size();i++)
	{
		cout<<newProductions[i]<<endl;
	}
	return 1;
}
int clearProductions(char c)
{
	vector<string> tempProds=productions;
	int j=0;
	while(true)
	{
		if(tempProds[j][0]==c)
		{
			tempProds.erase(tempProds.begin()+j);
		}
		else
		{
			j++;
		}
		if(j==tempProds.size())
		{
			break;
		}
	}
	productions = tempProds;
	return 1;
}
int isNonDeterministic(char c)
{
	vector<string> tempProductions;
	for(int j=0;j<productions.size();j++)
		{
		string tempString = productions[j];
		if(productions[j][0]==c)
		{
			tempProductions.push_back(productions[j]);
		}
	}
	for(int j=0;j<tempProductions.size();j++)
	{
		string tempString = tempProductions[j];
		for(int k=0;k<tempProductions.size();k++)
		{
			if(tempString==tempProductions[k])
			{
				continue;
			}
			else
			{
				if(tempString.length()>tempProductions[k].length())
				{
					for(int l=tempProductions[k].length();l>1;l--)
					{
						size_t found = tempString.find(tempProductions[k].substr(1,l));
						if(found!=string::npos)
						{
							if(found==1)
							{
								return 1;
							}
						}
					}
				}
				else
				{
					for(int l=tempString.length();l>1;l--)
					{
						size_t found = tempProductions[k].find(tempString.substr(1,l));
						if(found!=string::npos)
						{
							if(found==1)
							{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
int exists(string s)
{
	for(int m=0;m<deterministicProductions.size();m++)
	{
		if(s == deterministicProductions[m])
		{
			return 1;
		}
	}
	return 0;
}
int rectifyNonDeterminism(char c)
	{
	char newNonTerm = nonTermGen();
	if(newNonTerm=='$')
	{
		cout<<"Ran Out Of Non Terminals To Assign. Too Many Non Deterministic Entries.";
		exit;
	}
	vector<string> tempProductions;
	for(int j=0;j<productions.size();j++)
	{
		string tempString = productions[j];
		if(productions[j][0]==c)
		{
			tempProductions.push_back(productions[j]);
		}
	}
	for(int j=0;j<tempProductions.size();j++)
	{
		string tempString = tempProductions[j];
		int flag=0;
		for(int k=0;k<tempProductions.size();k++)
		{
			if(tempString==tempProductions[k])
			{
				continue;
			}
			else
			{
				if(tempString.length()>tempProductions[k].length())
				{
					for(int l=tempProductions[k].length();l>1;l--)
					{
						size_t found =tempString.find(tempProductions[k].substr(1,l));
						if(found!=string::npos)
						{
							if(found==1)
							{
								flag=1;
								if(!isInNonTerminal(newNonTerm))
								{
									nonTerminals.push_back(newNonTerm);
								}
								string newProd1 = "";
								newProd1+=c;
								newProd1 += (" "+tempString.substr(1,l));
								newProd1 += newNonTerm;
								string newProd2 = "";
								newProd2+=newNonTerm;
								newProd2 += (" "+tempString.substr(l+1));
								if(!exists(newProd1))
								{
									deterministicProductions.push_back(newProd1);
								}
								if(!exists(newProd2))
								{
									deterministicProductions.push_back(newProd2);
								}
							}
						}
					}
				}
				else
				{
					for(int l=tempString.length();l>1;l--)
					{
						size_t found = tempProductions[k].find(tempString.substr(1,l));
						if(found!=string::npos)
						{
							if(found==1)
							{
								flag=1;
								if(!isInNonTerminal(newNonTerm))
								{
									nonTerminals.push_back(newNonTerm);
								}
								string newProd1 = "";
								newProd1+=c;
								newProd1 += tempString.substr(1,l);
								newProd1 += newNonTerm;
								string newProd2 = "";
								newProd2+=newNonTerm;
								newProd2 += (" "+tempString.substr(l+1));
								if(!exists(newProd1))
								{
									deterministicProductions.push_back(newProd1);
								}
								if(!exists(newProd2))
								{
									deterministicProductions.push_back(newProd2);
								}
							}
						}
					}
				}
			}
		}
		if(flag==0)
		{
			if(!exists(tempString))
			{
				deterministicProductions.push_back(tempString);
			}
		}
	}
	return 1;
}
int printNDGrammar()
{
	cout<<"\nFINAL NON DETERMINISTIC FREE GRAMMAR IS : "<<endl;
	for(int i=0;i<productions.size();i++)
	{
		cout<<productions[i]<<endl;
	}
	return 1;
}
int main()
{
	cout<<"# => epsilon"<<endl;
	readProductions();
	int flag=0;
	for(int i=0;i<nonTerminals.size();i++)
	{
		if(isNonDeterministic(nonTerminals[i]))
		{
			rectifyNonDeterminism(nonTerminals[i]);
			clearProductions(nonTerminals[i]);
			flag=1;
		}
		else
		{
			for(int j=0;j< productions.size();j++)
			{
				if(productions[j][0]==nonTerminals[i])
				{
					deterministicProductions.push_back(productions[j]);
				}
			}
		}
	}
	if(flag==0)
	{
		cout<<"\nGrammar Is Free Of Non Determinism";
	}
	else
	{
		productions = deterministicProductions;
		printNDGrammar();
	}
	flag=0;
	for(int i=0;i<nonTerminals.size();i++)
	{
		if(isLeftRecursive(nonTerminals[i]))
		{
			rectifyLeftRecursion(nonTerminals[i]);
			clearProductions(nonTerminals[i]);
			flag=1;
		}
	}
	if(flag==0)
	{
		cout<<"\nGrammar Is Free Of Left Recursion"<<endl;
	}
	else
	{
		printFinalGrammar();
		productions = newProductions;
	}
	flag=0;
	return 1;
}
