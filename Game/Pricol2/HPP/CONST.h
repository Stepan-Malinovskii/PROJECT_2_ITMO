#pragma once
#ifndef CONSTS
#define CONSTS

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>

//#define REDACT_MODE

#define SQUARE(a) ((a) * (a))
#define GETDIST(a,b) (SQUARE(a.x - b.x) + SQUARE(a.y - b.y))
#define COMPARER(a, b, c) GETDIST(a, c) > GETDIST(b, c) ? true : false

constexpr float ROTATION_SPEED = 80.0f, VERTICAL_MOUSE_SPEED = 25.0f;
const int TEXTURE_SIZE = 128, ICON_SIZE = 64, TEXTURE_COUNT = 15;
constexpr int SCREEN_W = 1280, SCREEN_H = 720;
constexpr float PI = 3.14159265359f, TRIGER_DIST = 12.0f;
constexpr int ENEMY_MAX_INDEX = 12, PORTAL_INDEX = 17, SPAWN_RADIUS = 8;
constexpr int MAX_RAD = 30, MIN_RAD = 1;
constexpr int COUNT_ROW_TEXT = 7;
constexpr int MIN_LEAF_SIZE = 10, MAX_LEAF_SIZE = 20;
constexpr int ALL_LAYER = 4;
constexpr int LAYER_COUNT = 3;
constexpr int FLOOR_LAYER = 0;
constexpr int WALL_LAYER = 1;
constexpr int CELL_LAYER = 2;
constexpr int SPRITE_LAYER = 3;
constexpr int SPACE_SIZE_W = 40, SPACE_SIZE_H = 40;
constexpr int ENEMY_LEVEL_COUNT = 40;
constexpr int NEXT_LEVEL_N = -1, BASE_N = 0, ARENA_1_N = 1, ARENA_2_N = 2, ARENA_3_N = 3, BOSS_N = 4;
constexpr int MAX_DETH = 64;
constexpr float PLAYER_FOV = 60.0f, CAMERA_Z = SCREEN_H / 2.0f, ASPECT = (float)SCREEN_W / SCREEN_H * 0.5f, BRIGHTNESTDIST = MAX_DETH / 7.0f;
constexpr float DIALOG_W = SCREEN_W - 200, DIALOG_H = SCREEN_H - 100, INTERVAL = 40;
constexpr int TEXTSIZE = 50;

enum class SpriteType { Enemy, PlayerT, NPC, Convertor, Boss, Decoration };

enum EnemyState { Stay, Run, Attack, Spawn, Dead };

enum NpcType { Dilog, TraderNpcType, Traveler, ChangerNpcType, QuestNpcType, MechanicNpcType, PortalNpcType };

enum QuestType { KillMonster, CollectionMoney, CollectionDetails };

enum MusicType { MenuSound, BaseSound, LevelSound, StartIntro, EndIntro };

enum ImproveType { Damage, Spread, Magazin };

enum ItemType { MaxEnergy, MaxHeal, Heal, Armor, Patrons };

struct QuestData
{
	QuestType type;
	int progress;
	int target;
	int rewardCoins;
};

struct PlayerDef
{
	float maxHp;
	float nowHp;
	float maxEnergy;
	float nowEnergy;
	float defence;
	float maxStrenght;
	float nowStrenght;
	int countpantrons;
	int money;
	int details;
	std::vector<int> gunsData;
};

struct GunData
{
	int id;
	int nowCount;
	int nowMaxCount;
	int nowMaxRad;
	int nowDamage;
	int upgradeCount;
	std::vector<int> improveId;
};

struct GunDef
{
	int id;
	int damage;
	int maxCount;
	int nowCount;
	float shutTime;
	float maxDist;
	float resetTime;
	int cost;
	std::wstring name;
	std::wstring disc;
};

struct ItemsDef
{
	int id;
	ItemType type;
	std::wstring name;
	int effect;
	int maxUSing;
	int cost;
	std::wstring disc;
};

struct ImproveDef
{
	int id;
	ImproveType type;
	std::wstring name;
	float effect;
	int cost;
	std::wstring disc;
};

struct MapSprite
{
	int spriteDefId;
	sf::Vector2f position;
	float angle;
	float nowHealPoint;
};

struct SpriteDef
{
	std::wstring name;
	SpriteType type;
	float size;
	int texture;
	bool isDirectional;
};

struct EnemyDef
{
	bool isCanRun;
	float attackDist;
	float damage;
	int midleDrop;
	float timeBettwenAtack;
	float speed;
	float maxHealpoint;
};

struct ConverterDef
{
	std::vector<int> callingIndex;
	int maxSpawnCount;
};

struct NpcDef
{
	NpcType type;
	int idKey;
};

struct TraderDef
{
	int startKey;
	std::vector<int> title;
};

struct GameStateData
{
	bool isFirstGame;
	int effectVolume;
	int soundVolume;
	int levelNumber;
	bool isLevelBase;
	int changerCoef;
	float mouseSpeed;
	bool killFirst;
	bool killSecond;
	bool killTherd;
};

static std::vector<std::string> mapFileNames {
	"base.map",
	"converter1.map",
	"converter2.map",
	"converter3.map",
	"boss.map" 
};

static std::vector<ItemsDef> itemsDefs {
	{9,  ItemType::Heal, L"����� �������", 20, 1, 10, L"�������������� 20 HP"},
	{10, ItemType::Heal, L"������� �������", 50, 1, 20, L"�������������� 50 HP"},
	{11, ItemType::Heal, L"������� �������", 100, 1, 30, L"�������������� 100 HP"},
	{12, ItemType::MaxHeal, L"����������������� �������� 1", 20, 1, 300, L"80% ��� +20 � maxHP, 20% - -10 maxHP"},
	{13, ItemType::MaxEnergy, L"����������������� �������� 2", 2, 1, 300, L"80% ��� +2 � maxEnergy, 20% - -1 maxEnergy"},
	{14, ItemType::Armor, L"�������� ��������", 10, 50, 50, L"-10% ����������� �����, 50 �������������"},
	{15, ItemType::Armor, L"�������� ��������", 20, 70, 80, L"-20% ����������� �����, 70 �������������"},
	{16, ItemType::Armor, L"���������� ��������", 30, 90, 100, L"-30% ����������� �����, 90 �������������"},
	{17, ItemType::Armor, L"���������� ��������", 50, 110, 200, L"-50% ����������� �����, 110 �������������"},
	{18, ItemType::Patrons, L"����� ���� ��������", 50, 1, 20, L"�������� 50 ��������"},
	{19, ItemType::Patrons, L"������� ���� ��������", 100, 1, 35, L"�������� 100 ��������"},
	{20, ItemType::Patrons, L"������� ���� ��������", 150, 1, 50, L"�������� 150 ��������"}
};

static std::vector<GunDef> gunsDef {
	{21, 10, 100, 100, 0.5f, 2.0f, 0, 0,       L"����",        L"���� - 10  | ������ - 100 �� | ���������������� - 0.5 ��� | ��������� - 1  �"},
	{22, 10, 100, 100, 0.3f, 2.0f, 0, 0,       L"�����",       L"���� - 10  | ������ - 100 �� | ���������������� - 0.3 ��� | ��������� - 1  �"},
	{23, 10, 20, 20, 0.4f, 20.0f, 1.5f, 0,     L"��������",    L"���� - 10  | ������ - 20  �� | ���������������� - 0.4 ��� | ��������� - 20 �"},
	{24, 50, 5, 5, 1.0f, 5.0f, 2.0f, 340,      L"�����",       L"���� - 50  | ������ - 5   �� | ���������������� - 1.0 ��� | ��������� - 5  �"},
	{25, 90, 2, 2, 0.6f, 5.0f, 3.0f, 500,      L"�����������", L"���� - 90  | ������ - 2   �� | ���������������� - 0.6 ��� | ��������� - 5  �"},
	{26, 20, 30, 30, 0.4f, 15.0f, 3.0f, 600,   L"�������",     L"���� - 20  | ������ - 30  �� | ���������������� - 0.4 ��� | ��������� - 15 �"},
	{27, 200, 1, 1, 1.0f, 10.0f, 3.0f, 700,    L"������",      L"���� - 200 | ������ - 1   �� | ���������������� - 1.0 ��� | ��������� - 10 �"},
	{28, 10, 100, 100, 0.1f, 10.0f, 4.0f, 800, L"�������",     L"���� - 10  | ������ - 100 �� | ���������������� - 0.1 ��� | ��������� - 10 �"},
};

static std::vector<ImproveDef> improveDefs {
	{0, ImproveType::Magazin, L"����� �������", 1.2f, 200,   L"+20% � ������ ��������"},
	{1, ImproveType::Magazin, L"������� �������", 1.3f, 300, L"+30% � ������ ��������"},
	{2, ImproveType::Magazin, L"������� �������", 1.5f, 400, L"+50% � ������ ��������"},
	{3, ImproveType::Spread,  L"�������� ������", 1.4f, 150, L"-40% � ��������"},
	{4, ImproveType::Spread,  L"��������������� ������", 1.6f, 250, L"-60% � ��������"},
	{5, ImproveType::Spread,  L"���������� ������", 1.8f, 350, L"-80% � ��������"},
	{6, ImproveType::Damage,  L"�������������", 1.3f, 250, L"+30% � �����"},
	{7, ImproveType::Damage,  L"����", 1.4f, 350, L"+40% � �����"},
	{8, ImproveType::Damage,  L"�������", 1.5f, 450, L"+50% � �����"}
};

static std::vector<ItemsDef> travelerDefs {
	{29, ItemType::Heal, L"", NEXT_LEVEL_N, 1, 50,  L"����������� �� ��������� �������"},
	{30, ItemType::Heal, L"", ARENA_1_N,    1, 100, L"����������� �� ��������������� 1"},
	{31, ItemType::Heal, L"", ARENA_2_N,    1, 150, L"����������� �� ��������������� 2"},
	{32, ItemType::Heal, L"", ARENA_3_N,    1, 200, L"����������� �� ��������������� 3"},
	{33, ItemType::Heal, L"", BOSS_N,       1, 250, L"������� � �����"}
};

static std::vector<NpcDef> npcDefs{
	{PortalNpcType, 1},
	{TraderNpcType, 4},
	{TraderNpcType, 5},
	{ChangerNpcType, 3},
	{Traveler, 2},
	{QuestNpcType, 6},
	{MechanicNpcType, 7},
	{NpcType::Dilog, 8},
	{NpcType::Dilog, 9},
	{NpcType::Dilog, 10},
	{NpcType::Dilog, 11},
	{NpcType::Dilog, 12},
	{NpcType::Dilog, 13},
};

static std::vector<TraderDef> traderDefs {
	{4, {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}},
	{5, {24, 25, 26, 27, 28, 0, 1, 2, 3, 4, 5, 6, 7, 8}}
};

static std::vector<EnemyDef> enemyDefs {
	{true,  0.0f,   0.0f,  0,  0.0f, 5.0f, 0.0f },
	{true,  3.0f,  5.0f,  3, 1.5f, 3.0f, 70.0f  },
	{true,  3.0f,  8.0f,  5, 1.0f, 4.0f, 90.0f  },
	{true,  3.0f,  10.0f, 7, 1.5f, 5.0f, 100.0f },
	{true,  7.0f,  8.0f,  9, 1.0f, 4.0f, 120.0f },
	{true,  7.0f,  10.0f, 10, 1.0f, 5.0f, 200.0f },
	{true,  3.0f,  12.0f, 13, 1.5f, 6.0f, 150.0f },
	{true,  7.0f,  20.0f, 14, 1.5f, 3.0f, 300.0f },
	{true,  3.0f,  15.0f, 15, 1.5f, 6.0f, 200.0f },
	{true,  3.0f,  20.0f, 18, 1.5f, 6.0f, 200.0f },
	{true,  7.0f,  22.0f, 19, 1.0f, 5.0f, 180.0f },
	{false, 7.0f,  35.0f, 20, 1.5f, 4.0f, 300.0f },
	{true,  3.0f,  26.0f, 25, 1.5f, 4.0f, 320.0f },
	{true,  3.0f,  30.0f, 10, 1.5f, 5.0f, 8000.0f},
	{false, 6.0f,  0.0f,  20, 3.0f, 0.0f, 100.0f},
	{false, 6.0f,  0.0f,  40, 3.0f, 0.0f, 100.0f},
	{false, 6.0f,  0.0f,  60, 3.0f, 0.0f, 100.0f}
};

static std::vector<ConverterDef> converterDefs {
	{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 40},
	{{1, 2, 3, 4, 5}, 10},
	{{5, 6, 7, 8, 9}, 20},
	{{8, 9, 10, 11, 12}, 30}
};

static std::vector<SpriteDef> spriteDefs {
	{ L"player",           SpriteType::PlayerT,   0.3f, -1,  false},
	{ L"����",             SpriteType::Enemy,     1.0f,  0,  true},
	{ L"������",           SpriteType::Enemy,     1.0f,  1,  true},
	{ L"������� �����",    SpriteType::Enemy,     1.0f,  2,  true},
	{ L"����� �����",      SpriteType::Enemy,     1.0f,  3,  true},
	{ L"�������",          SpriteType::Enemy,     1.0f,  4,  true},
	{ L"������� �����",    SpriteType::Enemy,     1.0f,  5,  true},
	{ L"���������",        SpriteType::Enemy,     1.0f,  6,  true},
	{ L"������� �����",    SpriteType::Enemy,     1.0f,  7,  true},
	{ L"������� �����",    SpriteType::Enemy,     1.0f,  8,  true},
	{ L"��������",         SpriteType::Enemy,     1.0f,  9,  true},
	{ L"���� ����",        SpriteType::Enemy,     1.0f,  10, true},
	{ L"����",             SpriteType::Enemy,     1.0f,  11, true},
	{ L"Boss",             SpriteType::Boss,      1.0f,  12, true},
	{ L"���������������1", SpriteType::Convertor, 1.0f,  13, true},
	{ L"���������������2", SpriteType::Convertor, 1.0f,  14, true},
	{ L"���������������3", SpriteType::Convertor, 1.0f,  15, true},
	{ L"������",           SpriteType::NPC,       1.0f,  16, true},
	{ L"��������",         SpriteType::NPC,       1.0f,  17, true},
	{ L"�������",          SpriteType::NPC,       1.0f,  18, true},
	{ L"�����",            SpriteType::NPC,       1.0f,  19, true},
	{ L"������",           SpriteType::NPC,       1.0f,  20, true},
	{ L"�����",            SpriteType::NPC,       1.0f,  21, true},
	{ L"������",           SpriteType::NPC,       1.0f,  22, true},
	{ L"������ ��������",  SpriteType::NPC,       1.0f,  23, true},
	{ L"������ ��������",  SpriteType::NPC,       1.0f,  24, true},
	{ L"������� ���������",SpriteType::NPC,       1.0f,  25, true},
	{ L"���� �����������", SpriteType::NPC,       1.0f,  26, true},
	{ L"������",           SpriteType::NPC,       1.0f,  27, true},
	{ L"����",             SpriteType::NPC,       1.0f,  28, true},
	{ L"�����",            SpriteType::Decoration,1.0f,  29, false},
	{ L"�����",            SpriteType::Decoration,1.0f,  30, false},
	{ L"����",             SpriteType::Decoration,1.0f,  31, false},
	{ L"�������",          SpriteType::Decoration,1.0f,  32, false},
};

#endif // !CONSTS
