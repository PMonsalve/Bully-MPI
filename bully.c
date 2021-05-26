#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

/* o que pensei aqui ele faz um vetor com os maiores, salva o numero e usa pra mandar a mensagem 
sem modificar o current_process por que caso nenhum responda o lider e ele.
Duvida, como que sei que respondeu a mensagem pra poder eleger o lider?
*/
/*
int election (int current_process, int cluster, int previous_leader, int* inativos){
    int aux = current_process;
    int array[cluster]; 
    int i = 0, message_Item, j;
    //int new_leader = current_process;
    int resposta;

    printf("\nInicio da eleição.\n");
    //while (i < cluster){
    //    array [i] = i;
    //    i++;
    //}
    
    while (1){
        //for (j=current_process; j<cluster; j++){ // pra testar sempre do processo atual ate o cluster, 
        //quando muda nao o processo atual que ta enviando as mensagens o for muda tb pra nao repetir testes com anteriores
            //if(j==current_process){
                for(i=current_process+1; i<cluster; i++){
                    message_Item = 456;
                    MPI_Send(&message_Item, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                    printf("Messagens de eleição enviadas do processo %d\n",current_process);
                   // resposta=0;
                    if ()
                        MPI_Recv(&message_Item, 1, MPI_INT, current_process, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        printf("Messagem recebida, tem processos maiores\n");
                        aux=current_process;
                        current_process=i;
                    //resposta=1;
                    
                    
                }
            //}
            //if((j>current_process) && (j!=previous_leader)){
            //        MPI_Recv(&message_Item, 1, MPI_INT, current_process, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //        printf("Messagem recebida, tem processos maiores\n");
                    //new_leader = array[j]; // acredito que possa funcionar, atualiza sempre que recebe uma mensagem
                    //current_process = array[j]; // muda o processo atual
            //        resposta=1;
            //        aux=j;
            //}
        }
        if(resposta==0)
            printf("Novo lider: %d\n",aux);
            return aux;
        //if (current_aux == current_process) // se o anterior e igual ao processo atua quer dizer que ninguem respondeu retorna o new_leader
        // salvo por ultimo 
        //    return new_leader;
        //if (current_process == cluster) // aqui e um teste pra saber se o maior respondeu, ele enviou mensagem pra todos e o atual 
        //e o cluster, no caso o maior
        //    return new_leader;
        //else // se nao aconteceu nenhum caso anterior ele atualiza o processo atual com o new_leader e tenta enviar as mensagens a partir dele
        //    current_process = new_leader;
    //}
    //return new_leader;
}   
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
    int recv, flag, dormiu=0;
    int *inativos;
    int current_process, j, aux, resposta;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    inativos = malloc(size_Of_Cluster * sizeof(int));
    for(i=0;i<size_Of_Cluster;i++){
        inativos[i]=0;
    }

    elected_process = size_Of_Cluster -1;
    
    while(1){
        // duvida : por que é <=size_Of_Cluster e não < ? isso interfere na minha definição lá kkk talvez, pode ser que precise decrementar um se for menor
        for(i=0;i<size_Of_Cluster;i++){      
            if(process_Rank != elected_process){
                message_Item = 123;
                MPI_Send(&message_Item, 1, MPI_INT, elected_process, 1, MPI_COMM_WORLD);
                printf("Mensagem enviada de %d\n",process_Rank);
                current_process = process_Rank;
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
                    if(random_number(100)>90)
                        printf("Lider segue ativo.\n");
                    else{
                        printf("Lider dormiu.\n");
                        dormiu=1;
                        inativos[elected_process]=1;
                        while (1){
                            for(j=current_process+1; j<size_Of_Cluster; j++){
                                if (j!=inativos[elected_process]){
                                    message_Item = 456;
                                    MPI_Send(&message_Item, 1, MPI_INT, j, 1, MPI_COMM_WORLD);
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
                                
                        }
                        if(resposta==0)
                            printf("Novo lider: %d\n",aux);
                            return aux;   
                        //fazer o sleep e futuramente a eleição
                    }
                }
            }
            //if(dormiu){
            //    elected_process = election(process_Rank, size_Of_Cluster,elected_process);
            //    dormiu=0;
            //}
            MPI_Barrier(MPI_COMM_WORLD);
        }     
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