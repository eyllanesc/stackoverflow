#include "csprite2d.h"

CSprite2D::CSprite2D()
{
    //puts the sprite onto the openGl Panel
}

CSprite2D::~CSprite2D() {
    //removes the sprite off the panel
}

void CSprite2D::compile() {
    //puts the (translated) picture and the position/tilting info into the output which gets interpreted
}

void CSprite2D::setPos(int posX, int posY) {
    Q_UNUSED(posX)
    Q_UNUSED(posY)
    //sets the position on the openGl Panel (using the this-pointer)
}

int CSprite2D::getPosX () {
	return 0;
   //returns the position of the sprite on the X-Axis (using the this-pointer)
}

int CSprite2D::getPosY () {
	return 0;
    //returns the position of the sprite on the Y-Axis (this-pointer)
}
