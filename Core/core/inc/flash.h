#pragma once
#define FLASH_H
#include "stm32f7xx.h"
#include "header.h"


#define FLASH_START							0x08000000UL

#define SECTOR0_SIZE						0x8000UL	//32kbyte
#define SECTOR1_SIZE						0x8000UL
#define SECTOR2_SIZE						0x8000UL
#define SECTOR3_SIZE						0x8000UL
#define SECTOR4_SIZE						0x20000UL	//128kbyte
#define SECTOR5_SIZE						0x40000UL	//256kbyte
#define SECTOR6_SIZE						0x40000UL
#define SECTOR7_SIZE						0x40000UL
#define SECTOR8_SIZE						0x40000UL
#define SECTOR9_SIZE						0x40000UL
#define SECTOR10_SIZE						0x40000UL
#define SECTOR11_SIZE						0x40000UL

typedef struct {
	uint32_t sector0;
	uint32_t sector1;
	uint32_t sector2;
	uint32_t sector3;
	uint32_t sector4;
	uint32_t sector5;
	uint32_t sector6;
	uint32_t sector7;
	uint32_t sector8;
	uint32_t sector9;
	uint32_t sector10;
	uint32_t sector11;
	uint32_t flashStart;
	uint32_t flashEnd;
}sector_TypeDef;
sector_TypeDef sector;

typedef enum {
	sector0,
	sector1,
	sector2,
	sector3,
	sector4,
	sector5,
	sector6,
	sector7,
	sector8,
	sector9,
	sector10,
	sector11
}sector_t_enum;

void flash_init(void);
uint32_t flash_read(uint32_t address);
void flash_mass_erase(void);
int flash_erase_sector(sector_t_enum sector_address);
void flash_programm_byte(uint32_t address, uint8_t data);
void flash_programm_half_word(uint32_t address, uint16_t data);
void flash_programm_word(uint32_t address, uint32_t data);
void flash_programm_double_word(uint32_t address, uint64_t data);
//----------------------------------------------------------------
void flash_programm_byte_key(uint32_t address, uint8_t data);
void flash_programm_half_word_key(uint32_t address, uint16_t data);
void flash_programm_word_key(uint32_t address, uint32_t data);
void flash_programm_double_word_key(uint32_t address, uint64_t data);
int config_save(sector_t_enum sector_address);











