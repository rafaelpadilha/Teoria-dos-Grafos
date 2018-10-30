#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"

#define INFINITY 999

void dijkstra(Graph* graph, int ordem, int startnode)
{

    int cost[ordem][ordem], distance[ordem], pred[ordem], visited[ordem], adjMatrix[ordem][ordem], count, mindistance, nextnode, i, j, y;

    //inicializa matriz de adjacencias.
    for(int x=0; x<ordem; x++)
        for(int y=0; y<ordem; y++)
            adjMatrix[x][y] = 0;

    //Varre a lista de adjacencias de cada vertice e adiciona os pesos de cada caminho na respectiva posi��o da matriz de adjacencias
    for(int x=0; x<6; x++)
        if(graph->head[x] != NULL)
        {
            Node* tmp = graph->head[x]->head;
            while(tmp != NULL)
            {
                y = busca_noh(tmp->dest, graph, ordem);
                adjMatrix[x][y] = tmp->weight;
                tmp = tmp->next;
            }
        }

    //Imprime "lista" de adjacencias (0 significa que n�o existe caminho entre o v�rtice x ao v�rtice y)
    printf("\n\n***** Matriz de Adjac�ncias *****\n");
    printf("    ");
    for(int x=0; x<ordem; x++)
        printf(" %c   ", graph->head[x]->info);
    for(int x=0; x<ordem; x++)
    {
        printf("\n%c", graph->head[x]->info);
        for(int y=0; y<ordem; y++)
            printf("    %d", adjMatrix[x][y]);
    }
    printf("\n\n");

    //pred[] - guarda o predecessor de cada n�
    //count - quantidade de n�s visitados at� o momento
    //cria a matriz de custos
    for(i=0; i<ordem; i++)
        for(j=0; j<ordem; j++)
            if(adjMatrix[i][j]==0)
            {
                cost[i][j]=INFINITY;
            }
            else
                cost[i][j]=adjMatrix[i][j];

    //inicializa pred[], distance[] and visited[]
    for(i=0; i<ordem; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1; //define o n� de in�cio como j� visitado
    count = 1;

    while(count<ordem-1)
    {
        mindistance = INFINITY;

        //nextnode informa a posi��o do n� que est� a uma dist�ncia m�nima
        for(i=0; i<ordem; i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        //Confere se existe um caminho de menos dist�ncia a partir do n�
        visited[nextnode]=1;
        for(i=0; i<ordem; i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }

    //imprime o caminho e dist�ncia at� cada v�rtice
    for(i=0; i<ordem; i++)
    {
        if(i!=startnode)
        {
            if(distance[i] != 999)
            {
                printf("\nDistancia ate '%c' = %d",graph->head[i]->info,distance[i]);
                printf("\nCaminho de '%c' ate '%c': (%c) ", graph->head[startnode]->info, graph->head[i]->info, graph->head[i]->info);

                j=i;
                do
                {
                    j=pred[j];
                    printf("<- (%c) ",graph->head[j]->info);
                }
                while(j != startnode);
                printf("\n");
            }
            else
            {
                printf("\nDistancia ate '%c' = INFINITA",graph->head[i]->info);
                printf("\nNao existe caminho de '%c' ate '%c' :( \n", graph->head[startnode]->info, graph->head[i]->info);
            }
        }
    }
}
