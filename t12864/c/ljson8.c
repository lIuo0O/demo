#include "ljson.h"

char get_pair(const char symbol){
    if(symbol == '\"') return '\"';
    if(symbol == '(') return ')';
    if(symbol == '[') return ']';
    if(symbol == '{') return '}';
    return 0;
}

unsigned char lstr_len(const char *str){
    unsigned char res = 0;
    while(*(str + res) != '\0'){
        res++;
    }
    return res;
}

unsigned char str_to_int(char *s, unsigned char len){
    unsigned char res = 0;
    unsigned char i = 0;
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

unsigned char lget_arr(const char *model, const char *str, unsigned char *arr){
    unsigned char res = 0;
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char rlen = 0;
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

unsigned char lget_int(const char *pid, const char *str){
    unsigned char id = 0;
    unsigned char rlen = 0;
    char *s = lget_str(pid, str, 0, &rlen);
    id = str_to_int(s, rlen);
    return id;
}

char* lget_str(const char *model, const char *str, const char symbol, unsigned char *rlen){
    // 双引号对比KEY
    // 第一个字符不匹配，直接跳到下一个逗号处，
    char pair = get_pair(symbol);
    char *res = (char *)str;
    *rlen = 0;
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char f = KEY_SEARCH; //
    unsigned char t = 0;
    unsigned char mlen = lstr_len(model);
    unsigned char slen = lstr_len(str);
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
