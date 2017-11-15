Código para controlar o robô usado na competição de robótica RFC, usando o NodeMCU(esp8266).

O Esp funciona como um servidor, criando uma rede wifi, recebendo dados do cliente que foi implementado usando o QT Creator, e pode ser usado tanto no smartphone quanto em qualquer computador, e a partir dos dados recebidos, controla as direções que o robô deve seguir, enviando sinais nas suas portas de propósito geral, que através da circuitaria desenvolvida na matéria de eletrônica de potência, faz com que o robô seja controlado remotamente.

O código foi desenvolvido baseado na biblioteca nativa para c++ do esp8266.

Mapeamento das portas:
D1 = + (Motor 1 pra frente)
D2 = - (Motor 1 pra trás)
D3 = - (Motor 2 pra trás)
D4 = + (Motor 2 pra frente)

Will Douglas. 
