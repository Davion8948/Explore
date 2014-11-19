/*
 * 非物理引擎的碰撞检测 
 
 * 由于CollisionDomain(long long)的限制
 * 最多支持64-1个(不包括0)碰撞域
 
 * 要保证
 * 如果两个对象的selfDomain一样
 * 则它们的targetDomain也一样
 * 
*/
#pragma once

#include <set>
#include "cocos2d.h"

USING_NS_CC;

namespace lib4cc3x
{

	typedef long long CollisionDomain;

	//////////////////////////////////////////////////////////////////////////
	//任何想要实施碰撞功能的对象都必须继承这个类
	class Collisionable
	{
	public:
		Collisionable(void);
		virtual ~Collisionable(void);

		virtual void hitBy(Collisionable* obj) = 0;
		virtual Action* getAttackAction() = 0;

		virtual Rect getCollisionRect() = 0;

		CollisionDomain getSelfDomain();
		CollisionDomain getTargetDomain();	

	protected:
		//selfDomain保证对象能被正确碰撞
		//targetDomain保证能正确碰撞其它对象
		CollisionDomain m_selfDomain;
		CollisionDomain m_targetDomain;
	};


	//////////////////////////////////////////////////////////////////////////
	//碰撞检测的真正实施者
	class CollisionChecker
	{
	public:
		CollisionChecker(void);
		virtual ~CollisionChecker(void);

		void addObject(Collisionable* obj);
		void delObject(Collisionable* obj);
		void delAll();

		//在update中检测对象是否碰撞
		virtual void update(float delta);

	protected:
		typedef std::set<Collisionable*> ObjectGroup;
		typedef std::set<CollisionDomain> DomainGroup;

		virtual void CollisionTwoGroup(ObjectGroup& group1, ObjectGroup& group2);

	private:
		struct PrivateData
		{
			DomainGroup targets;
			ObjectGroup objects;
		};

		std::map<CollisionDomain, PrivateData> m_domain2obj;//actual data
	};

}
