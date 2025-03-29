#include "IBulletFactory.h"

#include "BHBullet.h"
#include "Image.h"

void IBulletFactory::AddBullet(std::vector<BHBullet*>* vecBullets, FPOINT pos, float radianAngle)
{
    pair<BHBullet*, int> bullets = CreateBullet(pos, radianAngle);
    // int size = sizeof(bullets) / sizeof(*bullets);
    for (int i=0; i < bullets.second; ++i)
    {
        vecBullets->push_back(&bullets.first[i]);
    }
    

    //TODO:
    // vecBullets->back()->Init(image,hit, pos, radianAngle);
}

pair<BHBullet*, int> MarisaSubWeaponBulletFactory::CreateBullet(FPOINT pos, float radianAngle)
{
    Image* image = new Image();
    if (FAILED(image->Init(TEXT("Image/Marisa_Lazer.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Image/Marisa_Lazer.bmp 생성 실패"), TEXT("경고"), MB_OK);
    }
    BHBullet* bullet =  new BHBullet();
    bullet->Init(image, 32.f, {pos.x, pos.y}, radianAngle, 0 , 0 ,0.1f);
    return {new BHBullet[]{*bullet}, 1};
}

pair<BHBullet*, int> MarisaLevel1BulletFactory::CreateBullet(FPOINT pos, float radianAngle)
{
    Image* image = new Image();
    if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
    }
    BHBullet* bullet =  new BHBullet();
    bullet->Init(image, 32.f, pos, radianAngle, 0 , 0 ,0.1f);
    return {new BHBullet[]{*bullet}, 1};
}

pair<BHBullet*, int> MarisaLevel2BulletFactory::CreateBullet(FPOINT pos, float radianAngle)
{
    Image* image = new Image();
    if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
    }
    BHBullet* bullet1 =  new BHBullet();
    bullet1->Init(image, 32.f, {pos.x + 15, pos.y + 15}, radianAngle + DEG_TO_RAD(15), 0 , 0 ,1.f);
    BHBullet* bullet2 =  new BHBullet();
    bullet2->Init(image, 32.f, {pos.x + 5, pos.y - 15}, radianAngle + DEG_TO_RAD(5), 0 , 0 ,1.f);
    BHBullet* bullet3 =  new BHBullet();
    bullet3->Init(image, 32.f, {pos.x - 5, pos.y - 15}, radianAngle - DEG_TO_RAD(5), 0 , 0 ,1.f);
    BHBullet* bullet4 =  new BHBullet();
    bullet4->Init(image, 32.f, {pos.x - 15, pos.y + 15}, radianAngle - DEG_TO_RAD(15), 0 , 0 ,1.f);
    return {new BHBullet[]{*bullet1, *bullet2, *bullet3, *bullet4} , 4};
}

// pair<BHBullet*, int> MarisaLevel3BulletFactory::CreateBullet(FPOINT pos, float radianAngle)
// {
//     Image* image = new Image();
//     if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
//     {
//         MessageBox(g_hWnd,
//             TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
//     }
//     BHBullet* bullet =  new BHBullet();
//     bullet->Init(image, 32.f, pos, radianAngle, 0 , 0 ,1.f);
//     return bullet;
// }
//
// pair<BHBullet*, int> MarisaLevel4BulletFactory::CreateBullet(FPOINT pos, float radianAngle)
// {
//     Image* image = new Image();
//     if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
//     {
//         MessageBox(g_hWnd,
//             TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
//     }
//     BHBullet* bullet =  new BHBullet();
//     bullet->Init(image, 32.f, pos, radianAngle, 0 , 0 ,1.f);
//     return bullet;
// }


