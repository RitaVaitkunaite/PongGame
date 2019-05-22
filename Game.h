#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

class Game
{
private:
	int meniuChoice;
	bool exitGame;
	bool currentChoice;
	bool hitPlayer;
	bool hitEnemy;
	sf::Text meniu[2];
	sf::Font meniuStilius;
	sf::Font stilius1;
	sf::Text rezultatas1;
	sf::Text rezultatas;
	sf::Font stilius;
	int scorePlayer,scoreEnemy;
	float ballx, bally;
	sf::Sprite meniuBackground;
	sf::Texture meniuBackgroundTexture;
	sf::Texture ballTexture;
	sf::Sprite ball;
	sf::Texture pitchTexture;
	sf::Sprite pitch;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Sprite player;
	sf::Sprite enemy;

public:
	Game();
  
	void Textures();

	void MainWindow();
	
	void PlayerMovement();

	void BallMovement();

	bool CheckCollision(sf::Sprite& player, sf::Sprite& ball);
  
	void EnemyMovement();
  
	void GameScore();
  
	void GameOver();
  
	void Meniu();

	~Game();
};

