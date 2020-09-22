#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include <SFML\System\String.hpp>
#include <SFML/Audio.hpp>
using namespace std;


const int GameField_Height = 14;
const int GameField_Width = 12;

const int SquareBlocks_Height = 7;
const int SqiareBlocks_Width = 4;



class Tetris {

public:    

  Tetris();   
~ Tetris();  

public:

	// functions
	bool check();
	void moveToLeft();
	void moveToRight();
	void moveDown();
	void rotateFigure();
	void dropDown();
	void checkLines();
	void generateFigure();
	void defaultGameField();
	void restartGame();
	int getHighScore();
	

	sf::Text createScoreText();
	sf::Text createGameOverText();
	sf::Text createStartText();
	sf::Text createRestartText();
	sf::Text createTitleText();
	sf::Text createHighScoreText();





public:   

	// For demonstration, all the member variables are made public
	string m_stGameTitle;
	int m_iGameField[GameField_Height][GameField_Width] = { 0 };
	int m_iMoveRate;
	int m_iColour;
	int m_iFigureNumber;
	float m_fTimer;
	float m_fDelay;
	bool m_GameStarted;
	int m_iScore;
	int m_iComboCount;
	bool m_bGameOver;
	bool m_bOnStartPage;
	int m_iHighScore;

	// A set of Y and X coodinates for each of the 4 squares
	Point m_Point_A[4] = { 0 };
	Point m_Point_B[4] = { 0 };

	string m_stSquarePicture;
	string m_stBackgroudPicture;
	string m_stStartPagePicture;

	// A coordinates system to assemble the squares to form different figures.
	const int m_iSquareBlocks[SquareBlocks_Height][SqiareBlocks_Width] = 
	{
          {1,3,5,7}, // I
          {2,4,5,7}, // Z
          {3,5,4,6}, // S
          {3,5,4,7}, // T
          {2,3,5,7}, // L
          {3,5,7,6}, // J
          {2,3,4,5}  // O
	};
	
};

