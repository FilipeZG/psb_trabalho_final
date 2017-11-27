#include <stdio.h>
#include <string.h>

struct candidato 
{
    int numero;
    char nome[20];
    char partido[20];
};

struct voto 
{
    int numero;
    char nome[20];
};

char fCandidatos[] = {"principal.dat"};
char fUrna[] = {"urna.dat"};

struct candidato candidatoNulo();
struct candidato procurar(int);
void info(struct candidato);
void votar(struct candidato);

int main() 
{
	int numCand;
	char confirma;	
  	struct candidato c;

  	system("cls");

  	do 
  	{
  		printf("Digite o número do candidato que deseja votar: ");
  		scanf("%d", &numCand);

  		if (numCand == 99999)
  		{
  			break;
  		}

  		c = procurar(numCand);

  		if (c.numero > 0) 
  		{
  			info(c);

  			printf("Deseja confirmar o voto? ");
  			scanf(" %c", &confirma);

  			if (confirma == 'S') {
  				votar(c);
  			}
  		}
  	} while (1);

  	return 0;
}

void votar(struct candidato c) 
{
	FILE * fp;
	struct voto v;

	v.numero = c.numero;
	strcpy(v.nome, c.nome);

  	fp = fopen(fUrna, "ab");

  	fwrite( &v, sizeof(v), 1, fp);
  	fclose(fp);

  	printf("\nVoto confrimado\n\n");
}

void info(struct candidato c) 
{
	printf("\n========================================================\n");
  	printf("\t\t Detalhes do candidato %d\n", c.numero);
  	printf("========================================================\n");
  
  	printf("Nome\tPartido\n\n");
  	printf("--------------------------------------------------------\n");

  	printf("%s\t", c.nome);
  	printf("%s\t\n\n", c.partido);

  	printf("========================================================\n\n");
}

struct candidato procurar(int numero) 
{
	FILE * fp;
  	struct candidato c;

  	fp = fopen(fCandidatos, "rb");

  	while (1) 
  	{
  		fread(&c, sizeof(c), 1, fp);

  		if (feof(fp)) 
  		{
  			printf("%s\n", "Candidato não foi encontrado!");
  			break;
  		}

  		if (c.numero == numero) 
  		{
			return c;
  		}
  	}

  	return candidatoNulo();
}

struct candidato candidatoNulo() 
{
	struct candidato nulo;
  	nulo.numero = -1;

  	return nulo;
}