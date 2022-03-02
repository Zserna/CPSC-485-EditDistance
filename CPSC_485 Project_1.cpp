// CPSC_485 Project_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*--------------------------------------------------------------------

CPSC485-Project1

Name:			Zach Serna
Class:			CPSC-485
Section:		01
last 4 digits of CWID: 2152


Language Used: C++

Description: An Edit distance program which calculate the distance
2 words are from one another. Program first creates the alignment 
matrix from top to bottom, then iterates through the matrix again
from bottom to top to find the optimal path


HOW TO RUN:

1. Open the program inside of visual studio, then run the program
using F5.

2. Enter in Word 1 followed by ENTER.

3. Enter in Word 2 followed by ENTER.

4. The aligment matrix along with the edit distance will then be displayed below


---------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include<algorithm>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int main()
{

	//Variables. . .
	string word1;
	string word2;

	//created array of size 50, since no word in the english language has this many letters
	//fill array with value impossible to reach, to ensure array does not go out of bounds
	int matrix[50][50];


	//Request words from user
	cout << "Enter Word 1: ";
	cin >> word1;

	cout << "\nEnter Word 2: ";
	cin >> word2;


	//initialize vectors outer row
	for (size_t i = 0; i < word1.length() + 1; i++)
	{
		//matrix[i][0].push_back(i);
		matrix[i][0] = i;
	}

	//initialize vectors outer column
	for (size_t j = 1;  j < word2.length() + 1; j++)
	{
		//matrix[0][j].push_back(j);
		matrix[0][j] = j;
	}


	/*----------------------------------------------------------------
		Loop will iterate through rows to fill in matrix
		Compares letters in words to see if they match:

		IF they match, compare left, left substituteonal, and above to find
		smallest value, place that value in box

		ELSE they don't match, compare left, left substituteonal, and above to find
		smallest value, ADD 1 and place that value in box 

		Add some way to track path of the variable and place it at the bottom
		Possibly make a string holder for the path
	----------------------------------------------------------------*/

	for (int i = 1; i < word1.length() + 1; i++)
	{
		for (int j = 1; j < word2.length() + 1; j++)
		{
			//compare the letters of word1 and word 2,  they match, move the smallest value to the
			//current column, ELSE,  smallest value + 1

			//variables to handle column assignment
			int insertion = matrix[i][j - 1];
			int substitute = matrix[i - 1][j - 1];
			int deletion = matrix[i - 1][j];
			int smallest = insertion;
		
			//if word matches, move diagonal to column
			if (word1[i - 1] == word2[j - 1])
			{
				matrix[i][j] = substitute;
			}
			//else, find smallest and add 1
			else
			{


				//find smallest of left, substitute left, and deletion
				if (smallest > substitute)
				{
					smallest = substitute;
				}
				if (smallest > deletion)
				{
					smallest = deletion;
				}

				matrix[i][j] = smallest + 1;
			}


		}
	}




	//test print
	for (int i = 0; i < word1.length() + 1; i++)
	{
		for (int j = 0; j < word2.length() + 1; j++)
		{
			cout << matrix[i][j] << "   ";
		}

		cout << endl;
	}


	
	//variables for 2nd iteration through
	int row = word1.length();
	int col = word2.length();

	//strings to keep track of the path of the words
	string word1Path;
	string word2Path;
	int largest;
	if (word1.length() > word2.length())
	{
		largest = word1.length();
	}
	else
	{
		largest = word2.length();
	}

	for (int i = largest ; i > 0; i--)
	{
		//variables to handle column assignment
		int insertion = matrix[row - 1][col];
		int substitute = matrix[row - 1][col - 1];
		int deletion = matrix[row][col - 1];

		//in cases where all are equal, favor substitution
		if ((substitute == insertion) && (substitute == deletion))
		{
			//move up 1 row and col
			row--;
			col--;

			word1Path.push_back(word1[row]);
			word2Path.push_back(word2[col]);

		}
		//if substitution is smallest
		else if ((substitute < insertion) && (substitute < deletion) && row !=0 && col != 0)
		{
			//move up 1 row and col
			row--;
			col--;

			word1Path.push_back(word1[row]);
			word2Path.push_back(word2[col]);

		}
		//in deletion is smallest
		else if ((deletion < substitute) && (deletion < insertion) && col != 0)
		{
			//move left 1 column;
			col--;

			//add space for word1 path, 
			//add proper letter for word2 path
			word2Path.push_back(word2[col]);
			word1Path.push_back('_');


		}

		//if insertion is smallest
		else if ((insertion < substitute) && (insertion < deletion) && row != 0)
		{
			//move down 1 row
			row--;

			//add proper letter for word1 path
			//add space for word2 path
			word1Path.push_back(word1[row]);
			word2Path.push_back('_');


		}
		else
		{
			//if col is 0, we have to move up, use insertion
			if (col == 0)
			{
				//move down 1 row
				row--;
				//add proper letter for word1 path
				//add space for word2 path
				word1Path.push_back(word1[row]);
				word2Path.push_back('_');
			}
			//if row is 0, we have to move left, use deletion
			else if (row == 0)
			{
				//move left 1 column;
				col--;

				//add space for word1 path, 
				//add proper letter for word2 path
				word2Path.push_back(word2[col]);
				word1Path.push_back('_');
			}
			//otherwise, move diag
			else
			{
				//move up 1 row and col
				row--;
				col--;

				word1Path.push_back(word1[row]);
				word2Path.push_back(word2[col]);
			}

		}

	}

	//flip the words around since we went from the bottom to the top
	reverse(word1Path.begin(), word1Path.end());
	reverse(word2Path.begin(), word2Path.end());


	//Display results

	int eDistance = matrix[word1.length()][word2.length()];
	cout << "Results: " << endl;
	cout << "word 1: " << word1Path << endl;
	cout << "word 2: " << word2Path << endl;
	cout << "Edit Distance: " << eDistance;


	
	return 0;
}
