# **CONVERSORES A/D NO RP2040**

Está contido neste repositório o diagrama, código-fonte e demais arquivos referentes a segunda parte da última Prática de Laboratório da matéria de Microcontroladores e Microprocessadores.

## **OBJETIVO**

Este projeto tem como objetivo o controle das cores de um LED RGB através de um joystick analôgico com conversores A/D, utilizando um Raspberry Pi Pico W e ferramentas de simulação virtual.

## **COMPONENTES UTILIZADOS**

- Microcontrolador Raspberry Pi Pico W;
- Joystick: Conectado às GPIOS 26 e 27.
- Botão do Joystick: Conectado à GPIO 22.
- LED RGB: Pinos conectados às GPIOs 12, 13 e 14.

## **FUNCIONALIDADES IMPLEMENTADAS**

1. Controle dos LEDs RGB via Joystick:  
- LED Verde: Brilho ajustado pelo eixo X do joystick.  
  - Posição central (2048): LED apagado.  
  - Movimento para esquerda ou direita: aumento gradual do brilho, atingindo o máximo nos extremos (0 e 4095).  
- LED Azul: Brilho ajustado pelo eixo Y do joystick.  
  - Posição central (2048): LED apagado.  
  - Movimento para cima ou baixo: aumento gradual do brilho, atingindo o máximo nos extremos (0 e 4095).  
- LED Vermelho: Acionamento ajustado pelo botão do joystick.
  - Botão acionado: LED ligado.
  - Botão desacionado: LED desligado.

2. Possíveis combinações de cores:  
- Com os ajustes do joystick pelos eixos X e Y e pelo acionamento e desacionamento do botão interno podem ser obtidas diversas combinação de cores, são essas:
  - VERDE: Eixo Y: 2048
           Eixo X: 0 ou 4095
           Botão: OFF
  - AZUL:  Eixo Y: 0 ou 4095
           Eixo X: 2048
           Botão: OFF
  - VERMELHO: Eixo Y: 2048
              Eixo X: 2048
              Botão: ON
  - CIANO: Eixo Y: 0 ou 4095
           Eixo X: 0 ou 4095
           Botão: OFF
  - AMARELO: Eixo Y: 2048
             Eixo X: 0 ou 4095
             Botão: ON
  - ROXO:  Eixo Y: 0 ou 4095
           Eixo X: 2048
           Botão: ON
  - BRANCO: Eixo Y: 0 ou 4095
            Eixo X: 0 ou 4095
            Botão: ON

## Organização da Equipe
- **Líder de Projeto: João Victor Guimarães** 
- **Desenvolvedor 1: Ryan Farias** 
- **Desenvolvedor 2: João Victor Teixeira Slva** 

---

## **VÍDEO EXPLICATIVO**

https://drive.google.com/file/d/1YDv92Qj4lw9x-DuUibWfgMvHdtY2YeqE/view?usp=drive_link

## Licença
Este projeto é destinado exclusivamente para fins acadêmicos na disciplina **ELET0021 — Microcontroladores e Microprocessadores**.

---
