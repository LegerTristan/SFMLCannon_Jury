#include <string>
#include "Player.h"
#include "Constants.h"
#include "KillZone.h"

Player::Player() :
	onPlayerLifeDecreased(std::make_unique<Action<const unsigned int&>>(nullptr)),
	onPlayerLose(std::make_unique<Action<>>(nullptr)),
	life(DEFAULT_PLAYER_LIFE),
	lifeBar(std::make_unique<LifeBar>(sf::Vector2f(WINDOW_WIDTH / 2 - LIFEBAR_POS.x, LIFEBAR_POS.y), DEFAULT_PLAYER_LIFE))
{
	lifeBar->BindToPlayerLife(*this);
}

void Player::Draw(sf::RenderWindow& _window)
{
	lifeBar->Draw(_window);
}

void Player::BindToEnemiesKillZone(KillZone& _killZone)
{
	_killZone.OnKillZoneTriggered().AddDynamic(this, &Player::DecrementHP);
}

void Player::DecrementHP(const EEntityType& type)
{
	if (life <= 0)
		return;

	life--;
	onPlayerLifeDecreased->Invoke(life);

	if (life == 0)
		onPlayerLose->Invoke();
}
