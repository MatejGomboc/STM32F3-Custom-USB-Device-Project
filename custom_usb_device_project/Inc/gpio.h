#ifndef __gpio_H
#define __gpio_H

#include <stdbool.h>

void MX_GPIO_Init(void);
void MX_GPIO_DeInit(void);
void MX_GPIO_Set_LD3(bool on);
void MX_GPIO_Set_LD4(bool on);

#endif /*__ pinoutConfig_H */
