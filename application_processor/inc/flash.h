#ifndef FLASH_H__
#define FLASH_H__
#include <stdint.h>

struct flash_entry;

int poll_flash(void);

void init_flash(uint32_t magic, uint32_t component_count, uint32_t* component_identifiers);

struct flash_entry read_flash(void);

void write_flash(struct flash_entry* info);

#endif
