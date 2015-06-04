#include "Bitmap.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

// destructor
BMP::~BMP(){
	if(m_data.pixels != NULL){
		int row = m_dib.getImageHeight();
		for(int i = 0; i < row; i++)
			delete[] m_data.pixels[i];
		delete[] m_data.pixels;
	}
}

void PixelArray::readPixelArray(istream& indev, uint32_t width, uint32_t height, uint32_t PAddress){
	unsigned char paddingCount = (4 - (width * (24 / 8) % 4)) % 4;
	int row = height; // row of pixel Array
	int col = width; // col of pixel Array

	pixels = new RGBColor* [row];

	indev.seekg(PAddress, ios::beg); // di chuyển con trỏ đọc đến vị trí lưu thông tin điểm ảnh

	for(int i = 0; i < row; i++){
		pixels[row - 1 - i] = new RGBColor[col];
		indev.read((char*)pixels[row - i - 1], col * sizeof(RGBColor)); // đọc thông tin về điểm ảnh vào mảng
		if(paddingCount != 0)
			indev.seekg(paddingCount, ios::cur); // bỏ qua vùng padding
	}
}

// đọc ảnh bitmap từ đường dẫn tập tin path
bool BMP::readBMP(const string& path){
	ifstream infile(path, ios::binary);
	if(!infile){
		cout << "BMP file is not found! Please check your path and try again!\n";
		return 0;
	}
	
	infile.read((char*)this, sizeof(BMP));
	m_data.readPixelArray(infile, m_dib.getImageWidth(), m_dib.getImageHeight(), m_head.getPAaddr());
	return 1;
}

void BMP::outBMP(){
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);
	int row = m_dib.getImageHeight();
	int col = m_dib.getImageWidth();

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++){
			Color c = m_data.pixels[i][j].getColor();
			SetPixel(hdc, j + PADDING_LEFT, i, RGB(c.m_red, c.m_green, c.m_blue));
		}
	ReleaseDC(console, hdc);
}

void BMP::writeBMP(const string& path){
	ofstream outfile(path, ios::binary);
	if(!outfile){
		cout << "Can not found path. Please check and try again!\n";
		return;
	}
	outfile.write((char*)&m_head, sizeof(m_head));
	outfile.write((char*)&m_dib, sizeof(m_dib));
	
	// estimate padding
	unsigned char paddingCount = (4 - (m_dib.getImageWidth() * (m_dib.getPixelSize() / 8) % 4)) % 4;
	int row = m_dib.getImageHeight(); // row of pixel Array
	int col = m_dib.getImageWidth(); // col of pixel Array

	// write pixels to outfile
	for(int i = row - 1; i >= 0; i--){
		outfile.write((char*)m_data.pixels[i], col * sizeof(RGBColor));
		if(paddingCount != 0)
			for(int x = 0; x < paddingCount; x++)
				outfile << 0;
	}
}

RGBColor BMP::ReadPixel(int i, int j){
	RGBColor result;
	int row = m_dib.getImageHeight();
	int col = m_dib.getImageWidth();
	if(i >= 0 && i <= row && j >= 0 && j <= col)
		result = m_data.pixels[i][j];
	return result;
}

void BMP::Brightness(int k){
	int row = m_dib.getImageHeight();
	int col = m_dib.getImageWidth();
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			m_data.pixels[i][j] = m_data.pixels[i][j] + k; // thay đổi độ sáng từng pixel
}

void BMP::ProcessBMP(void (*action)(RGBColor &)){
	int row = m_dib.getImageHeight();
	int col = m_dib.getImageWidth();
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			action(m_data.pixels[i][j]);
}

void BMP::crop(Toado TopLeft, Toado BottomRight, const string &path){
	if(TopLeft.x >= BottomRight.x || TopLeft.y >= BottomRight.y)
		return;
	int row = m_dib.getImageHeight();
	int col = m_dib.getImageWidth();
	int newRow = BottomRight.y - TopLeft.y + 1;
	int newCol = BottomRight.x - TopLeft.x + 1;
	BMP newBMP;
	newBMP.m_head = m_head;
	newBMP.m_dib = m_dib;
	newBMP.m_dib.changeHeight(newRow);
	newBMP.m_dib.changeWidth(newCol);
	unsigned char paddingCount = (4 - (newCol * (m_dib.getPixelSize() / 8) % 4)) % 4;
	newBMP.m_dib.changePASize(newRow * (newCol * 3 + paddingCount));
	newBMP.m_head.changeSize(newBMP.m_dib.getDIBSize() + newBMP.m_dib.getPASize());
	newBMP.m_data.pixels = new RGBColor* [newRow];
	int r, c;
	r = c = 0;
	for(int i = TopLeft.y; i <= BottomRight.y; i++){
		newBMP.m_data.pixels[r] = new RGBColor[newCol];
		for(int j = TopLeft.x; j <= BottomRight.x; j++)
			newBMP.m_data.pixels[r][c++] = m_data.pixels[i][j];
		c = 0;
		r++;
	}
	newBMP.writeBMP(path);
}

void copyBMP(const string& inpath, const string outpath){
	string outfile = outpath;
	if(outpath == ""){ // không truyền outpath vào
		outfile = inpath;
		int i;
		for(i = outfile.length() - 1; i >= 0; i--){
			if(outfile[i] == '\\')
				break;
		}
		outfile.insert(i + 1, "Copy of ");
	}
	BMP temp;
	temp.readBMP(inpath);
	temp.writeBMP(outfile);
}