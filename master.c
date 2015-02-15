/*
 * master.c - a very small MODBUS master example
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <modbus.h>

int main(void) {
  int i, j;
  modbus_t *ctx;
  int rc;
  int addr = 1;
  int16_t regs[10] = {101, 102 };
  int16_t regs2[10];
  int nb = sizeof(regs)/sizeof(int16_t);
  
  // connect to server
  ctx = modbus_new_tcp("127.0.0.1", 1502); 
  if (modbus_connect(ctx) == -1) {
    fprintf(stderr,"Connection failed: %s\n",modbus_strerror(errno));
    modbus_free(ctx);
    exit(101);
  }
  modbus_set_debug(ctx, FALSE);
  
  // write regs
  for(i = 0; i != 10; i++) {
    for(j = 0; j != nb; j++) {
      regs[j] = rand() % 100;
    }
    rc = modbus_write_registers(ctx, 1, nb, regs);
    if (rc != nb) {
      printf("ERROR modbus_write_registers (%d)\n", rc);
      printf("Address = %d, nb = %d\n", 1, nb);
      exit(102);
    } 
    rc = modbus_read_registers(ctx, 1, nb, regs2);
    if (rc != nb) {
      printf("ERROR modbus_read_registers (%d)\n", rc);
      printf("Address = %d, nb = %d\n", addr, nb);
      exit(102);
    } 
    
    // print and check the response
    printf("regs2[] =\t");
    for(j = 0; j != nb; j++) {
      if(regs[j] != regs2[j]) {
	printf("FAILED to read back what we wrote at %d\n", j);
	exit(103);
      }
      printf("%d ", regs2[j] );
    }
    printf("\n");
  }

  exit(0);
}
