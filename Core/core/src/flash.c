#include "flash.h"

/*nDBANK = 1; 			STM32F767ZI
 * ____NUMBER SECTOR________FULL SIZE_______INTERNAL ORGANIZATION___
 * |SECTOR	0			|32KB			|16KB		|		16KB	|0x0800 0000
 * |SECTOR	1			|32KB			|16KB		|		16KB	|
 * |SECTOR	2			|32KB			|16KB		|		16KB	|
 * |SECTOR	3			|32KB			|16KB		|		16KB	|
 * |SECTOR	4			|128KB			|64KB		|		64KB	|
 * |SECTOR	5			|256KB			|128KB		|		128KB	|
 * |SECTOR	6			|256KB			|128KB		|		128KB	|
 * |SECTOR	7			|256KB			|128KB		|		128KB	|
 * |SECTOR	8			|256KB			|128KB		|		128KB	|
 * |SECTOR	9			|256KB			|128KB		|		128KB	|
 * |SECTOR	10			|256KB			|128KB		|		128KB	|
 * |SECTOR	11			|256KB			|128KB		|		128KB	|0x081F FFFF
 */


static int flash_wait_for_last_operation(void)
{
	  while (FLASH->SR == FLASH_SR_BSY) {
	    //WWDG->CR = WWDG_CR_T;
	  }
	  return FLASH->SR;
}
static void flash_unlock(void)
{
  FLASH->KEYR = 0x45670123;
  FLASH->KEYR = 0xCDEF89AB;
}
static void flash_lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}
void flash_init(void)
{
	FLASH->OPTCR |= FLASH_OPTCR_nDBANK;		//bank1
	sector.flashStart = FLASH_START;
	sector.flashEnd = 0x081FFFFFUL;
	sector.sector0 = FLASH_START;
	sector.sector1 = sector.sector0 + SECTOR0_SIZE;
	sector.sector2 = sector.sector1 + SECTOR1_SIZE;
	sector.sector3 = sector.sector2 + SECTOR2_SIZE;
	sector.sector4 = sector.sector3 + SECTOR3_SIZE;
	sector.sector5 = sector.sector4 + SECTOR4_SIZE;
	sector.sector6 = sector.sector5 + SECTOR5_SIZE;
	sector.sector7 = sector.sector6 + SECTOR6_SIZE;
	sector.sector8 = sector.sector7 + SECTOR7_SIZE;
	sector.sector9 = sector.sector8 + SECTOR8_SIZE;
	sector.sector10 = sector.sector9 + SECTOR9_SIZE;
	sector.sector11 = sector.sector10 + SECTOR10_SIZE;

}
uint32_t flash_read(uint32_t address)
{
return (*(__IO uint32_t*) address);
}
void flash_mass_erase(void)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR |= FLASH_CR_SER;
	FLASH->CR |= FLASH_CR_PSIZE_1;
	FLASH->CR |= FLASH_CR_STRT;
	FLASH->CR |= FLASH_CR_MER;						//If nDBANK=1, MER activates erase of all user sectors in Flash memory
	flash_wait_for_last_operation();
	FLASH->CR = 0x80000000;
}
int flash_erase_sector(sector_t_enum sector_address)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR |= FLASH_CR_SER;
	FLASH->CR |= FLASH_CR_PSIZE_1;
	FLASH->CR |= ((uint32_t)sector_address << FLASH_CR_SNB_Pos);
	FLASH->CR |= FLASH_CR_STRT;
	flash_wait_for_last_operation();
	FLASH->CR = 0x80000000;

	  return 0;
}
void flash_programm_byte(uint32_t address, uint8_t data)
{
	flash_wait_for_last_operation();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint8_t*)address = data;
}
void flash_programm_half_word(uint32_t address, uint16_t data)
{
	flash_wait_for_last_operation();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE_0;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint16_t*)address = data;
}
void flash_programm_word(uint32_t address, uint32_t data)
{
	flash_wait_for_last_operation();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE_1;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint32_t*)address = data;
}
void flash_programm_double_word(uint32_t address, uint64_t data)
{
	flash_wait_for_last_operation();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint64_t*)address = data;
}
//--------------------------------------------------------------
void flash_programm_byte_key(uint32_t address, uint8_t data)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint8_t*)address = data;
	flash_lock();
}
void flash_programm_half_word_key(uint32_t address, uint16_t data)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE_0;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint16_t*)address = data;
	flash_lock();
}
void flash_programm_word_key(uint32_t address, uint32_t data)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE_1;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint32_t*)address = data;
	flash_lock();
}
void flash_programm_double_word_key(uint32_t address, uint64_t data)
{
	flash_wait_for_last_operation();
	flash_unlock();
	FLASH->SR = 0xFFFFFFFF;
	FLASH->CR &= !FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PSIZE;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint64_t*)address = data;
	flash_lock();
}
//--------------------------------------------------------------

int config_save(sector_t_enum sector_address)
{
	  uint16_t *src = (uint16_t*)&config;
	  uint16_t *dst = (uint16_t*)sector_address;
	  flash_erase_sector(sector_address);
	  int count = sizeof(config_t) / sizeof(uint16_t);
	  while (count-- > 0) {
		flash_programm_half_word_key((uint32_t)dst, *src++);
	    dst++;
	  }
	  flash_lock();

	  return 0;
}



















