# APC_trabalho2_Kmeans

Código desenvolvido como parte da avaliação da disciplina Algoritmos e Programação de Computadores (113476) com o professor Vinícius Ruela Pereira Borges do departamento de Ciência da computação da Universidade de Brasília no primeiro semestre de 2018, desenvolvido pelo estudante Felipe Luís PInheiro.

Este programa tem por objetivo realizar um filtro em uma imagem digital, deixando-a com a aparencia de pixelada, pegando cores que possuem tonalidades semelhantes e tornando as em uma única cor, para tanto precisamos de uma imagem no formato PPM (Portable  PixelMap), sem comentarios ou descricóes dentro do arquivo para que seja feita a conversão. 

Segue exemplo de um arquivo ppm ideal 

P3
4 4
255
0 0 0 0 0 0 0 0 0 255 0 255
0 0 0 0 255 7 0 0 0 0 0 0
0 0 0 0 0 0 0 255 7 0 0 0
255 0 255 0 0 0 0 0 0 0 0 0

No caso da realizaçào do trabalho usamos o programa IrfanView (https://www.irfanview.com/) para convertermos uma imagem JPEG (Joint Photographics Experts Group) comum para o formato desejado, lembrando que o IrfanView adiciona um comentario na imagem, segue exemplo

P3
# Created by IrfanView
1024 751
255

que precisa ser retirado para que o programa funciona corretamente, ficando assim

P3
1024 751
255

para compilar e executar o programa em ambiente linux é necessário usar o compilador GCC e executar o comando

gcc main.c -lm -o main.o

a diretiva -lm é necessária para que se use link a biblioteca matemática durante a compilação e posteriormente execute o comando 

./main.o

dai é só seguir os comando dados na tela do programa. 