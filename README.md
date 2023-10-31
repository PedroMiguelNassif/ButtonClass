[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/NStx7FZc)
# 1ELE911-23-SEM4-ADC-XY-DMA
Aquisição do sinal analógico de dois potenciômetros referentes aos eixos de um joystick.

Os sinais de dois potenciômetros referentes aos eixos X e Y de um joystick analógico devem ser adquiridos pelas portas AN0 e AN1 do ADC1, respectivamente.

O ADC1 deve operar no modo regular. A aquisição deve ser disparada através do sinal TRGO da TIM2, gerado a cada update event do timer principal (Overflow). Deste modo, o TIM2 controla a taxa de amostragem do ADC.

A cada disparo recebido, o ADC1 deve ler os canais AN0 e AN1 consecutivamente e os resultados devem ser transferidos através de um canal de DMA para um vetor na memória. Ao final da sequência de aquisição dos dois canais, uma interrupção de fim de conversão deve ser gerada informando que os dados estão prontos.

Os dados na memória devem ser armazenados em complemento de dois, onde o centro do joystick deve gerar o valor 0x000 em ambos os eixos. Com o joystick totalmente para a direita, o valor adquirido deve ser de 0x07FF (maior valor positivo em 12 bits). Com o joystick para a esquerda, o valor deve ser de 0x0800 (menor valor negativo em 12 bits). O mesmo vale para o potenciômetro do eixo Y (para cima terá valores positivos e para baixo terá valores negativos).

Mostre os valores de ambos os eixos em um gráfico usando a janela de "live variables" da ferramenta de debugação.
