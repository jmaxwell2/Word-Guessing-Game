// Jordan Maxwell
// November 13, 0202
// This program implements a word-guessing game

#include <iostream>
#include <ctime>
#include "graph1.h"
#include "WordGame.h"

using namespace std; 

int main()
{   
    int score = 0;
    int totalScore = 0;
    bool repeat;

    
        //Variable Declaration/Initialization
        string fn;

        //Display graphics
        displayGraphics();

        //Initialize random # generator
        srand(time(0));

        // Set the filename
        fn = "words1.txt";


    do {

        // More variables
        int rand_no = 0;
        WordGame game;

        //Set the filename
        game.setFileName(fn);

        //Generate random #
        rand_no = rand() % 1149;

        //Set the word
        game.setWord(rand_no);

        // Draw the boxes
        game.draw();

        // Invoke the Play method
        score = game.play();
        totalScore = totalScore + score;
        gout << setPos(100, 75) << setColor(0, 255, 0) << "Total Score: " << totalScore << endg;

        // Promt to run the program again
        cout << "\n\nPlay again? <1 for YES, 0 for NO>: ";
        cin >> repeat;
        cin.get();

        // clear the graphics window
        clearGraphics();
        gout << setPos(100, 75) << setColor(0, 255, 0) << "Total Score: " << totalScore << endg;

    } while (repeat);
}
