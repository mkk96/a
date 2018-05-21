#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#define MAX_ROWS 5
#define MAX_COLS 5
#define INPUT_FILE "input.txt"
int state_matrix[MAX_ROWS][MAX_COLS];
int output_matrix[MAX_ROWS][MAX_COLS];
void print_arr(int arr[], int size) 
{
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
void print_matrix(int mat[][MAX_COLS], int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		print_arr(mat[i], cols);
	}
	cout << endl;
}
void read_file()
{
	ifstream file("input.txt");
	/*if (!file.is_open())
	{
		cerr << "Couldn't open input file: " << INPUT_FILE;
	}*/
	string line;
	int i = 0;
	while (getline(file, line))
	{
		string cell;
		istringstream line_stream(line);
		int j = 0;
		while(getline(line_stream, cell, ' '))
		{
			state_matrix[i][j] = cell[0] - 48;
			output_matrix[i][j] = cell[2] - 48;
			j++;
		}
		i++;
	}
}
int main(int argc, char const *argv[])
{
	read_file();
	int cur_state = 0;
	int cur_output = 0;
	string input;
	cout << "Enter input string: ";
	cin >> input;
	cout << endl;
	cout << "Output: " << endl << endl;
	cout << "S - O" << endl;
	cout << "-----" << endl;
	int length = input.length();
	for (int i = 0; i < length; ++i)
	{
		int cur_input = input[i] - '0';
		cur_state = state_matrix[cur_state][cur_input];
		cur_output = output_matrix[cur_state][cur_input];
		cout << cur_state << " - " << cur_output << endl;
	}
	return 0;
}
