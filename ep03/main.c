#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define ITER 10000


int main()
{

  // para aproximação com pi
  unsigned long int dentro  =0;
  int i;
  for (i = 0; i < ITER; i++)
  {  
    pid_t p = fork();
    
    // Fork: Falha do fork
    if(p<0)
    {
      perror("Falha no fork");
      exit(1);
    } 

    // Fork: Processo pai
    else if (p != 0) 
    {
      //espera filho
      waitpid(p, 0, 0);
      // lê o arquivo
      FILE *file = fopen("comms", "r");
      char buffer[18];
      fgets(buffer, 18, file);
      fclose(file);

      // arruma a strinh
      buffer[17] = 0;
      buffer[8] = 0;
      char *val1 = &buffer[0];
      char *val2 = &buffer[9];
      
      double fval1 = atof(val1);
      double fval2 = atof(val2);    
      
      // pega a distância do centro (vê se está dentro no círculo)
      double length = sqrt(fval1*fval1 + fval2*fval2);
      if (length <= 1.0) {
        dentro += 1;
      }
    }

    // Fork: Processo filho
    else 
    {
      srand(i*time(NULL) + i%time(NULL));
      float val1 =(float)rand()/(float)(RAND_MAX);
      float val2 =(float)rand()/(float)(RAND_MAX);
      FILE *file = fopen("comms", "w");
      fprintf(file, "%.6f:%.6f", val1, val2);
      fclose(file);
      return 0;
    }
  }

  printf("\nNúmero de pontos gerados .........: %d", i);
  printf("\nNúmero de pontos dentro do círculo: %lu", dentro);

  double prop = (double)i/dentro;
  printf("\n\nProporção total/fora :%f", prop);
  printf("  \nAproximação de PI....:%f", 4/prop);
  return 0;
}
