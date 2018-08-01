#include "user_flash.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"

uint32_t writeFlashData = 0x55555555;
uint32_t addr = 0x08007000;
//FLASH??????
void writeFlashTest(void)
{
    //flash д�����ݲ���
  HAL_FLASH_Unlock();

    //����flash
      //��ʼ������
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = addr;
    f.NbPages = 1;
    //����PageError
    uint32_t PageError = 0;
    //���ò���flash
    HAL_FLASHEx_Erase(&f, &PageError);

    //3��flash��д
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, writeFlashData);

    //4��סflash
  HAL_FLASH_Lock();
}

//FLASH??????
void printFlashTest(void)
{
  uint32_t temp = *(__IO uint32_t*)(addr);

    printf("addr:0x%x, data:0x%x\r\n", addr, temp);
}


