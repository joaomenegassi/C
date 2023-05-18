/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/* Reduzindo a profundidade de bits de imagens (codificando). */
/*============================================================================*/

#include "trabalho1.h"

/*============================================================================*/

#define ARQUIVO_IMG "C:\\Users\\PC\\Documents\\projeto1\\projeto1\\img\\teste3-2.bmp" /* Imagem para teste. */
#define ARQUIVO_RBD "C:\\Users\\PC\\Documents\\projeto1\\projeto1\\img\\TESTEFINAL3-2.rbd" /* Saída codificada. */
#define BPP 2 /* Precisa ser 1, 2 ou 4. */

/*============================================================================*/

int main ()
{
    criaStreamsCod (ARQUIVO_IMG, ARQUIVO_RBD);
    codificaStreamImagem (BPP);
    destroiStreams ();

    return (0);
}

/*============================================================================*/

