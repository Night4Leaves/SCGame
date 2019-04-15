#pragma once
#ifndef __CHEMISTRY_SCENE_ITEM_H__
#define __CHEMISTRY_SCENE_ITEM_H__

#include "CustomizeStruct.h"

class ChemistrySceneItem : public Node
{
public:
	CREATE_FUNC(ChemistrySceneItem);
	virtual bool init();

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

	void setType(ChemistryType chemistryType);

protected:
	ChemistrySceneItem();
	virtual ~ChemistrySceneItem();

private:
	ChemistryType m_enChemistryType;
	Sprite* m_pSprite;
};

#endif // !__CHEMISTRY_SCENE_ITEM_H__
