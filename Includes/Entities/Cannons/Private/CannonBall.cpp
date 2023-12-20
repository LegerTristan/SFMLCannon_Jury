#include "TimeManager.h"
#include "CannonBall.h"
#include "Game.h"
#include "LevelState.h"
#include "EntityManager.h"

CannonBall::CannonBall(const sf::Vector2f _position)
	: Entity(_position, Game::GetInstance()->GetTextureManager().GetTexture(CANNON_BALL_TEXTURE_PATH), DEFAULT_BALL_LIFE)
{
	// Set sprite's texture and transform settings
	setScale(sf::Vector2f(DEFAULT_BALL_SCALE, DEFAULT_BALL_SCALE));
}

void CannonBall::Enable()
{
	Entity::Enable();
}

void CannonBall::OnCollide(const CollisionComponent& _comp)
{
	onEntityKilled->Invoke(shared_from_this());
}

void CannonBall::Disable()
{
	Entity::Disable();
}
