//
//  ExplosionEffect.cpp
//  stbProject
//
//  Created by Ryeeeeee on 14-6-20.
//
//

#include "ExplosionEffect.h"

USING_NS_CC;

bool ExplosionEffect::init(){
    
    auto phoenix = ParticleSystemQuad::create("Phoenix.plist");
    phoenix->setScale(2);
    addChild(phoenix);
    
    this->scheduleOnce(schedule_selector(ExplosionEffect::addExplosionCallBack), 0.8);
    
    return true;
}

void ExplosionEffect::addExplosionCallBack(float dt){
    auto explosionNode = Node::create();
    //explosionNode->setRotation3D(Vec3(60, 10, 0));
    explosionNode->setScaleY(0.25f);
    explosionNode->setPosition(Vec2(200, 200));
    auto explosion = ParticleSystemQuad::create("ExplodingRing.plist");
    explosion->setScale(1.5);
    explosionNode->addChild(explosion);
    
    this->addChild(explosionNode);
}