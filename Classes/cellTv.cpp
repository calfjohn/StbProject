#include "cellTv.h"

cellTv::cellTv(void)
{
}

cellTv::~cellTv(void)
{
}

cellTv * cellTv::create(void)
{
	cellTv * ret = new cellTv();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

cellTv* cellTv::createNode(const std::string& filename, float globalZorder)
{
    auto node = cellTv::create();
    
    Sprite* pcellTv = Sprite::createWithSpriteFrameName(filename);
    
    pcellTv->setGlobalZOrder(globalZorder);
    
    node->addChild(pcellTv);
    
    return node;
}

void cellTv::runRotateAction()
{
    float time = CCRANDOM_0_1() * 10;
    auto actionDelay = DelayTime::create(time+1.5);
    ActionInterval* action1 = OrbitCamera::create(2, 1, 0, 0, 360, 0, 0);
    runAction( Sequence::create(actionDelay, ReverseTime::create(action1), NULL) );
//    runAction( RepeatForever::create(Sequence::create(actionDelay, ReverseTime::create(action1), NULL)) );
}

void cellTv::runMoveAction()
{
    runAction(Sequence::create(
                                DelayTime::create(_time),
                                EaseOut::create(MoveTo::create(1.0, _destination), 1.0),
                                NULL));
}

void cellTv::onEnter()
{
    Node::onEnter();

}

void cellTv::onExit()
{
    Node::onExit();
}    
