/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Joao Guilherme Menegassi Silva - joaosilva.2005@alunos.utfpr.edu.br        */
/*============================================================================*/
/* Implementação das funções do projeto. */
/*============================================================================*/

#include"trabalho1.h"

//Declaração da função codifica.
void codificaStreamImagem (int n_bits);

//Funções Auxiliares.
unsigned int pegaProximoPixel ();
void enviaByteRBD (unsigned char byte);

void codificaStreamImagem (int n_bits)
{

    // Declaração das variaveis
    int i;
    int contador = 8 - n_bits;
    unsigned int byte;
    unsigned char aux = 0;

    // Armazena o primeiro byte;
    byte = pegaProximoPixel();

    // Loop até o ultimo pixel.
    while(byte != 0xFFFFFFFF)
    {

        // Loop para pegar apenas os n_bits mais significativos de cada byte e somar em aux.
        for(i = 0; i < 8 / n_bits ; i++)
        {
            byte =  byte >> 8 - n_bits;
            byte = byte << contador;

            //soma os n_bits significativos.
            aux = byte | aux;

            //Diminui a variável "contador" em n_bits para que a proxima soma seja correta.
            contador -= n_bits;

            byte = pegaProximoPixel();

        }
        // Envia a soma dos bits mais significativos de cada byte.
        enviaByteRBD(aux);

        //Reseta o contador e o aux para que não ocorra problemas na próxima soma.
        aux = 0;
        contador = 8 - n_bits;

    }
}

