#pragma once
enum Room {
	MONSTERS = 1,
	TREASURE,
	TRAP
};
enum Weapon {
	CROSSBOW = 1,
	KNIVES,
	SWORD
};
enum Npc {
	SKELETON = 1,
	ZOMBIE,
	SPIDER,
	TROLL,
	GHOST,
	KNIGHT,
	TRAP_DEATH
};
enum Treasures {
	COINS = 1,
	HEAL_POTION,
};
enum FirstAttack {
	PLAYER = 1,
	ENEMY
};

struct EnemyStats {
	std::string name;
	Npc type;
	int hp;
	int baseDamage;
};
struct WeaponStats {
	std::string name;
	Weapon type;
	short baseDamage;
	short maxHitChance;
	short minHitChance;
	short successHit;
};
struct PlayerStats {
	int hp;
	int coins;
	WeaponStats weapon;
	std::string name;
};


namespace Constants {
	const short minHeal = 15;
	const short maxHeal = 30;
	const short treasureTypes = 2;
	const short baseMinRandCase = 1;
	const short enemyTypes = 6;
	const short rooms_count = 3;
	const short maxConinsPerRoom = 15;
	const short minCoinsPerRoom = 5;
	const short maxTrapDamage = 12;
	const short minTrapDamage = 6;
	const short damagePercentsRange = 30;
	const short healthPercentsRange = 20;
	const short damageKnivesPercentsRange = 50;
	const int basePlayerHealth = 100;
	const int maxPlayerHealth = 150;
}
//Player and Enemy stats
PlayerStats player{};

EnemyStats spiderStats{ "œ¿” ", SPIDER, 30, 6};
EnemyStats skeletonStats{ "— ≈À≈“",SKELETON, 40, 8};
EnemyStats zombieStats{ "«ŒÃ¡»",ZOMBIE, 50, 10};
EnemyStats trollStats{ "“–ŒÀÀ‹",TROLL, 60, 14};
EnemyStats ghostStats{ "œ–»«–¿ ",GHOST, 70, 16};
EnemyStats knightStats{ "√–Œ«Õ€… –€÷¿–‹",KNIGHT, 100, 20 };

EnemyStats trap{ "ŒÒÚ˚È Í‡ÏÂÌ¸", TRAP_DEATH, 0, 0 }; //Condition of death caused by a trap

//Weapon stats
WeaponStats crossbow{ "¿·‡ÎÂÚ", CROSSBOW, 50, 3, 1, 1};
WeaponStats knives{ " ËÌÊ‡Î˚", KNIVES, 15, 2, 1, 2};
WeaponStats sword{ "ÃÂ˜", SWORD, 15, 1, 1, 1};




