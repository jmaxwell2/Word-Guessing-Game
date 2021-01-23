#include <iostream>
#include <cstring>
#include <fstream>
#include "graph1.h"
#include "WordGame.h"

using namespace std; 

WordGame::WordGame()
{
	fileName = "";
	word = "";
}

string WordGame::getFileName()
{
	return fileName;
}

void WordGame::setFileName(string fn)
{
	fileName = fn; 
}

void WordGame::setWord(int rand_no)
{
	string temp;

	//create a word counter
	int word_count = 0;

	// open the file we are reading
	fstream in_file(fileName, ios::in);

	// test the file
	if (!in_file)
		cout << "\n\nError opening file";

	// read
	while (true)
	{
		in_file >> temp;

		// test for end of file
		if (in_file.eof())
			break;

		if (word_count == rand_no)
		{
			word = temp;
			break;
		}

		++word_count;
	}

	in_file.close();

}

string WordGame::getWord()
{
	return word; 
}

void WordGame::draw()
{
	int startx = 100;
	int starty = 200;
	int box;

	for (int i = 0; i < word.length(); i++)
	{
		box = drawRect(startx, starty, 32, 32);
		setColor(255, 255, 255);
		startx = startx + 33;
	}

	Sleep(2000);

	clearGraphics();
}

int WordGame::play()
{
	int startx = 100;
	int starty = 200;
	int box; 
	int letterBoxes;
	string letter;

	// dynamically allocated array of booleons that show if 
	// the letters have been displayed or not
	bool* revealed = new bool[word.length()];
	*revealed = { 0 };

	// display the first letter 
	letter = word[0];
	letter = letter + ".bmp";
	displayBMP(letter, startx, starty); 
	revealed[0] = 1; 

	// display the hints
	for (int i = 1; i < word.length(); i++)
	{
		startx += 33;

		if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
		{
			letter = word[i];
			letter = letter + ".bmp";
			displayBMP(letter, startx, starty); 
			revealed[i] = 1;
		}	
		else
		{
			box = drawRect(startx, starty, 32, 32);
			setColor(255, 255, 255);
			revealed[i] = 0;
		}
	}

	int round = 1;
	string guess; 
	int empty = 0;
	int score = 0;
	int chances = 0;

		// calculates the number of chances 
		for (int i = 0; i < word.length(); i++)
		{
			if (revealed[i] == 0)
				chances = chances + 1;
		}

	// promt for the user to guess the remaining letters
	for (int i = 1; i < word.length(); i++)
	{
		gout << setPos(100, 120) << setColor(0, 255, 0) << "Guess Number: " << round << endg;

		cout << "\nGuess #" << round << endl;
		cout << "What is the word? ";
		cin >> guess; 

		// if guessed CORRECTLY!!!
		if (guess == word) 
		{
			for (int i = 0; i < word.length(); i++)
			{
				if (revealed[i] == 0)
					empty = empty + 1;
			}

			score = empty * 10; 

			//gout << setPos(100, 75) << setColor(0, 255, 0) << "Total Score: " << score << endg;
			gout << setPos(100, 105) << setColor(0, 255, 0) << "!!!Correct!!!" << endg;
			gout << setPos(100, 120) << setColor(0, 255, 0) << "Number of Guesses: " << round << endg;
			gout << setPos(100, 135) << setColor(0, 255, 0) << "Score: " << score << endg;

			startx = 100;

			for (int i = 0; i < word.length(); i++)
			{
				if (revealed[i] == 1)
				{
					startx += 33;
				}

				else if (revealed[i] == 0)
				{
					letter = word[i];
					letter = letter + ".bmp";
					displayBMP(letter, startx, starty);
					revealed[i] = 1;

					startx += 33;
				}
			}
			break;
		}
		
		// NOT guessed!!!
		else
		{
			gout << setPos(100, 105) << setColor(0, 255, 0) << "!!!Inorrect!!!" << endg;
			

			if (round % 2 == 1)
			{
				startx = 100;
				for (int i = 0; i < word.length(); i++)
				{
					if (revealed[i] == 1)
					{
						startx += 33;
					}

					else if (revealed[i] == 0)
					{
						letter = word[i];
						letter = letter + ".bmp";
						displayBMP(letter, startx, starty);
						revealed[i] = 1;

						break;
					}
				}
			}

			else if (round % 2 == 0)
			{
				startx = 100 + (((word.length()) - 1) * 33);
				for (int i = word.length() - 1; i > -1; i--)
				{
					if (revealed[i] == 1)
					{
						startx -= 33;
					}

					else if (revealed[i] == 0)
					{
						letter = word[i];
						letter = letter + ".bmp";
						displayBMP(letter, startx, starty);
						revealed[i] = 1;

						break;
					}
				}
			}
		}

		if (round == chances)
		{
			//gout << setPos(100, 75) << setColor(0, 255, 0) << "Total Score: " << score << endg;
			gout << setPos(100, 105) << setColor(0, 255, 0) << "!!!Game Over!!!" << endg;
			gout << setPos(100, 120) << setColor(0, 255, 0) << "Correct Answer: " << word << endg;
			gout << setPos(100, 135) << setColor(0, 255, 0) << "Score: 0" << endg;

			break;
		}

		++round;
	}

	
	delete[] revealed; 

	return score;
}