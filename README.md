# Project Mutex Traffic Light

Description: 

Implementação em C de um simulador de cruzamento viário formado por quatro ruas. Cada via é equipada com um semáforo de trânsito, controlando o fluxo de veículos que tentam atravessar enquanto seguem as regras de trânsito.

As seguintes funcionalidades foram implementadas:

- Os semáforos alternam entre os estados de sinalização (verde, amarelo e vermelho) de acordo com o mundo real;
- Os carros são implementados com threads;
- A densidade do tráfego é decidida de forma aleatória, porém, no mínimo, cada simulação contém 2 carros em ruas diferentes;
- O simulador garante que apenas uma direção tenha o sinal verde em um determinado momento, evitando colisão entre os veículos;
- O simulador inclui uma visualização do seu funcionamento, de forma clara e compreensível. Igual ao demonstrado no arquivo example.c;
- Na visualização, foi implementado de forma que que cada carro seja identificado de forma única. Por exemplo, nomes como C1, C2, etc.;
- O número de ruas é fixado em 4.

