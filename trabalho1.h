/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/* Funções pedidas e auxiliares para o 1o trabalho da disciplina CSF13
 * (Fundamentos de Programação 1), 2023-1, prof. Bogdan T. Nassu, Universidade
 * Tecnológica Federal do Paraná. */
/*============================================================================*/

#ifndef __TRABALHO1_H
#define __TRABALHO1_H

/*============================================================================*/
/* Funções do trabalho. */

void codificaStreamImagem (int n_bits);
void decodificaStreamRBD (int n_bits, int preenche);

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que DEVEM ser chamadas pelos alunos. */

unsigned int pegaProximoPixel ();
void enviaPixel (unsigned char pixel);
unsigned int pegaProximoByteRBD ();
void enviaByteRBD (unsigned char byte);

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que NÃO DEVEM ser chamadas pelos alunos. */

void criaStreamsCod (char* arquivo_img, char* arquivo_rle);
void criaStreamsDecod (char* arquivo_rbd);
void salvaStreamImagem (char* arquivo_img);
void destroiStreams ();

/*============================================================================*/
#endif /* __TRABALHO1_H */

