#include "BHObject.h"
#include "Image.h"

void BHObject::Init(SHAPE* shape, FPOINT position, float angle)
{
	this->Shape = shape;
	this->position = position;
	this->radianAngleDirection = angle;
	scale = 1;
	imgAlpha = 1;
	isAlive = true;
	
}

void BHObject::RenderSub(HDC hdc, Image* image, float size, float fade) {
	if (image) {
		image->FrameRender(hdc, position.x, position.y, size, size, 1);
	}

}

//void BHObject::RenderSub(CTexture* texture, float size, float fade)
//{
//	if (texture) {
//		float 
//			sw=Graphics->GetHeight()*MaxX/MaxY*0.5f,
//			sh=Graphics->GetHeight()/MaxY*0.5f,
//			c=cosf(D3DX_PI*2*Angle),
//			s=sinf(D3DX_PI*2*Angle),
//			dx=size*Scale*sw,
//			dx0=c*dx,
//			dx1=s*dx,
//			dy=size*Scale*sh,
//			dy0=-s*dy,
//			dy1=c*dy,
//			x=(X+1)*sw,
//			y=(Y+1)*sh;
//		D3DCOLOR color=D3DXCOLOR(1, 1, 1, Alpha*fade);
//		texture->Draw(
//			x-dx0-dy0, y-dx1-dy1, color, 0, 0,
//			x+dx0-dy0, y+dx1-dy1, color, 1, 0,
//			x-dx0+dy0, y-dx1+dy1, color, 0, 1,
//			x+dx0+dy0, y+dx1+dy1, color, 1, 1
//		);
//	}
//}


void BHObject::Render(HDC hdc)
{
	RenderSub(hdc, Shape->Texture[0], Shape->Size, 1.f);
	/*int i= ShowColor ?1:0;
	if (ShowHit) {
		RenderSub(Shape->Texture[i], Shape->Size, 0.25f);
		RenderSub(ShapeList[ShHit].Texture[i], Shape->Hit, 1);
	} else {
		RenderSub(Shape->Texture[i], Shape->Size, 1);
		if (ShowColor) {
			LPDIRECT3DDEVICE9 device=Graphics->GetDevice();
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			RenderSub(Shape->Texture[i], Shape->Size*1.1f, 0.3f);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}*/
}

bool BHObject::IsHit(BHObject* bhObject)
{
	//TODO: commonfunction.h GetDistance, compare with (r1+r2) * (r1+r2)
	float dx = bhObject->position.x - position.x, dy = bhObject->position.y - position.y, hit = bhObject->Shape->Hit + Shape->Hit;
	return dx * dx - +dy * dy < hit * hit;
}