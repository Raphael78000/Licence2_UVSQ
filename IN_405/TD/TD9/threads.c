#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct a_t{
  int* t;
  int s;
};
typedef struct a_t a_t;

void* question1(void* arg){
  printf("Hello World\n");

  return NULL;
}

void* question2(void* arg){
  printf("Nombre généré: %d\n",*(int*)arg);

  return NULL;
}

void* question3(void* arg){
  int* numb = malloc(sizeof(int*));
  *numb = 1 + rand() % 100;
  printf("Nombre généré: %d\n",*numb);

  return numb;
}

void* question4(void* arg){
  int moy = 0;int* tab = (int*) arg;

  for (int i = 0;i < 5;i++){
    moy = moy + tab[i];
  }
  moy = moy / 5;
  printf("Moyenne: %d\n",moy);

  return NULL;
}

void* question5(void* arg){
  a_t* tab = (a_t*) arg;
  int moy = 0;

  for (int i = 0;i < tab->s;i++){
    moy = moy + tab->t[i];
  }
  moy = moy / tab->s;
  printf("Moyenne: %d\n",moy);

  return NULL;
}

int main(int argc,char** argv){
  pthread_t tid;
  int* read;
  a_t t;
  srand(time(NULL));
  printf("Question 1:\n");
  pthread_create(&tid,NULL,question1,NULL); //create a new pthread
  pthread_join(tid,NULL); //join with a terminated thread

  printf("Question 2:\n");
  int numb = 1 + rand() % 100;
  printf("Pere: %d\n",numb);
  pthread_create(&tid,NULL,question2,&numb);
  pthread_join(tid,NULL);

  printf("Question 3: \n");
  pthread_create(&tid,NULL,question3,NULL);
  pthread_join(tid,(void**) &read);
  printf("Pere: %d\n",*read);
  free(read);

  printf("Question 4:\n");
  t.t = malloc(sizeof(int) * 5);
  t.s = 5;
  printf("Pere: tab ->");
  for (int i =0;i < 5;i++){
    t.t[i] = 1 + rand() %100;
    printf(" %d",t.t[i]);
  }
  printf("\n");
  pthread_create(&tid,NULL,question4,t.t);
  pthread_join(tid,NULL);

  printf("Question 5:\n");
  pthread_create(&tid,NULL,question5,&t);
  pthread_join(tid,NULL);
  free(t.t);

  return 0;
}
