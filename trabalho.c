#include <stdio.h>
#include <string.h>

struct candidato 
{
    int numero;
    char nome[20];
    char partido[20];
};

void incluir();
void listar();
void listarTodos();
void alterar();
void excluir();
void procurar();

char contiuar();

char fnome[] = {"principal.dat"};

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
      listarTodos();
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

  fp = fopen(fnome, "ab");

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

  fp = fopen(fnome, "rb");
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
    fp = fopen(fnome, "wb");
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

  fp = fopen(fnome, "rb");
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
    fp = fopen(fnome, "wb");
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

  fp = fopen(fnome, "rb");

  printf("\nInforme Número do candidato: ");
  scanf("%d", & numero);

  while (1) 
  {
    fread( & t, sizeof(t), 1, fp);

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

  fp = fopen(fnome, "rb");

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

void listarTodos() 
{
  FILE * fp;
  struct candidato t;

  fp = fopen(fnome, "rb");

  printf("\n========================================================\n");
  printf("\t\t Listagem de Candidatos\n");
  printf("========================================================\n");
          
  printf("Número\tNome\tPartido\n");
  printf("--------------------------------------------------------\n");

  while (1) 
  {
    fread( & t, sizeof(t), 1, fp);

    if ( feof(fp) )
    {
      break;
    }
    printf("%d\t", t.numero);
    printf("%s\t", t.nome);
    printf("%s\t\n", t.partido);

  }
  printf("========================================================\n\n");

  fclose(fp);
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