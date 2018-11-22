/* 
 * File:   main.c
 * Author: felipe pinheiro
 * Matricula: 18/0052667
 * Created on 14 de Junho de 2018, 18:00
 * projeto 2: Elabore um programa que leia uma imagem digital colorida (sob o 
 * formato Red-Blue-Green RGB) em disco e realize um processamento de forma a 
 * alterar suas cores, produzindo uma "arte" na imagem como ocorrem em alguns 
 * aplicativos em smartphones.
 */

/* declaracao de biblioteca */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * funcao alocaMatrizInt: aloca uma matriz
 * @param linhas: @int numero de linhas
 * @param colunas: @int numero de colunas
 * @return :@int** retorna o endereco da matriz alocada
 */
int** alocaMatrizInt(int linhas, int colunas) {

    /*declaracao de variaveis*/
    int i, j;
    int **matriz = (int**) malloc(linhas * sizeof (int*));

    /*corre palas linhas alocando a matriz*/
    for (i = 0; i < linhas; i++) {
        matriz[i] = (int*) malloc(colunas * sizeof (int));
        for (j = 0; j < colunas; j++) {
            /*inicia todos os elemtos da matriz com valor zero*/
            matriz[i][j] = 0;
        }
    }

    /*retorna a matriz*/
    return matriz;
}

/**
 * funcao @printMatrizInt: imprime a matriz
 * @param matriz: @int** matriz a ser impressa
 * @param linhas: @int numero de linhas
 * @param colunas: @int numero de colunas
 */
void printMatrizInt(int ** matriz, int linhas, int colunas) {
    /*declaracao de variaveis*/
    int i, j;

    /*percorre as linhas e colunas imprimindo a matriz*/
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    /*encerra a funcao*/
    return;
}

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
Pixel* alocaVetorPixel(int linhas) {

    /*declaracao de variaveis*/
    Pixel * p;
    int i;

    /*aloca a memoria para as linhas*/
    p = (Pixel*) malloc(sizeof (Pixel) * linhas);
    for (i = 0; i < linhas; i++) {
        /*aloca a memoria para as colunas*/
        p[i].red = 0;
        p[i].green = 0;
        p[i].blue = 0;
    }
    /*retorna o endereco da matriz de pixel*/
    //    printf("alocado %d\n", linhas);
    return p;
}

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
    fscanf(fp, "%d %d", &(*ppm).colunas, &(*ppm).linhas);

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
    printf("%d %d\n", (ppm).colunas, (ppm).linhas);

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
    fprintf(fp, "%d %d\n", (ppm).colunas, (ppm).linhas);

    /*imprime a intensidade maxima */
    fprintf(fp, "%d\n", (ppm).intensidade);

    /*imprime a matriz de pixel*/
    printMatrizPixelFile(fp, ppm.p, ppm.linhas, ppm. colunas);

    /* finaliza a funcao */
    return;
}

/**
 * @converte realiza a convercao de uma variavel @PPM seguindo o metodo K-means
 * ou K-medias.
 * @param ppm: imagem a ser processada.
 */
void converte(PPM * ppm, int T, int CENT_SIZE) {

    /**
     * @i: contador de linhas
     * @j: contador de colunas
     * @k: contador de centroide
     * @t: contador de itetacao
     * @rand_x: numero aleatorio associado a iniciacao do centroide
     * @rand_y: numero aleatorio associado a iniciacao do centroide
     * @class**: matriz de classe para os pixel, do mesmo tamanho de @ppm
     * @T: numero de iteracao
     * @cont: contador
     */
    int i, j, k, t, rand_x, rand_y, **class, cont;

    /* iniciacao da matriz de classe dos pixel para cada centroide*/
    class = alocaMatrizInt(ppm->linhas, ppm->colunas);

    /**
     * @cent: centroide
     */
    Pixel * cent;
    /* iniciacao do centroide */
    cent = alocaVetorPixel(CENT_SIZE);

    /**
     * @dist: distancia do pixel ao centroide
     * @red: distancia do pixel ao centroide parte vermelhar
     * @green: distancia do pixel ao centroide parte verde
     * @blue: distancia do pixel ao centroide parte azul
     * @test_class: serve para verificar qual o pixel mais perto
     */
    float dist, red, blue, green, test_class;

    /* inicia a semente da variavel aleatoria */
    srand(time(0));

    /* crio o centroide aleatoriamente*/
    for (k = 0; k < CENT_SIZE; k++) {
        /* escolhe aleatoriamente as componente x e y da imagem */
        rand_x = (rand() % ppm->linhas);
        rand_y = (rand() % ppm->colunas);

        /* salva os dados das componentes x e y escolhidas para o centroide */
        cent[k].blue = ppm->p[rand_x][rand_y].blue;
        cent[k].green = ppm->p[rand_x][rand_y].green;
        cent[k].red = ppm->p[rand_x][rand_y].red;
    }

    /*rodo a matriz inteira e mais o centroide*/
    for (t = 0; t < T; t++) {
        printf("porcentagem concluida %.2f %%\n", (float) t * 100 / T);
        /*corre a amatriz nas linhas */
        for (i = 0; i < ppm->linhas; i++) {
            /* corre a matriz nas colunas */
            for (j = 0; j < ppm->colunas; j++) {
                /* teste de verificacao da classe do centroide */
                test_class = -1;
                /* corre o centroide */
                for (k = 0; k < CENT_SIZE; k++) {
                    /* calcula a distancia do pixel ao centroide */
                    /* distancia da componente vermelha */
                    red = ppm->p[i][j].red - cent[k].red;
                    /* distancia da componente verde */
                    green = ppm->p[i][j].green - cent[k].green;
                    /* distancia da componente azul */
                    blue = ppm->p[i][j].blue - cent[k].blue;
                    /* distancia final */
                    dist = sqrt(red * red + green * green + blue * blue);
                    /* verifica a classe do centroide */
                    if (test_class == -1) {
                        test_class = dist;
                        class[i][j] = k;
                    }
                    if (test_class > dist) {
                        test_class = dist;
                        class[i][j] = k;
                    }
                }
            }
        }

        /* atulaiza o centroide */
        for (k = 0; k < CENT_SIZE; k++) {
            /* inicia as variaveis @red, @green, @blue, @cont como zero para serem usados */
            red = 0;
            green = 0;
            blue = 0;
            cont = 0;

            /* percorre toda a matriz de class verificando qual pixel eh de qual classe */
            for (i = 0; i < ppm->linhas; i++) {
                for (j = 0; j < ppm->colunas; j++) {
                    /* verifica qual pixel pertence a classe k */
                    if (class[i][j] == k) {
                        /* soma os valores para calculo de media */
                        red += ppm->p[i][j].red;
                        green += ppm->p[i][j].green;
                        blue += ppm->p[i][j].blue;
                        cont++;
                    }
                }
            }

            /* 
             * calcula a media inteira e verifica se ficaram maior do que o maximo 
             * permitido, caso positivo ficam igual ao maximo e atualiza o valor 
             * do centroide 
             */
            red /= cont;
            if (red > ppm->intensidade) {
                red = ppm->intensidade;
            }
            cent[k].red = red;
            green /= cont;
            if (green > ppm->intensidade) {
                green = ppm->intensidade;
            }
            cent[k].green = green;
            blue /= cont;
            if (blue > ppm->intensidade) {
                blue = ppm->intensidade;
            }
            cent[k].blue = blue;
        }

        /* imprime a porcentagem concluida */

    }

    /*atualizo a imagem*/

    for (i = 0; i < ppm->linhas; i++) {
        for (j = 0; j < ppm->colunas; j++) {
            ppm->p[i][j].red = cent[class[i][j]].red;
            ppm->p[i][j].green = cent[class[i][j]].green;
            ppm->p[i][j].blue = cent[class[i][j]].blue;
        }
    }

    /* imprime */
    printf("porcentagem concluida 100 %%\n");

    //    printMatrizInt(class, ppm->linhas, ppm->colunas);

    free(class);
    free(cent);
    return;
}

/*funcao de test - sera inutil apos a conclusao do programa*/
int test() {

    /* abre os arquivos de entreda = teste.ppm e saida = saida.ppm */
    FILE * fp = fopen("saida.ppm", "w");
    FILE * fp2 = fopen("teste.ppm", "r");

    /* inicia a variavel ppm */
    PPM ppm;

    /* ler o arquivo e armazena em ppm */
    readPPMFile(fp2, &ppm);

    /* realiza a conversao */
    converte(&ppm, 15, 5);

    /* esccreve o resultado final no arquivo de saida */
    printPPMFile(fp, ppm);

    /* fecha os arquivos */
    fclose(fp);
    fclose(fp2);

    /* finaliza o teste do programa com sucesso */
    return 0;
}

int teste2() {
    int i = 10;
    char str[100];

    FILE *fp = fopen("natureza.ppm", "r");

    PPM ppm;

    readPPMFile(fp, &ppm);
    converte(&ppm, i, 5);
    sprintf(str, "natureza T = %d.ppm", i);

    FILE * fp2;
    fp2 = fopen(str, "w");
    printPPMFile(fp2, ppm);

    fclose(fp2);
    fclose(fp);

    return 0;
}

/*
 * funcao mains
 */
int main(void) {

    /* chamada da funcao de teste - esse trecho de codigo deve ser comentado para o usuario final*/
    //    if (!teste2()) {
    //        return 0;
    //    }

    /*
     * @opcao: verifica qual eh a opcao escolhida pelo usuario
     */
    int opcao, T = 1, cent;

    /*
     * @ppm variavel de dados a ser trabalhada pelo programa
     */
    PPM ppm;
    /*
     * @nomeArquivo nome do arquivo a ser aberto pelo programa
     */
    char nomeArquivo[101];

    do {
        /*
         * lista de opcoes do programa
         */

        /* ler em arquivo se for inserido 1 em opcao */
        printf("Digite: 1 para ler um arquivo.\n");
        /* precessa a imagem se for inserido 2 em opcao */
        printf("Digite: 2 para processar a imgagem.\n");
        /* salva o arquivo se for inserido 3 em opcao*/
        printf("Digite: 3 para salvar o arquivo em disco.\n");
        /*finaliza a execucao do programa se for inserido 0 em opcao*/
        printf("digite: 0 para encerrar o programa\n");
        printf("\n\nOpcao: ");

        /* recebe a resposta do usuario */
        scanf("%d", &opcao);
        getchar();
        printf("\n\n");

        /* abre o arquivo */
        if (opcao == 1) {
            /*
             * @fp; ponteiro para o arquivo de nome @nomeArquivo 
             */
            FILE * fp;
            /* pede para o usuario entrar com o nome do arquivo a ser aberto */
            printf("Digite o nome do arquivo a ser aberto: ");
            scanf("%[^\n]s", &nomeArquivo);
            getchar();
            /* abre o arquivo */
            fp = fopen(nomeArquivo, "r");
            /* verifica se o arquivo foi aberto com sucesso */
            if (fp == NULL) {
                /* retorna erro caso nao pode abri e pede para abrir novamente */
                printf("ERRO: problema para abrir o arquivo \nVerifique e tente novamente.\n");
            } else {
                /* retorna sucesso caso tenha sido aberto com sucesso */
                printf("Arquivo aberto com sucesso\n");
                /* ler o arquivo ppm */
                readPPMFile(fp, &ppm);

                /* fecha o arquivo aberto para leitura */
                fclose(fp);
            }
        }

        if (opcao == 2) {
            /* realiza a conversao */
            printf("Entre com um valor para a quantidade de cores, dica use valores pequenos: ");
            scanf("%d", &cent);
            getchar();
            converte(&ppm, T, cent);
        }

        /* salca o arquivo */
        if (opcao == 3) {

            /* pede para o usuario entrar com o nome do arquivo a ser salvo */
            printf("Digite o nome do arquivo para salvar: ");
            scanf("%[^\n]s", &nomeArquivo);
            getchar();

            /* abre o arquivo para salvar */
            FILE * fp = fopen(nomeArquivo, "w");

            /* verifica se o arquivo foi aberto */
            if (fp == NULL) {
                /* caso negativo retorna uma mensagem de erro e pede para repetir execucao */
                printf("ERRO: arquivo nao pode ser aberto.\ntente de novo\n");
            } else {
                /* caso positivo retorna mensagem de sucesso e continua execucao */
                printPPMFile(fp, ppm);
                fclose(fp);
                printf("Aruivo salvo com sucesso.\n");
            }
        }

        /* verifica qual eh a escolha do usuario */
    } while (opcao != 0);

    /* finaliza o programa com sucesso */
    printf("Obrigado e volte sempre\n");
    return 0;
}
