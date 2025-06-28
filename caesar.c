/***********************************************************************/
// Copyright Buu Information Security Major
// File Name: caesar.c
// Author: ë����
// ID: 2023240381019
// Version: 1.0
// Date: 2025/3/2
// Description:
// ���ļ�ʵ���˴��ļ���ȡ�ı���ȥ�������ţ����п�����������ܣ��������ܺͽ��ܺ�����ݷֱ𱣴浽���ļ��Ĺ��ܡ�
/***********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function Name: is_punctuation
// Parameters:
// char c: ��in����Ҫ�жϵ��ַ�
// Return:
// Type: int
// ����ֵ: ��ʾ�ַ��Ǳ�����
// ��: ��ʾ�ַ����Ǳ�����
// Description:
// ����ctype.hͷ�ļ��е�ispunct�����ж��ַ��Ƿ�Ϊ������
int is_punctuation(char c) {
    return ispunct(c);
}

// Function Name: remove_punctuation_from_array
// Parameters:
// char *str: ��in/out����Ҫ������ַ�����������ַ����еı����Żᱻȥ��
// Return:
// Type: void
// None: �޷���ֵ
// Description:
// ���������ַ��������Ǳ����ŵ��ַ�������ǰ�ƶ�������ԭ�ַ����еı����ţ���������ַ���ĩβ����ַ���������'\0'
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
// char *words: ��in/out����Ҫ���ܵ��ַ��������ܺ�����ظ��ַ���
// int shift: ��in������ƫ����
// Return:
// Type: void
// None: �޷���ֵ
// Description:
// �����ַ���������д��ĸת��ΪСд��ĸ��Ȼ���Сд��ĸ���м��ܲ�����ͨ������ƫ��������ĸ���е�λ����ʵ�ּ���
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
// char *words: ��in/out����Ҫ���ܵ��ַ��������ܺ�����ظ��ַ���
// int shift: ��in������ƫ�����������ƫ������ͬ��
// Return:
// Type: void
// None: �޷���ֵ
// Description:
// �����ַ�������Сд��ĸ���н��ܲ�����ͨ���������ƫ��������ĸ���е�λ����ʵ�ֽ���
void caesar_decrypt(char *words, int shift) {
    for (int i = 0; words[i] != '\0'; i++) {
        if (islower(words[i])) {
            words[i] = 'a' + (words[i] - 'a' - shift + 26) % 26;
        }
    }
}

// Function Name: main
// Parameters:
// int argc: ��in�������в���������
// char *argv[]: ��in�����������в������ַ�������
// Return:
// Type: int
// 0: ������������
// ����ֵ: ������ִ������ļ��޷��򿪡����������
// Description:
// ���������ں������������ѧ�ź�������Ȼ����������в��������ִ�в�ͬ��������û�������в������Զ���ȡmessage.txt�ļ����ݣ�ȥ�������ţ����п������ܲ���������浽ciphers.txt�����Ŷ�ȡciphers.txt���ݽ��н��ܲ����浽decode.txt�����������в��������ݲ���-e��-d��ָ�������ļ����ݽ��м��ܻ���ܣ�����������浽ָ������ļ���
int main(int argc, char *argv[]) {
    // ���ѧ�ź�����
    printf("2023240381019 MaoJiaQi\n");
    int shift = 3;
    char words[100000] = {0};
    FILE *fp_in, *fp_out;
    int ch, i = 0;

    // �Զ�������ܺͽ������̣��������в���ʱ��
    if (argc == 1) {
        // ���� message.txt -> ciphers.txt
        fp_in = fopen("message.txt", "r");
        if (!fp_in) {
            // ���޷����ļ������������Ϣ�����ش������
            printf("�޷��� message.txt\n");
            return -1;
        }
        while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
            words[i++] = (char)ch;
        }
        words[i] = '\0';
        fclose(fp_in);
        // ȥ���ַ����еı�����
        remove_punctuation_from_array(words);
        // ���ַ������п�������
        caesar_encrypt(words, shift);
        fp_out = fopen("ciphers.txt", "w");
        if (!fp_out) {
            // ���޷������ļ������������Ϣ�����ش������
            printf("�޷����� ciphers.txt\n");
            return -1;
        }
        // �����ܺ���ַ���д���ļ�
        fprintf(fp_out, "%s", words);
        fclose(fp_out);

        // ���� ciphers.txt -> decode.txt
        // ����ַ�������
        memset(words, 0, sizeof(words));
        i = 0;
        fp_in = fopen("ciphers.txt", "r");
        if (!fp_in) {
            // ���޷����ļ������������Ϣ�����ش������
            printf("�޷��� ciphers.txt\n");
            return -1;
        }
        while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
            words[i++] = (char)ch;
        }
        words[i] = '\0';
        fclose(fp_in);
        // ���ַ������п�������
        caesar_decrypt(words, shift);
        fp_out = fopen("decode.txt", "w");
        if (!fp_out) {
            // ���޷������ļ������������Ϣ�����ش������
            printf("�޷����� decode.txt\n");
            return -1;
        }
        // �����ܺ���ַ���д���ļ�
        fprintf(fp_out, "%s", words);
        fclose(fp_out);
        // ������������Ϣ����֪�����ļ��ͽ����ļ�������
        printf("������ɣ������ļ���ciphers.txt�������ļ���decode.txt\n");
        return 0;
    }

    // ԭ�������в����������ܻ���ܣ�
    if (argc != 4) {
        // �������в�����������ȷ�����ʹ�÷�����ʾ��Ϣ�����ش������
        printf("�÷�: %s -e|-d �����ļ� ����ļ�\n", argv[0]);
        return -1;
    }
    fp_in = fopen(argv[2], "r");
    if (!fp_in) {
        // ���޷��������ļ������������Ϣ�����ش������
        printf("�ļ��޷���\n");
        return -1;
    }
    while ((ch = fgetc(fp_in)) != EOF && i < sizeof(words)-1) {
        words[i++] = (char)ch;
    }
    words[i] = '\0';
    fclose(fp_in);
    // ȥ���ַ����еı�����
   // remove_punctuation_from_array(words);
    if (strcmp(argv[1], "-e") == 0) {
        // �������в���Ϊ-e�����ַ������п�������
        caesar_encrypt(words, shift);
    } else if (strcmp(argv[1], "-d") == 0) {
        // �������в���Ϊ-d�����ַ������п�������
        caesar_decrypt(words, shift);
    } else {
        // �������в�������-e��-d�������Ч����������Ϣ�����ش������
        printf("��Ч�Ĳ���: %s\n", argv[1]);
        return -1;
    }
    fp_out = fopen(argv[3], "w");
    if (!fp_out) {
        // ���޷���������ļ������������Ϣ�����ش������
        printf("�޷���������ļ�\n");
        return -1;
    }
    // ���������ַ���д������ļ�
    fprintf(fp_out, "%s", words);
    fclose(fp_out);
    // ������������Ϣ����֪����ļ�������
    printf("������ɣ�����ļ���%s\n", argv[3]);
    return 0;
}
