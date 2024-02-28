#include "flash.h"
#include "board.h"
#include "mxc_device.h"
#include "ectf_params.h"
#include "icc.h"
#include "flc.h"

#include <stdio.h>
#include <string.h>

#define FLASH_ADDR ((MXC_FLASH_MEM_BASE + MXC_FLASH_MEM_SIZE) - (2 * MXC_FLASH_PAGE_SIZE))

flash_entry flash_info;

int init_flash(uint32_t magic) {
    MXC_ICC_Disable(MXC_ICC0);

    MXC_FLC_Read(FLASH_ADDR, ((uint32_t*)&flash_info), sizeof(flash_entry));

    if (flash_info.flash_magic != magic) {

        flash_info.flash_magic = magic;
        flash_info.component_cnt = COMPONENT_CNT;
        uint32_t component_ids[COMPONENT_CNT] = {COMPONENT_IDS};

        memcpy(flash_info.component_ids, component_ids, COMPONENT_CNT*sizeof(uint32_t));

        return write_flash(&flash_info);
    }

    return 0;
}

flash_entry read_flash(void) {
    flash_entry info = {};
    MXC_FLC_Read(FLASH_ADDR, ((uint32_t*)&info), sizeof(flash_entry));
    return info;
}

int write_flash(flash_entry* info) {
    MXC_FLC_PageErase(FLASH_ADDR);
    MXC_FLC_Write(FLASH_ADDR, sizeof(flash_entry), ((uint32_t*)info));
    return poll_flash();
}

int poll_flash(void) {
    uint32_t temp;
    while (1) {
        temp = MXC_FLC0->intr;

        if (temp & MXC_F_FLC_INTR_DONE) {
            MXC_FLC0->intr &= ~MXC_F_FLC_INTR_DONE;
            return 0;
        }

        if (temp & MXC_F_FLC_INTR_AF) {
            MXC_FLC0->intr &= ~MXC_F_FLC_INTR_AF;
            return 1;
        }
    }
    return 0;
}
