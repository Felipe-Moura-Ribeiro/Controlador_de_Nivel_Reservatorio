# Controlador_de_Nivel_Reservatorio

Este é um projeto simples de um controlador de nível de reservatório utilizando um sensor de nível. O código implementa um controle através da discretização da função transferência do controlador para manter o nível do reservatório próximo a um valor de referência pré-determinado.

## 1.Hardware necessário
- Sensor de Nível (sensorNivel)
- Arduino
- Módulo Serial para comunicação

## 2.Bibliotecas utilizadas
sensorNivel: Uma biblioteca para interagir com o sensor de nível.

## 3.Média Móvel
Foi utilizado o filtro Média Móvel de ordem 4 a fim de reduzir os ruídos existentes na leitura do sensor ultrassônico.
