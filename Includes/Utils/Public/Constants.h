#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#pragma region Window
const sf::Color CLEAR_COLOR = sf::Color(240, 240, 240, 255);	// Background color when window clear method is called.

const unsigned int WINDOW_WIDTH = 1280,
				   WINDOW_HEIGHT = 720;
#pragma endregion

#pragma region Time
const float TIME_FLOW_SPEED = 5.0f;

const int MINUTES_PER_HOUR = 60,
		  SECONDS_PER_MINUTE = 60;
#pragma endregion

#pragma region HUD
const std::string GAME_FONT_PATH = "Assets/Font/SUPER_BOOM.ttf",
			      CLOUD_IMAGE_PATH = "Assets/Textures/Cloud.png",
				  LEVEL_BACKGROUND_PATH = "Assets/Textures/Cannon_Background.png";

const float HUD_Y_OFFSET = 15.0f;				// Y offset for most part of UI elements of the HUD
const unsigned int HUD_CHARACTER_SIZE = 30;		// Character size of HUD texts
const unsigned int SCORE_CHARACTER_SIZE = 32;	// Character size of HUD texts
#pragma endregion

#pragma region Cannon
const std::string STATIC_PART_PATH = "Assets/Textures/Cannon_StaticPart.png",	// File path of the static part of the cannon
				  MOVING_PART_PATH = "Assets/Textures/Cannon_MovingPart.png";	// File path of the moving part of the cannon

const sf::Vector2f DEFAULT_SCALE = sf::Vector2f(0.2f, 0.2f),
				   MOVING_PART_OFFSET = sf::Vector2f(21.0f, -35.0f);	// Offset of the moving part in order to have a 
																		// correct location

const float DEFAULT_ANGLE = 30.0f,								// Default angle at the start of the game
			CANNON_POS_X = 50.0f,								// Cannon's offset X-Axis in the window
			CANNON_POS_Y = 30.0f;								// Cannon's offset Y-Axis in the window

const float RADIAN_CONVERSION = (3.1415f / 180.0f),				// Convert degrees to radian.
			ROTATION_OFFSET = 90.0f,							// Offset applied to the texture in order to orient the cannon.
			DIST_FROM_CANNON = 50.0f;							// Distance from the origin of the texture.
#pragma endregion

#pragma region InputRotationComponent
const float ADDING_ANGLE = 60.0f;								// Rotation angle to add when moving the cannon	
const float DEFAULT_ROTATION_SPEED = 36.0f;						// Default rotation's speed of the cannon
const float MAX_CANNON_ROTATION = 90.0f;						// Maximum rotation's angle of the cannon
const float MIN_CANNON_ROTATION = 20.0f;						// Minimum rotation's angle of the cannon
#pragma endregion

#pragma region CannonShootComponent
const float MAX_CANNON_FIRE_POWER = 125.0f;						// Maximum fire's power of the cannon
const float MIN_CANNON_FIRE_POWER = 50.0f;						// Minimum fire's power of the cannon

const float DEFAULT_LOAD_SPEED = 18.0f;							// Default fire load speed of the cannon
const float LOAD_SPEED_SCALAR = 1.0f;							// Scalar applied to the rank of the upgrade "Fire load speed"
#pragma endregion

#pragma region Gauge
const sf::Vector2f TO_CENTER = sf::Vector2f(5.0f, 5.0f);			// Offset in order to center part of the gauge
const sf::Vector2f BACKGROUND_MARGIN = sf::Vector2f(10.0f, 10.0f);	// Gauge background margin
const sf::Vector2f VERTICAL_OFFSET = sf::Vector2f(5.0f, 55.0f);		// Vertical offset to apply at the gauge value
	
const float GAUGE_WIDTH = 20.0f;							// Default width of the gauge (for vertical gauge).
const float GAUGE_HEIGHT = 50.0f;							// Default height of the gauge (for vertical gauge).
#pragma endregion

#pragma region CannonBalls
const std::string CANNON_BALL_TEXTURE_PATH = "Assets/Textures/Cannon_Ball.png";
const std::string CANNON_BALL_COLLISION_PATH = "Assets/JSON/CannonBall.json";	// Path of collision's informations 
																				// of CannonBall

const unsigned int DEFAULT_BALL_LIFE = 1;
const float DEFAULT_BALL_SCALE = 0.25f;
#pragma endregion

#pragma region MoveComponent
const float G = 9.8f;						// Constant of gravity's acceleration, defined here to be used in any subclass
											// that needs it.

const float PADDING_HEIGHT = 50.0f;			// Height padding for the screen boundary
#pragma endregion

#pragma region LifeBar
const std::string HEART_TEXTURE_PATH = "Assets/Textures/Heart.png";

const sf::Vector2f LIFEBAR_POS = sf::Vector2f(150.0f, 20.0f);		// Position of the lifebar
const sf::Vector2f HEART_SPRITE_SCALE = sf::Vector2f(0.05f, 0.05f);
const float SPACE_BETWEEN_LIFE = 30.0f;								// Space between two life sprite

const int DEFAULT_PLAYER_LIFE = 3;									// Default lifes of player, when an enemy pass outside the screen,
																	// it takes one life from the player
#pragma endregion

#pragma region WaveManager
const float ENEMY_SPAWN_RATE = 2.0f;								// Spawn rate of enemies
const float WAVE_RATE = 20.0f;										// Countdown before a new wave of enemies arrives

const int ENEMY_MAX_NBR_START = 3;									// Max number of enemy at the start
const int ENEMY_MAX_NBR_INCREMENT = 2;								// Incrementation value of enemy max number 
																	// at the same time in the level.

const sf::Vector2f SPAWN_POS_BOSS = sf::Vector2f(150.0f, 210.0f);	// Boss spawn position
const float SPAWN_FLOAT_ENEMY_OFFSET_Y_RANGE = 300.0f;				// Range of Y offset for spawning new floating enemy
const float SPAWN_FLOAT_ENEMY_OFFSET_Y_MIN = 100.0f;				// Min value of Y offset for spawning new floating enemy
const float SPAWN_ENEMY_OFFSET_X = 50.0f;							// X offset for spawning new enemy
const float SPAWN_GROUND_ENEMY_OFFSET_Y = 60.0f;					// Y offset for spawning new ground enemy
#pragma endregion

#pragma region Enemy
const unsigned int DEFAULT_ENEMY_LIFE = 1;							// Base life of enemies
#pragma endregion

#pragma region GroundEnemy
const std::string GROUND_ENEMY_TEXTURE = "Assets/Textures/Golem_Walking_1.png";	
const std::string GROUND_ENEMY_ANIMATION_PATH = "Assets/JSON/Golem_Walking_1.json";

const sf::Vector2f GROUND_ENEMY_VELOCITY = sf::Vector2f(-100.0f, 0.0f);				// Velocity of ground enemies
const sf::Vector2f GROUND_ENEMY_SCALE = sf::Vector2f(0.25f, 0.25f);					// Scale of ground enemies

const float GROUND_ENEMY_XP = 4.0f;													// XP given by ground enemies
const float GROUND_ENEMY_ANIM_DELAY = .1f;											// Animation's delay between each frame
																					// of floating enemy
#pragma endregion

#pragma region FloatEnemy
const std::string FLOAT_ENEMY_TEXTURE_PATH = "Assets/Textures/Wraith_Walking_1.png";
const std::string FLOAT_ENEMY_ANIMATION_PATH  = "Assets/JSON/Wraith_Walking_1.json";

const sf::Vector2f FLOAT_ENEMY_VELOCITY = sf::Vector2f(-500.0f, 0.0f);					// Velocity of floating enemy
const sf::Vector2f FLOAT_ENEMY_SCALE = sf::Vector2f(0.3f, 0.3f);						// Scale of floating enemy

const float DEFAULT_FLOAT_ENEMY_AMPLITUDE = 3.0f;										// Float movement amplitude for 
																						// floating enemy
const float DEFAULT_FLOAT_ENEMY_FREQUENCY = 0.3f;										// Float movement frequency for 
																						// floating enemy
const float FLOAT_ENEMY_XP = 7.0f;														// XP of floating enemy
const float FLOAT_ENEMY_ANIM_DELAY = .1f;												// Animation's delay between each frame
																						// of floating enemy
#pragma endregion

#pragma region KillZones
const sf::Vector2f CB_KILL_ZONE_OFFSET = sf::Vector2f(0.0f, 10.0f);				// Offset of cannon ball's kill zone
const sf::Vector2f CB_KILL_ZONE_EXTENT = sf::Vector2f(0.0, 1.0f);				// Extent of cannon ball's kill zone

const sf::Vector2f ENEMIES_KILL_ZONE_OFFSET = sf::Vector2f(-25.0f, 0.0f);		// Offset of enemies kill zone
const sf::Vector2f ENEMIES_KILL_ZONE_EXTENT = sf::Vector2f(1.0f, 0.0f);			// Extent of enemies kill zone
#pragma endregion

#pragma region CollisionManager
const float PHYSIC_CHECK_RATE = 0.1f;						// Check rate of all collision components in the game.
#pragma endregion

#pragma region ScoreManager
const std::string SCORE_SAVE_VALUE_NAME = "HScore";			// Value's name for saving the highest score.

const unsigned int GROUND_ENEMY_SCORE = 5;					// Score given by grounds enemies
const unsigned int FLOAT_ENEMY_SCORE = 8;					// Score of floating enemy
#pragma endregion

#pragma region StartHUD
const float GOAL_Y_OFFSET = 75.0f;							// Offset on Y-axis for goal.
const float CONTROLS_X_OFFSET = -500.f;						// Offset on X-axis for controls.
const float CONTROLS_Y_OFFSET = -350.f;						// Offset on Y-axis for controls.
#pragma endregion

#pragma region START_TEXT_SCALE_EFFECT
const float SCALE_EFFECT_DURATION = 2.0f;					// Duration of the scale effect of startText 
															// widget.
const float MIN_SCALE_EFFECT = 0.9f;						// Minimum value for startText scale effect
const float MAX_SCALE_EFFECT = 1.1f;						// Maximum value for startText scale effect
#pragma endregion

#pragma region TimerText
const unsigned int NUMBER_CHARACTER_TIMER = 6;				// Number of character displayed in the timer.
const std::string FORMAT_CHARACTER_TIMER = "%02d:%02d";		// Format of character displayed in the timer.
#pragma endregion

#pragma region IOManager
const std::string SAVE_DIRECTORY_NAME = "\\Save";			// Name of the directory that contains the save.
const std::string SAVE_FILE_NAME = "\\Save";				// Name of the file that contains the save.
const std::string SAVE_FILE_EXT = ".json";					// Save's extension.
#pragma endregion