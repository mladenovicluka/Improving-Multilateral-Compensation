#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int** dodavanje_cvora_u_graf(int** a, int* n)
{
    (*n)++;
    a = (int**)realloc(a, *n * sizeof(int*));
    a[*n - 1] = (int*)malloc(sizeof(int) * (*n));
    for (int j = 0; j < *n; j++)a[*n - 1][j] = 0;
    for (int i = 0; i < *n; i++)a[i][*n - 1] = 0;

    return a;
}
void printuj(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d:\t", i + 1);
        for (int j = 0; j < n; j++)printf("%d ", a[i][j]);
        printf("\n");
    }
}
int** ukloni_cvor_iz_grafa(int** a, int* n)
{
    printf("Unesite ID cvora\n");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < *n; i++)
    {
        for (int j = id; j < *n - 1; j++)a[i][j] = a[i][j + 1];
    }

    for (int i = id; i < *n - 1; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            a[i][j] = a[i + 1][j];
        }
    }
    free(a[*n - 1]);

    (*n)--;
    return a;

}
void resetuj(int* a, int* k)
{
    for (int i = 0; i < 90; i++)
        a[i] = 0;
    *k = 0;
}
void setuj(int a[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
}
void warshall(int** a, int** b,int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j]) b[i][j] = 1;
            else b[i][j] = 0;
        }
    }   
   
    for (int k = 0; k < n; k++)
    {
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                b[i][j] = b[i][j] || (b[i][k] && b[k][j]);
               // b[i][j] = b[i][j] + (b[i][k] * b[k][j]);
            }
        }
       

    }
   // printuj(b, n);
    int i = 0;
    printf("Ciklus obuhvata cvorove\n");
    int k = 0;
    int niz[30][30]={{0}};
    int pokazivaci[30]={0};
    while(i<n)
    {
       
        
        int counter = 0,maks=-1;
        for (int j = 1; j < n - 1; j++)
        {
            if (b[i][j - 1] == b[i][j] && b[i][j]&&b[i][i])counter++;
            else
            {  
                if (counter > maks)maks = counter;
                counter = 0;
            }
       }
        if (counter > maks)maks = counter;
        niz[maks][pokazivaci[maks]++] = i + 1;  
        
        i++;
    }
    int ciklusi[100][100];
    setuj(ciklusi, 100);
    int red = 0;
    for (i = 1; i < 30; i++)
    {
        int barjedan = 0;
        for (int j = 0; j < 30; j++)
        {
            if (!niz[i][j])break;
          
            ciklusi[red][j] = niz[i][j];
            barjedan = 1;
        }
        if (barjedan)
        {
            red++;
       
        }
    } 
  
    printf("RED \n");
    
    for (int m = 0; m < red; m++)
    {
        int x = 0;
        while (ciklusi[m][x])
        {
            printf("%d ", ciklusi[m][x]);
            x++;
        }
        printf("\n");
    }
    printf("Cene \n");
    for (int m = 0; m < red; m++)
    {
        int x = 0;
        int minimum = 111111;
        while (ciklusi[m][x])
        {
            if (ciklusi[m][x + 1])
            {
                printf("%d->", a[ciklusi[m][x]-1][ciklusi[m][x+1] - 1]);
                if (minimum > a[ciklusi[m][x] - 1][ciklusi[m][x + 1] - 1])minimum = a[ciklusi[m][x] - 1][ciklusi[m][x + 1] - 1];
            }
            else
            {
                printf("%d->", a[ciklusi[m][x] - 1][ciklusi[m][0] - 1]);
                if (minimum > a[ciklusi[m][x] - 1][ciklusi[m][0] - 1])minimum = a[ciklusi[m][x] - 1][ciklusi[m][0] - 1];
            }
            x++;
        }
        x = 0;

        printf("\t ovde se kompenzuje %d\n", minimum);
        while (ciklusi[m][x])
        {
            if (ciklusi[m][x + 1])
            {
                a[ciklusi[m][x] - 1][ciklusi[m][x + 1] - 1] -= minimum;
               
            }
            else
            {
                a[ciklusi[m][x] - 1][ciklusi[m][0] - 1] -= minimum;
            }
            x++;
        }




        
        printf("\n");
    }






}

int main()
{
    int** a = NULL;
    int n = 0;

    while (1)
    {
        FILE* ulaz;
        int izlaz = 0;
        int izbor;
        printf("\n#################################################################\n");
        printf("Unesite komandu!\n");
        printf("1-Kreiranje prazne strukture podataka za graf+alociranje memorije!.\n");
        printf("2-Dodavanje cvora u graf.\n");
        printf("3-Uklanjanje cvora iz grafa.\n");
        printf("4-Dodavanje grane izmedju dva cvora u grafu.\n");
        printf("5-Uklanjanje grane izmedju dva cvora u grafu.\n");
        printf("6-Ispis reprezentacije grafa.\n");
        printf("7-Brisanje grafa iz memorije.\n");
        printf("8-Unos grafa iz datoteke.\n");
        printf("9-Zavrsetak programa.\n");

        printf("\n#################################################################\n");

        scanf("%d", &izbor);
        switch (izbor)
        {
        case 1:
        {
            printf("Ucitajte dimenzije\n");
            scanf("%d", &n);
            a = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++)
                a[i] = (int*)malloc(n * sizeof(int));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)a[i][j] = 0;


            printf("Uspesno kreiranje grafa\n");
            break;
        }
        case 2:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            printf("Uspesno dodavanje cvor u graf\n");
            a = dodavanje_cvora_u_graf(a, &n);
            break;
        }
        case 3:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            a = ukloni_cvor_iz_grafa(a, &n);
            break;
        }
        case 4:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            printf("Unesite ID cvora kog zelite da povezete.\n");
            int od;
            scanf("%d", &od);
            printf("\nUnesite ID cvora sa kim zelite da povezete.\n");
            int doo;
            scanf("%d", &doo);
            a[od][doo] = 1;
            break;
        }
        case 5:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            printf("Unesite ID cvora od koje veza krece.\n");
            int od;
            scanf("%d", &od);
            printf("\nUnesite ID cvora gde se grana zavrsava.\n");
            int doo;
            scanf("%d", &doo);
            a[od][doo] = 0;
            break;
        }
        case 6:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            printuj(a, n);
            break;
        }
        case 7:
        {
            if (!a)
            {
                printf("Nije alociran prostor za graf!\n");
                break;
            }
            for (int i = 0; i < n; i++)free(a[i]);
            a = NULL;
            break;
        }
       
        case 8:
        {
            char imeulaznedatoteke[100];
            char imeulaznedatoteket[100];
            char linija[100];
            printf("Unesi ime ulazne datoteke\n");   
            scanf("%s", imeulaznedatoteke);
            memcpy(imeulaznedatoteket, imeulaznedatoteke,40);
            ulaz = fopen(strcat(imeulaznedatoteke,".txt"), "r");
           
            if (ulaz == NULL)
            {
                printf("NEUSPESNO UCITAVANJE DATOTEKE !");
                exit(0);
            }
            fscanf(ulaz, "%d", &n);
            a = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++)
                a[i] = (int*)malloc(n * sizeof(int));
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                    fscanf(ulaz, "%d", &a[i][j]);
            }
            printuj(a, n);
            printf("-------\n");
           int ** b = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++)
                b[i] = (int*)malloc(n * sizeof(int));
            warshall(a,b,n);
            printuj(a, n);
            FILE* fout;
            fout = fopen(strcat(imeulaznedatoteket, "-improved.txt"), "w");
            for (int i = 0; i < n; i++)
            {
                
                for (int j = 0; j < n; j++)fprintf(fout,"%d ", a[i][j]);
                fprintf(fout,"\n");
            }
            fclose(ulaz);
            fclose(fout);
            break;
        }
        case 9:
        {
            izlaz = 1;
            break;
        }
        default:
        {
            printf("Nevalidna komanda,probajte ponovo!\n");
            break;
        }
        }
        if (izlaz)break;


    }

}

