﻿// GenerateBMPpixel.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <memory>
#include <vector>
#define BI_RGB        0    // компрессия отсутствует
#define BI_RLE8       1    // компрессия (для одного пиксела - 8 бит)
#define BI_RLE4       2    // компрессия (для одного пиксела - 4 бита)
#define BI_BITFIELDS  3    // компрессия (другой формат компрессии)
#define BFSIZE 14
typedef unsigned int DWORD;
typedef unsigned short int WORD;
typedef int LONG;
typedef unsigned char BYTE;


typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;                 // тип файла (0x4D42)
    DWORD bfSize;                // размер файла
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;             // смещение битов изображения
}BITMAPFILEHEADER;
typedef BITMAPFILEHEADER* PBITMAPFILEHEADER;
typedef PBITMAPFILEHEADER* LPBITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;                 // размер структуры BITMAPFILEHEADER
    LONG  biWidth;                // ширина изображения в пикселах
    LONG  biHeight;               // высота изображения в пикселах
    WORD  biPlanes;               // количество плоскостей
    WORD  biBitCount;             // количество бит на пиксел
    DWORD biCompression;          // тип сжатия
    DWORD biSizeImage;            // размер изображения в байтах
    LONG  biXPelsPerMeter;        // разрешение устройства вывода по X
    LONG  biYPelsPerMeter;        // разрешение устройства вывода по Y
    DWORD biClrUsed;              // размер таблицы цветов
    DWORD biClrImportant;         // необходимое количество цветов
}BITMAPINFOHEADER;
typedef BITMAPINFOHEADER* PBITMAPINFOHEADER;
typedef PBITMAPINFOHEADER* LPBITMAPINFOHEADER;


typedef struct tagRGBTRIPLE
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
}RGBTRIPLE;
typedef RGBTRIPLE* LPRGBTRIPLE;


std::vector<bool> eratosthenes_sieve(int n) {
    std::vector<bool> result(n);
    for (size_t i = 2; i * i < n; ++i) {
        if (!result[i]) {
            for (size_t j = i; j * i < n; ++j) result[i * j] = true;
        }
    }
    return result;
}

std::vector<bool> squares(int n) {
    std::vector<bool> result(n);
    int64_t nn = n;
    for (size_t i = 0; i * i < nn * 100; ++i) {
        result[i * i / 100] = true;
    }
    return result;
}

std::vector<bool> dec_cubes(int n) {
    std::vector<bool> result(n);
    int64_t nn = n;
    for (size_t i = 0; i * i * i < nn * 1000000; ++i) {
        result[i * i * i / 1000000] = true;
    }
    return result;
}

int main()
{
    BITMAPFILEHEADER BitmapFileHeader;
    BITMAPINFOHEADER BitmapInfoHeader;
    RGBTRIPLE Green, Black, Blue, Yellow, Red, White, DarkBlue, LightBlue;
    BYTE buf;
    LONG Width;
    LONG Height;
    LONG EWidth;
    int i, j, k;
    buf = 0;
    Width = 2110;
    Height = 1470;
    EWidth = Width * sizeof(RGBTRIPLE);
    while (EWidth % 4 != 0) ++EWidth;
    int tail = EWidth - Width * sizeof(RGBTRIPLE);

    memset(&BitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));

    BitmapFileHeader.bfType = 0x4D42;    // тип файла (текстовая строка "BM")
    BitmapFileHeader.bfSize = BFSIZE +
        sizeof(BITMAPINFOHEADER) + Height * EWidth;
    BitmapFileHeader.bfReserved1 = 0;
    BitmapFileHeader.bfReserved2 = 0;
    BitmapFileHeader.bfOffBits = BFSIZE +
        sizeof(BITMAPINFOHEADER);

    memset(&BitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));

    BitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    BitmapInfoHeader.biHeight = Height;
    BitmapInfoHeader.biWidth = Width;
    BitmapInfoHeader.biPlanes = 1;
    BitmapInfoHeader.biBitCount = sizeof(RGBTRIPLE) * 8;
    BitmapInfoHeader.biSizeImage = Height * EWidth;
    BitmapInfoHeader.biCompression = BI_RGB;
    BitmapInfoHeader.biXPelsPerMeter = 0;
    BitmapInfoHeader.biYPelsPerMeter = 0;
    FILE* stream;
    stream = fopen("squares_primes_and_cubes_pixel_2.bmp", "w");
    if (stream == NULL)
    {
        std::cout << "Ошибка открытия файла для записи" << std::endl;
        exit(1);
    }

    fwrite(&BitmapFileHeader.bfType, sizeof(WORD), 1, stream);
    fwrite(&BitmapFileHeader.bfSize, sizeof(DWORD), 1, stream);
    fwrite(&BitmapFileHeader.bfReserved1, sizeof(WORD), 1, stream);
    fwrite(&BitmapFileHeader.bfReserved2, sizeof(WORD), 1, stream);
    fwrite(&BitmapFileHeader.bfOffBits, sizeof(DWORD), 1, stream);
    fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, stream);

    auto is_compose = eratosthenes_sieve(Height * Width);
    auto is_square = squares(Height * Width);
    auto is_dec_cube = dec_cubes(Height * Width);

    Green = RGBTRIPLE{ 0, 255, 0 };
    Black = RGBTRIPLE{ 0, 0, 0 };
    Blue = RGBTRIPLE{ 255, 0, 0 };
    LightBlue = RGBTRIPLE{ 255, 192, 0 };
    Yellow = RGBTRIPLE{ 0, 255, 255 };
    Red = RGBTRIPLE{ 0, 0, 255 };
    White = RGBTRIPLE{ 255, 255, 255 };
    DarkBlue = RGBTRIPLE{ 128, 0, 0 };

    int index = 0;

    for (size_t i = 0; i < Height; i++)
    {
        for (size_t j = 0; j < Width; j++) {
            index = i / 10 * (Width / 10) + j / 10;
            if (!is_square[index]) {
                if (!is_dec_cube[index]) {
                    if (is_compose[index]) {
                        fwrite(&Black, sizeof(RGBTRIPLE), 1, stream);
                    }
                    else {
                        fwrite(&LightBlue, sizeof(RGBTRIPLE), 1, stream);
                    }
                }
                else {
                    fwrite(&Green, sizeof(RGBTRIPLE), 1, stream);
                }
            }
            else {
                fwrite(&Yellow, sizeof(RGBTRIPLE), 1, stream);
            }
            ++index;
        }
        for (size_t k = 0; k < tail; k++)
        {
            fwrite(&buf, sizeof(BYTE), 1, stream);
        }
    }
    fclose(stream);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
