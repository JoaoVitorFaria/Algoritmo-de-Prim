
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>



void print_matriz(int ** matriz, int vertice)
{
	int u, v;
	for( u = 0; u < vertice; u++)
	{
		for(v = 0; v < vertice; v++)
		{
			if(matriz[u][v] == INT_MAX) printf("- ");
			else printf("%d ", matriz[u][v]);
		}
		printf("\n");
	}
}

//uso essa struct pois quero salvar informacoes das arestas que formam a arvore resultado
typedef struct pairVertice
{
	int first;
	int second;
	int peso;
} pair;

int main(int argc, char* argv[])
{
	//leitura do numero de vertices e arestas
	int vertice, aresta, u, e, v;
	scanf("%d %d", &vertice, &aresta);
	int ** matriz = (int **) malloc(vertice * sizeof(int*));
	//inicializo a matriz com valores infinitos
	for(u = 0; u < vertice; u++)
	{
		matriz[u] = (int*) malloc(vertice * sizeof(int));
		for( v = 0; v < vertice; v++) matriz[u][v] = INT_MAX;
	}
	//leitura da matriz
	for(e = 0; e < aresta; e++)
	{
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		matriz[u][v] = c;
		matriz[v][u] = c;
	}

	int custo_arvore = 0;
	//descomente a linha abaixo para imprimir a matriz referente ao grafo
	//print_matriz(matriz, vertice);

	//**************************


	//aqui eu declaro um vetor que vai me indicar se os vertices já foram visitados ou nao.
	//inicializo eles com false e mudo para true quando visita-los
	bool visitados[vertice];
	int i;

	for ( i = 0; i < vertice; i++)
	{
		visitados[i] = false;
	}



	//vou começar visitando do vertice 0, entao ja marco ele como visitado
	visitados[0] = true;
	//esse vetor vai servir para guardar informacoes das arestas escolhidas
	pair arestasEscolhidas[vertice];

	int contAresta = 0;


	//esse while vai fazer com que percorra todas as arestas do grafo
	//uso vertice-1 pois uma grafo tem um numero de arestas de no maximo vertice-1
	while (contAresta < vertice - 1)
	{
		//uso a variavel abaixo para armazenar a menor aresta que consigo alcancar a partir dos vertices visitados
		int menorPesoAresta = INT_MAX;
		u = 0;
		v = 0;
		//primeiramente eu visito um vertice
		for (int i = 0; i < vertice; i++)
		{
			//verifico se ela ja foi visitado. Se sim, entao eu posso buscar chegar em outros vertices atraves de arestas ligadas nele
			if (visitados[i])
			{
				//entao eu avalio a quais vertices consigo chegar
				for (int j = 0; j < vertice; j++)
				{
					//verifico se o vertice alvo nao esta visitado e se esta na matriz
					if (!visitados[j] && matriz[i][j])
					{
						//e aqui eu quero salvar a menor aresta possivel e quais os vertices que a compoe
						if (menorPesoAresta > matriz[i][j])
						{
							menorPesoAresta = matriz[i][j];
							u = i;
							v = j;
						}
					}
				}
			}
		}
		/*
		quando sair desses loops eu tenho a melhor opcao armazenada nas minhas variaveis
		achei interessante deixar salvo informacoes das arestas escolhidas entao eu as guardei em um struct

		obs: professor, tive que colocar essa adaptacao no codigo pois em alguns casos eu estava printando os vertices em ordem invertida em relacao a saida espera
		no caso  de teste 2 a minha saida era a primeira coluna e a espera era a segunda:
		(0,1)			(0,1)
		(0,8)			(0,8)
		(1,3)			(1,3)
		(3,7)			(3,7)
		(8,2)			(2,8)  -Ordem invertida
		(2,4)			(2,4)
		(2,5)			(2,5)
		(5,9)			(5,9)
		(8,6)			(6,8)  --Ordem invertida
		*/
		if(u >= v)
		{
			arestasEscolhidas[contAresta].first = v;
			arestasEscolhidas[contAresta].second = u;
		}
		else
		{
			arestasEscolhidas[contAresta].first = u;
			arestasEscolhidas[contAresta].second = v;
		}
		//o meu codigo anterior tinha apenas das duas linha abaixo
		//arestasEscolhidas[contAresta].first = u;
		//arestasEscolhidas[contAresta].second = v;
		arestasEscolhidas[contAresta].peso = matriz[u][v];
		//marco o vertice que eu cheguei como visitado
		visitados[v] = true;
		//e aumento o numero de arestas percorridas
		contAresta++;
	}
	for(int i = 0; i < contAresta; i++)
	{
		printf("(%d,%d)\n", arestasEscolhidas[i].first, arestasEscolhidas[i].second);
		custo_arvore += arestasEscolhidas[i].peso;
	}
	//**************************

	printf("%d\n", custo_arvore);
	for( u = 0; u < vertice; u++) free(matriz[u]);
	free(matriz);
	return 0;
}

















