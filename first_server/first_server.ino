/*---------------- 1 часть ----------------*/ 
#include "SPI.h" //библиотека для работы с SPI 
#include "Ethernet.h" //библиотека для работы с Ethernet 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
//вводим mac адрес, обычно он такого вида, может отличаться 
IPAddress ip(192, 168, 88, 223); 
//вводим любой IP , который не совпадает с вашим 
EthernetServer server(80); //инифиализация библиотеки Ethernet server library 

/*---------------- 2 часть ----------------*/ 
void setup() { 
pinMode (13, OUTPUT);//инициализируем 8 пин как выход для светодиода 
Ethernet.begin (mac, ip);//запускаем сервер с указанными ранее MAC и вашим IP 
Serial.begin (9600); 
server. begin(); 
} 

/*---------------- 3 часть ----------------*/ 
void loop() { 
  EthernetClient client = server.available(); //принимаем данные, посылаемые клиентом 
  Serial.println("server available");
  if (client){ //если запрос оканчивается пустой строкой 
    boolean currentLineIsBlank = true; 
    //char c = "";
    while (client.connected()) { //пока есть соединение с клиентом 
      if (client.available()) { //если клиент активен 
        char c = client.read(); //считываем посылаемую информацию в переменную "с" 
        
        
        if (c == '\n') { //если "с" равен символу новой строки
          currentLineIsBlank = true; //то начинаем новую строку 
          }
          else if (c != '\r') { //иначе, если "с" не равен символу возврата курсора на начало строки 
            currentLineIsBlank = false; //то получаем символ на текущей строке 
            }
            if (c == '\n' && currentLineIsBlank) { //выводим HTML страницу 

/*---------------- 4 часть ----------------*/ 
client. println ("HTTP/1.1 200 OK"); //заголовочная информация 
client. println ("Content-Type: text/html"); 
client. println ("Connection: close"); 
client. println ("Refresh: 5"); //автоматическое обновление каждые 5 сек 
client. println (); //Это не ошибка, так должно быть 
client. println ("<!DOCTYPE HTML>"); //HTML тип документа 
client. println ("<html>"); //открытие тега HTML 
client. println ("<head> "); //открытие тега Head 
client. println ("<meta http-equiv='Content-Type' content='text/html ; charset=utf-8'/> "); 
client. print ("<title>HelpDuino Web Server</title>"); //название страницы 
client. println ("</head>"); //заголовочная информация 
client. println ("<body>"); 
client. print ("<H1>HelpDuino Web Server</H1>"); //заголовк на странице 
client. println ("<br> "); //перенос на след. строчку 
client. println ("<hr/>"); //линия===================================== 
client. println ("</body>"); 
client. println ("</html>"); //закрываем тег HTML 
break; //выход 
} 
}
} 
 
delay (1); //время на получение новых данных 
client. stop(); //закрываем соеднение 
} 
}
