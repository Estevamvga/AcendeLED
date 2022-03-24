#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <Ethernet.h> //INCLUSÃO DE BIBLIOTECA

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x14 }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ETHERNET SHIELD W5100
byte ip[] = { 192, 168, 0, 15 }; //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110  **** ISSO VARIA, NO MEU CASO É: 192.168.0.175
byte gateway[] = {192, 168, 0, 1}; //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
byte subnet[] = {255, 255, 255, 0}; //MASCARA DE REDE (ALTERE PARA A SUA MÁSCARA DE REDE)
EthernetServer server(80); //PORTA EM QUE A CONEXÃO SERÁ FEITA

const int ledPin1 = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;
String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status1 = 0; //DECLARAÇÃO DE VARIÁVEL DO TIPO INTEIRA(SERÁ RESPONSÁVEL POR VERIFICAR O STATUS ATUAL DO LED)
int status2 = 0;
int status3 = 0;

void setup(){
  Ethernet.begin(mac, ip, gateway, subnet); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE
  server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA 80
  pinMode(ledPin1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(ledPin1, LOW);
  pinMode(ledPin2, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(ledPin2, LOW);
  pinMode(ledPin2, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(ledPin2, LOW);//LED INICIA DESLIGADO
  }
void loop(){
EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE, FAZ
    while (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
   if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
    char c = client.read(); //LÊ CARACTERE A CARACTERE DA REQUISIÇÃO HTTP
    if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
      {
        readString += c; // "readstring" VAI RECEBER OS CARACTERES LIDO
      }  
        if (c == '\n') { //SE ENCONTRAR "\n" É O FINAL DO CABEÇALHO DA REQUISIÇÃO HTTP
          if (readString.indexOf("?") <0){ //SE ENCONTRAR O CARACTER "?", FAZ
          }
          else{ //SENÃO,FAZ
        if(readString.indexOf("led1Param=1") >0) //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ
           {
             digitalWrite(ledPin1, HIGH); //LIGA O LED
             status1 = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
           }
        else if(readString.indexOf("led1Param=0") >0){
          digitalWrite(ledPin1, LOW);
          status1 = 0;
          }
        else if(readString.indexOf("led2Param=1") >0) //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ
           {
             digitalWrite(ledPin2, HIGH); //LIGA O LED
             status2 = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
           }
        else if(readString.indexOf("led3Param=1") >0) //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ
           {
             digitalWrite(ledPin3, HIGH); //LIGA O LED
             status3 = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
           }
        else if(readString.indexOf("led2Param=0") >0){
          digitalWrite(ledPin2, LOW);
          status2 = 0;
          }
        else if(readString.indexOf("led3Param=0") >0){
          digitalWrite(ledPin3, LOW);
          status3 = 0;
          }
          }
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println("");
          client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
          client.println("<html>"); //ABRE A TAG "html"
          client.println("<head>"); //ABRE A TAG "head"
          client.println("<link rel='icon' type='image/png' href='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/logo_mws.png'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
          client.println("<title>MasterWalker Shop - Controle de Led via Web server</title>"); //ESCREVE O TEXTO NA PÁGINA
          client.println("</head>"); //FECHA A TAG "head"
          client.println("<body style=background-color:#ADD8E6>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<center><font color='blue'><h1>MASTERWALKER SHOP</font></center></h1>"); //ESCREVE "MASTERWALKER SHOP" EM COR AZUL NA PÁGINA
          client.println("<h1><center>CONTROLE DE LED</center></h1>"); //ESCREVE "CONTROLE DE LED" NA PÁGINA
          if (status1 == 1){
          client.println("<center><form method=get name=LED><input type=hidden name=led1Param value=0 /><input type=submit value=APAGAR></form></center>");
          }else if(status1 == 0){
          client.println("<center><form method=get name=LED><input type=hidden name=led1Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          if (status1 == 1){ //SE VARIÁVEL FOR IGUAL A 1, FAZ
              client.println("<center><font color='green' size='5'>Status atual do LED: LIGADO</center>"); //ESCREVE "LIGADO" EM COR VERDE NA PÁGINA
          }else if(status1 == 0){ //SENÃO, FAZ
              client.println("<center><font color='red' size='5'>Status atual do LED: DESLIGADO</center>"); //ESCREVE "DESLIGADO" EM COR VERMELHA NA PÁGINA
          }
          if (status2 == 1){
          client.println("<center><form method=get name=LED><input type=hidden name=led2Param value=0 /><input type=submit value=APAGAR></form></center>");
          }else if(status2 == 0){
          client.println("<center><form method=get name=LED><input type=hidden name=led2Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          if (status2 == 1){ //SE VARIÁVEL FOR IGUAL A 1, FAZ
              client.println("<center><font color='green' size='5'>Status atual do LED: LIGADO</center>"); //ESCREVE "LIGADO" EM COR VERDE NA PÁGINA
          }else if(status2 == 0){ //SENÃO, FAZ
              client.println("<center><font color='red' size='5'>Status atual do LED: DESLIGADO</center>"); //ESCREVE "DESLIGADO" EM COR VERMELHA NA PÁGINA
          }
          if (status3 == 1){
          client.println("<center><form method=get name=LED><input type=hidden name=led3Param value=0 /><input type=submit value=APAGAR></form></center>");
          }else if(status3 == 0){
          client.println("<center><form method=get name=LED><input type=hidden name=led3Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          if (status3 == 1){ //SE VARIÁVEL FOR IGUAL A 1, FAZ
              client.println("<center><font color='green' size='5'>Status atual do LED: LIGADO</center>"); //ESCREVE "LIGADO" EM COR VERDE NA PÁGINA
          }else if(status3 == 0){ //SENÃO, FAZ
              client.println("<center><font color='red' size='5'>Status atual do LED: DESLIGADO</center>"); //ESCREVE "DESLIGADO" EM COR VERMELHA NA PÁGINA
          }
          //client.println("<center><font size='5'>Status atual do LED: </center>"); //ESCREVE "Status atual do LED:" NA PÁGINA
          
          client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("</body>"); //FECHA A TAG "body"
          client.println("</html>"); //FECHA A TAG "html"
          readString=""; //A VARIÁVEL É REINICIALIZADA
          client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
            }
          }
        }
      }
 }
