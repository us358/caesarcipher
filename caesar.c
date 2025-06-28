/***********************************************************************/
// Copyright Buu Information Security Major
// File Name: caesar.c
// Author: 毛家奇
// ID: 2023240381019
// Version: 1.0
// Date: 2025/3/2
// Description:
// 该文件实现了从文件读取文本，去除标点符号，进行凯撒加密与解密，并将加密和解密后的内容分别保存到新文件的功能。
/***********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function Name: is_punctuation
// Parameters:
// char c: 【in】需要判断的字符
// Return:
// Type: int
// 非零值: 表示字符是标点符号
// 零: 表示字符不是标点符号
// Description:
// 利用ctype.h头文件中的ispunct函数判断字符是否为标点符号
int is_punctuation(char c) {
    return ispunct(c);
}

// Function Name: remove_punctuation_from_array
// Parameters:
// char *str: 【in/out】需要处理的字符串，处理后字符串中的标点符号会被去除
// Return:
// Type: void
// None: 无返回值
// Description:
// 遍历输入字符串，将非标点符号的字符依次向前移动，覆盖原字符串中的标点符号，最后在新字符串末尾添加字符串结束符'\0'
void remove_punctuation_from_array(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!is_punctuation(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

// Function Name: caesar_encrypt
// Parameters:
// char *words: 【in/out】需要加密的字符串，加密后结果存回该字符串
// int shift: 【in】加密偏移量
// Return:
// Type: void
// None: 无返回值
// Description:
// 遍历字符串，将大写字母转换为小写字母，然后对小写字母进行加密操作，通过计算偏移量在字母表中的位置来实现加密
void caesar_encrypt(char *words, int shift) {
    for (int i = 0; words[i] != '\0'; i++) {
        if (isupper(words[i])) {
            words[i] = tolower(words[i]);
        }
        if (islower(words[i])) {
            words[i] = 'a' + (words[i] - 'a' + shift) % 26;
        }
    }
}

// Function Name: caesar_decrypt
// Parameters:
// char *words: 【in/out】需要解密的字符串，解密后结果存回该字符串
// int shift: 【in】解密偏移量（与加密偏移量相同）
// Return:
// Type: void
// None: 无返回值
// Description:
// 遍历字符串，对小写字母进行解密操作，通过反向计算偏移量在字母表中的位置来实现解密
void caesar_decrypt(char *words, int shift) {
    for (int i = 0; words[i] != '\0'; i++) {
        if (islower(words[i])) {
            words[i] = 'a' + (words[i] - 'a' - shift + 26) % 26;
        }
    }
}

// Function Name: main
// Parameters:
// int argc: 【in】命令行参数的数量
// char *argv[]: 【in】包含命令行参数的字符串数组
// Return:
// Type: int
// 0: 程序正常结束
// 非零值: 程序出现错误，如文件无法打开、参数错误等
// Description:
// 程序的主入口函数。首先输出学号和姓名，然后根据命令行参数的情况执行不同操作。若没有命令行参数，自动读取message.txt文件内容，去除标点符号，进行凯撒加密并将结果保存到ciphers.txt，接着读取ciphers.txt内容进行解密并保存到decode.txt；若有命令行参数，根据参数-e或-d对指定输入文件内容进行加密或解密，并将结果保存到指定输出文件。
int main(int argc, char *argv[]) {
    // 输出学号和姓名
    printf("2023240381019 MaoJiaQi\n");
    int shift = 3;
    char words[100000] = {0};
    FILE *fp_in, *fp_out;
    int ch, i = 0;

    // 自动处理加密和解密流程（无命令行参数时）
    if (argc == 1) {
        // 加密 message.txt -> ciphers.txt
        fp_in = fopen("message.txt", "r");
        if (!fp_in) {
            // 若无法打开文件，输出错误信息并返回错误代码
            printf("无法打开 message.txt\n");
            return -1;
        }
        while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
            words[i++] = (char)ch;
        }
        words[i] = '\0';
        fclose(fp_in);
        // 去除字符串中的标点符号
        remove_punctuation_from_array(words);
        // 对字符串进行凯撒加密
        caesar_encrypt(words, shift);
        fp_out = fopen("ciphers.txt", "w");
        if (!fp_out) {
            // 若无法创建文件，输出错误信息并返回错误代码
            printf("无法创建 ciphers.txt\n");
            return -1;
        }
        // 将加密后的字符串写入文件
        fprintf(fp_out, "%s", words);
        fclose(fp_out);

        // 解密 ciphers.txt -> decode.txt
        // 清空字符串数组
        memset(words, 0, sizeof(words));
        i = 0;
        fp_in = fopen("ciphers.txt", "r");
        if (!fp_in) {
            // 若无法打开文件，输出错误信息并返回错误代码
            printf("无法打开 ciphers.txt\n");
            return -1;
        }
        while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
            words[i++] = (char)ch;
        }
        words[i] = '\0';
        fclose(fp_in);
        // 对字符串进行凯撒解密
        caesar_decrypt(words, shift);
        fp_out = fopen("decode.txt", "w");
        if (!fp_out) {
            // 若无法创建文件，输出错误信息并返回错误代码
            printf("无法创建 decode.txt\n");
            return -1;
        }
        // 将解密后的字符串写入文件
        fprintf(fp_out, "%s", words);
        fclose(fp_out);
        // 输出处理完成信息，告知加密文件和解密文件的名称
        printf("处理完成！加密文件：ciphers.txt，解密文件：decode.txt\n");
        return 0;
    }

    // 原有命令行参数处理（加密或解密）
    if (argc != 4) {
        // 若命令行参数数量不正确，输出使用方法提示信息并返回错误代码
        printf("用法: %s -e|-d 输入文件 输出文件\n", argv[0]);
        return -1;
    }
    fp_in = fopen(argv[2], "r");
    if (!fp_in) {
        // 若无法打开输入文件，输出错误信息并返回错误代码
        printf("文件无法打开\n");
        return -1;
    }
    while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
        words[i++] = (char)ch;
    }
    words[i] = '\0';
    fclose(fp_in);
    // 去除字符串中的标点符号
   // remove_punctuation_from_array(words);
    if (strcmp(argv[1], "-e") == 0) {
        // 若命令行参数为-e，对字符串进行凯撒加密
        caesar_encrypt(words, shift);
    } else if (strcmp(argv[1], "-d") == 0) {
        // 若命令行参数为-d，对字符串进行凯撒解密
        caesar_decrypt(words, shift);
    } else {
        // 若命令行参数不是-e或-d，输出无效参数错误信息并返回错误代码
        printf("无效的参数: %s\n", argv[1]);
        return -1;
    }
    fp_out = fopen(argv[3], "w");
    if (!fp_out) {
        // 若无法创建输出文件，输出错误信息并返回错误代码
        printf("无法创建输出文件\n");
        return -1;
    }
    // 将处理后的字符串写入输出文件
    fprintf(fp_out, "%s", words);
    fclose(fp_out);
    // 输出处理完成信息，告知输出文件的名称
    printf("处理完成！输出文件：%s\n", argv[3]);
    return 0;
}
