#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include "Tetris.h"
using namespace std;

Tetris tetris;


int main() {

	//Use SFML to load up the Tetris graphics and put them in Sprites

	sf::RenderWindow window(sf::VideoMode(665, 780), tetris.m_stGameTitle);
	sf::Texture squareTexture, background, startpage;
	squareTexture.loadFromFile(tetris.m_stSquarePicture);
	background.loadFromFile(tetris.m_stBackgroudPicture);
    startpage.loadFromFile(tetris.m_stStartPagePicture);
	sf::Sprite squareSprite(squareTexture);
	sf::Sprite backgroundSprite(background);
    sf::Sprite startpageSprite(startpage);
    startpageSprite.setScale(1.2, 1);
	

	// Retrieve text lables
    
    sf::Text textPostGame = tetris.createRestartText();
    sf::Text textForGameOver = tetris.createGameOverText();
    sf::Text textForScore = tetris.createScoreText();
    sf::Text textForTitle = tetris.createTitleText();
    sf::Text textForStart = tetris.createStartText();
    sf::Text textForHighScore = tetris.createHighScoreText();

    // Load font
	sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Font not found!" << endl;
    }

    textForGameOver.setFont(font);
    textPostGame.setFont(font);
    textForTitle.setFont(font);
    textForStart.setFont(font);

    // Create a clock object
	sf::Clock clock;

    while (window.isOpen()) {

        // Set up a timer
        float time = clock.getElapsedTime().asSeconds();

        clock.restart();

        tetris.m_fTimer += time;

        sf::Event event;

        // Listen to button events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Up) {
                    tetris.rotateFigure();
                    
                    
                }
                if (event.key.code == sf::Keyboard::Right) {
                    tetris.moveToRight();
                }
                if (event.key.code == sf::Keyboard::Left) {
                    tetris.moveToLeft();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                     
                    tetris.restartGame();
                }

                if (event.key.code == sf::Keyboard::Escape) {
                    return 0;
                }

            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            tetris.moveDown();
        }


         
        // Check if Start screen is on
        if (tetris.m_bOnStartPage) {

            // Display the Start screen
            window.clear(sf::Color::White);
            window.draw(startpageSprite);
            window.draw(textForTitle);
            window.draw(textForStart);



        } else {

            // Let the figure drop
            tetris.dropDown();

            // Check if any line is filled
            tetris.checkLines();

            // Restore the default delay
            tetris.m_fDelay = 0.5;


           
            // Output the elements on the screen

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);

            // Load live score and the highest personal score
            textForScore = tetris.createScoreText();
            textForHighScore = tetris.createHighScoreText();
            textForScore.setFont(font);
            textForHighScore.setFont(font);
            window.draw(textForScore);
            window.draw(textForHighScore);

            // Check if game is over. Otherwise fill the positions in the
            // game field with the squares with their coresponding colours
            for (int i = 0;i < GameField_Width;i++) {

                if (tetris.m_iGameField[1][i] != 0) {

                    window.clear(sf::Color::White);
                    window.draw(backgroundSprite);
                    window.draw(textForGameOver);
                    window.draw(textPostGame);
                    window.draw(textForScore);
                    tetris.m_bGameOver = 1;
                    break;

                }
                else {

                    // Define and record the colours and coordinates of the squares that have landed
                    // And draw the squares on the screen
                    for (int i = 0;i < 14;i++) {
                        for (int j = 0;j < 12;j++) {
                            if (tetris.m_iGameField[i][j] == 0) {
                                continue;
                            }
                            squareSprite.setTextureRect(sf::IntRect(tetris.m_iGameField[i][j] * 56, 0, 56, 56));
                            squareSprite.setPosition(j * 56, i * 56);
                            window.draw(squareSprite);
                        }
                    }
                }
            }

            // When game starts, randomly generate a figure
            if (!tetris.m_GameStarted) {

                tetris.generateFigure();
                tetris.m_GameStarted = !tetris.m_GameStarted;
            }

            // Keep drawing the falling figure at each new position 
            if (!tetris.m_bGameOver) {
                for (int i = 0;i < 4;i++)
                {
                    squareSprite.setTextureRect(sf::IntRect(tetris.m_iColour * 56, 0, 56, 56));
                    squareSprite.setPosition(tetris.m_Point_A[i].iPointX * 56, tetris.m_Point_A[i].iPointY * 56);
                    window.draw(squareSprite);
                }

            }
        }

        window.display();

    }

		return 1;
}