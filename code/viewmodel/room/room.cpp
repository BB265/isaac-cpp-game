// viewmodel/room/room.cpp

#include "room.h"

Room::Room(int id, std::vector<EnemySpawnPoint> enemySpawnPoints)
	: m_id(id), m_enemySpawnPoints(std::move(enemySpawnPoints)) {

}

const std::vector<EnemySpawnPoint>& Room::getEnemySpawnPoints() const {
	return m_enemySpawnPoints;
}

int Room::getId() const {
	return m_id;
}






RoomFactory& RoomFactory::getInstance() {
	static RoomFactory instance;
	return instance;
}

Room RoomFactory::getRoom(int id) const {
	return *m_roomTemplates.at(id);
}

Room RoomFactory::getRandomRoom() const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, m_roomTemplates.size() - 1);
	int randomId = distrib(gen);
	return *m_roomTemplates.at(randomId);
}

RoomFactory::RoomFactory() {
    // 定义所有房间的模板

    // --- 房间模板 0: 左上角一个怪 ---
    m_roomTemplates[0] = std::make_unique<Room>(0, std::vector<EnemySpawnPoint>{
        {1, 1}
    });

    // --- 房间模板 1: 右下角两个怪 ---
    m_roomTemplates[1] = std::make_unique<Room>(1, std::vector<EnemySpawnPoint>{
        {11, 5},
		{10, 4}
    });

    // --- 房间模板 2: 四角各一个怪 ---
    m_roomTemplates[2] = std::make_unique<Room>(2, std::vector<EnemySpawnPoint>{
        {1, 1},
        {11, 1},
        {1, 5},
		{11, 5}
    });

    // --- 房间模板 3: 中心三个怪 ---
    m_roomTemplates[3] = std::make_unique<Room>(3, std::vector<EnemySpawnPoint>{
        {6, 3},
        {5, 2},
        {7, 4}
    });
}