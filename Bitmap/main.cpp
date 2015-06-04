#include "Photo.h"
#include <iostream>
using namespace std;

void turnBlack(RGBColor &p){
	p = p + 40;
}

int main(){
	BMP* a = loadImage();
	if(a == NULL) return 0;
	showInstruction();
	Command(a);
	delete a;
}