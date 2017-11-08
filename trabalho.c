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




void LoadArquivo(char *fn, estado *Estados, int *tam, int *finais, int *tam_final)
{
	FILE *f = fopen(fn,"r");
	if(!f)
		{
			printf("Erro na leitura do arquivo\n");
			return;
		}

	fscanf(f,"Q=%d%*c",tam); 				        //lendo a quantidade de estados, logo o tamanho do vetor de estados

	int i ;
	char aux;


	while(aux != '\n')
	{
		fscanf(f,"%c",&aux);			            //lendo a linhas q contem os finais
		if(isdigit(aux)){				        	//pegando somente os numeros
			finais[(*tam_final)] = aux - '0';       //transformando em int
			(*tam_final)++;
		}
	}	

	char *batata[100];
	fscanf(f,"%[^\n]%*c",batata);


	i = 0;
	 while(!feof(f))
	{
		char lado;

		int indice;
		fscanf(f,"(q%d",&Estados[i].num);

		fscanf(f,",%c)",&aux);
		Estados[i].leitura = aux ;                                //o char diretamente na struct



		fscanf(f,"=(q%d",&Estados[i].qual_ir);                    //lendo o próximo estado

		fscanf(f,",%c",&aux);                                     //lendo o q escreve
		Estados[i].escrita = aux;

		fscanf(f,",%c%*c%*c",&lado);                                 //lendo o lado

		if(lado == 'D')
			Estados[i].direcao = DIREITA;
		else
			Estados[i].direcao = ESQUERDA;

		i++;
	}

	*tam = i;

}


void PrintaVetorEstado(estado *estados, int tam)
{
	for (int i = 0; i < tam; ++i)
	{
		printf("num: %d\n",estados[i].num);
		printf("leitura:%c\n", estados[i].leitura);
		printf("direcao:%d\n",estados[i].direcao );
		printf("escrita:%c\n", estados[i].escrita);
		printf("qual_ir:%d\n", estados[i].qual_ir);
		printf("\n");
	}
}






void printPos (char s[], int pos, int num){
	int i;
	
	for (i = 0; i < strlen(s); i++){
		if (i != pos){
			printf ("%c", s[i]);
		}else{
			printf ("%c", s[i]);
			printf ("[q%d]", num);
		}
	}
	printf("\n");
}

int AdequaString(char s[])
{
	int aux = strlen(s);
	for (int i = aux +1; i > 0 ; --i)
	{
	//	printf("%c\n",s[i]);
		s[i] = s[i - 1];
	}
	s[aux+1] = '$';
	s[aux + 2] = '\0' ;
	

	s[0] = '*';
}

void MaquinaDeTuring(int atual, int pos_string, char *s,estado *vetor_estado, int *vetor_finais, int tam_estados, int tam_final)
{
	for (int i = 0; i < tam_estados; ++i)
	{
		if(vetor_estado[i].num == atual)
		{
			if (vetor_estado[i].leitura == s[pos_string])
			{
				if (vetor_estado[i].direcao == DIREITA)
				{
					s[pos_string] = vetor_estado[i].escrita;
					printPos(s,pos_string,atual);
					pos_string++;
					return MaquinaDeTuring(vetor_estado[i].qual_ir,pos_string,s,vetor_estado,vetor_finais,tam_estados,tam_final);
				}else
				{
					printPos(s,pos_string,atual);
					s[pos_string] = vetor_estado[i].escrita;
					pos_string--;
					return MaquinaDeTuring(vetor_estado[i].qual_ir,pos_string,s,vetor_estado,vetor_finais,tam_estados,tam_final);
				}
			}
		}
	}	for (int i = 0; i < tam_final; ++i)
	{
			if (atual == vetor_finais[i]){
			printf("aceita\n");
			return;
		}
	}

	printf("nao aceita\n");
	return;

}


int main(int argc, char const *argv[])
{
	estado Estados[MAX];
	int tam_estados;
	int finais[MAX], tam_finais = 0;
	char entrada[MAX];
	LoadArquivo("entrada.txt",Estados,&tam_estados,finais,&tam_finais);
	scanf("%[^\n]",entrada);
	AdequaString(entrada);
	printPos(entrada,0,0);
	MaquinaDeTuring(0,1,entrada,Estados,finais,tam_estados,tam_finais);
	//PrintaVetorEstado(Estados,tam_estados);

	//printPos("alisson",3,3);

	return 0;
}