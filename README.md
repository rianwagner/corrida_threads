# Corrida de Threads

Este é um projeto simples em C que simula uma corrida entre várias threads. Cada thread avança aleatoriamente em direção à linha de chegada, e a ordem de chegada é registrada e exibida ao final.

## Funcionalidades
- Simulação de uma corrida com múltiplas threads.
- Uso de números aleatórios para determinar o progresso de cada thread.
- Sincronização entre threads utilizando **mutex**.
- Exibição da ordem de chegada.

## Requisitos
- Um compilador C, como **gcc**.
- Biblioteca **pthread** (normalmente já incluída em sistemas baseados em Linux).
- Make (opcional, mas recomendado para facilitar o processo de compilação).

## Como Compilar e Executar

### Com Makefile
1. Certifique-se de que o Makefile está na mesma pasta do arquivo `corrida_threads.c`.
2. Compile o programa:
   ```bash
   make
