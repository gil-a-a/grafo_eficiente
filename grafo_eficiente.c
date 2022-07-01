#include <stdio.h>
#include <stdlib.h>

void Ligar (int **Adj, int no1, int no2);	
void Desligar (int **Adj, int no1, int no2);
int Adjacente (int **Adj, int no1, int no2);
int Tem_Caminho (int A, int B, int K, int **Adj, int n);
int** Aloca_Matriz(int **Mat, int n)
{
	int i, j;
	
	Mat = (int **) malloc(n*sizeof(int *));
	for (i = 0; i < n; i++){
		Mat[i] = (int *) malloc(n*sizeof(int));
		for (j = 0; j < n; j++){
			Desligar(Mat, i, j);
		}
	}
	
	return Mat;
}

int** Prod_Bool (int **AdjL, int **Adj, int n)
{
	int i, j, k, l;
	int **Mat;
	
	//daria pra deixar mais eficiente e botar um free antes de alocar mais memória,
	//mas vou só vou me preocupar com isso dps de implementar td certinho
	Mat = Aloca_Matriz(Mat, n);
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				Mat[i][j] += AdjL[i][k]*Adj[k][j];
	
	return Mat;
}

int main ()
{
	//dps mudo cidade pra nó
	int n;
	int i, j;
	int A, B, NE;
	int cidade_1, cidade_2;
	int **Adj;
	char aux;
	
	printf("Insira o numero de cidades: ");
		scanf("%d", &n);
	
	printf("Insira as cidades A e B: ");
		scanf(" %d%d", &A, &B);
	
	printf("Insira o numero desejado de estradas entre %d e %d: ", A, B);
		scanf(" %d", &NE);
	
	Adj = (int **) malloc(n*sizeof(int *));
	for (i = 0; i < n; i++){
		Adj[i] = (int *) malloc(n*sizeof(int));
		for (j = 0; j < n; j++){
			Desligar(Adj, i, j);
		}
	}
	
	while (aux != 'n' && aux != 'N'){
		printf("Insira duas cidades que estao ligadas: ");
			scanf(" %d%d", &cidade_1, &cidade_2);
		Ligar(Adj, cidade_1-1, cidade_2-1);
		//Ligar(Adj, cidade_2-1, cidade_1-1);
		
		printf("Quer inserir mais um arco?\n");
			scanf(" %c", &aux);
	}
	
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			printf("%d ", Adjacente(Adj, i, j));
		printf("\n");
	}
	
	if (Tem_Caminho(A, B, NE, Adj, n))
		printf("\n\nExiste caminho de comprimento NE");
	else
		printf("\n\nNao existe caminho de comprimento NE");
	
	return 0;
}

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

int Tem_Caminho (int A, int B, int K, int **Adj, int n)
{
	int C;
	
	if (K == 1){
		printf("<%d,%d> ", A, B);
		return Adjacente(Adj, A-1, B-1);
	}
	
	for (C = 0; C < n; C++){
		if (Adjacente(Adj, A, C)){
			if (Tem_Caminho(C, B, K-1, Adj, n)){
				printf("<%d,%d> ", A, B-1);
				return 1;
			}
		}
	}
	
	return 0;
}
