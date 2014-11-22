#pragma once
#include "mapobj.h"
#include "UDWhenPlay.h"

class Prop :
	public MapObj, public DynamicCreation
{
public:
	Prop(void);
	virtual ~Prop(void);

	DeclareDynamicCreation(Prop);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player);
	virtual bool onPlayerSteping(Player* player);
	virtual bool onPlayerFinished(Player* player);

	virtual bool canAStar() override;
private:
	udi_t m_type;
	string m_texture;
};

