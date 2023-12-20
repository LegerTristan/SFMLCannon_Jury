#include "AnimationComponent.h"
#include "json.hpp"
#include "Entity.h"
#include <fstream>

using json = nlohmann::json;

AnimationComponent::AnimationComponent(sptr<Entity> _entity, const float& _nextAnimDelay, const char* _filePath) 
	: EntityComponent(_entity),
	nextAnimDelay(_nextAnimDelay),
	currentAnimTime(0.0f),
	frameIndex(0)
{
	json _tempFile;
	std::ifstream _stream(_filePath);
	_stream >> _tempFile;

	AnimationFrame _newFrame;
	if (_tempFile.is_object())
	{
		json _frames = _tempFile["frames"];

		for (auto _frame : _frames)
		{
			_newFrame.uvRectPos = sf::Vector2i(_frame["frame"]["x"], _frame["frame"]["y"]);
			_newFrame.uvRectSize = sf::Vector2i(_frame["frame"]["w"], _frame["frame"]["h"]);

			frames.push_back(_newFrame);
		}
	}

	_entity->setOrigin({ _newFrame.uvRectSize.x / 2.0f, _newFrame.uvRectSize.y / 2.0f });
	_entity ->setTextureRect({
			frames[0].uvRectPos.x, frames[0].uvRectPos.y,
			frames[0].uvRectSize.x, frames[0].uvRectSize.y
	});
}

void AnimationComponent::UpdateComponent(const float& _dt)
{
	currentAnimTime += _dt;
	if (currentAnimTime >= nextAnimDelay)
	{
		frameIndex++;
		if (frameIndex >= frames.size())
			frameIndex = 0;

		AnimationFrame _currentFrame = frames[frameIndex];
		owner.lock()->setTextureRect({
			_currentFrame.uvRectPos.x, _currentFrame.uvRectPos.y,
			_currentFrame.uvRectSize.x, _currentFrame.uvRectSize.y
			});

		currentAnimTime -= nextAnimDelay;
	}
}