#pragma once

#include "Screen.h"
#include "Utils.h"
#include "MirrorShader.h"

template<class vt, class sh>
class Mirror : public Screen<vt, sh>
{
	XMFLOAT4 mirrorPlane;
	XMFLOAT4 zeroPlane;
public:
	Mirror(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, int resWidth, int resHeight, float screenWidth, float screenHeight);
	Mirror(Mirror &&other);

	XMVECTOR GetMirrorPlane(){ return XMLoadFloat4(&mirrorPlane); }
	XMVECTOR GetZeroPlane(){ return XMLoadFloat4(&zeroPlane); }
};

typedef Mirror<TextureVertexType, MirrorShader> SimpleMirror;

template<class vt, class sh>
Mirror<vt, sh>::Mirror(XMFLOAT3 screenPos, XMFLOAT3 rot, Model<vt> &screenModel, sh &screenShader, 
	int resWidth, int resHeight, float screenWidth, float screenHeight)
	:Screen(screenPos, rot, screenModel, screenShader, resWidth, resHeight, screenWidth, screenHeight)
{
	mirrorPlane = Utils::PlaneFromPointAndRot(screenPos, rot);
	zeroPlane = Utils::PlaneFromPointAndRot(ZeroVec3, rot);
}

template<class vt, class sh>
Mirror<vt, sh>::Mirror(Mirror &&other) : Screen(move(other)), mirrorPlane(other.mirrorPlane)
{
}