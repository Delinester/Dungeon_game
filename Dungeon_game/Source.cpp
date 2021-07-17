#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ItemsAndStats.h"

//#include <random>
//int randomizer(int max, int min) {
//	std::random_device rd;
//	return min + rd() % (max - min + 1);
//}//�������� ��������� ��������� ����� 
void roomCreate();
int randomizer(int max, int min) {
	return min + (rand() % ((max - min) + 1));
}
void playerDeath(EnemyStats enemy, int roomNumber) {
	system("CLS");
	std::cout << enemy.name << " ���� �������� ����� " << player.name << std::endl;	
	std::cout << "� ��� �������� ��������� " << player.coins << " �����" << std::endl;
	std::cout << "������ � ������� " << roomNumber << " ����� ����������� ����..." << std::endl;	
	system("Pause"); std::cout << std::endl;
	exit(0);
}
short playerGiveDamage(void) {
	short addDamage = ((static_cast<float>(player.weapon.baseDamage) / 100) * Constants::damagePercentsRange);
	switch (player.weapon.type) {
	case CROSSBOW:
		if (player.weapon.successHit != randomizer(player.weapon.maxHitChance, player.weapon.minHitChance)) return 0;
		return player.weapon.baseDamage + randomizer(addDamage, -addDamage);
	case KNIVES:
		short firstHit, secondHit;
		addDamage = ((static_cast<float>(player.weapon.baseDamage) / 100) * Constants::damageKnivesPercentsRange);
		if (player.weapon.successHit != randomizer(player.weapon.maxHitChance, player.weapon.minHitChance)) firstHit = 0;
		else firstHit = player.weapon.baseDamage + randomizer(addDamage, 0);
		if (player.weapon.successHit != randomizer(player.weapon.maxHitChance, player.weapon.minHitChance)) secondHit = 0;
		else secondHit = player.weapon.baseDamage + randomizer(addDamage, 0);
		return firstHit + secondHit;
	case SWORD:
		if (player.weapon.successHit != randomizer(player.weapon.maxHitChance, player.weapon.minHitChance)) return 0;
		return player.weapon.baseDamage + randomizer(addDamage, -addDamage);
	}
}
int enemyGiveDamage(short baseDamage) {
	short isSuccess = randomizer(1, 0);
	if (isSuccess == 0) return 0;
	if (isSuccess == 1) {
		short addDamage = ((static_cast<float>(baseDamage) / 100) * Constants::damagePercentsRange);
		int damage = baseDamage + randomizer(addDamage, -addDamage);
		return damage;
	}	
}
void enemyDrop(std::string monsterName) {
	Treasures enemyDrop = static_cast<Treasures>(randomizer(Constants::treasureTypes, 1));
    std::cout << std::endl << std::endl;
	std::cout << "-----------------------------------------\n";
	std::cout << "����� �������!\n";
	switch (enemyDrop) {
	case COINS:
	{
		short coinsAmount = randomizer(Constants::maxConinsPerRoom, Constants::minCoinsPerRoom);
		player.coins += coinsAmount;
		std::cout << monsterName << " ������� " << coinsAmount << " �����. ������ � ��� � ������� " 
			<< player.coins << " �����.";
		break;
	}
	case HEAL_POTION:
		short healAmount = randomizer(Constants::maxHeal, Constants::minHeal);
		player.hp += healAmount;
		std::cout << monsterName << " ������� ����� ���������. ����� ���, ���� �������� ����������� �� " 
			<< player.hp << " �����.";
		break;
	}
	std::cout << std::endl;
	std::cout << "-----------------------------------------\n";	
	system("Pause"); std::cout << std::endl;
	roomCreate();
}
void enemyBattle(EnemyStats enemy, int roomNumber) {
	short addEnemyHealth = (static_cast<float>(enemy.hp) / 100) * Constants::healthPercentsRange;
	enemy.hp += randomizer(addEnemyHealth, -addEnemyHealth);
	std::cout << enemy.name << " ����� " << enemy.hp << " ����� ��������.\n";
	std::cout << player.name << " ����� " << player.hp << " ����� ��������.\n\n";	
	system("Pause"); std::cout << std::endl;
	FirstAttack firstAttack = static_cast<FirstAttack>(randomizer(2, 1));
	switch (firstAttack) {
	case ENEMY:
	{
		std::cout << std::endl;
		short gainedDamage = enemyGiveDamage(enemy.baseDamage);
		player.hp -= gainedDamage;
		std::cout << enemy.name << " �������� ������� " << gainedDamage << " ����� ����� " << player.name << std::endl;
		if (player.hp <= 0) playerDeath(enemy, roomNumber);
		do {
			std::cout << "-----------------------------------------\n";
			std::cout << "� ����� " << player.hp << " ����� ��������\n";
			std::cout << "� ����� " << enemy.hp << " ����� ��������\n";
			std::cout << "-----------------------------------------\n\n";			
			system("Pause"); std::cout << std::endl;
			int dealDamage = playerGiveDamage();
			enemy.hp -= dealDamage;
			std::cout << "����� ��������� " << player.weapon.name << ", �� ������� " << dealDamage
				<< " ����� ����� " << enemy.name << std::endl;
			if (enemy.hp <= 0) {
				std::cout << "�� �������� ����� " << enemy.name << std::endl << std::endl;
				system("Pause"); std::cout << std::endl; 
				enemyDrop(enemy.name);
			}
			dealDamage = enemyGiveDamage(enemy.baseDamage);
			player.hp -= dealDamage;
			std::cout << enemy.name << " ������� ������������ � ������� " << dealDamage << " ����� ����� "
				<< player.name << std::endl;
			if (player.hp <= 0) playerDeath(enemy, roomNumber);
		} while (enemy.hp > 0);
	}
	case PLAYER:
	{
		std::cout << std::endl;
		short gainedDamage = playerGiveDamage();
		enemy.hp -= gainedDamage;
		std::cout << player.name << " �������� ������� " << gainedDamage << " ����� ����� " << enemy.name << std::endl;
		if (enemy.hp <= 0) enemyDrop;
		do {
			std::cout << "-----------------------------------------\n";
			std::cout << "� ����� " << enemy.hp << " ����� ��������\n";
			std::cout << "� ����� " << player.hp << " ����� ��������\n";
			std::cout << "-----------------------------------------\n\n";			
			system("Pause"); std::cout << std::endl; 
			int dealDamage = enemyGiveDamage(enemy.baseDamage);
			player.hp -= dealDamage;
			std::cout << enemy.name << " ������� ������������ � ������� " << dealDamage << " ����� ����� "
				<< player.name << std::endl;
			if (player.hp <= 0) playerDeath(enemy, roomNumber);
			dealDamage = playerGiveDamage();
			enemy.hp -= dealDamage;
			std::cout << "����� ��������� " << player.weapon.name << ", �� ������� " << dealDamage
				<< " ����� ����� " << enemy.name << std::endl;
			if (enemy.hp <= 0) {
				std::cout << "�� �������� ����� " << enemy.name << std::endl;				
				system("Pause"); std::cout << std::endl;
				enemyDrop(enemy.name);
			}

		} while (enemy.hp > 0);
	}
	}
}
void enemyPrint(EnemyStats enemy, int roomNumber) {
	std::cout << "����� ������ �� ��������� ������, �� �������� � �������, �� ������� �������� �������� �����...\n\n";
	switch (enemy.type) {
	case SPIDER:
		std::cout << "��������� �� ������� �������, �� ��������� ������ ���������. ��� ��� ��� ��� ����� �� ����?\n";
        std::cout << "�� ������� ������ � ����������� ������� ��������.\n";
		std::cout << "� ���! �������� ������������ � ��������� ����� ����� ���. �����������, ��� �������� ����!\n\n";
		break;
	case SKELETON:
		std::cout << "� ������ �������� ����� ����� ������.\n";
		std::cout << "��� ������ �� � ��� ������������, ������, �������� ��������, ����� ����������� � ���������������� " <<
			"��������.\n";
		std::cout << "� ���, ��� ������! �� �������� ����������!\n\n";
		break;
	case ZOMBIE:
		 std::cout << "�� ����� ���������� ���������� �����, ��-�� �������� ����������� ���������� ������.\n";
		 std::cout << "�������� �������, �� ������������ � ��������� ����� ��������. �� �������� �����, ���������� " <<
			 "���-�� �������!\n ���������� ���, �� ������� � �������� � ���� �������!\n\n";
		 break;
	case TROLL:
		 std::cout << "�� �������� ���� ������� ��������� ����� ������� � ��������������� ����.\n";
		 std::cout << "�������� ������������, ��� ������ �������� ����� ����� �� �����, �� ���� ����������� ���������� ����\n";
		 std::cout << "�� ��������� � ��������� �����. � ���� ����� ���������� ������� ������� ������, �������� ������� �� " <<
			 "������ ������.\n���� ������������ ��������� ���������� ������� �����, ������� ����� ���� �����������...\n\n";
		 break;
	case GHOST:
		std::cout << "�������� ��� ���������� ����� �������, ��� ������� ��� ��� ����� ���. "
			<< "\"��� �����������,\" - �������� ��.\n";
		std::cout << "�������� ����, ������� ���������� ������, ����������� ����� �� ���� �������.\n";
		std::cout << "�� ������ ��������� ������� �����. �����������, �� ������ �������������� �����. ��� �� �������!\n\n";
		break;
	case KNIGHT:
		 std::cout << "���� �������� � ������� ���� ���������� ���� �� ���� �������.\n";
		 std::cout << "������� ���������� � ���������, �� ������� ���� ������������ � ���� �������...\n";
		 std::cout << "� ��� ������������ ������, ������ � ������ �������! �� ��� ���� ����� �������, ��� �� �������\n";
		 std::cout << "�������������, ������� ����� ���� ����� �� �� �����, � �� ������\n\n";
		 break;
	}	
	system("Pause"); std::cout << std::endl; 
	enemyBattle(enemy, roomNumber);
}
EnemyStats enemySpawn() {
	EnemyStats enemy;
	enemy.type = static_cast<Npc>(randomizer(Constants::enemyTypes, Constants::baseMinRandCase));
	switch (enemy.type) {
	case SPIDER:
		return spiderStats;
	case SKELETON:
		return skeletonStats;
	case ZOMBIE:
		return zombieStats;
	case TROLL:
		return trollStats;
	case GHOST:
		return ghostStats;
	case KNIGHT:
		return knightStats;	  
	}
		
}
void roomCreate(){
	static int roomNumber = 0;
	roomNumber++;
	short random_room = randomizer(Constants::rooms_count, Constants::baseMinRandCase);
	Room room = static_cast<Room>(random_room);
	system("CLS");
	switch (room) {
	case MONSTERS:
		enemyPrint(enemySpawn(), roomNumber);
		break;
	case TREASURE:
	{Treasures treasure = static_cast<Treasures>(randomizer(Constants::treasureTypes, Constants::baseMinRandCase));
	switch (treasure) {
	case COINS:
		player.coins += randomizer(Constants::maxConinsPerRoom, Constants::minCoinsPerRoom);
		std::cout << "�� ������� � ���������� �������, ���������� ������� ����� ������...\n";
		std::cout << "�� ����� ���������! ������ ��� ������ ����� " << player.coins << std::endl << std::endl;		
		system("Pause"); std::cout << std::endl;
		roomCreate();
		break;
	case HEAL_POTION:
		player.hp += randomizer(Constants::maxHeal, Constants::minHeal);
		std::cout << "�� ������� � ���������� �������, ���������� ������� ����� ������...\n";
		std::cout << "�� ����� ������� � ����������! ��� ����� �����, �������� ����������� �� "
			<< player.hp << " �����." << std::endl << std::endl;		
		system("Pause"); std::cout << std::endl;
		roomCreate();
		break;
	}
	break;
	}
	case TRAP:
		player.hp -= randomizer(Constants::maxTrapDamage, Constants::minTrapDamage);
	    std::cout << "����� �� ������� � ����� ���������, �� �������� ���������� �� �������� �����.\n";
		std::cout << "������� ������ ������� ����������.\n�������� �� ���� � ����� � ��� ��������� ���-�� ������.\n";
		std::cout << "�� ���������� ���� ����. ��� ����� �������� �������� �� " << player.hp << " �����\n\n";
		if (player.hp <= 0) playerDeath(trap, roomNumber);		
		system("Pause"); std::cout << std::endl;
		roomCreate();
		break;
	}
}
void definePlayerWeapon(Weapon weaponType) {
	switch (weaponType) {
	case CROSSBOW: 
		player.weapon = crossbow;
		break;
	case KNIVES:
		player.weapon = knives;
		break;
	case SWORD:
		player.weapon = sword;
		break;
	}
}

void gameStart() {
	using namespace std;
	setlocale(LC_ALL, "Russian");
	cout << "�������� ������ �����(�� ���������): ";
	cin >> player.name;
	system("CLS");
	cout << player.name << " - �������� �������� �����������, �������� ����������� � �������� � ������ ����������.\n";
	cout << "�������, �� ��������� � ��������, ������� ��� �������, �������, ������ ��� ���� ����������,\n";
	cout << "������������� � ��������� �����." << endl;
	cout << "����������� �������� �� �����...\n";
	short weaponNum;
	do {
		cout << "�� �������� �� ������ �������, ������� � ���\n";
		cout << "����� ������ �������� ����� ������� � �����?\n";
		cout << "1 - �������(������� ����. ���� ��������� 30 ���������)\n";
		cout <<	"2 - �������(������ ����. ������� ����. ���� ��������� 50 ��������� ������)\n";
		cout <<	"3 - ���(������ ����. ���� ��������� 100 ���������)\n ������� ����� ������: ";
		cin >> weaponNum;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (weaponNum > 3 || weaponNum < 1);
	player.weapon.type = static_cast<Weapon>(weaponNum);
	definePlayerWeapon(player.weapon.type);
	system("CLS");
	player.hp = randomizer(Constants::maxPlayerHealth, Constants::basePlayerHealth);
	cout << "����, " << player.name << ", � ��� � ����� " << player.weapon.name <<
		". �� ����� ���, � ��� " << player.hp << " ����� ��������\n";
	cout << "���� ���� � �����, �� ������� � ������ ������...\n\n";
	system("Pause"); std::cout << std::endl;
	roomCreate();
}

int main() {
	srand(static_cast<long long>(time(0)));
	gameStart();
	return 0;
}