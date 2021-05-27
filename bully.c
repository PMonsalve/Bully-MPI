//Integrantes: Pedro Monsalve, Taíne Freitas e Tamires Rodrigues

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

int main(int argc, char** argv){
    int process_Rank, size_Of_Cluster, message_Item, DATA;
    int n, result_random = 0, i, elected_process;
    int recv, flag=0, flag2, dormiu=0;
    int *inativos;
    int current_process, j, aux, resposta;
    double start,end,total;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
    MPI_Status status;
    MPI_Request req;
    inativos = malloc(size_Of_Cluster * sizeof(int));

    //Buffer de processos inativos
    for(i=0;i<size_Of_Cluster;i++){
        inativos[i]=i;
    }
    current_process=0;
    elected_process = size_Of_Cluster -1;
    while(1){
        //Envia mensagem dos processos para o líder
        for(i=0;i<size_Of_Cluster;i++){ 
     
            if(current_process != elected_process){
                message_Item = 123;
                start=MPI_Wtime();
           //     MPI_Irecv(&inativos,size_Of_Cluster,MPI_INT,MPI_ANY_SOURCE,DATA,MPI_COMM_WORLD, &req);
                MPI_Send(&inativos, size_Of_Cluster, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
                sleep(1);
     //           MPI_Test(&req, &flag, &status);
                printf("Mensagem enviada de %d\n",process_Rank);
                current_process = process_Rank;              
            }
            //Teste se o líder recebeu a mensagem
            if(process_Rank == elected_process){
                
                MPI_Recv(&recv, size_Of_Cluster, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Lider recebeu a mensagem do processador %d.\n",status.MPI_SOURCE);
            //Nova Eleição
            }else{
                printf("Lider dormiu.\n");
                dormiu=1;
                inativos[elected_process]=1;
                while (1){
                    for(j=current_process+1; j<size_Of_Cluster; j++){
                        if (j!=elected_process){
                            message_Item = 456;
                            MPI_Send(&message_Item, 1, MPI_INT, j, 1, MPI_COMM_WORLD);
      //                      MPI_Test(&req, &flag2, &status);
                            printf("Messagens de eleição enviadas do processo %d\n",current_process);
                            resposta=0;
                            aux = current_process;
                            if (process_Rank == j){
                                MPI_Recv(&message_Item, 1, MPI_INT, current_process, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                                printf("Messagem recebida, tem processos maiores\n");
                                current_process = j;
                                resposta=1;
                            }            
                        }                                            
                    }
                    //Líder Definido
                    if(resposta==0)
                        printf("Novo lider: %d\n",aux);
                    elected_process = aux;  
                    break;
                }
            }
            //Auxilia a sincronização dos processos
            MPI_Barrier(MPI_COMM_WORLD);
        }   
        //Tempo de execução do processo 
        end = MPI_Wtime();
        printf("\nTempo decorrido: %f.3\n", end-start); 
    }
    MPI_Finalize();
    return 0;
}
