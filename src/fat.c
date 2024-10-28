#include "fat.h"
#include "sd.h" // See this file for function prototype of ata_lba_read()
struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;

int fatInit() {
   sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
   bs = bootSector; // Point boot_sector struct to the boot sector so we can read fields
   // Print out some of the elements of the BIOS information block using rprintf...
   if(bs->boot_signature!=0xaa55){// Validate the boot signature = 0xaa55
      return 1;
   }
   char fatCheck[10]="";
   int x=0;
   while(bs->fs_type[x]!=' '){
      char temp[2];
      temp[0]=bs->fs_type[x];
      temp[1]="\0";
      strcat(fatCheck,temp);
      x++;
   }
   if(strcmp(fatCheck,"FAT16")!=0){//Validate fs_type = "FAT16" using strcmp
      return 1;
   }
   sd_readblock(bs->num_reserved+sectors,fat_table,bs->num_sectors_per_fat);// Read FAT table from the SD card into array fat_table
   root_sector=bs->num_fat_tables+bs->num_sectors_per_fat+bs->num_reserved_sectors+bs->num_hidden_sectors;
   return 0;
}

void fatOpen(){
   char holder[8*512]; 
   for(int a=0;a<bs->num_root_dir_entries;a++){
      sd_readblock(root_sector+(a/32),holder,1);
      struct root_directory_entry *sectorHolder = (struct root_directory_entry) holder;
   }
}

void fatRead(){
}
