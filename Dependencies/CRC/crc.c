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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crc.h"
#define CRC_DLL 1
//Polynomial seed. SEED64 = 0x800000008000808B;
#define INT64_BYTESIZE 8
#define INT64_BITSIZE 64
#define max(a,b) (a>b?a:b)

uint64_t CRC_EXPORT CRC_DECL crc64(const char* buff, size_t len)
{
    uint64_t crc = 0xFFFFFFFFFFFFFFFF;
    size_t i, j = 0;

    for (i = 0; i < len; i += INT64_BYTESIZE)
    {
        crc ^= extract_int(buff, len, i, INT64_BYTESIZE);
        for (j = 0; j < INT64_BITSIZE; j++)
        {
            if (crc & 1)
                crc ^= SEED64;
            crc >>= 1;
        }
    }
  return crc;
}

uint64_t CRC_EXPORT CRC_DECL extract_int(const char* buff, size_t len, size_t start, byte width)
{
    uint64_t val = 0;
    size_t end = start + width;
    size_t shift = 0;

    for(; start < end; start++)
    {
        if(start >= len)
            break;
        val <<= shift * 8;
        val += buff[start];
    }

    return val;
}

size_t CRC_EXPORT CRC_DECL get_file_size(const char* file)
{
    FILE* f = NULL;
    size_t file_s = 0;

    //open file
    fopen(file, "r");
    if(f)
    {
        //reset cursor
        fseek(f, 0, SEEK_END);
        //Get size
        file_s = ftell(f);
        //close file
        fclose(f);
    }
    return file_s;
}

char* CRC_EXPORT CRC_DECL get_file_chunk(const char* file, size_t start, size_t s)
{
    FILE* f = NULL;
    char* buff = (char*)malloc(s);

    //open file
    fopen(file, "r");
    if(f)
    {
        //reset cursor
        fseek(f, start, SEEK_SET);
        //Get size
        fread((void*)buff, 1, s, f);
        //close file
        fclose(f);
    }
    return buff;
}

uint64_t CRC_EXPORT CRC_DECL crc64_on_file_fast(const char* file)
{
    size_t chunk_size = 0;
    size_t file_size = get_file_size(file);
    char* buffer = NULL;
    uint64_t crc_hash = 0;

    chunk_size = (file_size * MULTIPLIER) / DIVISOR;

    buffer = get_file_chunk(file, 0, chunk_size);

    crc_hash = crc64(buffer, chunk_size);

    free(buffer);

    return crc_hash;
}

uint64_t CRC_EXPORT CRC_DECL crc64_on_file_fastest(const char* file, size_t s)
{
    char* buffer = NULL;
    uint64_t crc_hash = 0;

    buffer = get_file_chunk(file, 0, s);

    crc_hash = crc64(buffer, s);

    free(buffer);

    return crc_hash;
}

uint64_t CRC_EXPORT CRC_DECL crc64_on_file(const char* file)
{
    size_t s = 0;
    char* buffer = NULL;
    uint64_t crc_hash = 0;

    s = get_file_size(file);

    buffer = get_file_chunk(file, 0, s);

    crc_hash = crc64(buffer, s);

    free(buffer);

    return crc_hash;
}
