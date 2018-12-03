#pragma once
#include <map>
#include "Vertex.h"

class Armor {
public:
	int id;
	std::string abvr;
	std::string name;
	float protection;
	float duration;
	Armor(int id, std::string abvr, std::string name, float protection, float duration)
		: id(id), abvr(abvr), name(name), protection(protection), duration(duration) { }
};

class Motor {
public:
	int id;
	int nmotors;
	float speed;
	Motor(int id, int nmotors, float speed) : id(id), nmotors(nmotors), speed(speed) { }
};

class Shield {
public:
	int id;
	float duration;
	ColorRGBA color;
	Shield(int id, ColorRGBA color, float duration) : 
		id(id), color(color), duration(duration) { }
};

class Canon {
public:
	int id;
	int nbullets;
	int ncanons;
	int time;
	Canon(int id, int nbullets, int ncanons, int time) : 
		id(id), nbullets(nbullets), ncanons(ncanons), time(time) {}
};

class Bullet {
public:
	int id;
	std::string abvr;
	float speed;
	float damage;
	Bullet(int id, std::string abvr, float speed, float damage) :
		id(id), abvr(abvr), speed(speed), damage(damage) { }
};

class ARMOR {
public:
	static const int ALUMINIUM = 0;
	static const int TITANIUM = 1;
	static const int STEEL = 2;
	static const int GRAPHENE = 3;
	static std::map<int, Armor*> VALUES;
};

class MOTOR {
public:
	static const int BASIC = 0;
	static const int DOUBLE = 1;
	static const int THREE = 2;
	static const int THREE_ADVANCED = 3;
	static std::map<int, Motor*> VALUES;
};

class SHIELD {
public:
	static const int NONE = 0;
	static const int BASIC = 1;
	static const int ADVANCED = 2;
	static const int DOUBLE = 3;
	static std::map<int, Shield*> VALUES;
};

class CANON {
public:
	static const int BASIC = 0;
	static const int DOUBLE = 1;
	static const int DOUBLE_FASTER = 2;
	static const int THREE = 3;
	static std::map<int, Canon*> VALUES;
};

class BULLET {
public:
	static const int BASIC = 0;
	static const int ADVANCED = 1;
	static const int SUPER = 2;
	static const int ULTRA = 3;
	static std::map<int, Bullet*> VALUES;
};
