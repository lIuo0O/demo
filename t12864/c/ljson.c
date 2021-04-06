#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define     KEY_SEARCH     0x00
#define     KEY_EQUAL      0x01
#define     KEY_FOUND      0x02
#define     VALUE_SEARCH   0x03
#define     VALUE_FOUND    0x04
#define     ARR_LEN        0x0c

int lstr_len(const char *str);
int str_to_int(char *s, int len);
char* lget_str(const char *model, const char *str, const char symbol, int *rlen);
int lget_int(const char *model, const char *str);
int lget_arr(const char *model, const char *str, int *arr);
void print_str(const char *str, int len);
char get_pair(const char symbol);
void print_arr(int *arr, int len);


int main(int argc, char **argv){
    char str[] = "{\"s\":\"OK\", \"pid\":1157, \"no\":\"CY-H78\", \"q\":5000, \"es\":[1,3,6,9,11,99]}";
    int slen = strlen(str);
    char model[] = "no";
    int mlen = 2;
    printf("%s\n", str);
    int rlen = 0;
    char *s = lget_str(model, str, '\"',&rlen);
    print_str(s, rlen);
    char pid[] = "pid";
    int plen = 3;
    int id = lget_int(pid, str);
    printf("pid=%d\n", id);
    int arr[ARR_LEN] = {0};
    int arr_len = 0;
    char es[] = "es";
    int elen = 2;
    arr_len = lget_arr(es, str, arr);
    print_arr(arr, arr_len);
    getchar();
    return 0;
}

char get_pair(const char symbol){
    if(symbol == '\"') return '\"';
    if(symbol == '(') return ')';
    if(symbol == '[') return ']';
    if(symbol == '{') return '}';
    return 0;
}
void print_arr(int *arr, int len){
    int i = 0;
    while(i < len){
        printf("arr[%d]=%d\n", i, *(arr+i));
        i++;
    }
}
void print_str(const char *str, int len){
    int i = 0;
    while(i<len){
        printf("%c", *(str+i));
        i++;
    }
    printf("\n");
}

int lstr_len(const char *str){
    int res = 0;
    while(*(str + res) != '\0'){
        res++;
    }
    return res;
}

int str_to_int(char *s, int len){
    int res = 0;
    int i = 0;
    while(i < len){
        char tmp = *(s+i);
        res *= 10;
        if( tmp >= '0' || tmp <= '9'){
            res += tmp - '0';
        }
        i++;
    }
    return res;
}

int lget_arr(const char *model, const char *str, int *arr){
    int res = 0;
    int i = 0;
    int j = 0;
    int rlen = 0;
    char *s = lget_str(model, str, '[', &rlen);
    char tmp = *s;
    while(i < rlen){
        tmp = *(s + i);
        if(tmp == ','){
            *(arr + res) = str_to_int((s+j), i - j );
            j = i + 1;
            res++;
            if(res >= ARR_LEN){
                res = ARR_LEN;
                break;
            }
        }
        i++;
    }
    if(j < i){
        *(arr + res) = str_to_int((s+j), i - j);
        j = i + 1;
        res++;
    }
    if(res >= ARR_LEN){
        res = ARR_LEN;
    }
    return res;
}

int lget_int(const char *pid, const char *str){
    int id = 0;
    int rlen = 0;
    char *s = lget_str(pid, str, 0, &rlen);
    id = str_to_int(s, rlen);
    return id;
}

char* lget_str(const char *model, const char *str, const char symbol, int *rlen){
    // 双引号对比KEY
    // 第一个字符不匹配，直接跳到下一个逗号处，
    char pair = get_pair(symbol);
    char *res = (char *)str;
    *rlen = 0;
    int i = 0;
    int j = 0;
    int f = KEY_SEARCH; //
    int t = 0;
    int mlen = lstr_len(model);
    int slen = lstr_len(str);
    char tmp = *str;
    char mc = *model;
    char sc = *str;

    while(i < slen){
        char tmp = *(str + i);
        if(f == KEY_SEARCH){
            if(tmp == '\"'){
                j = 0;
                t = i + 1;
                f = KEY_EQUAL;
                while(j < mlen){
                    mc = *(model +j);
                    sc = *(str + t);
                    if(mc == sc){
                        j++;
                        t++;
                    }else{
                        f = KEY_SEARCH;
                        i += j;
                        break;
                    }
                }
                if(f == KEY_EQUAL){
                    if(*(str+t) == '\"'){
                        i += mlen + 3; // 
                        f = KEY_FOUND;
                    }else{
                        i += mlen + 1;
                        f = KEY_SEARCH;
                    }
                }else{
                    i++;
                }
            }else{
                i++;
            } 
        }else if(f == KEY_FOUND){
            if(symbol){
                if( tmp == symbol){
                    res = (char *)str + i + 1;
                    i++;
                    f = VALUE_SEARCH;
                }else{
                    f = KEY_SEARCH;
                    i++;
                }
            }else{
                res = (char *)str + i;
                f = VALUE_SEARCH;
            }
        }else if(f == VALUE_SEARCH){
            if(symbol){
                if(tmp == pair){
                    f = VALUE_FOUND;
                }else{
                    (*rlen)++;
                    i++;
                }
            }else{
                if(tmp == ','){
                    f = VALUE_FOUND;
                    break;
                }else{
                    (*rlen)++;
                    i++;
                }
            }        
        }else if(f == VALUE_FOUND){
            break;
        }
    }
    if(f != VALUE_FOUND){
        *rlen = 0;
    }
    return res;
}
