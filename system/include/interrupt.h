#pragma once

#include <stdint.h>

struct _IDTE {
  uint16_t offset_15_0;             //part of handler address
  uint16_t seg_selector;            //segment selector from GDT (0x8)
  uint16_t flags;                   //description below
  uint16_t offset_31_16;            //part of handler address
  uint32_t offset_63_32;            //part of handler address
  uint32_t reserved;                //reserved by cpu
};
typedef struct _IDTE IDTE;

struct _IDTP{
    uint16_t limit;
    uint64_t address;
} __attribute__((packed)) ;
typedef struct _IDTP IDTP;

void InitInterrupt(void);