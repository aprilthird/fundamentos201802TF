#pragma once
#include <string>

class PATH {
public:
	static const std::string SPRITES;
	static const std::string BACKGROUND;
	static const std::string SFX;
	static const std::string SONG;
	static const std::string FONT;

	class FONTS {
	public:
		static const std::string BITS8;
	};

	class SPRITES_NAMES {
	public:
		static const std::string PLAYER;
		static const std::string ALIEN_SPACHESHIP;
		static const std::string ALIEN_MOTOR;
		static const std::string ALIEN_CANON;
		static const std::string PLAYER_BULLET;
		static const std::string ALIEN_BULLET;
		static const std::string SHIELD;
	};

	class BACKGROUNDS {
	public:
		static const std::string MENU;
		static const std::string GAME;
		static const std::string GAME_OVER;
	};
};