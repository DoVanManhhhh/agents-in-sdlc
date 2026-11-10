#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 100
#include <string.h>

int main() {
    char s2[100] = { 0 }, ans[100] = { 0 };
    int i, j = 0, k = 0;

    printf("문자열 >> ");   // 소문자 -> 대문자
    gets(s2);               // scanf_s("%s", sizeof(ans), ans);

    s2[0] -= 32;            // Chuyển ký tự đầu tiên thành chữ hoa

    s2[strlen(s2)] = '.';  // Thêm dấu chấm vào cuối chuỗi
    s2[strlen(s2) + 1] = '\0';  // Thêm ký tự kết thúc chuỗi

   
    puts(s2);                // In chuỗi s2
    printf("%d\n", strlen(s2));
     return 0;
}


