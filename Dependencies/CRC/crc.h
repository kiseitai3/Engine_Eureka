/*
    Copyright (C) 2014 Luis M. Santos
    Contact: luismigue1234@hotmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED
#include <stdint.h>

#define CRC_DECL __cdecl
#ifndef CRC_DLL
#define CRC_EXPORT __declspec(dllexport)
#else
#define CRC_EXPORT __declspec(dllimport)
#endif // CRC_DLL

typedef unsigned int size_t;
typedef unsigned char byte;

///Let's do some compatibility management
#ifdef __cplusplus
extern "C" {
#endif
/**Below are the constant polynomials that I will use depending on the CRC type. Notice that I use the format
SEED#, where # represent the bit size, which implies what crc function will use it!*/
static const uint64_t SEED64 = 0x800000008000808B;

/**Below are some utility constants used by the utility functions!*/
static const char DIVISOR = 100;///This value will be used to compute chunk of file to be used for crc
static const char MULTIPLIER = 10;///This value goes from 1 to 100 and will be used for the same purpose as DIVISOR

/**Below are the utility functions each crc function may use.*/
uint64_t CRC_DECL extract_int(const char* buff, size_t len, size_t start, byte width);
size_t CRC_DECL get_file_size(const char* file);
char* CRC_DECL get_file_chunk(const char* file, size_t start, size_t s);

/**Below are the actual crc functions I will provide*/
uint64_t CRC_DECL crc64(const char* buff, size_t len);

/**Below are functions that will compute the crc hash of files*/
//Fast versions
uint64_t CRC_DECL crc64_on_file_fast(const char* file);

//Fastest versions
uint64_t CRC_DECL crc64_on_file_fastest(const char* file, size_t s);

//Slow versions
uint64_t CRC_DECL crc64_on_file(const char* file);

#ifdef __cplusplus
}
#endif
#endif // CRC_H_INCLUDED
