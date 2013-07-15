#include <stdio.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <string.h>
//Cadastra
#define cadprog   ((u_long)150000)
#define cadver    ((u_long)1)
#define cadproc   ((u_long)1) 
//Atualiza
#define atuaprog  ((u_long)150100)
#define atuaver   ((u_long)1)
#define atuaproc  ((u_long)1)
//Deleta
#define delprog   ((u_long)150200)
#define delver    ((u_long)1)
#define delproc   ((u_long)1)
//Consulta
#define conprog   ((u_long)150300)
#define conver    ((u_long)1)
#define conproc   ((u_long)1)


main(argc, argv)
   int argc;
   char *argv[];
{
   char* innumber = malloc(64);
   char* outnumber = malloc(64);
   int error;
   int on = 1;
   while(on ==1){
        printf("Selecione a opcao desejada \n");
        printf("1 - Armazenar / Atualizar \n");
        printf("2 - Remover um registro \n");
        printf("3 - Acessar um registro \n");
        printf("4 - Finalizar aplicacao \n");
        int opcao;
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
            {
                setbuf(stdin, NULL);
                char nome[50];
                char telefone[50];
                char final[100];
                printf("\n\n Opcao escolhida: Armazenar / Atualizar um registro \n");
                setbuf(stdin, NULL);
                printf("Entre com o nome do contato ");
                scanf("%[^\n]", nome);
                setbuf(stdin, NULL);
                strcat(nome,"#");
                strcpy(final,nome);
                printf("Entre com o telefone do contato ");
                scanf("%[^\n]",telefone);
                setbuf(stdin, NULL);
                strcat(telefone,"#");
                strcat(final,telefone);
                innumber = final;
                strcpy(outnumber,"");
                callrpc(argv[1],cadprog,cadver,cadproc,xdr_wrapstring,&innumber,xdr_wrapstring,&outnumber);
                if (!strcmp(outnumber, "Existe!")) {
                    printf("Atencao: ja existe contato registrado com este nome! \n");
                    printf("Voce deseja atualizar esse contato com o telefone informado? \n");
                    printf("1 - SIM \n");
                    printf("2 - NAO \n");
                    int atualiza;
                    scanf("%d", &atualiza);
                    setbuf(stdin, NULL);
                    if(atualiza == 1){
                        printf("Entrando em atualizacao!!");
                        setbuf(stdin, NULL);
                        callrpc(argv[1],atuaprog,atuaver,atuaproc,xdr_wrapstring,&innumber,xdr_wrapstring,&outnumber);
                        printf("%s \n",outnumber);
                    } else{
                        printf("O contato sera mantido com os dados anteriores \n");
                    }
                } else{
                    printf("%s \n",outnumber);
                }
                break;
            }

            case 2:
            {
                setbuf(stdin, NULL);
                printf("\n\n Opcao escolhida: Remover um registro!! \n");
                char nome[50];;
                printf("Entre com o nome do contato ");
                scanf("%[^\n]", nome);
                setbuf(stdin, NULL);
                innumber = nome;
                strcpy(outnumber,"");
                callrpc(argv[1],delprog,delver,delproc,xdr_wrapstring,&innumber,xdr_wrapstring,&outnumber);
                printf("%s \n",outnumber);
                break;
            }
            case 3:
            {
                setbuf(stdin, NULL);
                printf("\n\n Opcao escolhida: Acessar um registro!! \n");
                char nome[50];
                printf("Entre com o nome do contato ");
                scanf("%[^\n]", nome);;
                setbuf(stdin, NULL);
                innumber = nome;
                strcpy(outnumber,"");
                callrpc(argv[1],conprog,conver,conproc,xdr_wrapstring,&innumber,xdr_wrapstring,&outnumber);
                printf("%s \n",outnumber);
                break;
            }
            case 4:
            {
                printf("\n\n Opcao escolhida: Finalizar Aplicacao!! \n");
                exit(0);
                on = 0;
                break;

            }

        }

   }

}

