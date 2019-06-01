#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct BmpFileHeader {
	uint16_t fileType{0x4D42};          // File type always BM which is 0x4D42
	uint32_t fileSize{0};               // Size of the file (in bytes)
	uint16_t reserved1{0};               // Reserved, always 0
	uint16_t reserved2{0};               // Reserved, always 0
	uint32_t offsetData{0};             // Start position of pixel data (bytes from the beginning of the file)
};

struct BmpInfoHeader {
	uint32_t size{ 0 };                      // Size of this header (in bytes)
	int32_t width{ 0 };                      // width of bitmap in pixels
	int32_t height{ 0 };                     // width of bitmap in pixels
	//       (if positive, bottom-up, with origin in lower left corner)
	//       (if negative, top-down, with origin in upper left corner)
	uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
	uint16_t bitCount{ 0 };                 // No. of bits per pixel
	uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED Bmp images
	uint32_t sizeImage{ 0 };                // 0 - for uncompressed images
	int32_t xPixelsPerMeter{ 0 };
	int32_t yPixelsPerMeter{ 0 };
	uint32_t colorsUsed{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bitCount
	uint32_t colorsImportant{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct BmpColorHeader {
	uint32_t redMask{ 0x00ff0000 };         // Bit mask for the red channel
	uint32_t greenMask{ 0x0000ff00 };       // Bit mask for the green channel
	uint32_t blueMask{ 0x000000ff };        // Bit mask for the blue channel
	uint32_t alphaMask{ 0xff000000 };       // Bit mask for the alpha channel
	uint32_t colorSpaceRype{ 0x73524742 }; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};

class Bmp {
private:
	BmpFileHeader fileHeader;
	BmpInfoHeader bmpInfoHeader;
	BmpColorHeader bmpColorHeader;
	std::vector<uint8_t> data;
	uint32_t rowStride{ 0 };

	uint32_t makeStrideAligned(uint32_t alignStride);

	void writeHeaders(std::ofstream& of);
	void writeHeadersAndData(std::ofstream& of);
public:
	Bmp(size_t height, size_t width);

	void write(std::string const& fileName);

	void writePixel(uint32_t width, uint32_t height, uint32_t R, uint32_t G, uint32_t B);
};

