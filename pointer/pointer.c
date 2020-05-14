#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(int* a, int* b)
{
  int c; 
  // int* <- int型変数のアドレス値を入れるためのポインタ変数型
  //        つまり、a とb にはそれぞれアドレス値が入る
  // *a <- ポインタ変数a が示すアドレスに入っているint 値。
  //        ポインタ変数ではない変数c に対して *c と書くとコンパイルエラー
  // a <- int 型のアドレス値
  // &a <- ポインタ変数a が存在する場所（アドレス値）
  // &c <- int型変数c が格納されているアドレス値。
  // 
  // *a, a, &a の使い分けができるようになりましょう。

  c = *a;
  *a = *b;
  *b = c;

  printf("int* a, *b;\n");
  printf("*a = 0x%016lx, *b = 0x%016lx \n", a, b);

  // *a, a, &a の使い分けができるようになりましょう(２回目)。
  printf("a = 0x%016lx, b = 0x%016lx \n", &a, &b);
}

void ex_swap()
{
	printf("\n\n\n========================== ex_swap =====================\n");
	int x = 5; 
	int y = 10;
	printf("int x, y;\n");
	printf("x = %d, y = %d\n", x, y); 
	// 昔は32bit マシンだったので0x%08x と書いていた。
	// 今回は64bit 環境を想定しているので%016lx とした。
	printf("&x = 0x%016lx, &y = 0x%016lx \n", &x, &y);

	printf("\nswap a and b then...\n\n");

    // swap の引数２つにはそれぞれint型変数のアドレス値をいれる。
	// int 型変数a, b のアドレス値は&a, &b である。
	swap(&x, &y);

	printf("x = %d, y = %d\n", x, y);

}

void multi_out(int* out0, short* out1)
{
	// 引数で渡されるのは変数の中身ではなく、変数の場所(アドレス値)。
	// 同じアドレス値でも、int 型変数のアドレスなのかshort 型変数のアドレスなのかは
	// 区別される。
	// 関数multi_out を呼び出した側から教えられた場所に
	// 値を書き込んでいく。

	// out0 と&(*out0) は同じ意味。
	// multi_out の呼び出し元とこことで中身は同じになっているはず。
	printf("int* out0; short *out1;\n");
	printf("out0: 0x%016x, out1: 0x%016x in ex_multi_out()\n", out0, out1);
	printf("&(*out0): 0x%016x, &(*out1): 0x%016x in ex_multi_out()\n", &(*out0), &(*out1));

	printf("*out0: %d, *out1: %d\n", *out0, *out1);

	*out0 = 100; 
	*out1 = 200;

	printf("-> *out0: %d, *out1: %d\n", *out0, *out1);
}

void ex_multi_out()
{
	printf("\n\n\n========================== ex_multi_out =====================\n"); 
	// これはよく使うやり方。
	int x = 0; 
	short y = 0; 

	printf("int x, y;\n");
	printf("x: %d, y: %d\n", x, y); 
	printf("&x: 0x%016x, &y: 0x%016x in ex_multi_out()\n", &x, &y);

	// 変数x のアドレス値と、変数y のアドレス値とを渡す。
	// 関数multi_out に、どの変数領域を書き換えればよいのかを教えてあげる。
	multi_out(&x, &y); 

	printf("-> x: %d, y: %d\n", x, y);
}

void ex_tolower()
{
	printf("\n\n\n========================== ex_tolower =====================\n"); 
	// こう書くと、"abcDEF" がメモリのどこかに格納される。
	// コンパイル時に決められる。
	// text にはこの文字列の先頭（つまり'a' の部分)のアドレスが代入される。
	// C言語の場合、文字列の終端は'\0' になる（つまりtext[6] == '\0'）。
	// n文字の文字列は実際には'\0' を加えた(n+1)文字が使用される。
	//
	// なお、こういった文字列定数のアドレスはchar* ではなく
	// const char* 型で保持する。安易にconst char* からchar* へキャストもしない。
	// 文字列定数は書き換えられないことが想定されているので、
	// char* 型で宣言して、文字列定数のメモリ領域に書き込みをすると
	// Segmentation fault で落ちることもある。
	const char* text = "abcDEF";

	// これはこの時点では長さ32の文字型配列。中身は何が入っているかわからない。
	char buf[32];

	// printf で%s を指定すると、引数で示されるアドレス(text)から
	// '\0' が見つかるまで順に標準出力へ出力される。
	printf("text: %s\n", text);

	// 文字列の末尾は'\0' になっている。
	printf("text[6]: 0x%02x\n", text[6]); 

	// text[2] = 'X';   <- こんなことをやると落ちるかも。

	// text をbuf にコピー。コピー先のメモリサイズがコピー元より小さくならないように
	// 注意。
	strcpy(buf, text); 

	// 'a', 'b', 'c', 'D', 'E', 'F', '\0', ...
	printf("buf: %s\n", buf);

	// buf の先頭から１文字ずつ文字列領域を書き換えていく
	buf[0] = 'X'; 
	buf[1] = 'Y';
	buf[2] = 'Z'; 

	// buf の先頭が書き換わってるはず。

	printf("-> buf: %s\n", buf);

	// この時点でのbufは先頭から順に
	// 'X', 'Y', 'Z', 'D', 'E', 'F', '\0', ...


	// &buf[6] はアドレス値(buf + 6)をしめす。
	// つまり文字列領域buf の先頭から６番目のアドレスであり、
	// buf の途中から('\0 の部分から)"HIJ" を上書きする。
	strcpy(&buf[6], "HIJ"); 

	// この時点でのbufは先頭から順に
	// 'X', 'Y', 'Z', 'D', 'E', 'F', 'H', 'I', 'J', '\0', ...
	printf("-> buf: %s\n", buf);

}

int main(int argc, const char** argv)
{
	// ポインタ変数のよく出てくる使い方色々
	ex_swap();

	ex_multi_out();

	ex_tolower(); 

	return 0; 
}
