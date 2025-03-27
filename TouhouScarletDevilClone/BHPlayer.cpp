#include "BHPlayer.h"
#include "config.h"
#include "BHEnemy.h"
#include "BHBullet.h"

void BHPlayer::Move(FPOINT moveDirection, bool isPressingShift)
{
    float angle = atan2(moveDirection.x , moveDirection.y);
    
    //TODO: SetSpeed;
    position.x += sin(angle) * isPressingShift ? 1.f : 2.f;
    position.y += cos(angle) * isPressingShift ? 1.f : 2.f;

}

void BHPlayer::Update()
{
    //TODO: Determine move direction
    //TODO: sqrt(,2) when (1,1)-like-directional movement
#pragma region WASD_INPUT
    FPOINT moveDir = { 0,0 };
    // W
    if (KeyManager::GetInstance()->IsStayKeyDown(0x57))
    {
        moveDir.y-=1;
    }
    // A
    if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
    {
        moveDir.x -= 1;
    }
    // S
    if (KeyManager::GetInstance()->IsStayKeyDown(0x53))
    {
        moveDir.y+=1;
    }
    // D
    if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
    {
        moveDir.x += 1;
    }
#pragma endregion
	//TODO: Case of shift press - slow and attack2
    bool isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);

    //TODO: Update position
    Move(moveDir, isPressingShift);
   
	//TODO: Move back when go out screen
    MoveBackToBorder();


}


void BHPlayer::MoveBackToBorder() {

}

void BHPlayer::OnCollide(BHObject* objectCollided)
{	
    //TODO: Check collision
    //TODO: if collides with enemy or enemy bullet, than:
    //TODO:  alive false
    //TODO:  do something such as invincible...
    BHEnemy* enemy = static_cast<BHEnemy*>(objectCollided);
    if (enemy) {

        return;
    }
    BHBullet* bullet = static_cast<BHBullet*>(objectCollided);
    if (bullet) {
        //...

        return;
    }
}
