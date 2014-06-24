#include "cellTv.h"
//#include "SpriteBlur.h"

#define COVER_TAG 1111
#define CELL_TAG 1112
#define FRAME_TAG 1113

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
    node->setGlobalZOrder(globalZorder);
    
//    SpriteBlur* pcellTv = SpriteBlur::createWithSpriteFrameName(filename.c_str());
    Sprite* pcellTv = Sprite::createWithSpriteFrameName(filename);
    pcellTv->setGlobalZOrder(globalZorder);
    pcellTv->setTag(CELL_TAG);
    
    node->addChild(pcellTv);
    
    Sprite* pcellFrame = Sprite::createWithSpriteFrameName("cellframe.png");
    pcellFrame->setGlobalZOrder(globalZorder);
    pcellFrame->setTag(FRAME_TAG);
    node->addChild(pcellFrame);

    if (withCover) {
//        pcellTv->setBlurSize(1.5);
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
    
    runAction(EaseElasticOut::create(Sequence::create(DelayTime::create(time), ReverseTime::create(action1), NULL)));
}

void cellTv::rotateDelay(int delayTime)
{
    auto delayAction = DelayTime::create(0.25*delayTime);
    ActionInterval* action1 = OrbitCamera::create(0.5, 1, 0, 0, 360, 0, 0);
   
    runAction(EaseSineOut::create(Sequence::create(delayAction,
                               action1,
                               CallFunc::create( CC_CALLBACK_0(cellTv::setCoverVisible,this)),
                               NULL)));
}

void cellTv::moveToDestination()
{
    runAction(EaseSineOut::create(Sequence::create(
                               DelayTime::create(_time),
                               Show::create(),
                               EaseSineOut::create(MoveTo::create(0.5, _destination)),
                               NULL)));
}

void cellTv::moveToSource()
{
    runAction(EaseSineOut::create(Sequence::create(
                               DelayTime::create(_time),
                               EaseSineOut::create(MoveTo::create(0.5, _source)),
                               Hide::create(),
                               NULL)));
}

void cellTv::setCoverVisible()
{
    auto node = this->getChildByTag(COVER_TAG);
    if(node == NULL) return;
    
    node->setVisible(false);
    
//    SpriteBlur *node = (SpriteBlur *)this->getChildByTag(CELL_TAG);
//    if(node == NULL) return;
//    
//    node->setBlurSize(1.0);
}

void cellTv::resetGlobelZorder()
{
    getChildByTag(CELL_TAG)->setGlobalZOrder(_globelZorder);
    getChildByTag(FRAME_TAG)->setGlobalZOrder(_globelZorder);
}

void cellTv::bringNodeToTop()
{
    getChildByTag(CELL_TAG)->setGlobalZOrder(10000);
    getChildByTag(FRAME_TAG)->setGlobalZOrder(10000);
}


void cellTv::onEnter()
{
    Node::onEnter();

}

void cellTv::onExit()
{
    Node::onExit();
}    
