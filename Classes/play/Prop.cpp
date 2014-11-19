#include "Prop.h"
#include "GameMap.h"
#include "UserData.h"

ImplementDynamicCreation(Prop);

Prop::Prop(void)
{
}


Prop::~Prop(void)
{
}

void Prop::config( const cocos2d::ValueMap& cfg )
{	
	MapObj::config(cfg);
	safe_assign(m_texture, cfg, "texture");
	map<string,UserData::UserDataIndex> data;
	data.insert( make_pair("heart.png", UserData::udi_heart) );
	data.insert( make_pair("shield.png", UserData::udi_shield) );
	data.insert( make_pair("key.png", UserData::udi_key) );
	data.insert( make_pair("arrow.png", UserData::udi_arrow) );
	data.insert( make_pair("hoe.png", UserData::udi_hoe) );
	data.insert( make_pair("bomb.png", UserData::udi_bomb) );
	data.insert( make_pair("map.png", UserData::udi_map) );
	m_type = data.at(m_texture);
}

bool Prop::willPlayerEnter( Player* player )
{
	return true;
}

bool Prop::onPlayerSteping( Player* player )
{
	Sprite* texture = Sprite::create(m_texture);
	texture->setPosition(getPosition());
	Label* text = Label::createWithTTF( "+1", "fonts/Marker Felt.ttf", 32);
	text->setPositionX(getContentSize().width);
	text->setPositionY(getContentSize().height/2);
	text->setAnchorPoint(Point(0, 0.5f));
	texture->addChild(text);
	texture->setScale(0.5f);
	getParent()->addChild(texture);

	texture->runAction( Sequence::create(MoveBy::create(3, Vec2(0, 64+32)), CCCallFunc::create(std::bind(&Node::removeFromParent,texture)), 0) );

	return true;
}

bool Prop::onPlayerFinished( Player* player )
{
	UserData::inst().addValue(m_type, 1);
	return false;
}
