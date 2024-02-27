#include <stdint.h>
#include "ectf_params.h"

#define UNREACHABLE while(1) {}

// ------------------- BOTH -------------------
typedef struct {
    uint32_t id;
    const char* boot_msg;
    const char* attestation_loc;
    const char* attestation_date;
    const char* attestation_customer;
} extern_comp ;

typedef struct {
    const char* ap_pin;
    const char* ap_token;
    const char* boot_msg;
    uint32_t* comp_ids;
    uint32_t comp_num;
} extern_ap ;

// Which device this was compiled for
// - 0 = Component
// - 1 = Application Processor
int comp_or_ap(void) {
#ifdef COMPONENT_ID
    return 0;
#else
    return 1;
#endif
}

// ------------------- FOR COMPONENT -------------------
#ifdef COMPONENT_ID

// Get component items
extern_comp get_comp(void) {
    extern_comp comp = {
        .id = COMPONENT_ID,
        .boot_msg = COMPONENT_BOOT_MSG,
        .attestation_loc = ATTESTATION_LOC,
        .attestation_date = ATTESTATION_DATE,
        .attestation_customer = ATTESTATION_CUSTOMER
    };

    return comp;
}

// should never be called for component
extern_ap get_ap(void) {
    // should never be called
    UNREACHABLE;
}

// ------------------- FOR APPLICATION PROCESSOR -------------------
#else

// should never be called for application processor
extern_comp get_comp(void) {
    // should never be called
    UNREACHABLE;
}

// Get Application Processor items
extern_ap get_ap(void) {
    uint32_t comp_ids[COMPONENT_CNT] = { COMPONENT_IDS };

    extern_ap ap = {
        .ap_pin = AP_PIN,
        .ap_token = AP_TOKEN,
        .boot_msg = AP_BOOT_MSG,
        .comp_ids = (uint32_t*)comp_ids,
        .comp_num = COMPONENT_CNT,
    };

    return ap;
}
#endif
