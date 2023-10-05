// importa alocação junto
#include "../libs/j_strings.h"
#include <stdio.h>
#include <stdlib.h>
struct partition {
 unsigned char status;
 unsigned char CHSfirst[3];
 unsigned char filesystem;
 unsigned char CHSlast[3];
 unsigned char lba[4];
 unsigned char nsectors[4];
};

struct mbr{
  unsigned char bootstrap[446];
  struct partition partition[4];
  unsigned char signature[2];
};

/// retorna quantos argumentos há para a flag
int get_argsize(int index, char **argv) {
  int size = 0;
  index += 1; // sai da flag
  while (argv[index] != 0) {
    if (argv[index][0] == '-')
      return size;

    size++;
    index++;
  }
  return size;
}

/// transfere n bytes para um inteiro
unsigned int get_nbytes_toint(unsigned char *ptr, int n) {

  unsigned int num = 0;
  unsigned char auxptr[] = {0, 0, 0, 0};
  for (int i = 0; i < n; i++) {
    auxptr[i] = ptr[i];
  }

  // 20 21 00
  num = *((int*)auxptr);
  return num;
}

/// main
int main(int argc, char **argv) {
  // parse args
  if (argc <= 1) {
    return 0;
  }

  int index = 0;
  while(index < argc) {
    int argsize = get_argsize(index, argv);

    // list disk and partitions
    if (str_match(argv[index], "-l")) {
      // list all
      if (argsize == 0) {

      }

      // list selected
      else {
        for (int j = 1; j <= argsize; j++) {

          char *filename = argv[index+j];
          FILE *filepointer = fopen(filename, "r");
          struct mbr mbr;

          if (filepointer != 0) {
            fread((void *) &mbr, 1, 512, filepointer);
            if (mbr.signature[0] == 0x55 && mbr.signature[1] == 0xaa) {

              for (int i = 0; i < 4; i++) {
                struct partition * partition = &mbr.partition[i];
                unsigned int filesystem = (unsigned int) partition->filesystem;
                unsigned int lba = get_nbytes_toint(partition->lba, 4);
                unsigned int sectors = get_nbytes_toint(partition->nsectors, 4);
                unsigned int bytes = 512*sectors;
                unsigned int c = 0, aux = bytes;
                unsigned int end = sectors + lba - 1;

                while (aux/1024 >= 1) {
                  c += 1;
                  aux /= 1024;
                  if (c == 3) break;
                }

                const char *notation = 0;
                if (c == 1) {
                  notation = "KiB";
                } else if (c == 2) {
                  notation = "Mib";
                } else if (c >= 3) {
                  notation = "Gib";
                }

                printf("\n  %12s%d: %d %s,  %d bytes,  %d sectors", filename, i, aux, notation, bytes, sectors);
                printf("\n  %12c   begin: %d,  end: %d,  id: %d", ' ', lba, end, filesystem);
                printf("\n");

              }

            }
            fclose(filepointer);
          } else {
            printf("jdisk: cannot open %s: No such file or directory", filename);

          }
        }
      }
    }

    index+=argsize+1;
  }

  return 0;
}
