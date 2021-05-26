#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

/* o que pensei aqui ele faz um vetor com os maiores, salva o numero e usa pra mandar a mensagem 
sem modificar o current_process por que caso nenhum responda o lider e ele.
Duvida, como que sei que respondeu a mensagem pra poder eleger o lider?
*/

int election (int current_process, int cluster){
    int aux = current_process + 1;
    int array[cluster]; 
    int i = 0;
    int j, new_leader = current_process;

    while (aux <= cluster){
        array [i] = aux;
        aux++;
        i++;
    }

    while (1){
        for (j=current_process; j<=cluster; j++){ // pra testar sempre do processo atual ate o cluster, 
        //quando muda nao o processo atual que ta enviando as mensagens o for muda tb pra nao repetir testes com anteriores
            if(process_Rank == current_process){
                message_Item = 456;
                MPI_Send(&message_Item, 1, MPI_INT, array[j], 1, MPI_COMM_WORLD);
                printf("Message Sent: %d\n", message_Item);
            }

            else if(process_Rank == array[j]){
                MPI_Recv(&message_Item, 1, MPI_INT, current_process, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Message Received: %d\n", message_Item);
                new_leader = array[j]; // acredito que possa funcionar, atualiza sempre que recebe uma mensagem
                current_process = array[j]; // muda o processo atual
            }
        }
        if (current_aux == current_process) // se o anterior e igual ao processo atua quer dizer que ninguem respondeu retorna o new_leader
        // salvo por ultimo 
            return new_leader;
        if (current_process == cluster) // aqui e um teste pra saber se o maior respondeu, ele enviou mensagem pra todos e o atual 
        //e o cluster, no caso o maior
            return new_leader;
        else // se nao aconteceu nenhum caso anterior ele atualiza o processo atual com o new_leader e tenta enviar as mensagens a partir dele
            current_process = new_leader;
    }
    return new_leader;
}   

/*
int greater(int current_process, int cluster){
    //função para definir os processos maiores, por exemplo os processos 5, 6 e 7 são processos maiores que 4
    //cluster é o grupo de processos, current_process é pra ver quais são maiores que ele
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
    int n, result_random = 0, i, elected_process, enviando;
    int recv, flag;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    elected_process = size_Of_Cluster -1;
    
    while(1){
        // duvida : por que é <=size_Of_Cluster e não < ? isso interfere na minha definição lá kkk talvez, pode ser que precise decrementar um se for menor
    for(i=0;i<=size_Of_Cluster;i++){      
        if(process_Rank != elected_process){
            message_Item = 123;
            MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
            printf("Mensagem enviada de %d\n",process_Rank);
            enviando=process_Rank;
        }else if(process_Rank == elected_process){
            MPI_Status status;
            MPI_Request req;
            //MPI_Irecv(&recv,1,MPI_INT,MPI_ANY_SOURCE,DATA,MPI_COMM_WORLD, &req);
            MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sleep(5);
            //MPI_Test(&req, &flag, &status);
            //printf("Lider recebeu a mensagem. %d\n",status.MPI_SOURCE);
            if(flag){
                printf("Lider recebeu a mensagem do processador %d.\n",status.MPI_SOURCE);
                if(random_number(100)>50)
                    printf("Lider segue ativo.\n");
                else{
                    printf("Lider dormiu.\n");
                    //fazer o sleep e futuramente a eleição
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
            elected_process = election (process_Rank, size_Of_Cluster); 
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