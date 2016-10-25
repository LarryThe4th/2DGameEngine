#pragma once
#include <glm\glm.hpp>
#include <GameEngine\SpriteBatch.h>
	class Projectile
	{
	public:
		Projectile(float speed, glm::vec2 position, glm::vec2 direction, int lifeTime);
		~Projectile();

		void InitProjectile(float speed, glm::vec2 position, glm::vec2 direction, int lifeTime);

		// Add the projectile sprite into the sprite batch.
		void AddProjectile(GameEngine::SpriteBatch& spriteBatch);
		// Return the projectile's remain of the life time.
		void UpdateProjectile();
		// Check If the projectile's life time is passed.
		// If its over then return true.
		bool IsLifeTimePassed();
	private:
		// The life time of the projectile.
		int _lifeTime;
		// The moving speed of the projectile.
		float _movingSpeed;
		// The direction of the moving projectile.
		glm::vec2 _direction;
		glm::vec2 _position;
	};

