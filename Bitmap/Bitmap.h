#ifndef _BITMAP_H
#define _BITMAP_H
#include "RGB.h"
#include <string>
#include <iostream>
using namespace std;

#define PADDING_LEFT 350

#pragma pack (1)
struct bmpsign{
	unsigned char data[2];
};

#pragma pack (1)
class Header{
	bmpsign signature;
	int32_t size;
	int16_t reserved1;
	int16_t reserved2;
	int32_t PAaddr;
public:
	void outHeader(){
		cout << "Size of file: " << size << endl;
	}
	int32_t getPAaddr(){ return PAaddr; }
	void changeSize(uint32_t newsize){
		size = newsize;
	}
};

#pragma pack (1)
class DIB{
	uint32_t dibsize;
	int32_t ImageWidth;
	int32_t ImageHeight;
	uint16_t colorPlane;
	uint16_t pixelSize;
	uint32_t compress;
	uint32_t PASize;
	int32_t NgangPG;
	int32_t DocPG;
	uint32_t ColorCount;
	uint32_t MainColorCount;
public:
	void outDIB(){
		cout << "Width: " << ImageWidth << " Height: " << endl;
		cout << "Number of bits per pixel: " << pixelSize << endl;
		cout << "Horizontal resolution " << NgangPG << endl;
		cout << "Vertical resolution " << DocPG << endl;
	}
	uint32_t getImageWidth(){ return ImageWidth; }
	uint32_t getImageHeight(){ return ImageHeight; }
	uint16_t getPixelSize(){ return pixelSize; }
	int32_t getDIBSize(){ return dibsize; }
	uint32_t getPASize(){ return PASize; }
	void changeWidth(uint32_t width){
		ImageWidth = width;
	}
	void changeHeight(uint32_t height){
		ImageHeight = height;
	}
	void changePASize(uint32_t size){
		PASize = size;
	}
};

struct PixelArray{
	RGBColor** pixels;
public:
	void readPixelArray(istream& indev, uint32_t width, uint32_t height, uint32_t PAddress);
};

struct Toado{
	int x, y;
	Toado(): x(0), y(0) {};
	Toado(int x, int y): x(x), y(y) {};
};

class BMP{
	Header m_head;
	DIB m_dib;
	PixelArray m_data;
	void ReadPixelArray(istream& indev);
public:
	// constructor
	BMP(){
		m_data.pixels = NULL;
	}

	// destructor
	~BMP();
	bool readBMP(const string& path); // đọc ảnh bitmap từ đường dẫn tập tin.
	void outBMP(); // xuất ảnh bitmap ra màn hình console.
	void writeBMP(const string& path); // ghi ảnh bitmap với đường dẫn path.
	
	/* in ra thông tin của ảnh */
	void outInf(){
		system("cls");
		m_head.outHeader();
		m_dib.outDIB();
	}

	/* tạo ảnh mới bằng cách cắt một khung ảnh
	*	Khung ảnh được giới hạn bởi tọa độ của góc trái trên và phải dưới
		với gốc (0, 0) nằm ở góc trái trên của ảnh gốc, trục x hướng sang phải, trục y hướng xuống dưới.
	*/
	void crop(Toado trai_tren, Toado phai_duoi, const string &path);

	RGBColor ReadPixel(int i, int j); // đọc màu của 1 điểm ảnh có tọa độ i, j
	
	void Brightness(int k); // tăng độ sáng 1 mức so với mức cũ là k (k dương sáng hơn, k âm tối đi).

	void ProcessBMP(void (*action)(RGBColor &)); // xử lý tất cả điểm ảnh cùng lúc với hàm xử lý được truyền từ ngoài vào
};

void copyBMP(const string& inpath, const string outpath = ""); // copy ảnh bitmap từ inpath đến outpath, nếu không truyền outpath thì copy cùng chỗ.

#endif