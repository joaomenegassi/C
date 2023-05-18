/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/* Reduzindo a profundidade de bits de imagens (decodificando). */
/*============================================================================*/

#include "trabalho1.h"

/*============================================================================*/

#define ARQUIVO_RBD "C:\\Users\\PC\\Documents\\projeto1\\projeto1\\img\\TESTEFINAL3-2.rbd" /* Entrada codificada. */
#define ARQUIVO_IMG "C:\\Users\\PC\\Documents\\projeto1\\projeto1\\img\\TESTEFINAL3-2.bmp" /* Imagem de saída. */
#define BPP 2 /* Precisa ser 1, 2 ou 4. */

/*============================================================================*/

int main ()
{
    criaStreamsDecod (ARQUIVO_RBD);
    decodificaStreamRBD (BPP, 0);
    salvaStreamImagem (ARQUIVO_IMG);
    destroiStreams ();
    return (0);
}

/*============================================================================*/
