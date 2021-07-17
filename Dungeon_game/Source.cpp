#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ItemsAndStats.h"

//#include <random>
//int randomizer(int max, int min) {
//	std::random_device rd;
//	return min + rd() % (max - min + 1);
//}//ТЕСТОВЫЙ ГЕНЕРАТОР СЛУЧАЙНЫХ ЧИСЕЛ 
void roomCreate();
int randomizer(int max, int min) {
	return min + (rand() % ((max - min) + 1));
}
void playerDeath(EnemyStats enemy, int roomNumber) {
	system("CLS");
	std::cout << enemy.name << " убил храброго героя " << player.name << std::endl;	
	std::cout << "В его кошельке оказалось " << player.coins << " монет" << std::endl;
	std::cout << "Теперь в комнате " << roomNumber << " лежит бездыханное тело..." << std::endl;	
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
	std::cout << "Какое счастье!\n";
	switch (enemyDrop) {
	case COINS:
	{
		short coinsAmount = randomizer(Constants::maxConinsPerRoom, Constants::minCoinsPerRoom);
		player.coins += coinsAmount;
		std::cout << monsterName << " обронил " << coinsAmount << " монет. Теперь у Вас в мешочке " 
			<< player.coins << " монет.";
		break;
	}
	case HEAL_POTION:
		short healAmount = randomizer(Constants::maxHeal, Constants::minHeal);
		player.hp += healAmount;
		std::cout << monsterName << " обронил зелье исцеления. Выпив его, ваше здоровье увеличилось до " 
			<< player.hp << " очков.";
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
	std::cout << enemy.name << " имеет " << enemy.hp << " очков здоровья.\n";
	std::cout << player.name << " имеет " << player.hp << " очков здоровья.\n\n";	
	system("Pause"); std::cout << std::endl;
	FirstAttack firstAttack = static_cast<FirstAttack>(randomizer(2, 1));
	switch (firstAttack) {
	case ENEMY:
	{
		std::cout << std::endl;
		short gainedDamage = enemyGiveDamage(enemy.baseDamage);
		player.hp -= gainedDamage;
		std::cout << enemy.name << " внезапно наносит " << gainedDamage << " урона герою " << player.name << std::endl;
		if (player.hp <= 0) playerDeath(enemy, roomNumber);
		do {
			std::cout << "-----------------------------------------\n";
			std::cout << "У героя " << player.hp << " очков здоровья\n";
			std::cout << "У врага " << enemy.hp << " очков здоровья\n";
			std::cout << "-----------------------------------------\n\n";			
			system("Pause"); std::cout << std::endl;
			int dealDamage = playerGiveDamage();
			enemy.hp -= dealDamage;
			std::cout << "Ловко используя " << player.weapon.name << ", Вы нанесли " << dealDamage
				<< " урона врагу " << enemy.name << std::endl;
			if (enemy.hp <= 0) {
				std::cout << "Вы победили врага " << enemy.name << std::endl << std::endl;
				system("Pause"); std::cout << std::endl; 
				enemyDrop(enemy.name);
			}
			dealDamage = enemyGiveDamage(enemy.baseDamage);
			player.hp -= dealDamage;
			std::cout << enemy.name << " яростно замахивается и наносит " << dealDamage << " урона герою "
				<< player.name << std::endl;
			if (player.hp <= 0) playerDeath(enemy, roomNumber);
		} while (enemy.hp > 0);
	}
	case PLAYER:
	{
		std::cout << std::endl;
		short gainedDamage = playerGiveDamage();
		enemy.hp -= gainedDamage;
		std::cout << player.name << " внезапно наносит " << gainedDamage << " урона врагу " << enemy.name << std::endl;
		if (enemy.hp <= 0) enemyDrop;
		do {
			std::cout << "-----------------------------------------\n";
			std::cout << "У врага " << enemy.hp << " очков здоровья\n";
			std::cout << "У героя " << player.hp << " очков здоровья\n";
			std::cout << "-----------------------------------------\n\n";			
			system("Pause"); std::cout << std::endl; 
			int dealDamage = enemyGiveDamage(enemy.baseDamage);
			player.hp -= dealDamage;
			std::cout << enemy.name << " яростно замахивается и наносит " << dealDamage << " урона герою "
				<< player.name << std::endl;
			if (player.hp <= 0) playerDeath(enemy, roomNumber);
			dealDamage = playerGiveDamage();
			enemy.hp -= dealDamage;
			std::cout << "Ловко используя " << player.weapon.name << ", Вы нанесли " << dealDamage
				<< " урона врагу " << enemy.name << std::endl;
			if (enemy.hp <= 0) {
				std::cout << "Вы победили врага " << enemy.name << std::endl;				
				system("Pause"); std::cout << std::endl;
				enemyDrop(enemy.name);
			}

		} while (enemy.hp > 0);
	}
	}
}
void enemyPrint(EnemyStats enemy, int roomNumber) {
	std::cout << "Долго бродив по старинной крипте, Вы заходите в комнату, из которой издаются странные звуки...\n\n";
	switch (enemy.type) {
	case SPIDER:
		std::cout << "Посмотрев на высокий потолок, Вы замечаете черные очертания. Кто или что это могло бы быть?\n";
        std::cout << "Вы кидаете камень в направлении черного существа.\n";
		std::cout << "О нет! Существо зашевелилось и спрыгнуло около ваших ног. Оказывается, это ОГРОМНЫЙ ПАУК!\n\n";
		break;
	case SKELETON:
		std::cout << "В центре комнтаты стоит груда костей.\n";
		std::cout << "Как только Вы к ней приблизились, старые, покрытые плесенью, кости выстроились в человекоподобное " <<
			"существо.\n";
		std::cout << "О нет, это СКЕЛЕТ! Он настроен агрессивно!\n\n";
		break;
	case ZOMBIE:
		 std::cout << "Вы сразу чувствуете неприятный запах, из-за которого практически невозможно дышать.\n";
		 std::cout << "Задержав дыхание, Вы подбираетесь к источнику этого зловония. Им оказался ЗОМБИ, пожирающий " <<
			 "чьи-то останки!\n Заприметив Вас, он зарычал и двинулся в Вашу сторону!\n\n";
		 break;
	case TROLL:
		 std::cout << "Из дальнего угла комнаты доносится очень громкий и продолжительный смех.\n";
		 std::cout << "Интуиция подсказывает, что ничего хорошего здесь можно не ждать, но Ваше любопытство охватывает верх\n";
		 std::cout << "Вы подходите к источнику смеха. В углу сидит громоздкий грязный зеленый ТРОЛЛЬ, стучащий дубиной по " <<
			 "своему животу.\nВаша сдержанность оказалось непосильна чувству смеха, который выдал Ваше присутствие...\n\n";
		 break;
	case GHOST:
		std::cout << "Внезапно Вам становится очень холодно, при дыхании изо рта валит пар. "
			<< "\"Это ненормально,\" - подумали Вы.\n";
		std::cout << "Внезапно шкаф, стоящий неподалеку падает, разбрасывая книги по всей комнате.\n";
		std::cout << "За спиной доносятся шипящие звуки. Обернувшись, Вы видите полупрозрачное нечто. Это же ПРИЗРАК!\n\n";
		break;
	case KNIGHT:
		 std::cout << "Звон доспехов и скрежет меча отражаются эхом по всей комнате.\n";
		 std::cout << "Неясное бормотание и медленные, но громкие шаги направляются в Вашу сторону...\n";
		 std::cout << "К Вам приближается РЫЦАРЬ, одетый в латные доспехи! По его виду можно сказать, что он безумен\n";
		 std::cout << "Приготовьтесь, схватка между Вами будет не на жизнь, а на смерть\n\n";
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
		std::cout << "Вы входите в освещенную комнату, посередине которой стоит сундук...\n";
		std::cout << "Вы нашли сокровище! Теперь Ваш баланс равен " << player.coins << std::endl << std::endl;		
		system("Pause"); std::cout << std::endl;
		roomCreate();
		break;
	case HEAL_POTION:
		player.hp += randomizer(Constants::maxHeal, Constants::minHeal);
		std::cout << "Вы входите в освещенную комнату, посередине которой стоит сундук...\n";
		std::cout << "Вы нашли бутылек с лекарством! Вам стало лучше, здоровье увеличилось до "
			<< player.hp << " очков." << std::endl << std::endl;		
		system("Pause"); std::cout << std::endl;
		roomCreate();
		break;
	}
	break;
	}
	case TRAP:
		player.hp -= randomizer(Constants::maxTrapDamage, Constants::minTrapDamage);
	    std::cout << "Бродя по мрачным и сырым коридорам, Вы случайно наступаете на нажимную плиту.\n";
		std::cout << "Вдалеке слышен скрежет механизмов.\nВнезапно из щели в стене в Вас вонзается что-то острое.\n";
		std::cout << "Вы чувствуете себя хуже. Ваш запас здоровья снизился до " << player.hp << " очков\n\n";
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
	cout << "Назовите своего героя(На анлийском): ";
	cin >> player.name;
	system("CLS");
	cout << player.name << " - отважный искатель приключений, решивший отправиться в одиночку в жуткое подземелье.\n";
	cout << "Кончено, Вы наслышаны о монстрах, которые там обитают, поэтому, собрав все свои сбережения,\n";
	cout << "отправляетесь в оружейную лавку." << endl;
	cout << "Ассортимент магазина не велик...\n";
	short weaponNum;
	do {
		cout << "На витринах Вы видите АРБАЛЕТ, КИНЖАЛЫ и МЕЧ\n";
		cout << "Какое оружие отважный герой возьмет с собой?\n";
		cout << "1 - Арбалет(Высокий урон. Шанс попадания 30 процентов)\n";
		cout <<	"2 - Кинжалы(Низкий урон. Двойной удар. Шанс попадания 50 процентов каждый)\n";
		cout <<	"3 - Меч(Низкий урон. Шанс попадания 100 процентов)\n Введите номер оружия: ";
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
	cout << "Итак, " << player.name << ", у Вас в руках " << player.weapon.name <<
		". Вы полны сил, у Вас " << player.hp << " очков здоровья\n";
	cout << "Взяв волю в кулак, Вы входите в темную крипту...\n\n";
	system("Pause"); std::cout << std::endl;
	roomCreate();
}

int main() {
	srand(static_cast<long long>(time(0)));
	gameStart();
	return 0;
}