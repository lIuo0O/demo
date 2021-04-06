#ifndef __ESP8266_H
#define __ESP8266_H

code unsigned char http_head[] = "http://192.168.1.203:8001/";
code unsigned char log_url[] = "user/sign_in.do";
code unsigned char user[] = "";
code unsigned char passwd[] = "";

code unsigned char AT_CWMODE[] = "AT+CWMODE=3";
code unsigned char AT_CWJAP0[] = "AT+CWJAP=\"cy-technology\",\"87777830\"";
code unsigned char AT_CWJAP[] = "AT+CWJAP_DEF=\"cy-technology\",\"87777830\"";
code unsigned char AT_CIPSTART[] = "AT+CIPSTART=\"TCP\",\"192.168.1.203\",8001";
code unsigned char AT_CIPMODE[] = "AT+CIPMODE=";

code unsigned char AT_CIPSEND[] = "AT+CIPSEND";

code unsigned char AT_CIPCLOSE[] = "AT+CIPCLOSE";

code unsigned char AT_CIPEND[] = "+++";

code unsigned char AT_LINE[] = "\r\n"




#endif
