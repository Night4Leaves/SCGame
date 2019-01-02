#include "MapUtil.h"
#include "Entity/Monster.h"

void MapUtil::installMonsters(TMXObjectGroup* objectsPoints)
{
	ValueMap monsterPoint = {};
	float monsterX = 0.0;
	float monsterY = 0.0;
	int i = 1;

	do
	{
		log(StringUtils::format("monster_%02d", i).c_str());
		monsterPoint = objectsPoints->getObject(StringUtils::format("monster_%02d", i++).c_str());
		monsterX = monsterPoint.at("x").asFloat();
		monsterY = monsterPoint.at("y").asFloat();
	} while (!monsterPoint.empty());
}
