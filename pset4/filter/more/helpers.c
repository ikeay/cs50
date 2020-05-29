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
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int blue;
        int green;
        int red;
    } bgr;

    bgr result_gx[height][width];
    bgr result_gy[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // [notice]
    // ここもmemcpy を使いましょう。
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result_gx[i][j].red = 0;
            result_gx[i][j].green = 0;
            result_gx[i][j].blue = 0;
            result_gy[i][j].red = 0;
            result_gy[i][j].green = 0;
            result_gy[i][j].blue = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // [note]
            // ここは敢えて修正不要ですが(速度〇、品質△、実行ファイルサイズ〇)、
            // 選択肢がいくつかあります（ケースバイケース。半分雑学。）
            // 
            // opt 1. for (int k = i - 1... の部分を関数化してコードの見通しをよくする(速度△、品質〇、実行ファイルサイズ〇)
            // 
            // ネストが深いのはコード品質的にはよろしくないので、関数化すると見通しが良くなります。
            // 一方、関数呼び出し自体にオーバーヘッドがありますので、実行速度は下がる傾向にあります。
            // 但し、コンパイラの最適化によってこのオーバーヘッドはある程度の解消が期待できるので、
            // 関数化はコード品質向上のための一つの選択肢です。
            //
            // 
            // opt 2. k とl の組み合わせは3x3 の9通りなので、9通りをループを使わずに記述する(速度◎、品質×、実行ファイルサイズ×)
            // 
            // ループ処理自体にもオーバーヘッドがあります。分岐処理をすることで命令パイプラインが乱れ、実行速度の低下を招きます。
            // (命令パイプラインの説明は端折りますが、ざっくり言うと、連続する命令をプロセッサレベルでプチ並列化して高速化する技術です。)
            // ループ回数が予め分かっている場合、中身を展開すると命令パイプラインがうまく働いて高速化が期待できます。
            // 。。。ただ、賢いコンパイラであればこの辺はうまくコンパイル時に最適化してくれたりもするので、
            // この対策を実施することはほとんどないでしょうね。。。
            // 出番があるとすれば、性能の低いコンパイラを使っている場合に、コード品質・ファイルサイズを犠牲にしてでも高速化したい時でしょうか。。。
            // 極端な高速化が求められる場合なので、画像処理などの一部の用途限定で、
            // opt 1 で品質をある程度担保した後のチューニングフェーズ
            // でやる可能性があるくらいでしょうか…（最初からコード品質を犠牲にすると沼にハマるので注意。）
            //
            // opt 3. (C++ 限定)インライン関数を使う(速度〇、品質〇、実行ファイルサイズ△)
            //
            // opt 1 を実施する際に、インライン関数を使うと関数呼び出しのオーバーヘッドを避けながら
            // コードの見通しを改善することができます。
            // 但し、C++ 限定であることと、呼び出し箇所が複数の場合に実行ファイルのサイズが大きくなることが欠点です。
            // (Arduinoのようなメモリの少ない環境では無視できなくなる。今回は呼び出し箇所が1か所だけなので影響軽微。)
            //
            // オススメは、現状維持のままか、opt 1 とコンパイルの最適化の併用で、コードの品質向上を図るか、でしょうかね。
            for (int k = i - 1, m = 0; k <= i + 1; k++, m++)
            {
                for (int l = j - 1, n = 0; l <= j + 1; l++, n++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        result_gx[i][j].red += gx[m][n] * image[k][l].rgbtRed;
                        result_gx[i][j].green +=  gx[m][n] * image[k][l].rgbtGreen;
                        result_gx[i][j].blue +=  gx[m][n] * image[k][l].rgbtBlue;
                        result_gy[i][j].red += gy[m][n] * image[k][l].rgbtRed;
                        result_gy[i][j].green += gy[m][n] * image[k][l].rgbtGreen;
                        result_gy[i][j].blue += gy[m][n] * image[k][l].rgbtBlue;
                    }
                    else
                    {
                        // [notice]
                        // ここのコードは不要では？(0を加算しているだけで、実行後に変化がないため。)
                        result_gx[i][j].red += 0;
                        result_gx[i][j].green += 0;
                        result_gx[i][j].blue += 0;
                        result_gy[i][j].red += 0;
                        result_gy[i][j].green += 0;
                        result_gy[i][j].blue += 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // [note]
            // このコードで維持、ですかね。
            // rgb それぞれ同じような処理なので関数化する方が見通しが良いですが、
            // 関数呼び出しのオーバーヘッドで処理速度低下を招くかもしれないので、
            // べた書きでもＯＫかと思います。
            int edge_red = round(sqrt((result_gx[i][j].red * result_gx[i][j].red) + (result_gy[i][j].red * result_gy[i][j].red)));
            if (edge_red > 255)
            {
                edge_red = 255;
            }
            image[i][j].rgbtRed = edge_red;

            int edge_green = round(sqrt((result_gx[i][j].green * result_gx[i][j].green) + (result_gy[i][j].green * result_gy[i][j].green)));
            if (edge_green > 255)
            {
                edge_green = 255;
            }
            image[i][j].rgbtGreen = edge_green;

            int edge_blue = round(sqrt((result_gx[i][j].blue * result_gx[i][j].blue) + (result_gy[i][j].blue * result_gy[i][j].blue)));
            if (edge_blue > 255)
            {
                edge_blue = 255;
            }
            image[i][j].rgbtBlue = edge_blue;
        }
    }
}
