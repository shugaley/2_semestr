
#include "hash-table_header.h"

int Hash_Func1(const char* word)
{
    assert(word);

    return 1;
}


int Hash_Func_First_Letter(const char* word)
{
    assert(word);

    return word[0];
}


int Hash_Func_Len(const char* word)
{
    assert(word);

    int len = 0;
    while(word[len++])
        ;

    return len-1;
}


int Hash_Func_Sum_Let(const char* word)
{
    assert(word);

    int sum = 0, i_sym = 0;
    while(word[i_sym])
        sum += word[i_sym++];

    return sum;
}


int Hash_Func_Rol(const char* word)
{

    if(!(*word))
        return 0;

    char temp = *word;
    char c = '\0';

    c = c | *word;
    c = c >> 7;

    temp = temp << 1;
    temp = temp | c;

    return temp + Hash_Func_Rol(word + 1);
}


int Hash_Func_GNU(const char* word)
{
    assert(word);

    int h = 5381;

    for (unsigned char c = *word; c != '\0'; c = *++word)
        h = h * 33 + c;

    h %= 1000;

    return (h < 0)? -h : h;
}


unsigned int Hash_FuncMURMUR (const char* word)
{
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    int len = 0;
    while(word[len++]);

    unsigned int h = seed ^ len;

    auto data = (const unsigned char*)word;
    unsigned int k;

    while (len >= 4)
    {
        k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}
