#include "Collisionable.h"

using namespace lib4cc3x;
using namespace std;

Collisionable::Collisionable( void )
	:m_selfDomain(0)
	,m_targetDomain(0)
{

}

Collisionable::~Collisionable( void )
{

}

CollisionDomain Collisionable::getTargetDomain()
{
	return m_targetDomain;
}

CollisionDomain Collisionable::getSelfDomain()
{
	return m_selfDomain;
}

//////////////////////////////////////////////////////////////////////////
// 工具函数
// 把level集合转换成LevelGroup类型
set<CollisionDomain> parseCollision(CollisionDomain level)
{
	set<CollisionDomain> ret;

	int temp = level;
	int i = 1;
	while (0 != temp)
	{
		if (0 != (level&i))
		{
			ret.insert(level&i);
		}
		i *= 2;
		temp /= 2;
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// 工具类
// 记录两个对象(通过对象的SelfLevel)是否已经碰撞过
class LevelRecord
{
public:
	bool has(CollisionDomain level1, CollisionDomain level2)
	{
		set< pair<CollisionDomain, CollisionDomain> >::iterator iter = m_record.find( make_pair(min(level1,level2), max(level1,level2)) );
		return (iter!=m_record.end());
	}
	void record(CollisionDomain level1, CollisionDomain level2)
	{
		m_record.insert( make_pair(min(level1,level2), max(level1,level2)) );
	}
private:
	set< pair<CollisionDomain, CollisionDomain> > m_record;
};

//////////////////////////////////////////////////////////////////////////
CollisionChecker::CollisionChecker(void)
{
}


CollisionChecker::~CollisionChecker(void)
{
}

void CollisionChecker::addObject( Collisionable* obj )
{
	//保存obj被碰撞的信息
	CollisionDomain self = obj->getSelfDomain();
	map<CollisionDomain, PrivateData>::iterator iter = m_domain2obj.find(self);
	if (iter == m_domain2obj.end())
	{
		PrivateData data;
		data.objects.insert(obj);
		data.targets = parseCollision(obj->getTargetDomain());
		m_domain2obj.insert( make_pair(self, data) );
	}
	else
	{
		iter->second.objects.insert(obj);
	}
}

void CollisionChecker::delObject( Collisionable* obj )
{
	map<CollisionDomain, PrivateData>::iterator iter = m_domain2obj.find( obj->getSelfDomain() );
	if (iter != m_domain2obj.end())
	{
		iter->second.objects.erase(obj);
	}
}

void CollisionChecker::delAll()
{
	m_domain2obj.clear();
}

void CollisionChecker::update(float delta)
{
	LevelRecord rd;//防止重复碰撞，A vs B 后又执行 B vs A
	for (map<CollisionDomain, PrivateData>::iterator iter = m_domain2obj.begin(); iter != m_domain2obj.end(); ++iter)
	{
		PrivateData& data = iter->second;
		DomainGroup& targets = data.targets;
		ObjectGroup& objs = data.objects;

		for (DomainGroup::iterator it = targets.begin(); it != targets.end(); ++it)
		{
			CollisionDomain tar = *it;
			map<CollisionDomain, PrivateData>::iterator pos = m_domain2obj.find(tar);
			if (pos != m_domain2obj.end() && !rd.has(iter->first, *it))
			{
				CollisionTwoGroup(objs, pos->second.objects);
				rd.record(iter->first, *it);
			}
		}
	}
}

void CollisionChecker::CollisionTwoGroup( ObjectGroup& group1, ObjectGroup& group2 )
{
	for (ObjectGroup::iterator iter = group1.begin(); iter != group1.end(); ++iter)
	{
		for (ObjectGroup::iterator it = group2.begin(); it != group2.end(); ++it)
		{
			Rect src = (*iter)->getCollisionRect();
			Rect dst = (*it)->getCollisionRect();
			if ( src.intersectsRect( dst ) )
			{
				(*iter)->hitBy( *it );
				(*it)->hitBy( *iter );
			}
		}
	}
}
