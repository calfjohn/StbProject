#include "SpriteBlur.h"

SpriteBlur::~SpriteBlur()
{
}

SpriteBlur* SpriteBlur::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
#endif
    
    return createWithSpriteFrame(frame);
}

SpriteBlur* SpriteBlur::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    SpriteBlur *sprite = new (std::nothrow) SpriteBlur();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteBlur* SpriteBlur::create(const char *pszFileName)
{
    SpriteBlur* pRet = new SpriteBlur();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool SpriteBlur::initWithTexture(Texture2D* texture, const Rect& rect)
{
    _blurRadius = 0;
    if( Sprite::initWithTexture(texture, rect) ) 
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
                setGLProgram(nullptr);
                initGLProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        auto s = getTexture()->getContentSizeInPixels();

        _pixelSize = Vec2(1/s.width, 1/s.height);

        _samplingRadius = 0;
        this->initGLProgram();

        getGLProgramState()->setUniformVec2("onePixelSize", _pixelSize);

        return true;
    }

    return false;
}

void SpriteBlur::initGLProgram()
{
    GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(
                                FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();  
    auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);

    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    setGLProgramState(glProgramState);
}

void SpriteBlur::setBlurSize(float f)
{
    if(_blurRadius == (int)f)
        return;
    _blurRadius = (int)f;

    _samplingRadius = _blurRadius;
    if (_samplingRadius > 10)
    {
        _samplingRadius = 10;
    }
    if (_blurRadius > 0)
    {
        float sigma = _blurRadius / 2.0f;
        _scale = -0.5f / (sigma * sigma);
        _cons = -1.0f * _scale / 3.141592f;
        _weightSum = -_cons;

        float weight;
        int squareX;
        for(int dx = 0; dx <= _samplingRadius; ++dx)
        {
            squareX = dx * dx;
            weight = _cons * exp(squareX * _scale);
            _weightSum += 2.0 * weight;
            for (int dy = 1; dy <= _samplingRadius; ++dy)
            {
                weight = _cons * exp((squareX + dy * dy) * _scale);
                _weightSum += 4.0 * weight;
            }
        }
    }
    log("_blurRadius:%d",_blurRadius);

    getGLProgramState()->setUniformVec4("gaussianCoefficient", Vec4(_samplingRadius, _scale, _cons, _weightSum));
}
