#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

#define DIREITA 1
#define ESQUERDA 0
#define TRUE 1
#define FALSE 0

typedef struct 
{
	int num;
	char leitura;
	int direcao;
	char escrita;
	int qual_ir;
}estado;

void LoadArquivo(char *fn, estado *Estados, int *tam, int *finais, int *tam_final);
//printa o vetor de estados
void PrintaVetorEstado(estado *estados, int tam);
//printa a string na forma que o professor dado na específicação do trabralho
void printPos (char s[], int pos, int num);
//acresenta as caracteres '*' e '$' no começo e no final respectivamente
int AdequaString(char s[]);
// processa a string na maquina de turing recursivamente
void MaquinaDeTuring(int atual, int pos_string, char *s,estado *vetor_estado, int *vetor_finais, int tam_estados, int tam_final);
