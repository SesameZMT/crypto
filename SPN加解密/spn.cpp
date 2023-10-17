#include <iostream>
#include <cstring>

char * clear_text = (char*)malloc(16 * sizeof(char)); // 储存明文
char * key_text = (char*)malloc(32 * sizeof(char)); // 储存密钥
int pi_s[16] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
int pi_p[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

// 计算第n轮的密钥
char * key_now(int n,char * key)
{
    int index = 0;
    for(int i = 4*n-4;i < 4*n+12;i++)
    {
        key[index] = key_text[i];
        index++;
    }
    return key;
}

char * encode_pi_s(char * clear)
{
    for(int i = 0;i < 4;i++)
    {
        int dec = 0;
        for(int j = 0;j < 4;j++)
        {
            dec *= 2;
            dec += (clear[4*i + j] - '0');
        }
        int dec_ex = pi_s[dec];
        for(int j = 0;j < 4;j++)
        {
            clear[4*i + 3 - j] = ((dec_ex % 2) + '0');
            dec_ex /= 2;
        }
    }
    return clear;
}

char * encode_pi_p(char * clear)
{
    char temp[16];
    for(int i = 0;i < 16;i++)
    {
        temp[i] = clear[i];
    }
    for(int i = 0;i < 16;i++)
    {
        clear[i] = temp[pi_p[i]];
    }
    return clear;
}

char * encode_XOR(char * clear , char * key)
{
    for(int i = 0;i < 16;i++)
    {
        clear[i] = (((clear[i] - '0') ^ (key[i] - '0')) + '0');
    }
    return clear;
}

int main()
{
    scanf("%s" , clear_text);
    scanf("%s" , key_text);

    char * encode_text = clear_text;
    char * keynow = (char*)malloc(16 * sizeof(char));
    for(int i = 1;i <= 4;i++)
    {
        keynow = key_now(i,keynow);
        if(i == 4)
        {
            encode_text = encode_pi_s(encode_XOR(encode_text,keynow));
        }
        else
        {
            encode_text = encode_pi_p(encode_pi_s(encode_XOR(encode_text,keynow)));
        }
    }

    keynow = key_now(5,keynow);
    encode_text = encode_XOR(encode_text,keynow);

    printf("%s",encode_text);
    
    return 0;
}