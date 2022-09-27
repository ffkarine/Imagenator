# TO DO LIST

- [x] ~~Fazer o GLFW e GLUT funcionarem no projeto~~
- [x] ~~Criar um repositório pro projeto~~
- [x] ~~Criar uma To Do List~~
- [x] Já fizemo bastante coisa po
- [ ] FAZER A DOCUMENTAÇÃO (E A APRESENTAÇÃO):

    a) ~~Diagrama de Classes;~~
    
    b) Diagrama de fluxo de software;
    
    c) features do programa (basicamente os requisitos que ele pediu);
    

# REQUISITOS
- [x] ~~Permitir ao usuário escolher no mínimo as seguintes figuras geométricas planas regulares a serem desenhadas: Triângulo, Quadrado, Hexágono.~~
- [x] ~~Permitir ao usuário digitar as coordenadas dos vértices de cada figura. Neste caso, os polígonos a serem desenhados poderão ser irregulares.~~
- [x] ~~Permitir ao usuário utilizar cliques de mouse para determinar os vértices e/ou o centro de cada figura, no caso de polígonos irregulares.~~

- [x] ~~Permitir ao usuário digitar o ponto central e o tamanho da aresta (borda) de cada polígono. Neste caso os polígonos desenhados serão regulares.~~ 

``` diff
+Feito. Parabén Karine</span>
```
- [x] ~~Desenhar a figura na tela conforme parâmetros de entrada fornecidos pelo usuário (requisitos R1 a R4). Suportar o desenho e visualização de no mínimo 5 figuras simultaneamente.~~

- [x] ~~Permitir escolher qualquer uma das seguintes TGs, a serem realizadas sobre uma figura já desenhada: Translação, Escala, Rotação, Reflexão, Cisalhamento~~
- [x] ~~Conforme a TG escolhida, solicitar ao usuário os parâmetros correspondentes e necessários para realizar a transformação. O usuário deverá poder escolher os parâmetros livremente por digitação (proibido fixar os parâmetros no programa). 
As seguintes funcionalidades devem ser implementadas para cada TG:~~

    a) ~~Translação: permitir a translação positiva ou negativa em qualquer direção a  escolha do usuário (eixo x, o eixo y).~~

    b) ~~Escala: permitir aumentar e permitir reduzir o objeto.~~

    c) ~~Reflexão: permitir fazer a reflexão em relação ao eixo x e em relação ao eixo y~~.

    d) ~~Rotação: permitir escolher o ângulo de rotação, que deve ser indicado em graus, podendo ser positivo ou negativo. A figura deve ser rotacionada na mesma posição em que se encontra (ver requisito R8 para mais detalhes).~~

    e) ~~Cisalhamento: permitir escolher uma proporção da figura para gerar o cisalhamento (ex: 10%, 20%, etc).~~ 

- [x] ~~Somente a transformação solicitada pelo usuário deve ser aplicada a cada vez e mostrada ao usuário (o programa pode fazer mais transformações em segundo plano, mas para o usuário somente uma irá aparecer a cada operação). 
No caso específico da rotação, a figura deve ser rotacionada sobre o mesmo “local” onde se encontra. Ao aplicar a rotação, sugere-se utilizar a seguinte técnica:~~

  ~~Passo 1: Transladar o objeto (pelo centro deste) para a origem do sistema de coordenadas.~~

  ~~Passo 2: Rotacionar o objeto (pelo centro deste).~~

  ~~Passo 3: Transladar o objeto (pelo centro deste) de volta para o seu local original.~~

- [x] ~~Após confirmação do usuário o programa deve aplicar a TG escolhida conforme os parâmetros informados (R5, R6 e R7), e mostrar o resultado na tela.~~
- [x] ~~Desenhar um sistema de referência na tela de visualização, com escala indicativa das distâncias, com as seguintes características:~~

    ~~a) Centralizar o ponto central de coordenadas no centro da tela de visualização.~~

    ~~b) Deve mostrar um eixo de coordenadas x (linha contínua)~~

    ~~c) Deve mostrar um eixo de coordenadas y (linha contínua)~~

    ~~d) Dividir os eixos x e y em 10 segmentos positivos e 10 segmentos negativos, e criar pequenas marcações (um pequeno tracinho) para sinalizar cada divisão.~~

```diff
+Parabéns Karine!
```

- [ ] Permitir ao usuário alternar livremente entre telas de desenho e de entrada de parâmetros.
  
```diff
!acredito que seja simples.
!Tem que corrigir o bloqueio da tela aqui (quando o prompt está esperando por um input do usuário)
``` 

- [x] ~~Permitir apagar os polígonos desenhados e redesenhar outros polígonos ou usar outras opções (aplicar mais de uma transformação por exemplo) sem sair do programa.~~

- [x] ~~Validar as coordenadas de entrada conforme segue:~~

    a) ~~As coordenadas devem estar dentro dos limites do sistema de coordenadas do universo (da tela);~~
    
    b) ~~Não permitir a entrada de pontos repetidos (iguais).~~
    
    c) ~~Permitir o desenho de polígonos convexos ou côncavos para figuras irregulares.~~

```diff
!só falta fazer p/ o mouse input
```
