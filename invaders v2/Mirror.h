#pragma once

#include "Screen.h"
#include "Utils.h"
#include "MirrorShader.h"

template<class vt, class sh>
class Mirror : public Screen<vt, sh>
{
	D3DXPLANE mirrorPlane;
	D3DXPLANE zeroPlane;
public:
	Mirror(D3DXVECTOR3 screenPos, D3DXVECTOR3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Mirror(Mirror &&other);

	D3DXPLANE &GetMirrorPlane(){ return mirrorPlane; }
	D3DXPLANE &GetZeroPlane(){ return zeroPlane; }
};

typedef Mirror<TextureVertexType, MirrorShader> SimpleMirror;

template<class vt, class sh>
Mirror<vt, sh>::Mirror(D3DXVECTOR3 screenPos, D3DXVECTOR3 rot, Model<vt> &screenModel, sh &screenShader, 
	int resWidth, int resHeight, float screenWidth, float screenHeight)
	:Screen(screenPos, rot, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight)
{
	mirrorPlane = Utils::PlaneFromPointAndRot(screenPos, rot);
	zeroPlane = Utils::PlaneFromPointAndRot(DefVec3, rot);
}

template<class vt, class sh>
Mirror<vt, sh>::Mirror(Mirror &&other) : Screen(move(other)), mirrorPlane(other.mirrorPlane)
{
}