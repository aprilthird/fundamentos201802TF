#include "SpaceShipParts.h"

std::map<int, Armor*> ARMOR::VALUES = {
	{ ARMOR::ALUMINIUM, new Armor(ARMOR::ALUMINIUM, "AL", "Aluminio", 0.1f, 200.0f) },
	{ ARMOR::TITANIUM, new Armor(ARMOR::TITANIUM, "TI", "Titanio", 0.2f, 450.0f) },
	{ ARMOR::STEEL, new Armor(ARMOR::STEEL, "ST", "Acero", 0.3f, 800.0f) },
	{ ARMOR::GRAPHENE, new Armor(ARMOR::GRAPHENE, "GP", "Grafeon", 0.5f, 1200.0f) }
};

std::map<int, Motor*> MOTOR::VALUES = {
	{ MOTOR::BASIC, new Motor(MOTOR::BASIC, 1, 3.0f) },
	{ MOTOR::DOUBLE, new Motor(MOTOR::DOUBLE, 2, 6.0f) },
	{ MOTOR::THREE, new Motor(MOTOR::THREE, 3, 9.0f) },
	{ MOTOR::THREE_ADVANCED, new Motor(MOTOR::THREE_ADVANCED, 3, 12.0f) }
};

std::map<int, Shield*> SHIELD::VALUES = {
	{ SHIELD::NONE, new Shield(SHIELD::NONE, ColorRGBA(0,0,0,100), 200.0f) },
	{ SHIELD::BASIC, new Shield(SHIELD::BASIC, ColorRGBA(0,255,0,100), 300.0f) },
	{ SHIELD::ADVANCED, new Shield(SHIELD::ADVANCED, ColorRGBA(0,0,255,100), 500.0f) },
	{ SHIELD::DOUBLE, new Shield(SHIELD::DOUBLE, ColorRGBA(255,127,80,100), 1000.0f) }
};

std::map<int, Canon*> CANON::VALUES = {
	{ CANON::BASIC, new Canon(CANON::BASIC, 1, 1, 500) },
	{ CANON::DOUBLE, new Canon(CANON::DOUBLE, 2, 1, 500) },
	{ CANON::DOUBLE_FASTER, new Canon(CANON::DOUBLE_FASTER, 3, 2, 300) },
	{ CANON::THREE, new Canon(CANON::THREE, 4, 2, 400) }
};

std::map<int, Bullet*> BULLET::VALUES = {
	{ BULLET::BASIC, new Bullet(BULLET::BASIC, "B", 15, 20) },
	{ BULLET::ADVANCED, new Bullet(BULLET::ADVANCED, "S", 15, 30) },
	{ BULLET::SUPER, new Bullet(BULLET::SUPER, "P", 20, 40) },
	{ BULLET::ULTRA, new Bullet(BULLET::ULTRA, "E", 20, 50) }
};
