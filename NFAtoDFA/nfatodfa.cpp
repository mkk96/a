#include <stdio.h>
#include <string.h>
#define STATES 256
#define SYMBOLS 20
int N_symbols;
int NFA_states;
char *NFAtab[STATES][SYMBOLS];
int DFA_states; 
int DFAtab[STATES][SYMBOLS];
void put_dfa_table(int tab[][SYMBOLS], int nstates, int nsymbols) 
{
	int i, j;
	puts("STATE TRANSITION TABLE");
	printf(" | ");
	for (i = 0; i < nsymbols; i++) printf(" %c ", '0'+i);
		printf("\n-----+--");
	for (i = 0; i < nsymbols; i++) printf("-----");
		printf("\n");
	for (i = 0; i < nstates; i++) 
	{
		printf(" %c | ", 'A'+i); 
		for (j = 0; j < nsymbols; j++)
			printf(" %c ", 'A'+tab[i][j]);
		printf("\n");
	}
}
void init_NFA_table()
{
	NFAtab[0][0] = "12";
	NFAtab[0][1] = "13";
	NFAtab[1][0] = "12";
	NFAtab[1][1] = "13";
	NFAtab[2][0] = "4";
	NFAtab[2][1] = "";
	NFAtab[3][0] = "";
	NFAtab[3][1] = "4";
	NFAtab[4][0] = "4";
	NFAtab[4][1] = "4";
	NFA_states = 5;
	DFA_states = 0;
	N_symbols = 2;
}
void string_merge(char *s, char *t)
{
	char temp[STATES], *r=temp, *p=s;
	while (*p && *t) 
	{
		if (*p == *t) 
		{
			*r++ = *p++; t++;
		} 
		else if (*p < *t) 
		{
			*r++ = *p++;
		} else
		{
			*r++ = *t++;
		}
		
	}
	*r = '\0';
	if (*p) strcat(r, p);
	else if (*t) strcat(r, t);
	strcpy(s, temp);
}
void get_next_state(char *nextstates, char *cur_states, char *nfa[STATES][SYMBOLS], int n_nfa, int symbol)
{
	int i;
	char temp[STATES];
	temp[0] = '\0';
	for (i = 0; i < strlen(cur_states); i++)
	string_merge(temp, nfa[cur_states[i]-'0'][symbol]);
	strcpy(nextstates, temp);
}
int state_index(char *state, char statename[][STATES], int *pn)
{
	int i;
	if (!*state) 
		return -1;
	for (i = 0; i < *pn; i++)
		if (!strcmp(state, statename[i])) 
			return i;
	strcpy(statename[i], state); 
	return (*pn)++;
}
int nfa_to_dfa(char *nfa[STATES][SYMBOLS], int n_nfa, int n_sym, int dfa[][SYMBOLS])
{
	char statename[STATES][STATES];
	int i = 0;
	int n = 1; 
	char nextstate[STATES];
	int j;
	strcpy(statename[0], "0");
	for (i = 0; i < n; i++)
	{ 
		for (j = 0; j < n_sym; j++) 
		{ 
			get_next_state(nextstate, statename[i], nfa, n_nfa, j);
			dfa[i][j] = state_index(nextstate, statename, &n);
		}
	}
	return n;
}
int main()
{
	init_NFA_table();
	DFA_states = nfa_to_dfa(NFAtab, NFA_states, N_symbols, DFAtab);
	put_dfa_table(DFAtab, DFA_states, N_symbols);
	return 0;
}
