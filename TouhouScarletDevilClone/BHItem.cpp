//#include "BHItem.h"
//#include "D2DImage.h"
//#include "Shape.h"
//#include "GameState.h"
//#include "GameStateManager.h"
//
//void BHItem::Init(string shapeKey, FPOINT pos)
//{
//	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
//	if (shape) {
//		this->hitRadius = shape->GetHitWidth() / 2;
//	}
//	this->position = pos;
//	this->isAlive = true;
//
//
//	point = 49200;
//	isItemGet = false;
//	speedY = -400.0f;
//	gravity = 400.0f;
//
//	SetCollisionLayer(LAYER_ITEM, LAYER_PLAYER);
//}
//
//void BHItem::InitGameState(GameState* state)
//{
//	gameState = state;
//}
//
//void BHItem::Update(float dt)
//{
//	Move(dt);
//}
//
//void BHItem::Render(HDC hdc)
//{
//	if (!isAlive) return;
//	if (shape && shape->GetImage())
//		shape->GetImage()->Render(position.x, position.y);
//}
//
//void BHItem::OnHit(ICollideable* hitObject)
//{
//	if (hitObject->GetLayer() == LAYER_PLAYER)
//	{
//		isItemGet = true;
//		isAlive = false;
//
//		if (gameState)
//			Score(gameState) += point;
//
//	}
//}
//
//void BHItem::Move(float dt)
//{
//	if (isGoingUpItem)
//	{
//		speedY += gravity * dt;
//		position.y += speedY * dt;
//		if (speedY >= 0.0f)
//		{
//			isGoingUpItem = false;
//			gravity = 0.0f;
//		}
//	}
//	else
//	{
//		position.y += 130.0f * dt;
//	}
//	if (position.y > WINSIZE_Y)
//		isItemGet = false;
//}
//
//void BHItem::Move(float angle, float speed, float dt)
//{
//}
//
//void BHItem::Shoot(string shapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
//{
//}
//
//void BHItem::Release()
//{
//}
