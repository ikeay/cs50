#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // [notice]
            // 汎整数拡張 という仕組みで、BYTE 型同士の足し算をした結果が一時的にint 型に拡張されています。
            // なので、内部的には
            // (BYTE)255 + (BYTE)255 -> (int)(BYTE)255 + (int)(BYTE)255 -> (int)510
            // と評価されます。
            // 今回は関係していませんが、ビット演算や符号有り・無しを区別しているケースではビット長や型に注意。
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE original_red = image[i][j].rgbtRed;
            BYTE original_green = image[i][j].rgbtGreen;
            BYTE original_blue = image[i][j].rgbtBlue;
            int sepia_red = round(.393 * original_red + .769 * original_green + .189 * original_blue);
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            image[i][j].rgbtRed = sepia_red;

            int sepia_green = round(.349 * original_red + .686 * original_green + .168 * original_blue);
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            image[i][j].rgbtGreen = sepia_green;

            int sepia_blue = round(.272 * original_red + .534 * original_green + .131 * original_blue);
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // [notice]
    // ここはcopy 配列を使わずに記述できるでしょう。
    // また、仮にcopy 配列を使う場合でも、要素を一つ一つ代入するよりは、
    // memcpy などの関数を使う方が高速です。    
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - 1 - j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // [notice]
    // ここはメモリを確保して変換前・変換後のバッファが両方存在する必要があるので、
    // copy 領域を確保するやり方でＯＫです。
    // 高速なmemcpy を使いましょう。
    // (おまけ)
    // 画像処理の場合、4byte alignment に注意。
    // OpenCV などの画像ライブラリでは、画像バッファの横方向のラインを確保する際に
    // バッファのサイズが4の倍数になるように、バッファの後ろにダミーデータが詰められることもあります。
    // (画像ライブラリでalignment の情報を取得出来たり、予め仕様で決まっていたりします。)
    // ダミーデータが入っていると、memcpy の時のバッファサイズ計算が変わってくるので注意。
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        sum_red += copy[k][l].rgbtRed;
                        sum_green += copy[k][l].rgbtGreen;
                        sum_blue += copy[k][l].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) sum_red / (float) count);
            image[i][j].rgbtGreen = round((float) sum_green / (float) count);
            image[i][j].rgbtBlue = round((float) sum_blue / (float) count);
        }
    }
}
