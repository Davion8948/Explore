#pragma once
#include "cex/cex.h"
#include "EncryptValue.h"

class LevelDataMgr 
    : public cex::Singleton<LevelDataMgr>
{
public:
    LevelDataMgr();
    ~LevelDataMgr();
    
public:
    void setMainLevel(int val);
    int getMainLevel();
    
    void setViceLevel(int val);
    int getViceLevel();
    
    int getMainLevelCount();
    int getViceLevelCount();
    bool isUnlock(int mainLevel);
private:
    EVI m_mainLevel;
    EVI m_viceLevel;
};