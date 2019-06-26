#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

//Define Menu
#define ESCREVER 1
#define CH_PUBLICA 1
#define CHAVES 2
#define CH_PRIVADA 2
#define CRIPTOGRAFADA 3
#define DESENCRIPTOGRAFAR 3
#define ADMIN 4
#define NUM_OP 5
#define SAIR NUM_OP

//Define de cores
#define AZUL_CLARO "Color 9"
#define VERDE_CLARO "Color A"
#define AMARELO_CLARO "Color E"
#define VERMELHO_CLARO "Color C"
#define BRANCO_BRILHANTE "Color F"

//Define Arquivo
#define ARQ_KEY "Tibruto.dat"
#define ARQ_CRIP "Krypton.dat"
#define ARQ_DESENCRIP "Dekudifica.txt"

typedef struct
{
    int n;
    int e;
} publica;

typedef struct
{
    int d;
    int p;
    int q;
    int tontN;
} privada;

typedef struct
{
    publica pbl;
    privada pvd;
} key;


//Funções
void lindeza(void);
void escrever(void);
void sem_chave(void);
int criptografar(int);
bool testa_e(int, int);
void chave_acesso(void);
int menu(char *[], int);
void administrador(void);
bool testa_primo(int, int);
int inverso_modular(int, int);
void desencriptografar (void);

int main ()
{
    int op;
    char * opcoes[NUM_OP] =
    {
        "Escrever Mensagem", "Criar chaves de acesso", "Desencriptografar", "Comandos de Adiministrados", "Sair"
    };
    setlocale(LC_ALL, "Portuguese");

    system(VERDE_CLARO);
    printf("\n\t\t ||||\n\t\t||||||\n\t\t||||||\n\t\t||||||\n\t\t ||||\n\t\t ||||\n\t\t  ||\n\n\t\t ||||\n\t\t||||||\n\t\t ||||\n\n\n");
    printf("\tCOLOCAR EM TELA CHEIA!!");
    getch();

    system("cls");
    lindeza();
    getch();

    do
    {
        system("cls");
        system(BRANCO_BRILHANTE);
        op = menu(opcoes, NUM_OP);
        switch(op)
        {
        case ESCREVER:
            escrever();
            break;

        case CHAVES:
            chave_acesso();
            break;

        case DESENCRIPTOGRAFAR:
            desencriptografar();
            getch();
            break;

        case ADMIN:
            administrador();
            break;

        case SAIR:
            system(VERDE_CLARO);
            printf("\n\t\t\t\t\t\t\t\t\tObrigado por utilizar o encripnator\n");
            lindeza();
            getch();
            break;
        }
    }
    while(op != SAIR);
    return 0;
}

int menu(char *opcoes[], int n)
{
    int i, op;

    printf("\t\t\t\t\t\t\t\t    ---    --  --------  ---     -  --      -\n\t\t\t\t\t\t\t\t    ---------  --        -----   -  --      -\n");
    printf("\t\t\t\t\t\t\t\t    --  --  -  --------  ------  -  --      -\n\t\t\t\t\t\t\t\t    --      -  --        --  -----   --    -\n");
    printf("\t\t\t\t\t\t\t\t    --      -  --------  --    ---     ----\n");
    printf("\t ___________________________________________________________________________");
    printf("_____________________________________________________________________________\n");
    printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
    for (i = 0; i < n; i++)
    {
        printf("\t|\t\t\t\t\t\t\t\t%-2d - %-25s\t\t\t\t\t\t\t\t |\n", i + 1, opcoes[i]);
    }
    printf("\t|___________________________________________________________________________");
    printf("_____________________________________________________________________________|\n");
    op = getch();
    system("cls");

    return op - 48;
}

void lindeza()
{
    printf("\n\t\t\t\t\t\t\t89360297559246085645 ..	     .    -.	  -  uLGFUTDFUHlihKFIGUglih\n\t\t\t\t\t\t\t6136118786418634162875	.     ..   ..    .ihSI>ccHFEOHiwhwdhAIHNAye\n\t\t\t\t\t\t\t43876161134561234654136 .. 		UEOnsiwInninIOaksaiIPippiip\n\t\t\t\t\t\t\t	       71549764.   -	...	EWDFUOljy\n\t\t\t\t\t\t\t	      7898  .....	        ...IFjlik\n\t\t\t\t\t\t\t             049060202..   -	..	gjfKKYGfhgfLKGGsfkçWTYIBNMv\n\t\t\t\t\t\t\t  	    098790568			QÇIYFAjbnjdfab:KJBfFDaSfxAa\n\t\t\t\t\t\t\t	   0049744  ...		...	IEPifhPlusUltra,WTKUwkuGbkw\n\t\t\t\t\t\t\t	  717968100	.-.		YIGELFyigligeflmcnmxbc<CB e\n\t\t\t\t\t\t\t         6678860.  ---		...	efaCAFefv\n\t\t\t\t\t\t\t        874049640	....		EFdcvrrRt\n\t\t\t\t\t\t\t       240542499  ..  --  	      ... FDsdvdg\n\t\t\t\t\t\t\t      654649008			..	FeLPOOWEf\n\t\t\t\t\t\t\t     126459658		....		OÇASfhiLHnflaHSiufçHILnjnffA\n\t\t\t\t\t\t\t    097602.  ..			...	WÇInfleilfEfnkpçjçmfogrgPOGJ\n\t\t\t\t\t\t\t   270819980	...	--   ... 	- ÇOJUHulfehbeultOubofesOEBF\n");
}

void escrever()
{
    int crip;
    char ch;
    FILE *arqC, *arqK;

    if((arqK = fopen(ARQ_KEY, "rb")) == NULL)
    {
        sem_chave();
        return;
    }

    if((arqC = fopen(ARQ_CRIP, "wb")) == NULL)
    {
        system(VERMELHO_CLARO);
        printf ("\nERRO: Não foi possível abrir o arquivo\n");
        getch();
        return;
    }

    printf("\t\t\t\t\t\t\t\t\t\tMensagem:\n");
    setbuf(stdin, NULL);
    do
    {
        scanf("%c", &ch);
        if(ch != '\n')
        {
            crip = criptografar(ch);
            fprintf(arqC, "%d\t", crip);
        }
    }
    while (ch != '\n');
    fclose(arqC);
    fclose(arqK);

    system("cls");
    system(VERDE_CLARO);
    printf("\n\t\t\t\t\t\t\t\t\tMensagem criptografada com sucesso!\n");
    getch();
}

void chave_acesso()
{
    key k;
    FILE *arqK;
    bool certo;

    printf("\t\t\t\t\t\t\t\t\tCadastrar chaves de acesso.\n\n\t\t\t\t\t\t\t\t\tInsira dois números primos:\n");

    do
    {
        scanf("%3d%3d", &k.pvd.p, &k.pvd.q);
        certo = testa_primo(k.pvd.p, k.pvd.q);
        if (!certo)
        {
            printf("\n\t\t\t\t\t\t\t\t   Um, ou mais, números não são primos!\n\t\t\t\t\t\t\t\t\t    Insira novamente:\n");
        }
    }
    while(!certo);
    k.pbl.n = k.pvd.p * k.pvd.q;
    k.pvd.tontN = (k.pvd.p - 1) * (k.pvd.q - 1);
    printf("\t\t\t\t\t\t\t\t\t    Informe a chave e:\n\t\t\t\t\t\t\tDeve ser um número entre 1 e %d e sem divisores comuns\n", k.pvd.tontN);
    do
    {
        scanf("%d", &k.pbl.e);
        certo = testa_e(k.pbl.e, k.pvd.tontN);

        if (k.pbl.e >= k.pvd.tontN || k.pbl.e <= 1)
        {
            printf("\t\t\t\t\t\t\t\t    Este número não está entre 1 e %d\n\t\t\t\t\t\t\t\t\t    Insira novamente:\n", k.pvd.tontN);
        }
        else
        {
            if (!certo)
            {
                printf("\n\t\t\t\t\t\t\t\t    Este número possue divisores comuns!\n\t\t\t\t\t\t\t\t\t    Insira novamente:\n");
            }
        }
    }
    while(!certo || k.pbl.e >= k.pvd.tontN || k.pbl.e <= 1);
    k.pvd.d = inverso_modular(k.pbl.e, k.pvd.tontN);

    if ((arqK = fopen(ARQ_KEY, "wb")) == NULL)
    {
        system(VERMELHO_CLARO);
        fprintf(stderr, "ERRO: Não foi possível armazenar as chaves!");
        getch();
        return;
    }
    fwrite(&k, sizeof(key), 1, arqK);
    fclose(arqK);

    remove(ARQ_CRIP);
    system("cls");
    system(VERDE_CLARO);
    printf("\n\t\t\t\t\t\t\t\t\tChave criada com sucesso!\n");
    getch();
}

bool testa_primo(int p, int q)
{
    int i, cont = 0;
    bool primo = false;

    for (i = 1; i <= p; i++)
    {
        if(p % i == 0)
        {
            cont++;
        }
    }
    if (cont == 2)
    {
        primo = true;
    }

    cont = 0;
    for (i = 1; i <= q; i++)
    {
        if(q % i == 0)
        {
            cont++;
        }
    }
    if (cont != 2)
    {
        primo = false;
    }

    return primo;
}

int inverso_modular(int A, int C)
{
    int i;

    for (i = 0; i < C; i++)
    {
        if (A * i % C == 1)
        {
            return i;
        }
    }
}

void sem_chave()
{
    char ch;

    system(VERMELHO_CLARO);
    printf("\n\t\t\t\t\t\t\t\t\tNão foi encontrada chave pública\n\t\t\t\t\t\t\t\t      Gostaria de criar uma agora (S | N)?\n");
    ch = getch();
    ch = toupper(ch);
    if(ch == 'S')
    {
        system("cls");
        system(BRANCO_BRILHANTE);
        chave_acesso();
    }
}

int criptografar(int ch)
{
    key k;
    FILE *arqK;
    int crip, ch_red, e;

    if((arqK = fopen(ARQ_KEY, "rb")) == NULL)
    {
        sem_chave();
        return;
    }
    fread(&k, sizeof(key), 1, arqK);

    e = k.pbl.e;
    ch_red = ch % k.pbl.n;
    crip = 1;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            crip *= ch_red;
            crip = crip % k.pbl.n;
        }
        e /= 2;
        ch_red = (ch_red * ch_red) % k.pbl.n;
    }

    fclose(arqK);
    return crip;
}

void administrador()
{
    key k;
    char ch;
    FILE *arqK, *arqC;
    int op, crip, linha = 0;
    char * opcoes_admin[NUM_OP] =
    {
        "Variáveis Públicas", "Variáveis Privadas", "Mensagem Criptografada", "Voltar",
    };


    do
    {
        system("cls");
        system(AMARELO_CLARO);
        op = menu(opcoes_admin, NUM_OP - 1);
        switch(op)
        {
        case CH_PUBLICA:
            if ((arqK = fopen(ARQ_KEY, "rb")) == NULL)
            {
                sem_chave();
                break;
            }
            fread(&k, sizeof(key), 1, arqK);

            printf("\t\t\t\t\t\t\t\t\t   %s\n", opcoes_admin[CH_PUBLICA - 1]);
            printf("\t ___________________________________________________________________________");
            printf("_____________________________________________________________________________\n");
            printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
            printf("\t|\t\t\t\t\t\t\t\t\tn = %d\t\t\t\t\t\t\t\t\t\t |\n", k.pbl.n);
            printf("\t|\t\t\t\t\t\t\t\t\te = %d\t\t\t\t\t\t\t\t\t\t |\n", k.pbl.e);
            printf("\t|___________________________________________________________________________");
            printf("_____________________________________________________________________________|\n");
            fclose(arqK);
            getch();
            break;

        case CH_PRIVADA:
            if ((arqK = fopen(ARQ_KEY, "rb")) == NULL)
            {
                sem_chave();
                break;
            }
            fread(&k, sizeof(key), 1, arqK);

            printf("\t\t\t\t\t\t\t\t\t   %s\n", opcoes_admin[CH_PRIVADA - 1]);
            printf("\t ___________________________________________________________________________");
            printf("_____________________________________________________________________________\n");
            printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
            printf("\t|\t\t\t\t\t\t\t\t\tp = %d\t\t\t\t\t\t\t\t\t\t |\n\t|\t\t\t\t\t\t\t\t\tq = %d\t\t\t\t\t\t\t\t\t\t |\n", k.pvd.p, k.pvd.q);
            printf("\t|\t\t\t\t\t\t\t\t\tTontN = %d\t\t\t\t\t\t\t\t\t |\n\t|\t\t\t\t\t\t\t\t\tInver_mult = %d\t\t\t\t\t\t\t\t |\n", k.pvd.tontN, k.pvd.d);
            printf("\t|___________________________________________________________________________");
            printf("_____________________________________________________________________________|\n");
            fclose(arqK);
            getch();
            break;

        case CRIPTOGRAFADA:
            if ((arqC = fopen(ARQ_CRIP, "rb")) == NULL)
            {
                system(VERMELHO_CLARO);
                printf("\n\t\t\t\t\t\t\t\tNão há nenhuma mensagem criptografada!");
                getch();
                break;
            }

            printf("\t\t\t\t\t\t\t\t\t   %s\n", opcoes_admin[CRIPTOGRAFADA - 1]);
            printf("\t ___________________________________________________________________________");
            printf("_____________________________________________________________________________\n");
            printf("\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t |\n\t\t");
            while (!feof(arqC))
            {
                fscanf(arqC, "%d", &crip);
                if(!feof(arqC))
                {
                    printf("%d\t", crip);
                    linha++;
                    if(linha == 18)
                    {
                        linha = 0;
                        printf("\n\t\t");
                    }
                }
            }
            printf("\n\n\t|___________________________________________________________________________");
            printf("_____________________________________________________________________________|\n");
            fclose(arqC);
            getch();
            break;

        case SAIR:
            break;
        }
    }
    while (op != NUM_OP - 1);
}

bool testa_e(int e, int tontN)
{
    int resto;
    bool valido;

    resto = tontN % e;
    while(resto!=0)
    {
        tontN = e;
        e = resto;
        resto = tontN % e;
    }
    if (e == 1)
    {
        valido = true;
    }
    else
    {
        valido = false;
    }

    return valido;
}

void desencriptografar(void)
{
    key k;
    FILE *arqK, *arqC, *arqD;
    int c_red, descrip, crip, d;

    if ((arqK = fopen(ARQ_KEY, "rb")) == NULL)
    {
        sem_chave();
        return;
    }
    fread(&k, sizeof(key), 1, arqK);

    if ((arqC = fopen(ARQ_CRIP, "rb")) == NULL)
    {
        system(VERMELHO_CLARO);
        printf("\n\t\t\t\t\t\t\t\tNão há nenhuma mensagem criptografada!");
        getch();
        return;
    }

    if ((arqD = fopen(ARQ_DESENCRIP, "w")) == NULL)
    {
        system(VERMELHO_CLARO);
        printf("Não foi possível criar o arquivo de mensagem desencriptografada");
        getch();
        return;
    }