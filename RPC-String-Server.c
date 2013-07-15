#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdbm.h>

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
#define datum_set(um, buf) { um.dptr = buf; um.dsize = strlen(buf); }


main()
{

   char **cadastro(char**);
   char **atualiza(char**);
   char **deleta(char**);
   char **consulta(char**);
   //Cadastro
   registerrpc(cadprog,cadver,cadproc,cadastro,xdr_wrapstring,xdr_wrapstring);
   //Atualiza
   registerrpc(atuaprog,atuaver,atuaproc,atualiza,xdr_wrapstring,xdr_wrapstring);
   //Deleta
   registerrpc(delprog,delver,delproc,deleta,xdr_wrapstring,xdr_wrapstring);
   //Consulta
   registerrpc(conprog,conver,conproc,consulta,xdr_wrapstring,xdr_wrapstring);

   printf("String Registration with Port Mapper completed\n");
   svc_run();
   printf("Error:svc_run returned!\n");
   exit(1);
}

char **
cadastro(in)
   char **in;
{
   char* dbname = "bdsd";
   char *out = malloc(64);
   char manipula[500];
   strcpy(manipula,"");
   int limitenome = 0;
   int limitetelefone = 0;
   char nome[500];
   char telefone[500];
   char aux[500];
   char aux2[500];
   char *ptr;
   memset(manipula, 0, 500);
   strcpy(manipula, *in);
   memset(telefone, 0, 500);
   memset(nome, 0, 500);
   memset(aux, 0, 500);
   memset(aux2, 0, 500);
   //printf("RECEBENDO: %s \n",*in);
   ptr = strchr(manipula, '#');
   if (*ptr)
      {
        limitenome = 0;
        limitenome = ptr - manipula;
      }
  // printf("LIMITE NOME: %d \n",limitenome);
   ptr = strrchr(manipula, '#');
   if (*ptr)
      {
        limitetelefone = 0;
        limitetelefone = ptr - manipula;
      }
  // printf("LIMITE TELEFONE: %d \n",limitetelefone);
   int i;
   int j;
   for(i = 0 ; i < limitenome ; i++){
      //   printf("Fazendo posicao: %d \n",i);
         nome[i]=0;
         char letra = manipula[i];
        // printf("Letra: %c",letra);
         nome[i]=letra;
         
   }
   int sizetel = limitetelefone - limitenome - 1;
   for(j = 0 ; j < sizetel  ; j++){
        // printf("Fazendo posicao: %d \n",j);
         aux[j]="";
         char numero = manipula[limitenome + j + 1];
      //   printf("Numero: %c",numero);
         aux[j]=numero;
         
   }
   strcpy(telefone,"");
   int x;
   for(x = 0 ; x < sizetel ; x++){
      aux2[x] = aux[x];
   }
   int o;
   for(o = 0 ; o < sizetel ; o++){
      telefone[o] = aux2[o];
   }
   GDBM_FILE dbf;
   datum key,data;
   datum_set(key, nome);
   datum_set(data, telefone);
   if (!(dbf = gdbm_open(dbname, 0, GDBM_WRCREAT, 0644, NULL))) {
            strcpy(out, "Erro na conexao com o banco de dados");
        }
   if(gdbm_store(dbf,key,data,GDBM_INSERT)){
      strcpy(out, "Existe!");
   } else{
    //  printf("Fazendo a insercao do contato: %s \n",nome);
    //  printf("com o telefone: %s \n",telefone);
      strcpy(out, "Contato gravado com sucesso!");
   }
   gdbm_close(dbf);
   return (&out);
}

char **
atualiza(in)
   char **in;
{
  // printf("RECEBENDO: %s \n",*in);
   char* dbname = "bdsd";
   char *out = malloc(64);
   char manipulaAt[500];
   int limitenomeAt = 0;
   int limitetelefoneAt = 0;
   char nomeAt[500];
   char telefoneAt[500];
   char aux[500];
   char aux2[500];
   char *ptrAt;
   memset(manipulaAt, 0, 500);
   strcpy(manipulaAt, *in);

   int p;
   for(p = 0 ; p < 500 ; p++){
      telefoneAt[p] = "";
   }
   memset(telefoneAt, 0, 500);
   memset(nomeAt, 0, 500);
   memset(aux, 0, 500);
   memset(aux2, 0, 500);
   ptrAt = strchr(manipulaAt, '#');
   if (*ptrAt)
      {
        limitenomeAt = ptrAt - manipulaAt;
      }
  // printf("LIMITE NOME: %d \n",limitenomeAt);
   ptrAt = strrchr(manipulaAt, '#');
   if (*ptrAt)
      {
        limitetelefoneAt = ptrAt - manipulaAt;
      }
  // printf("LIMITE TELEFONE: %d \n",limitetelefoneAt);
   int i;
   int j;
   for(i = 0 ; i < limitenomeAt ; i++){
     //    printf("Fazendo posicao: %d \n",i);
         nomeAt[i]=0;
         char letra = manipulaAt[i];
   //      printf("Letra: %c",letra);
         nomeAt[i]=letra;
         
   }
   strcpy(telefoneAt,"");
   int sizetel = limitetelefoneAt - limitenomeAt - 1;
   for(j = 0 ; j < sizetel  ; j++){
     //    printf("Fazendo posicao: %d \n",j);
         aux[j]="";
         char numero = manipulaAt[limitenomeAt + j + 1];
     //    printf("Numero: %c",numero);
         aux[j]=numero;     
   }
   
   int k;
   for(k = 0 ; k < sizetel ; k++){
      aux2[k] = aux[k];
   }
   int o;
   for(o = 0 ; o < sizetel ; o++){
      telefoneAt[o] = aux2[o];
   }
   GDBM_FILE dbf;
   datum key,data;
   datum_set(key, nomeAt);
   datum_set(data, telefoneAt);
   if (!(dbf = gdbm_open(dbname, 0, GDBM_WRCREAT, 0644, NULL))) {
            strcpy(out, "Erro na conexao com o banco de dados");
        }
   gdbm_delete(dbf, key);
   gdbm_store(dbf, key, data, GDBM_INSERT);
 //  printf("Fazendo atualizacao do contato com nome: %s \n",nomeAt);
 //  printf("Com o telefone: %s \n",telefoneAt);
   strcpy(out, "Contato atualizado com sucesso!!!");
   gdbm_close(dbf);
   return (&out);


}

char **
deleta(in)
   char **in;
{

   char* dbname = "bdsd";
   GDBM_FILE dbf;
   datum key,data;
   char manipula[500];
   strcpy(manipula,"");
   strcpy(manipula, *in);
   key.dptr = manipula;
   key.dsize = strlen(manipula);
   char *out = malloc(64);
      if (!(dbf = gdbm_open(dbname, 0, GDBM_WRCREAT, 0644, NULL))) {
            strcpy(out, "Erro na conexao com o banco de dados");
        }
      if (gdbm_delete(dbf, key)) {
                strcpy(out, "Contato solicitado nao foi encontrado!");
                gdbm_close(dbf);
            } else {
         //       printf("Apagando contato com o nome: %s \n",manipula);
                strcpy(out, "Contato Apagado Com Sucesso");
                gdbm_close(dbf);

            };         
   return (&out);

}

char **
consulta(in)
   char **in;
{

   char *out = malloc(64);
   char* dbname = "bdsd";
   GDBM_FILE dbf;
   datum key,data;
   char manipulaCon[500];
   strcpy(manipulaCon,"");
   strcpy(manipulaCon, *in);
   key.dptr = manipulaCon;
   key.dsize = strlen(manipulaCon);
         if (!(dbf = gdbm_open(dbname, 0, GDBM_WRCREAT, 0644, NULL))) {
            strcpy(out, "Erro na conexao com o banco de dados");
        }
   if (!gdbm_exists(dbf, key)) {
      strcpy(out, "Contato solicitado nao existe");
   } else{
  //    printf("Recuperando contato com o nome: %s \n",manipulaCon);
      data = gdbm_fetch(dbf, key);
      strcpy(out, data.dptr);
   }
   return (&out);

}

