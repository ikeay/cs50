#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int my_atoi(char *str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *keys = argv[1];

	// 引数文字列(keys)の正当性チェック
	if(strlen(keys) != 26) {
		printf("Key must contain 26 characters.\n");
		return -1; 
	}

	for(int i=0;i<26;i++) {
		// 大文字・小文字を区別しないので小文字に統一して判定する
		char key = tolower(keys[i]);
		if(key < 'a' || key > 'z') {
			printf("The key %c is not alphabet. \n", key); 
			return 1; 
		}

		for(int j=0;j<26;j++) {
			char key2 = tolower(keys[j]); 
			if(i != j && key == key2) {
				printf("Duplicate characters in key.\n");
				return 1; 
			}
		}
	}

	// 文字コードx -> x へのマップ。
	// 但し、アルファベット文字の場合はkeys に合わせてマップ先を変更する。
	char convert_map[256]; 
	for(int i=0;i<256;i++) {
		char c = (char)i;
		int index; 
		if(c >= 'a' && c <= 'z') {
			// index: keys のどこを参照するかを示す
			index = (int)(c - 'a'); 
			convert_map[i] = tolower(keys[index]); 
		} else if(c >= 'A' && c <= 'Z') {
			// index: keys のどこを参照するかを示す
			index = (int)(c - 'A');
			convert_map[i] = toupper(keys[index]);
		} else {
			convert_map[i] = c; 
		}
	}

	char *text = get_string("plaintext: ");
	// 実際に変換処理を行う。
	for(int i = 0;text[i] != '\0';i++) {
		int index = (int)text[i]; // 1バイトデータなので、index は0～255 になる。
		printf("%c", convert_map[index]); 
	}
    return 0;
}
