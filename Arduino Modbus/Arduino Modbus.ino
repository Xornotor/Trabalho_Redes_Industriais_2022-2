/* Trabalho Final - Redes Industriais 2022.2
 * Desenvolvido por:
 * André Paiva
 * Caroline Alves
 * Jeisiane
 * Pedro Augusto Correia
 */

// Definição de constrantes dos pinos utilizados
#define LED 13
#define BTN 8

#include <Modbus.h>
#include <ModbusSerial.h>

// Offset de registradores
const int LED_HREG = 100;
const int BTN_HREG = 108;

// Objeto ModbusSerial
ModbusSerial mb;

void setup() {
  // Configuração da comunicação Modbus Serial 
  mb.config(&Serial, 9600, SERIAL_8N1);

  // Configuração de ID
  mb.setSlaveId(4); 
    
  // Definição de pinos
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Configuração de registradores
  mb.addHreg(LED_HREG, 0);
  mb.addHreg(BTN_HREG, 0);
}

void loop() {
  // Chamada da task Modbus
  mb.task();
   
  // Rotina de atualização do LED
  if(mb.Hreg(LED_HREG) == 1){
    digitalWrite(LED, true);
  }else if(mb.Hreg(LED_HREG) == 0){
    digitalWrite(LED, false);
  }

  // Rotina de leitura do botão
  mb.Hreg(BTN_HREG, !digitalRead(BTN));
}