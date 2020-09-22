#include "Tetris.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor
Tetris::Tetris()
    :m_iMoveRate(0),
    m_iColour(1),
    m_iFigureNumber(0),
    m_fTimer(0),
    m_fDelay(0.5),
    m_GameStarted(0),
    m_iScore(0),
    m_iComboCount(1),
    m_bGameOver(0),
    m_bOnStartPage(1),
    m_iHighScore(0)
{

    m_stSquarePicture = "tetris_pic.jpg";
    m_stBackgroudPicture = "sky.jpg";
    m_stGameTitle = "True Tetris";
    m_stStartPagePicture = "start.jpg";

   
}
// Destructor
Tetris::~Tetris() {}

// Functions 

// Check if a position has been filled or out of bound
bool Tetris::check() {

    for (int i = 0;i < 4;i++) {
        if (m_Point_A[i].iPointX < 0 || m_Point_A[i].iPointX >= 12 || m_Point_A[i].iPointY >= 14) {
            return 0;
        }
        else if (m_iGameField[m_Point_A[i].iPointY][m_Point_A[i].iPointX] > 0) {
            return 0;
        }

    }
    return 1;
}



// To move left
void Tetris::moveToLeft() {

    m_iMoveRate = -1;

    for (int i = 0;i < 4;i++)
    {
        m_Point_B[i] = m_Point_A[i];

        m_Point_A[i].iPointX += m_iMoveRate;

    }

    // Return to previous coordinates if there is no way through.
    if (!check()) {
        for (int i = 0;i < 4;i++) {
            m_Point_A[i] = m_Point_B[i];
        }
    }


}


 // To move right
void Tetris::moveToRight() {
    
    m_iMoveRate = 1;

    for (int i = 0;i < 4;i++)
    {
        m_Point_B[i] = m_Point_A[i];

        m_Point_A[i].iPointX += m_iMoveRate;

    }

    // Return to previous coordinates if there is no way through.
    if (!check()) {
        for (int i = 0;i < 4;i++) {
            m_Point_A[i] = m_Point_B[i];
        }
    }
}

 // To move down faster
void Tetris::moveDown() {

    // Reduce the response time for the figure to move down
    m_fDelay = 0.07;
}

  // To rotate the figure
void Tetris::rotateFigure() {

    // The square figure cannot be rotated (when m_iFigure = 6)
    if (m_iFigureNumber != 6) {
        
        
            // Center of rotation
            Point p = m_Point_A[1]; 
            for (int i = 0;i < 4;i++)
            {
                m_Point_B[i] = m_Point_A[i];
                int x = m_Point_A[i].iPointY - p.iPointY;
                int y = m_Point_A[i].iPointX - p.iPointX;

               m_Point_A[i].iPointX = p.iPointX - x;
               m_Point_A[i].iPointY = p.iPointY + y;
            }

            // Check if there is enough space for the figure to rotate. 
            // If not, return to previous coordinates

            if (!check()) {
                for (int i = 0;i < 4;i++) {
                    m_Point_A[i] = m_Point_B[i];
                }
            }
        
    }
}

 // To drop down at each time interval
void Tetris::dropDown() {

    if (m_fTimer > m_fDelay && !m_bGameOver) {

        for (int i = 0;i < 4;i++)
        {
           m_Point_B[i] = m_Point_A[i];
            m_Point_A[i].iPointY += 1;


        }

        // If the figure lands on previous figures or on the bottom of the frame,
        // mark the positions in game field with the colour integer.

        if (!check()) {
            for (int i = 0;i < 4;i++) {
                m_iGameField[m_Point_B[i].iPointY][m_Point_B[i].iPointX] = m_iColour;
            }

            // To randomly generate a new figure 
            generateFigure();

        }
        m_fTimer = 0;

    }


}

 // To check if a line has been filled. 
 //If so, replace it with the immediate upper level

void Tetris::checkLines() {


    int k = GameField_Height - 1;
    for (int i = GameField_Height - 1;i > 0;i--)
    {
        int count = 0;

        for (int j = 0;j < GameField_Width;j++)
        {   
            // Count how many blocks are filled in a row
            if (m_iGameField[i][j]) { 
                count++; 
            }

            // Replace the last row 
            m_iGameField[k][j] =m_iGameField[i][j];
        }
            // Check if last row needs to be replaced
        if (count < GameField_Width) { 
            
            k--; 
         
            m_iComboCount = 1; 
        }
        if (count == GameField_Width) {

            // To score bonus points when multiple lines are removed 
            // at the same time or consecutively
            
            m_iScore = m_iScore + 10 * m_iComboCount;
            m_iComboCount += 1;
            
        }
    }

}

// Randomly generate a figure by assembling 4 squares
void Tetris::generateFigure() {

    srand(time(0));
    m_iColour = 1 + rand() % 7;
    m_iFigureNumber = rand() % 7;
    for (int i = 0;i < 4;i++)
    {   
        // Add 5 to xPoint so the figure will be pushed to the middle
        m_Point_A[i].iPointX = m_iSquareBlocks[m_iFigureNumber][i] % 2 + 5;
        m_Point_A[i].iPointY = m_iSquareBlocks[m_iFigureNumber][i] / 2;
    }

}

// Restore the default game field for new games
void Tetris::defaultGameField() {

    for (int i = 0; i < GameField_Height;i++) {

        for (int j = 0; j < GameField_Width; j++) {

            m_iGameField[i][j] = { 0 };
        }


    }
    
}

// Restart a game
void Tetris::restartGame() {

           defaultGameField();
           m_bGameOver = 0;
           m_GameStarted = 0;
           m_iScore = 0;
           m_bOnStartPage = 0;

}

// Define a Game Over text label
sf::Text Tetris::createGameOverText() {
    sf::Text text;
    text.setString("Game Over!");
    text.setPosition(132, 300);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Magenta);

    return text;

}

// Define a Score text label
sf::Text Tetris::createScoreText() {
    sf::Text text;
    text.setString("Score: " + to_string(m_iScore));
    text.setPosition(35, 3);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(25);

    return text;

}

// Define a Restart text label
sf::Text Tetris::createRestartText() {
    sf::Text text;
        text.setString("Press Enter to restart or ESC to quit.");
        text.setPosition(115,450);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

    return text;

}

// Define a Start text label
sf::Text Tetris::createStartText() {
    sf::Text text;
    text.setString("Press Enter to start.");
    text.setPosition(200, 460);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    return text;

}

// Define a Game Title text label
sf::Text Tetris::createTitleText() {
    sf::Text text;
    text.setString("TRUE TETRIS");
    text.setPosition(75, 100);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Magenta);
    text.setStyle(sf::Text::Bold);

    return text;

}

 // Get the highest score
int Tetris::getHighScore() {

    if (m_iHighScore >= m_iScore) {

        return m_iHighScore;
    }
    else {

        m_iHighScore = m_iScore;
        return m_iHighScore;
    }

}

 // Create a text label for high score
sf::Text Tetris::createHighScoreText() {
    sf::Text text;
    text.setString("High: " + to_string(getHighScore()));
    text.setPosition(500, 3);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(25);

    return text;

}

