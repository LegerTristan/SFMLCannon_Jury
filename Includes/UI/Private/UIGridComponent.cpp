#include "UIGridComponent.h"
#include "LevelButtonComponent.h"

UIGridComponent::UIGridComponent(const vector<LevelButtonComponent*>& _sprites, const Vector2f& _pos, const unsigned int& _column,
	const float& _spaceRow, const float& _spaceColumn)
{
	mPos = _pos;
	mColumn = _column;

	Order(_sprites, _spaceRow, _spaceColumn);
}

void UIGridComponent::Order(const vector<LevelButtonComponent*>& _sprites, const float& _spaceRow, const float& _spaceColumn)
{
	float offsetX = 0.0f, offsetY = 0.0f;
	for (unsigned int i = 0; i < _sprites.size(); ++i)
	{
		offsetX = mPos.x + (_spaceColumn * (i % mColumn));
		offsetY = mPos.y + ( _spaceRow * (i / mColumn));

		_sprites[i]->Anchor(Vector2f(offsetX, offsetY));
	}
}
