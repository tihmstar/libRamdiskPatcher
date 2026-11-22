//
//  RPPF.cpp
//  libRamdiskPatcher
//
//  Created by tihmstar on 17.11.26.
//


#include "../include/RamdiskPatcher/RPPF.hpp"
#include "../include/RamdiskPatcher/RPPF32.hpp"
#include "../include/RamdiskPatcher/RPPF64.hpp"
#include "../include/RamdiskPatcher/utils.hpp"

#pragma mark provider

using namespace RamdiskPatcher;

RAMDISK_PATCHER_API void RPPF::applyPatches(std::vector<tihmstar::patchfinder::patch> patches){
    for (auto p : patches) {
        uint8_t *file = (uint8_t*)buf();
        uint64_t off = (uint64_t)((const uint8_t *)memoryForLoc(p._location) - file);
#ifdef DEBUG
        printf("RPPF: Applying patch=%p : ",(void*)p._location);
        for (int i=0; i<p.getPatchSize(); i++) {
            printf("%02x",((uint8_t*)p.getPatch())[i]);
        }
        if (p.getPatchSize() == 4) {
            printf(" 0x%08x",*(uint32_t*)p.getPatch());
        } else if (p.getPatchSize() == 2) {
            printf(" 0x%04x",*(uint16_t*)p.getPatch());
        }
        printf("\n");
#endif
        memcpy(&file[off], p.getPatch(), p.getPatchSize());
    }
#ifdef DEBUG
    printf("RPPF: Patches applied!");
#endif
}

#pragma mark noimplement
std::vector<tihmstar::patchfinder::patch> RPPF::getASRSigcheckPatches(){
    FAIL_UNIMPLEMENTED;
}

std::vector<tihmstar::patchfinder::patch> RPPF::getLibIMG4SigcheckPatches(){
    FAIL_UNIMPLEMENTED;
}

std::vector<tihmstar::patchfinder::patch> RPPF::getRestoredSigcheckPatches(){
    FAIL_UNIMPLEMENTED;
}

std::vector<tihmstar::patchfinder::patch> RPPF::getASRHardcodedPWPatches(const char *rootfsPW){
    FAIL_UNIMPLEMENTED;
}

#pragma mark static
RAMDISK_PATCHER_API std::shared_ptr<RPPF> RPPF::make_RPPF(const void *buf, size_t size){
    try {return std::make_shared<RPPF64>(buf, size);} catch (...) {}
    try {return std::make_shared<RPPF32>(buf, size);} catch (...) {}
    reterror("Failed to make RRPF");
}
