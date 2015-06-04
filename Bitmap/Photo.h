#ifndef _PHOTO_H
#define _PHOTO_H
#include "Bitmap.h"

BMP* loadImage();

void showInstruction();
int CmdListener();
void Command(BMP* &a);

#endif