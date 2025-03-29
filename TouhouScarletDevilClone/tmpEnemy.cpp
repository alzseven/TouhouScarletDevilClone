#include "tmpEnemy.h"

tmpEnemy::tmpEnemy()
{
	image = ImageManager::GetInstance()->AddImage("enemy", TEXT("Image/enemy1.png"), 4, 1);

}

void tmpEnemy::Init(FPOINT pos)
{
	this->pos;

}

void tmpEnemy::Update()
{
}

void tmpEnemy::Render()
{
}

void tmpEnemy::Release()
{
}
