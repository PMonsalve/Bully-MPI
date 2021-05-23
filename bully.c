#include <stdio.h>
#include <stdlib.h>

//Função random
int random_number (int max){
    int result;
    result = rand() % max;
    return result;
}

void main(){
    int n, result_random = 0, i, *vector_process, elected_process, isRecieved;
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
                i = -1;
            }else{
                printf("Líder recebeu a mensagem\n");
            }
        }
    }
}