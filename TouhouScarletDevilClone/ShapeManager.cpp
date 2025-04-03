#include "ShapeManager.h"
#include "Shape.h"
#include "D2DImage.h"

void ShapeManager::Init()
{
    ShapeManager::GetInstance()->AddShapeCircle("Error", TEXT("Image/MissingNo.png"), 0.0f);

    D2DImage* image = nullptr;
    image = ImageManager::GetInstance()->AddImage("enemy", TEXT("Image/enemy1.png"), 4, 1);
    ShapeManager::GetInstance()->AddShapeCharacter("enemy", image, 3.0f);

    D2DImage* marisaImg = ImageManager::GetInstance()->AddImage("Marisa", TEXT("Image/Marisa_Move_Vertical.bmp"), 4, 1); 
    ShapeManager::GetInstance()->AddShapeCharacter("Marisa", marisaImg, 3.0f);

    ShapeManager::GetInstance()->AddShapeCircle("marisa_bullet", TEXT("Image/kunai.png"), 3.0f);

    ShapeManager::GetInstance()->AddShapeCircle("kunai", TEXT("Image/kunai.png"), 3.0f);
    ShapeManager::GetInstance()->AddShapeCircle("ball_green", TEXT("Image/ball_green.png"), 5.0f);

    //NormalBullet
    {
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_blue", TEXT("Image/Bullet/NormalBullet/NormalBullet_blue.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_blueb", TEXT("Image/Bullet/NormalBullet/NormalBullet_blueb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_gray", TEXT("Image/Bullet/NormalBullet/NormalBullet_gray.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_grayb", TEXT("Image/Bullet/NormalBullet/NormalBullet_grayb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_green", TEXT("Image/Bullet/NormalBullet/NormalBullet_green.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_greenb", TEXT("Image/Bullet/NormalBullet/NormalBullet_greenb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_lime", TEXT("Image/Bullet/NormalBullet/NormalBullet_lime.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_orange", TEXT("Image/Bullet/NormalBullet/NormalBullet_orange.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_purple", TEXT("Image/Bullet/NormalBullet/NormalBullet_purple.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_purpleb", TEXT("Image/Bullet/NormalBullet/NormalBullet_purpleb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_red", TEXT("Image/Bullet/NormalBullet/NormalBullet_red.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_redb", TEXT("Image/Bullet/NormalBullet/NormalBullet_redb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_sky", TEXT("Image/Bullet/NormalBullet/NormalBullet_sky.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_skyb", TEXT("Image/Bullet/NormalBullet/NormalBullet_skyb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_white", TEXT("Image/Bullet/NormalBullet/NormalBullet_white.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_yellow", TEXT("Image/Bullet/NormalBullet/NormalBullet_yellow.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("NormalBullet_yellowb", TEXT("Image/Bullet/NormalBullet/NormalBullet_yellowb.png"), 5.0f);
    }
    //MiddleBullet
    {
        // MiddleBlankBullet
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBlankBullet_black", TEXT("Image/Bullet/MiddleBullet/MiddleBlankBullet_black.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBlankBullet_blue", TEXT("Image/Bullet/MiddleBullet/MiddleBlankBullet_blue.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBlankBullet_green", TEXT("Image/Bullet/MiddleBullet/MiddleBlankBullet_green.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBlankBullet_red", TEXT("Image/Bullet/MiddleBullet/MiddleBlankBullet_red.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBlankBullet_yellow", TEXT("Image/Bullet/MiddleBullet/MiddleBlankBullet_yellow.png"), 4.0f);

        // MiddleBullet
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBullet_black", TEXT("Image/Bullet/MiddleBullet/MiddleBullet_black.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBullet_blue", TEXT("Image/Bullet/MiddleBullet/MiddleBullet_blue.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBullet_green", TEXT("Image/Bullet/MiddleBullet/MiddleBullet_green.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBullet_red", TEXT("Image/Bullet/MiddleBullet/MiddleBullet_red.png"), 4.0f);
        ShapeManager::GetInstance()->AddShapeCircle("MiddleBullet_yellow", TEXT("Image/Bullet/MiddleBullet/MiddleBullet_yellow.png"), 4.0f);

    }
    //SmallBullet
    {
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_black", TEXT("Image/Bullet/SmallBullet/SmallBullet_black.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_blueb", TEXT("Image/Bullet/SmallBullet/SmallBullet_blueb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_greenb", TEXT("Image/Bullet/SmallBullet/SmallBullet_greenb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_lime", TEXT("Image/Bullet/SmallBullet/SmallBullet_lime.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_orange", TEXT("Image/Bullet/SmallBullet/SmallBullet_orange.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_purple", TEXT("Image/Bullet/SmallBullet/SmallBullet_purple.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_purpleb", TEXT("Image/Bullet/SmallBullet/SmallBullet_purpleb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_red", TEXT("Image/Bullet/SmallBullet/SmallBullet_red.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_redb", TEXT("Image/Bullet/SmallBullet/SmallBullet_redb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_sky", TEXT("Image/Bullet/SmallBullet/SmallBullet_sky.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_skyb", TEXT("Image/Bullet/SmallBullet/SmallBullet_skyb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_white", TEXT("Image/Bullet/SmallBullet/SmallBullet_white.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_yellow", TEXT("Image/Bullet/SmallBullet/SmallBullet_yellow.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("SmallBullet_yellowb", TEXT("Image/Bullet/SmallBullet/SmallBullet_yellowb.png"), 3.0f);

    }
    //LineBullet
    {
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_blue", TEXT("Image/Bullet/LineBullet/LineBullet_blue.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_blueb", TEXT("Image/Bullet/LineBullet/LineBullet_blueb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_gray", TEXT("Image/Bullet/LineBullet/LineBullet_gray.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_greenb", TEXT("Image/Bullet/LineBullet/LineBullet_greenb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_lime", TEXT("Image/Bullet/LineBullet/LineBullet_lime.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_orange", TEXT("Image/Bullet/LineBullet/LineBullet_orange.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_purple", TEXT("Image/Bullet/LineBullet/LineBullet_purple.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_purpleb", TEXT("Image/Bullet/LineBullet/LineBullet_purpleb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_red", TEXT("Image/Bullet/LineBullet/LineBullet_red.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_redb", TEXT("Image/Bullet/LineBullet/LineBullet_redb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_sky", TEXT("Image/Bullet/LineBullet/LineBullet_sky.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_skyb", TEXT("Image/Bullet/LineBullet/LineBullet_skyb.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_white", TEXT("Image/Bullet/LineBullet/LineBullet_white.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_yellow", TEXT("Image/Bullet/LineBullet/LineBullet_yellow.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("LineBullet_yellowb", TEXT("Image/Bullet/LineBullet/LineBullet_yellowb.png"), 5.0f);
    }
    //Kunai
    {
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_blue", TEXT("Image/Bullet/Kunai/Kunai_blue.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_blueb", TEXT("Image/Bullet/Kunai/Kunai_blueb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_gray", TEXT("Image/Bullet/Kunai/Kunai_gray.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_green", TEXT("Image/Bullet/Kunai/Kunai_green.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_lime", TEXT("Image/Bullet/Kunai/Kunai_lime.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_orange", TEXT("Image/Bullet/Kunai/Kunai_orange.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_purple", TEXT("Image/Bullet/Kunai/Kunai_purple.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_purpleb", TEXT("Image/Bullet/Kunai/Kunai_purpleb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_red", TEXT("Image/Bullet/Kunai/Kunai_red.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_redb", TEXT("Image/Bullet/Kunai/Kunai_redb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_skyb", TEXT("Image/Bullet/Kunai/Kunai_skyb.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_white", TEXT("Image/Bullet/Kunai/Kunai_white.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_yellow", TEXT("Image/Bullet/Kunai/Kunai_yellow.png"), 3.0f);
        ShapeManager::GetInstance()->AddShapeCircle("Kunai_yellowb", TEXT("Image/Bullet/Kunai/Kunai_yellowb.png"), 3.0f);
    }
    //Sword
    {
        ShapeManager::GetInstance()->AddShapeCircle("Sword_blue", TEXT("Image/Bullet/Sword/Sword_blue.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_gray", TEXT("Image/Bullet/Sword/Sword_gray.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_green", TEXT("Image/Bullet/Sword/Sword_green.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_purple", TEXT("Image/Bullet/Sword/Sword_purple.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_red", TEXT("Image/Bullet/Sword/Sword_red.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_sky", TEXT("Image/Bullet/Sword/Sword_sky.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_white", TEXT("Image/Bullet/Sword/Sword_white.png"), 5.5f);
        ShapeManager::GetInstance()->AddShapeCircle("Sword_yellow", TEXT("Image/Bullet/Sword/Sword_yellow.png"), 5.5f);

    }
    //Jewel
    {
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_blue", TEXT("Image/Bullet/Jewel/Jewel_blue.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_blueb", TEXT("Image/Bullet/Jewel/Jewel_blueb.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_gray", TEXT("Image/Bullet/Jewel/Jewel_gray.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_green", TEXT("Image/Bullet/Jewel/Jewel_green.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_greenb", TEXT("Image/Bullet/Jewel/Jewel_greenb.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_lime", TEXT("Image/Bullet/Jewel/Jewel_lime.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_orange", TEXT("Image/Bullet/Jewel/Jewel_orange.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_purple", TEXT("Image/Bullet/Jewel/Jewel_purple.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_purpleb", TEXT("Image/Bullet/Jewel/Jewel_purpleb.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_redb", TEXT("Image/Bullet/Jewel/Jewel_redb.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_sky", TEXT("Image/Bullet/Jewel/Jewel_sky.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_skyb", TEXT("Image/Bullet/Jewel/Jewel_skyb.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_white", TEXT("Image/Bullet/Jewel/Jewel_white.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_yellow", TEXT("Image/Bullet/Jewel/Jewel_yellow.png"), 3.8f);
        ShapeManager::GetInstance()->AddShapeCircle("Jewel_yellowb", TEXT("Image/Bullet/Jewel/Jewel_yellowb.png"), 3.8f);

    }
    //Energy
    {
        ShapeManager::GetInstance()->AddShapeCircle("Energy_blue", TEXT("Image/Bullet/Energy/Energy_blue.png"), 18.f);
        ShapeManager::GetInstance()->AddShapeCircle("Energy_green", TEXT("Image/Bullet/Energy/Energy_green.png"), 18.f);
        ShapeManager::GetInstance()->AddShapeCircle("Energy_red", TEXT("Image/Bullet/Energy/Energy_red.png"), 18.f);
        ShapeManager::GetInstance()->AddShapeCircle("Energy_yellow", TEXT("Image/Bullet/Energy/Energy_yellow.png"), 18.f);
    }
    //EllipseBullet
    {
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_blue", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_blue.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_gray", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_gray.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_green", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_green.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_greenb", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_greenb.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_lime", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_lime.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_orange", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_orange.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_purple", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_purple.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_purpleb", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_purpleb.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_red", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_red.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_redb", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_redb.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_skyb", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_skyb.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_white", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_white.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_yellow", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_yellow.png"), 3.4f);
        ShapeManager::GetInstance()->AddShapeCircle("EllipseBullet_yellowb", TEXT("Image/Bullet/EllipseBullet/EllipseBullet_yellowb.png"), 3.4f);

    }
    //BigFadeBullet
    {
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_blue", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_blue.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_gray", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_gray.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_green", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_green.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_purple", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_purple.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_red", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_red.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_sky", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_sky.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_white", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_white.png"), 11.0f);
        ShapeManager::GetInstance()->AddShapeCircle("BigFadeBullet_yellow", TEXT("Image/Bullet/BigFadeBullet/BigFadeBullet_yellow.png"), 11.0f);

    }
    //marisa
    {
        image = ImageManager::GetInstance()->AddImage("marisa_goleft", TEXT("Image/Character/Marisa/marisa_goleft.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("marisa_goleft", image, 10.0f);
        image = ImageManager::GetInstance()->AddImage("marisa_idle", TEXT("Image/Character/Marisa/marisa_idle.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("marisa_idle", image, 10.0f);
        image = ImageManager::GetInstance()->AddImage("marisa_left", TEXT("Image/Character/Marisa/marisa_left.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("marisa_left", image, 10.0f);
        ShapeManager::GetInstance()->AddShapeCircle("marisa_sub", TEXT("Image/Character/Marisa/marisa_sub.png"), 5.0f);
    }
    //cirno
    {
        ShapeManager::GetInstance()->AddShapeCircle("cirno_idle", TEXT("Image/Character/Cirno/cirno_idle.png"), 5.0f);
        ShapeManager::GetInstance()->AddShapeCircle("cirno_left", TEXT("Image/Character/Cirno/cirno_left.png"), 5.0f);
    }
    //sakuya
    {
        image = ImageManager::GetInstance()->AddImage("sakuya_idle", TEXT("Image/Character/Sakuya/sakuya_idle.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("sakuya_idle", image, 10.0f);
        image = ImageManager::GetInstance()->AddImage("sakuya_rightmove", TEXT("Image/Character/Sakuya/sakuya_rightmove.png"), 3, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("sakuya_rightmove", image, 10.0f);
        ShapeManager::GetInstance()->AddShapeCircle("sakuya_right", TEXT("Image/Character/Sakuya/sakuya_right.png"), 10.0f);
    }
    //enemy(normal)
    {
        image = ImageManager::GetInstance()->AddImage("fairy_white", TEXT("Image/Character/Enemy/fairy_white.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("fairy_white", image, 10.0f);

        image = ImageManager::GetInstance()->AddImage("zako_pink", TEXT("Image/Character/Enemy/zako_pink.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("zako_pink", image, 10.0f);

        image = ImageManager::GetInstance()->AddImage("zako_blue", TEXT("Image/Character/Enemy/zako_blue.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("zako_blue", image, 10.0f);

        image = ImageManager::GetInstance()->AddImage("zako_red", TEXT("Image/Character/Enemy/zako_red.png"), 4, 1);
        ShapeManager::GetInstance()->AddShapeCharacter("zako_red", image, 10.0f);
    }
    //
}

void ShapeManager::Release()
{
    for (map<string, Shape*>::iterator iter = mapShapes.begin(); iter != mapShapes.end(); ++iter)
    {
        if (iter->second)
        {
            delete (iter->second);
            (iter->second) = nullptr;
        }
    }
    mapShapes.clear();
    ReleaseInstance();
}

Shape* ShapeManager::AddShapeCharacter(string key, D2DImage* image, float radius)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeCircle(string key, const wchar_t* filePath, float radius)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeRect(string key, const wchar_t* filePath, float scaleX, float scaleY, float width, float height)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeRect(image, scaleX, scaleY, width, height);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

void ShapeManager::DeleteShape(string key)
{
    map<string, Shape*>::iterator iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return;

    delete (iter->second);
    (iter->second) = nullptr;

    mapShapes.erase(iter);
}

Shape* ShapeManager::FindShapeAdd(string key)
{
    map<string, Shape*>::iterator iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return nullptr;

    return iter->second;
}

Shape* ShapeManager::FindShape(string key)
{
    map<string, Shape*>::iterator iter;
    iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return mapShapes["Error"];

    return iter->second;
}