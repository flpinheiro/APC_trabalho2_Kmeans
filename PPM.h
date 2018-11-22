/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PPm.h
 * Author: flpin
 *
 * Created on 15 de Junho de 2018, 18:58
 */

#ifndef PPM_H
#define PPM_H

#ifdef __cplusplus
extern "C" {
#endif

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
    Pixel** alocaMatrizPixel(int linhas, int colunas);

    /**
     * @readPixel ler um pixel do teclado
     * @param p @pixel
     * @return @void
     */
    void readPixel(Pixel * p);

    /**
     * @readPixelFile ler um pixel de um arquivo
     * @param fp @FILE arquivo de onde sera lido o pixel
     * @param p @Pixel pixel no qual sera armazenado a informacao
     * @retrun @void
     */
    void readPixelFile(FILE * fp, Pixel * p);

    /**
     * @readMatrizPixelFIle ler uma matriz de pixel de um arquivo
     * @param fp @FILE arquivo de onde eh realizado a leitura
     * @param p @Pixel onde sera armazenado a informacao lida
     * @param linhas @int numero de linhas da matriz
     * @param colunas @int numero de colunas da matriz
     * @return @void
     */
    void readMatrizPixelFile(FILE * fp, Pixel ** p, int linhas, int colunas);

    /**
     * @readPPMFile ler um arquivo PPM inteiro
     * @param fp @FILE arquivo que sera efetuado a leitura
     * @param ppm @PPM onde sera armazenado a informacao
     * @retrun @void
     */
    void readPPMFile(FILE * fp, PPM * ppm);


    /**
     * @printPixel imprime um pixel em tela
     * @param p @Pixel pixel a ser impresso
     */
    void printPixel(Pixel p);

    /**
     * @printPixelFile imprime um pixel em arquivo
     * @param fp @file Arquivo no qual o pixel eh impresso
     * @param p @Pixel pixel a ser impresso
     */
    void printPixelFile(FILE * fp, Pixel p);

    /**
     * @printMatrizPixel imprime uma matriz de pixel inteira na tela
     * @param p @Pixel** matriz de pixel a ser impressa
     * @param linhas @int numero de linhas da matriz
     * @param colunas @int numer de colunas da matriz
     */
    void printMatrizPixel(Pixel ** p, int linhas, int colunas);

    /**
     * @printMatrizPixel imprime uma matriz de pixel inteira em arquivo
     * @param fp @FILE arquivo no qual a matriz eh impressa
     * @param p @Pixel** matriz de pixel a ser impressa
     * @param linhas @int numero de linhas da matriz
     * @param colunas @int numer de colunas da matriz
     */
    void printMatrizPixelFile(FILE * fp, Pixel ** p, int linhas, int colunas);

    /**
     * @printPPM imprime uma variavel @PPM inteira na tela
     * @param ppm @PPM variavel a ser impressa
     */
    void printPPM(PPM ppm);

    /**
     * @printPPMFile imprime uma variavel @PPM inteira em arquivo
     * @param fp @FILE arquivo no qual sera impresso
     * @param ppm @PPM variavel a ser impressa
     */
    void printPPMFile(FILE * fp, PPM ppm);

#ifdef __cplusplus
}
#endif

#endif /* PPM_H */

