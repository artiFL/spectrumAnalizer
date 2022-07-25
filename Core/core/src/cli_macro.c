#include "cli.h"
#include "string.h"
#include "stdio.h"
#include <sys/unistd.h>
#include <errno.h>
#include "stm32f7xx.h"
#include "USART.h"
#include "clock.h"


void Sprint_Ok_Helper(const char *in, char *out, uint16_t out_max)
{
    snprintf(out, out_max, "\r\nOk:%s\r\n", in);
}

void Sprint_Error_Helper(const char *in, char *out, uint16_t out_max)
{
    snprintf(out, out_max, "\r\nError:CMD invalid->%s\r\n", in);
}

void Sprint_Ok_Done_Helper(const char *in, char *out, uint16_t out_max)
{
    snprintf(out, out_max, "\r\nOk:%s\r\nDone\r\n", in);
}

void CLI_usart_init(void)
{
	  CLI_Init();

	  CLI_Command_t read_ID =
	      {
	          .CLI_Command = "show id",
	          .CLI_Command_Description = "read unique id and memory size",
	          .CLI_Callback = (void*)read_id_Callback,
	  };

	  CLI_Command_t clock_tree =
	      {
	          .CLI_Command = "show clock tree",
	          .CLI_Command_Description = "calculate clock tree & sohw",
	          .CLI_Callback = (void*)clock_read_Callback,
	  };
	  CLI_Add_Command(&read_ID);
	  CLI_Add_Command(&clock_tree);


}

void read_id_Callback (uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	volatile uint16_t *Flashsize = (uint16_t *)FLASHSIZE_BASE;
	volatile uint32_t *UniqueID = (uint32_t *)UID_BASE;


	printf("STM32F767ZIT6 UID - %li:%li:%li", UniqueID[0], UniqueID[1], UniqueID[2]);
	printf("__CORTEX_M%d __CM7_CMSIS_VERSION - %d",  __CORTEX_M, __CM7_CMSIS_VERSION);
	printf("Flash Size - %d Kbytes ", Flashsize[0]);

}

void clock_read_Callback (uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	Clock_Conf.Core > 216000000 ? (printf("Core Boost	-%liMHz\n", Clock_Conf.Core / 1000000)) : \
									  (printf("Core	- %liMHz\n", Clock_Conf.Core / 1000000));
		printf(" -- APB1_Perip - %liMHz\n", Clock_Conf.APB1Perip / 1000000);
		printf(" -- APB1_Timer - %liMHz\n", Clock_Conf.APB1Timer / 1000000);
		printf(" -- APB2_Perip - %liMHz\n", Clock_Conf.APB2Perip / 1000000);
		printf(" -- APB2_Timer - %liMHz", Clock_Conf.APB2Timer / 1000000);

}
















