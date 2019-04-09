#pragma once
#ifndef __CHARACTER_SELECTOR_H__
#define __CHARACTER_SELECTOR_H__

#include "CustomizeStruct.h"

class CharacterSelector : public Node
{
public:
	static CharacterSelector * create(PlayerData playerData);

	void setCreateNewDataVol();
	void setLoadSaveDataVol();

	void startGame(Ref* pSender);
	void deleteSavedata(Ref* pSender);

protected:
	CharacterSelector();
	virtual ~CharacterSelector();

	virtual bool init(PlayerData playerData);

private:
	PlayerData m_sctPlayerData;
};

#endif // !__CHARACTER_SELECTOR_H__
