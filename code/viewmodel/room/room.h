// viewmodel/room/room.h

#pragma once

#include <vector>
#include <map>
#include <random>
#include <memory>
#include "../entity/enemy.h"
#include "../../common/Grid.h"

struct EnemySpawnPoint {
	int gridX;
	int gridY;
};

class Room {
public:
	Room(int id, std::vector<EnemySpawnPoint> enemySpawnPoints);
	const std::vector<EnemySpawnPoint>& getEnemySpawnPoints() const;
	int getId() const;

private:
	int m_id;
	std::vector<EnemySpawnPoint> m_enemySpawnPoints;
};

class RoomFactory {
public:
	static RoomFactory& getInstance();  // 单例
	Room getRoom(int id) const;
	Room getRandomRoom() const;

private:
	RoomFactory();
	std::map<int, std::unique_ptr<Room>> m_roomTemplates;  // 房间模板库，<id, Room*>

	RoomFactory(const RoomFactory&) = delete;
	RoomFactory& operator=(const RoomFactory&) = delete;
};