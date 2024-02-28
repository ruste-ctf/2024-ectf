#ifndef FLASH_H__
#define FLASH_H__
#include <stdint.h>

typedef struct {
    uint32_t flash_magic;
    uint32_t component_cnt;
    uint32_t component_ids[32];
} flash_entry;

int init_flash(uint32_t magic);

flash_entry read_flash(void);

int write_flash(flash_entry* info);

int poll_flash(void);

#endif
