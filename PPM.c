/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PPM.c
 * Author: flpin
 *
 * Created on 15 de Junho de 2018, 19:00
 */

#include <stdio.h>
#include <stdlib.h>
#include "PPM.h"

/**
 * @struct color: define a strutura cor de @Pixel no formato RGB
 * @param @int red
 * @param @int green
 * @param @int blue
 */
struct color {
    int red, green, blue;
};

/**
 * @typedef @Pixel define o tipo Pixel
 */
typedef struct color Pixel;

/**
 * @struct @imagem define a estrutura imagem @PPM
 * @param @char codificacao
 * @param @int intensidade
 * @param @int linhas
 * @param @int colunas
 * @param @Pixel p
 */
struct imagem {
    char codificacao[10];
    int linhas, colunas, intensidade;
    Pixel ** p;
};

/**
 * @typedef @PPM define o tipo de dado PPM
 */
typedef struct imagem PPM;

/**
 * funcao @alocaMatrizPIxel aloca uma matriz de pixel de tamanho linhas X colunas
 * @param linhas @int numeros de linhas da matriz
 * @param colunas @int numero de colunas da matriz
 * @return @Pixel retorna uma matriz de pixel de tamanho linhas X colunas
 */
Pixel** alocaMatrizPixel(int linhas, int colunas) {

    /*declaracao de variaveis*/
    Pixel ** p;
    int i, j;

    /*aloca a memoria para as linhas*/
    p = (Pixel**) malloc(sizeof (Pixel*) * linhas);
    for (i = 0; i < linhas; i++) {
        /*aloca a memoria para as colunas*/
        p[i] = (Pixel*) malloc(sizeof (Pixel) * colunas);
        /*inicia todos os valores como zero*/
        for (j = 0; j < colunas; j++) {
            p[i][j].blue = 0;
            p[i][j].green = 0;
            p[i][j].red = 0;
        }
    }
    /*retorna o endereco da matriz de pixel*/
    return p;
}

/**
 * @readPixel ler um pixel do teclado
 * @param p @pixel
 * @return @void
 */
void readPixel(Pixel * p) {
    /*realiza a leitura*/
    scanf("%d %d %d", &(*p).red, &(*p).green, &(*p).blue);
    return;
}

/**
 * @readPixelFile ler um pixel de um arquivo
 * @param fp @FILE arquivo de onde sera lido o pixel
 * @param p @Pixel pixel no qual sera armazenado a informacao
 * @retrun @void
 */
void readPixelFile(FILE * fp, Pixel * p) {
    /*realiza a leitura*/
    fscanf(fp, "%d %d %d", &(*p).red, &(*p).green, &(*p).blue);
    return;
}

/**
 * @readMatrizPixelFIle ler uma matriz de pixel de um arquivo
 * @param fp @FILE arquivo de onde eh realizado a leitura
 * @param p @Pixel onde sera armazenado a informacao lida
 * @param linhas @int numero de linhas da matriz
 * @param colunas @int numero de colunas da matriz
 * @return @void
 */
void readMatrizPixelFile(FILE * fp, Pixel ** p, int linhas, int colunas) {
    /*declaracao de variaveis*/
    int i, j;

    /*realiza a leitura*/
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            /*ler pixel por pixel RGB*/
            readPixelFile(fp, &p[i][j]);
        }
    }

    /*retorna void*/
    return;
}

/**
 * @readPPMFile ler um arquivo PPM inteiro
 * @param fp @FILE arquivo que sera efetuado a leitura
 * @param ppm @PPM onde sera armazenado a informacao
 * @retrun @void
 */
void readPPMFile(FILE * fp, PPM * ppm) {
    /*ler a codificacao do arquivo*/
    fscanf(fp, "%s", &(*ppm).codificacao);

    /*ler o numero de linhas e colunas do arquivo*/
    fscanf(fp, "%d %d",&(*ppm).colunas, &(*ppm).linhas);

    /*ler a intensidade maxima do arquivo*/
    fscanf(fp, "%d", &(*ppm).intensidade);

    /*aloca a matriz de pixel*/
    (*ppm).p = alocaMatrizPixel((*ppm).linhas, (*ppm).colunas);

    /*realiza a leitura da matriz*/
    readMatrizPixelFile(fp, (*ppm).p, (*ppm).linhas, (*ppm).colunas);

    /*retorn void*/
    return;
}

/**
 * @printPixel imprime um pixel em tela
 * @param p @Pixel pixel a ser impresso
 */
void printPixel(Pixel p) {
    /*realiza a impressao*/
    printf("%d %d %d ", (p).red, (p).green, (p).blue);
    return;
}

/**
 * @printPixelFile imprime um pixel em arquivo
 * @param fp @file Arquivo no qual o pixel eh impresso
 * @param p @Pixel pixel a ser impresso
 */
void printPixelFile(FILE * fp, Pixel p) {
    /*realiza a impressao no arquivo*/
    fprintf(fp, "%d %d %d ", (p).red, (p).green, (p).blue);
    return;
}

/**
 * @printMatrizPixel imprime uma matriz de pixel inteira na tela
 * @param p @Pixel** matriz de pixel a ser impressa
 * @param linhas @int numero de linhas da matriz
 * @param colunas @int numer de colunas da matriz
 */
void printMatrizPixel(Pixel ** p, int linhas, int colunas) {
    /*declaracao de variaveis*/
    int i, j;

    /*realiza a impressao em arquivo*/
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printPixel(p[i][j]);
        }
        printf("\n");
    }
    return;
}

/**
 * @printMatrizPixel imprime uma matriz de pixel inteira em arquivo
 * @param fp @FILE arquivo no qual a matriz eh impressa
 * @param p @Pixel** matriz de pixel a ser impressa
 * @param linhas @int numero de linhas da matriz
 * @param colunas @int numer de colunas da matriz
 */
void printMatrizPixelFile(FILE * fp, Pixel ** p, int linhas, int colunas) {
    /*declaracao de variaveis*/
    int i, j;

    /*realiza a impressao*/
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printPixelFile(fp, p[i][j]);
        }
        fprintf(fp, "\n");
    }
    return;
}

/**
 * @printPPM imprime uma variavel @PPM inteira na tela
 * @param ppm @PPM variavel a ser impressa
 */
void printPPM(PPM ppm) {
    /*imprime a codificacao*/
    printf("%s\n", (ppm).codificacao);

    /*imprime o numero de linhas e colunas*/
    printf("%d %d\n", (ppm).colunas,(ppm).linhas);

    /*imprime a intensidade maxima*/
    printf("%d\n", (ppm).intensidade);

    /*imprime a matriz de pixel*/
    printMatrizPixel(ppm.p, ppm.linhas, ppm. colunas);
}

/**
 * @printPPMFile imprime uma variavel @PPM inteira em arquivo
 * @param fp @FILE arquivo no qual sera impresso
 * @param ppm @PPM variavel a ser impressa
 */
void printPPMFile(FILE * fp, PPM ppm) {
    /*imprime a codificacao*/
    fprintf(fp, "%s\n", (ppm).codificacao);

    /*imprime o numero de linhas e colunas*/
    fprintf(fp, "%d %d\n", (ppm).colunas,(ppm).linhas);

    /*imprime a intensidade maxima */
    fprintf(fp, "%d\n", (ppm).intensidade);

    /*imprime a matriz de pixel*/
    printMatrizPixelFile(fp, ppm.p, ppm.linhas, ppm. colunas);
}
