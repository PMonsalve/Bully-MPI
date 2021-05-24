#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
int greater(int current_process, int cluster){
    //função para definir os processos maiores, por exemplo os processos 5, 6 e 7 são processos maiores que 4
    return greater_than;
}
// Processo 4 manda mensagem para 5, 6 e 7 querendo resposta, quem responder é um possivel lider e vai repetindo até definir o novo lider
int election(int current_process, int cluster){
    int new_leader;
    while(1){
        if(process_Rank == current_process){
        message_Item = 456;
        MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
        printf("Message Sent: %d\n", message_Item);
    }

    else if(process_Rank == ){
        MPI_Recv(&message_Item, 1, MPI_INT, current_process, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Message Received: %d\n", message_Item);
    }
        return new_leader;
    }
}
*/

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

void main(int argc, char** argv){
    int process_Rank, size_Of_Cluster
    int n, result_random = 0, i, *vector_process, elected_process, isRecieved;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    printf("Entre com o número de processos\n");
    scanf("%d", &n);

    vector_process = malloc(n * sizeof(int));

    //Define se o processo está ativo(1) ou dormindo (0)  
    for (i = 0; i < n; i++){
        vector_process[i] = 0;
    }
    elected_process = i;
    vector_process[elected_process] = 1;

    while(1){
        for(i = 0; i < elected_process; i++){
            printf("Enviando mensagem de %d\n", i);
            //Determina se o processo líder recebeu mensagem ou não
            isRecieved = random_number(2);
            if (isRecieved == 0){
                vector_process[elected_process] = 0;
                elected_process = elected_process -1;
                printf("Líder dormiu, o novo processo líder é: %d\n", elected_process);
                vector_process[elected_process] = 1;
                //elected_process= election(&process_Rank,&size_Of_Cluster); chamada da função da eleição com o processo atual e o grupo de processos
                i = -1;
            }else{
                printf("Líder recebeu a mensagem\n");
            }
        }
    }
    MPI_Finalize();
    return 0;
}
/* PROTOTIPO DE ENVIO DE MESAGENS ENTRE PROCESSOS NORMAIS E LIDERES
if(process_Rank != elected_process){
        message_Item = 123;
        MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
        printf("Message Sent: %d\n", message_Item);
    }

    else if(process_Rank == elected_process){
*///        MPI_Recv(&message_Item, 1, MPI_INT, /*de quem recebeu a msg, colocar variavel no lugar do 0*/0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
/*        printf("Message Received: %d\n", message_Item);
    }
*/

