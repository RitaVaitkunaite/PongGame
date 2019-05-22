#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <sstream>


Game::Game()
{
	hitPlayer = false;
	hitEnemy = false;
	ballx = 1.5f;
	bally = 1.5f;
	scorePlayer = 0;
	scoreEnemy = 0;
	meniuChoice = -1;
	currentChoice = true;
	exitGame = false;

}

void Game::Textures()
{
	enemy.setPosition(900.0f, 31.0f);
	enemyTexture.loadFromFile("ronaldo8.png");
	enemy.setTexture(enemyTexture);
	ball.setPosition(400.0f, 100.0f);
	ballTexture.loadFromFile("ball4.png");
	ball.setTexture(ballTexture);
	pitchTexture.loadFromFile("pitch1.jpg");
	pitch.setTexture(pitchTexture);
	meniuBackgroundTexture.loadFromFile("fonas2.png");
	meniuBackground.setTexture(meniuBackgroundTexture);
	player.setPosition(1.0f, 0.0f);
  playerTexture.loadFromFile("messi4.png");
	player.setTexture(playerTexture);
	stilius.loadFromFile("font.otf");
	rezultatas.setFont(stilius);
	rezultatas.setPosition(433.0f, 50.0f);
	rezultatas.setCharacterSize(100.0f);
	rezultatas.setFillColor(sf::Color::Black);
	rezultatas1.setFillColor(sf::Color::Black);
	rezultatas1.setFont(stilius);
	rezultatas1.setPosition(520.0f, 50.0f);
	rezultatas1.setCharacterSize(100.0f);
	stilius1.loadFromFile("fontas.otf");
	meniu[0].setFont(stilius1);
	meniu[1].setFont(stilius1);
	meniu[0].setFillColor(sf::Color::Green);
	meniu[1].setFillColor(sf::Color::Blue);
	meniu[0].setPosition(430.0f, 400.0f);
	meniu[1].setPosition(430.0f, 500.0f);
	meniu[0].setCharacterSize(70.0f);
	meniu[1].setCharacterSize(70.0f);
	meniu[0].setString("PLAY");
	meniu[1].setString("EXIT");
	

}

void Game::PlayerMovement()
{
	sf::Vector2f position = player.getPosition();
	if (position.y < 555)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			player.move(0.0f, 1.0f); 

		}
	}
	if (position.y > -2.0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			player.move(0.0f, -1.0f);

		}
	}
}

void Game::BallMovement()

{  
	ball.move(ballx,bally);
	sf::Vector2f ballPosition = ball.getPosition();
	if (ballPosition.y >= 800 || ballPosition.y <= -2.0)
	{
		bally *= -1;
	}
	if (CheckCollision(ball, player) == true && hitPlayer == false )
	{
		ballx = 1.9f;
		// ballx *= -1;
		if (bally < 0)
		{
			bally = -0.8f;
		}
		else if (bally > 0)
		{
			bally = 0.8f;
		}
		hitPlayer = true;
		hitEnemy = false;
	}
	else if (CheckCollision(ball, enemy) == true && hitEnemy == false)
	{
		ballx = -1.5f;
		//ballx *= -1;
		if (bally < 0)
		{
			bally = -0.6f;
		}
		else if (bally > 0)
		{
			bally = 0.6f;
		}
		hitEnemy = true;
		hitPlayer = false;
	}
}
void Game::EnemyMovement()
{
	sf::Vector2f enemyposition = enemy.getPosition();
	sf::Vector2f ballposition = ball.getPosition();
	if (enemyposition.y < 555)
	{
		if (ballposition.y > enemyposition.y)
		{
			enemy.move(0.0f,0.6f);
		}
	}
	if (enemyposition.y > -2.0)
	{
    if (ballposition.y < enemyposition.y)
	{
		enemy.move(0.0f, -0.6f);
	}
	}

}


bool Game::CheckCollision(sf::Sprite& player, sf::Sprite& ball)
{
	return player.getGlobalBounds().intersects(ball.getGlobalBounds());

}
void  Game::GameScore()
{

	std::stringstream ss;
	std::stringstream ss1;
	ss << scorePlayer;
	rezultatas.setString(ss.str());
	ss1 << scoreEnemy;
	rezultatas1.setString(ss1.str());

	sf::Vector2f ballposition = ball.getPosition();
	if (ballposition.x <= -100)
	{
		scoreEnemy++;
		ball.setPosition(300.0f, 400.0f);
		
	}
	if (ballposition.x >= 1000)
	{
		scorePlayer++;
		ball.setPosition(800.0f, 400.0f);
		
	}
}
void Game::GameOver()
{
	if (scorePlayer == 11)
	{
		scorePlayer = 0;
		scoreEnemy = 0;
	}
	else if (scoreEnemy == 11)
	{
		scorePlayer = 0;
		scoreEnemy = 0;
	}

}
void Game::Meniu()
{    
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) )
	{
		meniuChoice = 1;
		meniu[0].setCharacterSize(50.0f);
		meniu[1].setCharacterSize(80.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		meniuChoice = 0;
		meniu[0].setCharacterSize(80.0f);
		meniu[1].setCharacterSize(50.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (meniuChoice == 0)
		{
		   currentChoice = false;
		}
		else if (meniuChoice == 1)
		{
			currentChoice = false;
			exitGame = true;

		}
	}
}

void Game::MainWindow()
{
	sf::RenderWindow window(sf::VideoMode(1000, 850), "Pong Game", sf::Style::Close | sf::Style::Resize);
	Textures();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "New window width" << event.size.width << "New window height" << event.size.height << std::endl;
				break;
			}
		}
		if (exitGame == true)
		{
			window.close();
		}
		if (currentChoice == true)
		{
			Meniu();
			window.clear();
			window.draw(meniuBackground);
			window.draw(meniu[0]);
			window.draw(meniu[1]);
			window.display();
		}
		else {

			PlayerMovement();
			BallMovement();
			EnemyMovement();
			GameScore();
			GameOver();
			window.clear();
			window.draw(pitch);
			window.draw(player);
			window.draw(enemy);
			window.draw(ball);
			window.draw(rezultatas);
			window.draw(rezultatas1);

			window.display();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			currentChoice = true;
		}
	}



}

Game::~Game()
{
}
