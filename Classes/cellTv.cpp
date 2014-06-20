#include "cellTv.h"

#define COVER_TAG 1111
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

cellTv* cellTv::createNode(const std::string& filename, float globalZorder, bool withCover)
{
    auto node = cellTv::create();
    
    Sprite* pcellTv = Sprite::createWithSpriteFrameName(filename);
    pcellTv->setGlobalZOrder(globalZorder);
    
    node->addChild(pcellTv);
    
    if (withCover) {
        Sprite* pCover = Sprite::createWithSpriteFrameName("cellbackground.png");
        pCover->setTag(COVER_TAG);
        pCover->setOpacity(255*3/4);
        pCover->setGlobalZOrder(globalZorder+0.01);
        node->addChild(pCover, 1);
    }

    return node;
}

void cellTv::runRotateAction()
{
    ActionInterval* action1 = OrbitCamera::create(2, 1, 0, 0, 360, 0, 0);
    
    float time = CCRANDOM_0_1() * 10 + _time;
    
    runAction( Sequence::create(DelayTime::create(time), ReverseTime::create(action1), NULL) );
    //    runAction( RepeatForever::create(Sequence::create(actionDelay, ReverseTime::create(action1), NULL)) );
}

void cellTv::rotateDelay(int delayTime)
{
    auto delayAction = DelayTime::create(0.25*delayTime);
    ActionInterval* action1 = OrbitCamera::create(0.5, 1, 0, 0, 180, 0, 0);
   
    runAction(Sequence::create(delayAction,
                               action1,
                               CallFunc::create( CC_CALLBACK_0(cellTv::setCoverVisible,this)),
                               NULL));
}

void cellTv::moveToDestination()
{
    runAction(Sequence::create(
                               DelayTime::create(_time),
                               Show::create(),
                               EaseSineOut::create(MoveTo::create(0.5, _destination)),
                               NULL));
}

void cellTv::moveToSource()
{
    runAction(Sequence::create(
                               DelayTime::create(_time),
                               EaseSineOut::create(MoveTo::create(0.5, _source)),
                               Hide::create(),
                               NULL));
}

void cellTv::setCoverVisible()
{
    auto node = this->getChildByTag(COVER_TAG);
    if(node == NULL) return;
    
    node->setVisible(false);
}

void cellTv::onEnter()
{
    Node::onEnter();

}

void cellTv::onExit()
{
    Node::onExit();
}    
