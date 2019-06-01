#include "Bmp.hpp"

#include <stdexcept>
#include <ios>
#include <fstream>

Bmp::Bmp(size_t height, size_t width) {
	if (height <= 0 || width <= 0) {
		throw std::runtime_error("Height and width must be positive");
	}

	this->bmpInfoHeader.height = height;
	this->bmpInfoHeader.width = width;
	this->bmpInfoHeader.size = sizeof(BmpInfoHeader);
	this->fileHeader.offsetData = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader);

	this->bmpInfoHeader.bitCount = 24;
	this->bmpInfoHeader.compression = 0;
	this->rowStride = width * 3;
	this->data.resize(this->rowStride * height);

	uint32_t const newStride = this->makeStrideAligned(4);
	this->fileHeader.fileSize = this->fileHeader.offsetData + this->data.size() +
		this->bmpInfoHeader.height * (newStride - this->rowStride);
}

uint32_t Bmp::makeStrideAligned(uint32_t alignStride) {
	uint32_t newStride = this->rowStride;
	while (newStride % alignStride != 0) {
		++newStride;
	}
	return newStride;
}

void Bmp::write(std::string const& fileName) {
	std::ofstream of { fileName.c_str(), std::ios_base::binary };

	if (of) {
		if (this->bmpInfoHeader.bitCount == 32) {
			this->writeHeadersAndData(of);
			return;
		}
		
		if (this->bmpInfoHeader.bitCount == 24) {
			if (this->bmpInfoHeader.width % 4 == 0) {
				this->writeHeadersAndData(of);
				return;
			}

			uint32_t newStride = this->makeStrideAligned(4);
			std::vector<uint8_t> paddingRow(newStride - rowStride);
			this->writeHeaders(of);

			for (int32_t y = 0; y < this->bmpInfoHeader.height; ++y) {
				of.write((const char*)(data.data() + this->rowStride * y), this->rowStride);
				of.write((const char*)paddingRow.data(), paddingRow.size());

			}
			return;
		}

		throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
	}

	throw std::runtime_error("Unable to open the output image file.");
}

void Bmp::writeHeaders(std::ofstream& of) {
	of.write((const char*)&this->fileHeader, sizeof(this->fileHeader));
	of.write((const char*)&this->bmpInfoHeader, sizeof(this->bmpInfoHeader));
	if (this->bmpInfoHeader.bitCount == 32) {
		of.write((const char*)&this->bmpColorHeader, sizeof(this->bmpColorHeader));
	}
}

void Bmp::writeHeadersAndData(std::ofstream& of) {
	this->writeHeaders(of);
	of.write((const char*)this->data.data(), this->data.size());
}

void Bmp::writePixel(uint32_t width, uint32_t height, uint32_t R, uint32_t G, uint32_t B) {
	const uint32_t channels = this->bmpInfoHeader.bitCount / 8;
	this->data[channels * (height * this->bmpInfoHeader.width + width) + 0] = B;
	this->data[channels * (height * this->bmpInfoHeader.width + width) + 1] = G;
	this->data[channels * (height * this->bmpInfoHeader.width + width) + 2] = R;
}
