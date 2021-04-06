#ifndef  __LJSON8_H
#define  __LJSON8_H

#define     KEY_SEARCH     0x00
#define     KEY_EQUAL      0x01
#define     KEY_FOUND      0x02
#define     VALUE_SEARCH   0x03
#define     VALUE_FOUND    0x04
#define     ARR_LEN        0x0c


int lstr_len(const char *str);
int str_to_int(char *s, unsigned char len);
char* lget_str(const char *model, const char *str, const char symbol, unsigned char *rlen);
int lget_int(const char *model, const char *str);
int lget_arr(const char *model, const char *str, unsigned char *arr);
char get_pair(const char symbol);


#endif
