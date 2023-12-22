#include <fstream>
#include <iostream>
#include "CollisionComponent.h"
#include "json.hpp"
#include "Entity.h"
#include "Game.h"
#include "Utilities.h"

using json = nlohmann::json;

CollisionComponent::CollisionComponent(sptr<Entity> _entity, const ECollisionType& _type, const char* _hitBoxPath,
    const char _collisionMask) :
    EntityComponent(_entity),
    onCollide(std::make_unique<Action<const CollisionComponent&>>(nullptr)),
    collisionType(_type),
    collisionMask(_collisionMask)
{
    if (!_entity || !_hitBoxPath || _hitBoxPath == "")
        return;

    json _tempJSON;
    std::ifstream _stream(_hitBoxPath);
    _stream >> _tempJSON;

    if (_tempJSON.is_object())
    {
        hitBox.setSize({ _tempJSON["hitbox"]["w"] * _entity->getScale().x,
            _tempJSON["hitbox"]["h"] * _entity->getScale().y });
        hitBox.setOrigin((hitBox.getSize().x / 2.0f) + _tempJSON["hitbox"]["offsetX"],
            (hitBox.getSize().y / 2.0f) + _tempJSON["hitbox"]["offsetY"]);
    }
    else
        throw "JSON file element \"hitbox\" not corresponding to type object.";

    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOutlineThickness(1);
    hitBox.setOutlineColor(sf::Color::Black);

    InitBindings();
    UpdateHitBoxPosition();
}

CollisionComponent::CollisionComponent(sptr<Entity> _entity, const ECollisionType& _type, const sf::Vector2f& _size,
    const char _collisionMask) :
    EntityComponent(_entity),
    onCollide(std::make_unique<Action<const CollisionComponent&>>(nullptr)),
    collisionType(_type),
    collisionMask(_collisionMask)
{
    if (!_entity)
        return;

    hitBox.setSize({ _size.x * _entity->getScale().x, _size.y * _entity->getScale().y });
    hitBox.setOrigin(hitBox.getSize() / 2.0f);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOutlineThickness(3);
    hitBox.setOutlineColor(sf::Color::Black);

    InitBindings();
    UpdateHitBoxPosition();
}

void CollisionComponent::UpdateComponent(const float& dt)
{
    UpdateHitBoxPosition();
}

void CollisionComponent::DrawComponent(sf::RenderWindow& _window)
{
    _window.draw(hitBox);
}

void CollisionComponent::UpdateHitBoxPosition()
{
    const sptr<Entity> _entity = owner.lock();
    const sf::Vector2f _ownerPos = _entity->getPosition();
    sf::IntRect _ownerTextureRect = _entity->getTextureRect();
    const sf::FloatRect _newHitBoxPos = sf::FloatRect(_ownerPos.x, _ownerPos.y, _ownerTextureRect.width,
        _ownerTextureRect.height);

    hitBox.setPosition(_newHitBoxPos.left, _newHitBoxPos.top);
}

void CollisionComponent::HandleCollision(const CollisionComponent* _otherCollision) const
{
    if (!_otherCollision)
        return;

    const sf::FloatRect _otherRect = _otherCollision->hitBox.getGlobalBounds();
    const bool _collidingWithMask = collisionMask & static_cast<char>(_otherCollision->collisionType);
    const sf::FloatRect _ownRect = hitBox.getGlobalBounds();
    if (_collidingWithMask && _ownRect.intersects(_otherRect))
        onCollide->Invoke(*_otherCollision);
}

void CollisionComponent::InitBindings()
{
    BindToCollisionManager();

    sptr<Entity> _entity = owner.lock();
    onCollide->AddDynamic(_entity.get(), &Entity::OnCollide);
    _entity->OnEntityEnabled().AddDynamic(this, &CollisionComponent::BindToCollisionManager);
    _entity->OnEntityKilled().AddDynamic(this, &CollisionComponent::UnbindFromCollisionManager);
}

void CollisionComponent::BindToCollisionManager()
{
    // We need to reset the hitbox position in order to correspond to entity position.
    UpdateHitBoxPosition();
    // Give the collision component to the manager to handle collision's logic
    Game::GetInstance()->GetCollisionManager().RegisterCollisionComponent(this);
}

void CollisionComponent::UnbindFromCollisionManager(sptr<Entity> _owner)
{
    // Remove the collision component from the manager to prevent applies of the collision's logic
    Game::GetInstance()->GetCollisionManager().UnregisterCollisionComponent(this);
}
