/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/* Funções auxiliares para o 1o trabalho da disciplina CSF13 (Fundamentos de
 * Programação 1), 2023-1, prof. Bogdan T. Nassu, Universidade Tecnológica
 * Federal do Paraná. */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "trabalho1.h"
#include "imagem.h"

/*============================================================================*/
/* Estas variáveis são globais somente para isolar parte do trabalho dos alunos (evita o uso de ponteiros para structs por eles). */

Imagem1C* img = NULL; // Imagem de entrada (codificação) ou saída (decodificação).
int linha_atual; // Linha atual na imagem.
int coluna_atual; // Coluna atual na imagem.
FILE* stream_rbd = NULL; // Stream de entrada (decodificação) ou saída (codificação).

/*============================================================================*/
/* Cria "streams simulados" para codificar - a entrada é simplesmente uma
 * imagem com uma posição associada, a saída é simplesmente um arquivo. */

void criaStreamsCod (char* arquivo_img, char* arquivo_rbd)
{
    unsigned int tam_imagem;

    /* Abre a imagem. */
    img = abreImagem1C (arquivo_img);
    if (!img)
    {
        printf ("Erro abrindo imagem %s\n", arquivo_img);
        exit (1);
    }

    /* Aponta para o início. */
    linha_atual = 0;
    coluna_atual = 0;

    /* Abre o arquivo para mandar os dados codificados. */
    stream_rbd = fopen (arquivo_rbd, "wb");
    if (!stream_rbd)
    {
        printf ("Erro abrindo arquivo %s\n", arquivo_rbd);
        exit (1);
    }

    /* Já coloca nas 2 primeiras posições do arquivo o tamanho da imagem. */
    /* Usamos 2 bytes para a altura e 2 bytes para a largura. */
    if (img->altura > 0xFFFF || img->largura > 0xFFFF)
    {
        printf ("A imagem não deve ter mais do que %d linhas/colunas (tem %lu linhas e %lu colunas).\n", 0xFFFF, img->altura, img->largura);
        exit (1);
    }

    tam_imagem = (img->altura << 16) | img->largura;
    fwrite (&tam_imagem, 1, 4, stream_rbd);
}

/*----------------------------------------------------------------------------*/
/* Cria "streams simulados" para decodificar - a entrada é simplesmente um
 * arquivo, a saída é uma imagem com uma posição associada. */

void criaStreamsDecod (char* arquivo_rbd)
{
    unsigned int tam_imagem, largura, altura;

    /* Abre o arquivo para ler os dados codificados. */
    stream_rbd = fopen (arquivo_rbd, "rb");
    if (!stream_rbd)
    {
        printf ("Erro abrindo arquivo %s\n", arquivo_rbd);
        exit (1);
    }

    /* Obtém o tamanho da imagem. São 2 bytes para a altura e 2 bytes para a largura. Lemos os 4 bytes de uma só vez. */
    fread (&tam_imagem, 1, 4, stream_rbd);
    altura = tam_imagem >> 16;
    largura = tam_imagem & 0xFFFF;

    /* Cria a imagem. */
    img = criaImagem1C (largura, altura);

    /* Aponta para o início. */
    linha_atual = 0;
    coluna_atual = 0;
}

/*----------------------------------------------------------------------------*/
/* Simplesmente salva a imagem usada no momento. */

void salvaStreamImagem (char* arquivo_img)
{
    if (!img)
    {
        printf ("Primeiro crie um stream para a imagem!\n");
        exit (1);
    }

    if (!salvaImagem1C (img, arquivo_img))
    {
        printf ("Erro salvando imagem %s\n", arquivo_img);
        exit (1);
    }
}

/*----------------------------------------------------------------------------*/
/* Desaloca e fecha os "streams simulados". */

void destroiStreams ()
{
    if (img)
        destroiImagem1C (img);

    if (stream_rbd)
        fclose (stream_rbd);
}

/*============================================================================*/
/* As funções abaixo são aquelas usadas pelos alunos. Vou supor que todos os
 * streams estão abertos e funcionando. */

/* Retorna o valor do pixel atual, e aponta para o próximo. Retorna
 * 0xFFFFFFFF se não tiver mais pixels para retornar. */

unsigned int pegaProximoPixel ()
{
    unsigned int pixel;

    /* Final do stream. Retorna um valor especial. */
    if (linha_atual >= img->altura)
        return (0xFFFFFFFF);

    pixel = img->dados [linha_atual][coluna_atual];

    /* Vai para a próxima posição antes de retornar. */
    coluna_atual++;
    if (coluna_atual == img->largura)
    {
        linha_atual++;
        coluna_atual = 0;
    }

    return (pixel);
}

/*----------------------------------------------------------------------------*/
/* Adiciona um pixel à imagem. Passamos a apontar para o próximo pixel. */

void enviaPixel (unsigned char pixel)
{
    // Ignora pixels recebidos após completar a imagem.
    if (linha_atual >= img->altura)
        return;

    img->dados [linha_atual][coluna_atual] = pixel;

    coluna_atual++;
    if (coluna_atual >= img->largura) // Terminou uma linha.
    {
        coluna_atual = 0;
        linha_atual++;
    }
}

/*----------------------------------------------------------------------------*/
/* Pega o próximo byte do arquivo que simula o stream com bit depth reduzido.
 * Retorna 0xFFFFFFFF se não tiver mais nada para retornar. */

 unsigned int pegaProximoByteRBD ()
 {
    unsigned char byte;

    /* Lê 1 byte do stream. */
    if (!fread (&byte, 1, 1, stream_rbd))
        return (0xFFFFFFFF);

    return (byte);
}

/*----------------------------------------------------------------------------*/
/* Escreve um byte no stream com bit depth reduzido. */

void enviaByteRBD (unsigned char byte)
{
    fwrite (&byte, 1, 1, stream_rbd);
}

/*============================================================================*/

