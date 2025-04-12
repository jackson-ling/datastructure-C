// 串的存储方式注意点：字符窜都是从下标为一的位置开始存储的，下标为0的位置限制不用

#define maxsize 100

typedef struct
{
    char arr[maxsize + 1];
    int length;
} sstring; // 表示顺序串
