#include "Photo.h"

BMP* loadImage(){
	cout << "Enter image's name or path name: ";
	string path;
	cin >> path;

	BMP* a = new BMP;
	bool isExist = a->readBMP(path);
	if(isExist){
		a->outBMP();
		return a;
	}
	return NULL;
}

void showInformation(BMP& a){
	cout << "Information of bitmap:" << endl;
	a.outInf();
	cout << endl;
}

void changeBrightness(BMP* &a){
	cout << "Change brightness:" << endl;
	cout << "Enter k > 0 if you want your image brighter, k < 0 if you want it darker!" << endl;
	int k;
	cout << "Enter k: "; cin >> k;
	a->Brightness(k);
	a->outBMP();
}

void copyImage(){
	cout << "Enter the source link: ";
	string inPath;
	getline(cin, inPath);
	cout << "Enter the destination: " << endl;
	cout << "If you want to put your new Image to the same place as the source file, just Press Enter!";
	string outPath;
	getline(cin, outPath);
	copyBMP(inPath, outPath);
}

void cropImage(BMP* a){
	int type;
	Toado TopLeft;
	cout << "Enter the co-ordinate (x, y) of the Top-Left point: ";
	cin >> TopLeft.x >> TopLeft.y;
	Toado BottomRight;
	cout << "Enter the co-ordinate (x, y) of the Bottom-Right point: ";
	cin >> BottomRight.x >> BottomRight.y;
	cout << "Where do you want to put new Image?\n";
	cout << "Enter dest path: ";
	string path;
	cin >> path;
	a->crop(TopLeft, BottomRight, path);
}

void showInstruction(){
	cout << "(1): Change Brightness." << endl;
	cout << "(2): Copy Image." <<  endl;
	cout << "(3): Show Image." << endl;
	cout << "(4): Crop Image." << endl;
	cout << "(5): Print Information of bitmap." << endl;
	cout << "(6): Show Instruction." << endl;
	cout << "(0): Exit!" << endl;
}

int CmdListener(){
	cout << "Enter your choice: ";
	int type;
	cin >> type;
	return type;
}

void Command(BMP* &a){
	int type;
	while(true){
		type = CmdListener();
		system("cls");
		switch(type){
		case 1: changeBrightness(a); break;
		case 2: copyImage(); break;
		case 3: a->outBMP(); break;
		case 4: cropImage(a); break;
		case 5: a->outInf(); break;
		case 6: showInstruction(); break;
		default: return;
		}
	}
}