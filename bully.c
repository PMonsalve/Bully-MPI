#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

/*  não entendi o cluster, se era algo dos processos maiores ou o que, vou ver com calma amanha nao to conseguindo pensar

/* O que o Gerson mandou no email

int recv, flag;
MPI_Request req;
MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,DATA,MPI_COMM,WORLD, &req);
sleep(5); // aguarda 5 segundos
MPI_Test(*req, &flag, status);
if(flag == true) Então recebeu mensagem (lider acordado)
else Não recebeu, lider falhou
*/

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

int main(int argc, char** argv){
    int process_Rank, size_Of_Cluster, message_Item, DATA;
    int n, result_random = 0, i, elected_process;
    int recv, flag;
    MPI_Status *status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    elected_process = size_Of_Cluster -1;
    
    while(1){
            
        if(process_Rank != elected_process){
        message_Item = 123;
        MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
        printf("Mensagem enviada de %d\n",process_Rank);
        }else if(process_Rank == elected_process){
            MPI_Request req;
            MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,DATA,MPI_COMM_WORLD, &req);
            sleep(5);
            MPI_Test(*req, &flag, status);
            if(flag == 1){
                printf("Lider recebeu a mensagem.\n");
                if(random_number(1))
                    printf("Lider segue ativo.\n");
                else{
                    printf("Lider dormiu.\n");
                }
            }
        }
            //elected_process= election(&process_Rank,&size_Of_Cluster); chamada da função da eleição com o processo atual e o grupo de processos
    }
    MPI_Finalize();
    return 0;
}

/* PROTOTIPO DE ENVIO DE MESAGENS ENTRE PROCESSOS NORMAIS E LIDERES
if(process_Rank != elected_process){
        message_Item = 123;
        MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
        printf("Mensagem enviada: %d\n", message_Item);
    }


int recv, flag;
MPI_Request req;
MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,DATA,MPI_COMM,WORLD, &req);
sleep(5); // aguarda 5 segundos
MPI_Test(*req, &flag, status);
if(flag == true) Então recebeu mensagem (lider acordado)
else Não recebeu, lider falhou


    else if(process_Rank == elected_process){
*///        MPI_Recv(&message_Item, 1, MPI_INT, /*de quem recebeu a msg, colocar variavel no lugar do 0*/0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
/*        printf("Message Received: %d\n", message_Item);
    }
*/

