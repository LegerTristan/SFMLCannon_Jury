#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class LevelButtonComponent;

/// <summary>
/// Component that order LevelButtonComponent in an invisible grid.
/// </summary>
class UIGridComponent
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	UIGridComponent(const vector<LevelButtonComponent*>& sprites, const Vector2f& pos, const unsigned int& column, 
		const float& spaceRow = 100.0f, const float& spaceColumn = 100.0f);
	~UIGridComponent() {}

	/// <summary>
	/// Order LevelButtonsComponent.
	/// </summary>
	/// <param name="sprites">Vector of the level button component.</param>
	/// <param name="spaceRow">Space between two elements in a row.</param>
	/// <param name="spaceColumn">Space between two elements in a column.</param>
	void Order(const vector<LevelButtonComponent*>& sprites, const float& spaceRow, const float& spaceColumn);

private:

	/// <summary>
	/// Position of the grid component.
	/// </summary>
	Vector2f mPos;

	/// <summary>
	/// Number of elements needed by column.
	/// </summary>
	unsigned int mColumn;
};

