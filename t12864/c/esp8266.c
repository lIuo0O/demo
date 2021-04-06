#include "esp8266.h"
#include "uart.h"


code unsigned char http_head = "http://192.168.1.203:8001/";
#define HTTP_HEAD_LEN           0x1b
code unsigned char log_url[] = "akey/sign_in.do";
#define LOG_URL_LEN             0x0e
code unsigned char user[] = "";
code unsigned char passwd[] = "";


code unsigned char AT_AT[] = "AT";
#define  AT_CWMODE_LEN          0x02
code unsigned char AT_CWMODE[] = "AT+CWMODE=3";
#define  AT_CWMODE_LEN          0x0b

code unsigned char AT_CWJAP[] = "AT+CWJAP=\"CY-WIFI\",\"87777830\"";
code unsigned char AT_CIPSTART[] = "AT+CIPSTART=\"TCP\",\"192.168.1.203\",8001";
code unsigned char AT_CIPMODE[] = "AT+CIPMODE=";

code unsigned char AT_CIPSEND[] = "AT+CIPSEND";

code unsigned char AT_CIPCLOSE[] = "AT+CIPCLOSE";

code unsigned char AT_CIPEND[] = "+++";

code unsigned char AT_LINE[] = "\r\n"

/*
unsigned char strcmp(unsigned char *s, unsigned char *m, unsigned char len){
    unsigned char i = 0;
    while(i < len){
        if(*(s+i) != *(m+i)){
            return 0;
        }
        i++;
    }
    return 0;
}


unsigned char send_cmd(unsigned char *s, unsigned char s_len){
    
}
*/
unsigned char check_at_on(void){
    write_str(&(AT_AT[0]), AT_CWMODE_LEN);
    write_str(&(AL_LINE[0]), AT_LINE_LEN);
    read_str();
    if(uart.rx_buffer[][] != ) return 1;
    return 0;

}
unsigned char set_wifi_mode(void){
    write_str(&(AT_CWMODE[0]), AT_CWMODE_LEN);
    write_str(&(AL_LINE[0]), AT_LINE_LEN);
    read_str();
    if(uart.rx_buffer[][] != ) return 1;
    return 0;
}

unsigned char connect_wifi(void){
    write_str(&(AT_CWJAP[0]), AT_CWJAP_LEN);
    write_str(&(AL_LINE[0]), AT_LINE_LEN);
    read_str();
    if(uart.rx_buffer[][] != ) return 1;
    return 0;
}

unsigned char set_tcp_connect(void){
    
}

void sign_in(void){

}

void get_error(void){
    
}
