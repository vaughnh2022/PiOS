#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include "fat.h"
int fd = 0;
char sector_buf[512];
char rde_region[2048];
void init() {
  fd = open("disk.img", O_RDONLY);
  if(fd < 0) {
    perror("open");
    fprintf(stderr, "open() failed\n");
    exit(-1);
  }
}

void readSector(uint64_t sector,
                char *buf) {
  off_t o = lseek(fd, 512*sector, SEEK_SET);
  size_t n = read(fd, buf, 512);
}

int main() {
  struct boot_sector *bs = (struct boot_sector*)sector_buf;
  struct root_directory_entry *rde = (struct root_directory_entry*)rde_region;
  init();
  readSector(0, sector_buf);

  printf("\n");
  printf("bytes per sector = %d\n", bs->bytes_per_sector);
  printf("sectors per cluster = %d\n", bs->num_sectors_per_cluster);
  printf("reserved sectors = %d\n", bs->num_reserved_sectors);
  printf("number of FATs = %d\n", bs->num_fat_tables);
  printf("number of RDEs = %d\n", bs->num_root_dir_entries);

  readSector(bs->num_reserved_sectors +
             bs->num_fat_tables * bs->num_sectors_per_fat,
             rde_region);
  for(int k = 0; k < 8; k++) {
   printf("name of file %d is \"%s\"\n", k, rde[k].file_name);
  }
  for(int k = 0; k < 16; k++) {
    printf("%02x ", rde_region[k]);
  }
  return 0;
}

















