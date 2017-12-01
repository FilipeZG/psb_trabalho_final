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

void incluir();
void listar();
void listarTodos(int);
void listarTodosVotos();
void alterar();
void excluir();
void procurar();
int votosCandidato(int);

char contiuar();

char fCandidatos[] = {"principal.dat"};
char fUrna[] = {"urna.dat"};

int main() 
{
  int ch;
  int continua = 1;

  while (continua) 
  {
    system("cls");

    printf("+-------------------------------------------------------+\n");
    printf("|                 Cadastro de Candidatos                |\n");
    printf("+-------------------------------------------------------+\n");
    printf("|                                                       |\n");
    printf("| 1. Adicionar                                          |\n");
    printf("| 2. Alterar                                            |\n");
    printf("| 3. Excluir                                            |\n");
    printf("| 4. Procurar                                           |\n");
    printf("| 5. Listar Candidato                                   |\n");
    printf("| 6. Listar Todos                                       |\n");
    printf("| 7. Listar Todos Votos                                 |\n");
    printf("| 8. Candidatos e Votos                                 |\n");
    printf("| 0. Sair                                               |\n");
    printf("|                                                       |\n");
    printf("+-------------------------------------------------------+\n");

    printf("Informe a sua opção: ");
    scanf("%d", &ch);

    switch (ch) 
    {
    case 1:
      incluir();
      break;

    case 2:
      alterar();
      break;

    case 3:
      excluir();
      break;

    case 4:
      procurar();
      break;

    case 5:
      listar();
      break;

    case 6:
      listarTodos(0);
      break;

    case 7:
      listarTodosVotos();
      break;

    case 8:
      listarTodos(1);
      break;


    case 0:
      continua = 0;
    }

    contiuar();
  }

  return 0;
}
void incluir() 
{
  FILE * fp;
  struct candidato t1;

  fp = fopen(fCandidatos, "ab");

  printf("\nInforme o Número: ");
  scanf("%d", &t1.numero);
  
  printf("Nome de candidato: ");
  scanf("%s", t1.nome);

  printf("Nome o partido do candidato: ");
  scanf("%s", t1.partido);
  
  fwrite( & t1, sizeof(t1), 1, fp);
  fclose(fp);
  
  printf("Registro inserido.\n");  
}

void alterar() 
{
  FILE * fp, * fp1;
  struct candidato t, t1;
  int numero, found = 0, count = 0;

  fp = fopen(fCandidatos, "rb");
  fp1 = fopen("temp.dat", "wb");

  printf("\nInforme o número do candidato que deseja modificar: ");
  scanf("%d", & numero);

  while (1) 
  {
    fread( & t, sizeof(t), 1, fp);

    if ( feof(fp) )
    {
      break;
    }
    
    if (t.numero == numero)
    {
      found = 1;
      printf("\nNovo Número: ");
      scanf("%d", & t.numero);
      fflush(stdin);
      
      printf("Novo Nome: ");
      scanf("%s", t.nome);

      printf("Novo Partido: ");
      scanf("%s", t.partido);
      
      fwrite( & t, sizeof(t), 1, fp1);
    } 
    else 
    {
      fwrite( & t, sizeof(t), 1, fp1);
    }
  }
  
  fclose(fp);
  fclose(fp1);

  if (found == 0) 
  {
    printf("Desculpe, registro não encontrado.\n\n");
  } 
  else 
  {
    fp = fopen(fCandidatos, "wb");
    fp1 = fopen("temp.dat", "rb");

    while (1) 
    {
      fread( & t, sizeof(t), 1, fp1);

      if (feof(fp1)) {
        break;
      }
      fwrite( & t, sizeof(t), 1, fp);
    }
    
    fclose(fp);
    fclose(fp1);
    
    printf("Dados alterados.\n");    
  }
}

void excluir() 
{
  FILE * fp, * fp1;
  struct candidato t, t1;
  int numero, found = 0, count = 0;

  fp = fopen(fCandidatos, "rb");
  fp1 = fopen("temp.dat", "wb");

  printf("\nInforme Número do candidato que deseja excluir: ");
  scanf("%d", & numero);

  while(1) 
  {
    fread( & t, sizeof(t), 1, fp);

    if ( feof(fp) ) 
    {
      break;
    }
    
    if (t.numero == numero)
    {
      found = 1;
    } 
    else 
    {
      fwrite( & t, sizeof(t), 1, fp1);
    }
  }
  
  fclose(fp);
  fclose(fp1);

  if (found == 0) 
  {
    printf("Desculpe, registro não encontrado!\n");
  } 
  else 
  {
    fp = fopen(fCandidatos, "wb");
    fp1 = fopen("temp.dat", "rb");

    while(1) 
    {
      fread( & t, sizeof(t), 1, fp1);

      if (feof(fp1)) 
      {
        break;
      }
      fwrite( & t, sizeof(t), 1, fp);
    }
    
    fclose(fp);
    fclose(fp1);
    
    printf("Registro excluido.\n");
  }
  
}

void listar() 
{
  FILE * fp;
  struct candidato t;
  int numero, found = 0;

  fp = fopen(fCandidatos, "rb");

  printf("\nInforme Número do candidato: ");
  scanf("%d", & numero);

  while (1) 
  {
    fread( &t, sizeof(t), 1, fp);

    if ( feof(fp) )
    {
      break;
    }
    
    if ( t.numero == numero )
    {
      found = 1;
      printf("\n========================================================\n");
      printf("\t\t Dados do Candidato %d\n", t.numero);
      printf("========================================================\n");
      printf("Nome\tPartido\n");
      printf("--------------------------------------------------------\n");

      printf("%s\t", t.nome);
      printf("%s\t\n", t.partido);

      printf("========================================================\n");
    }
  }
  
  if (found == 0) 
  {
    printf("\nDesculpe, candidato não encontrado. \n");
  }
  fclose(fp);
}

void procurar() 
{
  FILE * fp;
  struct candidato t;
  int found = 0;
  char nome[20];

  fp = fopen(fCandidatos, "rb");

  printf("\nInforme nome do candidato:");
  scanf("%s", nome);

  while (1) 
  {
    fread( & t, sizeof(t), 1, fp);

    if (feof(fp)) 
    {
      break;
    }
    
    if ( strcmp(nome, t.nome) == 0) 
    {
      printf("\n========================================================\n");
      printf("\t\t Detalhes do candidato %d\n", t.numero);
      printf("========================================================\n");
      
      printf("Nome\tPartido\n\n");
      printf("--------------------------------------------------------\n");

      printf("%s\t", t.nome);
      printf("%s\t\n\n", t.partido);

      printf("========================================================\n\n");

    }
  }
  
  if ( found == 0 ) 
  {
    printf("\nDesculpe, candidato não encontrado.\n");
  }
  fclose(fp);
}

void listarTodos(int voto) 
{
  FILE * fp;
  struct candidato t;
  int countVoto = 0;

  fp = fopen(fCandidatos, "rb");

  printf("\n========================================================\n");
  printf("\t\t Listagem de Candidatos\n");
  printf("========================================================\n");
          
  printf("Número\t\tNome\t\tPartido");

  if (voto) 
  {
    printf("\t\tVotos");
  }

  printf("\n--------------------------------------------------------\n");

  while (1) 
  {
    fread( & t, sizeof(t), 1, fp);

    if ( feof(fp) )
    {
      break;
    }

    if (voto) 
    {
      countVoto = votosCandidato(t.numero);
    }

    printf("%d\t\t", t.numero);
    printf("%s\t\t", t.nome);
    printf("%s\t\t", t.partido);

    if (voto) 
    {
      printf("%d\t\t", countVoto);
    }

    printf("\n");

    countVoto = 0;
  }
  printf("\n========================================================\n\n");

  fclose(fp);
}

void listarTodosVotos() 
{
  FILE * fp;
  struct voto v;

  fp = fopen(fUrna, "rb");

  printf("\n========================================================\n");
  printf("\t\t Listagem de Votos\n");
  printf("========================================================\n");
          
  printf("Número\tNome\t\n");
  printf("--------------------------------------------------------\n");

  while (1) 
  {
    fread( &v, sizeof(v), 1, fp);

    if ( feof(fp) )
    {
      break;
    }

    printf("%d\t", v.numero);
    printf("%s\t", v.nome);

  }
  
  printf("\n========================================================\n\n");

  fclose(fp);
}

int votosCandidato(int numero) 
{
  int count = 0;
  FILE * fp;
  struct voto v;


  fp = fopen(fUrna, "rb");

  while (1) 
  {
    fread( &v, sizeof(v), 1, fp);

    if ( feof(fp) )
    {
      break;
    }

    if (v.numero == numero) 
    {

      count++;
    }

  }

  fclose(fp);

  return count;
}

char contiuar() 
{
  char val;
  char rel;

  printf("Pressione <ENTER> para continuar...");
  scanf("%c", & val);
  scanf("%c", & rel);
  return (val);
}
