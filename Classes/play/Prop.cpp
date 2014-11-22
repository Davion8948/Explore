#include "Prop.h"
#include "GameMap.h"
#include "UDWhenPlay.h"

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
	map<string,udi_t> data;
	data.insert( make_pair("heart.png", udi_t::udi_heart) );
	data.insert( make_pair("shield.png", udi_t::udi_shield) );
	data.insert( make_pair("key.png", udi_t::udi_key) );
	data.insert( make_pair("arrow.png", udi_t::udi_arrow) );
	data.insert( make_pair("hoe.png", udi_t::udi_hoe) );
	data.insert( make_pair("bomb.png", udi_t::udi_bomb) );
	data.insert( make_pair("map.png", udi_t::udi_map) );
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
	UDWhenPlay::inst().addValue(m_type, 1);
	return false;
}

bool Prop::canAStar()
{
	return true;
}
