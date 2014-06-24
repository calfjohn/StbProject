#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


// ShaderBlur

class SpriteBlur : public Sprite
{
public:
    ~SpriteBlur();
    void setBlurSize(float f);
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    void initGLProgram();
    
    static SpriteBlur* create(const char *pszFileName);
    
    static SpriteBlur* createWithSpriteFrame(SpriteFrame *spriteFrame);

    static SpriteBlur* createWithSpriteFrameName(const std::string& spriteFrameName);
protected:
    
    int         _blurRadius;
    Vec2     _pixelSize;
    
    int       _samplingRadius;
    //gaussian = cons * exp( (dx*dx + dy*dy) * scale);
    float     _scale;
    float     _cons;
    float     _weightSum;
};

#endif
