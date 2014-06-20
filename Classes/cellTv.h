#ifndef _cellTv_H_
#define _cellTv_H_

#include "cocos2d.h"

USING_NS_CC;

class cellTv : public Node
{
public:
    cellTv(void);
    virtual ~cellTv(void);

    static cellTv * create(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
        
    static cellTv* createNode(const std::string& filename, float globalZorder);

    void runRotateAction();

    void runMoveAction();
    
    void setSourcePosition(Vec2 source){_source = source;}
    
    Vec2 getSourcePosition(){return _source;}
    
    void setDestinationPosition(Vec2 destination){_destination = destination;}
    
    Vec2 getDestinationPosition(){return _destination;}
    
    void setDelayTime(float time){_time=time;}
    
    float getDelayTime(){return _time;}
protected:
    Vec2 _source;
    Vec2 _destination;
    float _time;
};

#endif
