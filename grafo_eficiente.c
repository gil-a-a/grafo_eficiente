#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Ligar (int **Adj, int no1, int no2);	
void Desligar (int **Adj, int no1, int no2);
int Adjacente (int **Adj, int no1, int no2);
int Tem_Caminho (int A, int B, int K, int **Adj, int n);
int** Aloca_Matriz(int n);
void Prod_Bool (int **AdjL, int **Adj, int **Res, int n);
int** Fecham_Trans(int **Adj, int **Caminho, int n);
int** Fecham_Trans_Warshall(int **Adj, int **Caminho, int n);

int main ()
{
	int n;
	int i, j;
	int A, B, NE;
	int no_1, no_2;
	int **Adj, **Caminho;
	char aux;
	
	printf("Insira o numero de nos: ");
		scanf("%d", &n);
	
	/*printf("Insira os nos A e B: ");
		scanf(" %d%d", &A, &B);
	
	printf("Insira o numero desejado de caminhos entre %d e %d: ", A, B);
		scanf(" %d", &NE);*/
	
	Adj = Aloca_Matriz(n);
	
	while (aux != 'n' && aux != 'N'){
		printf("Insira dois nos que estao ligados: ");
			scanf(" %d%d", &no_1, &no_2);
		Ligar(Adj, no_1-1, no_2-1);
		//Ligar(Adj, cidade_2-1, cidade_1-1);
		
		printf("Quer inserir mais um arco?\n");
			scanf(" %c", &aux);
	}
	
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			printf("%d ", Adjacente(Adj, i, j));
		printf("\n");
	}
	
	Sleep(1500);
	printf("==Fechamento transitivo==");
	Caminho = Fecham_Trans(Adj, Caminho, n);
	printf("\n---------Matriz de caminhos:\n");
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%d ", Caminho[i][j]);
		}
		printf("\n");
	}
	
	Sleep(1500);
	Caminho = Fecham_Trans_Warshall(Adj, Caminho, n);
	printf("\n==Warshall==\n");
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%d ", Caminho[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

///////////////////Funcoes//////////////////

void Ligar (int **Adj, int no1, int no2)
{
	Adj[no1][no2] = 1; /* adiciona um arco do No1 ao No2 */
}	

void Desligar (int **Adj, int no1, int no2)
{
	Adj[no1][no2] = 0; /* retira o arco que liga No1 ao No2 */
}

int Adjacente (int **Adj, int no1, int no2)
{
	return Adj[no1][no2];	/* verifica se há um arco do No1 ao No2 */
}

int** Aloca_Matriz(int n)
{
	int i, j;
	int **Mat;
	
	Mat = (int **) malloc(n*sizeof(int *));
	for (i = 0; i < n; i++){
		Mat[i] = (int *) malloc(n*sizeof(int));
		for (j = 0; j < n; j++)
			Desligar(Mat, i, j);
	}
	
	return Mat;
}

void Prod_Bool (int **AdjL, int **Adj, int **Res, int n)
{
	int i, j, k;
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				Res[i][j] += AdjL[i][k]*Adj[k][j];
}

int** Fecham_Trans(int **Adj, int **Caminho, int n)
{
	int i, j, k;
	int **NovoProd, **AdjProd;
	
	AdjProd = Adj;
	Caminho = Adj;
	NovoProd = Aloca_Matriz(n);
	
	for (k = 0; k < n-1; k++){
		Prod_Bool(AdjProd, Adj, NovoProd, n);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++){
				Caminho[i][j] += NovoProd[i][j];
				if (Caminho[i][j] > 0)
					Caminho[i][j] = 1;
			}
		AdjProd = NovoProd;
	}
	
	return Caminho;
}

int** Fecham_Trans_Warshall(int **Adj, int **Caminho, int n)
{
	int i, j, k;
	
	Caminho = Adj;
	
	for (k = 0; i < n; i++)
		for (i = 0; i < n; i++)
			if (Caminho[i][k])
				for (j = 0; j < n; j++)
					Caminho[i][j] += Caminho[k][j];
	
	return Caminho;
}
