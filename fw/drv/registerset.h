// NVIC
#define REG_NVIC_ADDR 0xE000E100
    #define REG_NVIC_ISER0_OFFS 0x00
    #define REG_NVIC_ISER1_OFFS 0x04
        #define REG_NVIC_ISER1_USART1_MASK (1 << 5)

// RCC
#define REG_RCC_ADDR 0x40021000
    #define REG_RCC_APB2RSTR_OFFS 0x0C
    #define REG_RCC_APB1RSTR_OFFS 0x10
    #define REG_RCC_APB1ENR_OFFS 0x1C
        #define REG_RCC_APB1ENR_USART2EN_MASK (1 << 17)
        #define REG_RCC_APB1ENR_USART3EN_MASK (1 << 18)
        #define REG_RCC_APB1ENR_USART4EN_MASK (1 << 19)
        #define REG_RCC_APB1ENR_USART5EN_MASK (1 << 20)
        #define REG_RCC_APB1ENR_BKPEN_MASK (1 << 27)
        #define REG_RCC_APB1ENR_PWREN_MASK (1 << 28)
        #define REG_RCC_APB1ENR_DACEN_MASK (1 << 29)
        #define REG_RCC_APB1ENR_TIM2EN_MASK (1 << 0)
        #define REG_RCC_APB1ENR_TIM3EN_MASK (1 << 1)
        #define REG_RCC_APB1ENR_TIM4EN_MASK (1 << 2)
    #define REG_RCC_APB2ENR_OFFS 0x18
        #define REG_RCC_APB2ENR_USART1EN_MASK (1 << 14)
        #define REG_RCC_APB2ENR_SPI1EN_MASK (1 << 12)
        #define REG_RCC_APB2ENR_ADC1EN_MASK (1 << 9)
        #define REG_RCC_APB2ENR_IOPEEN_MASK (1 << 6)
        #define REG_RCC_APB2ENR_IOPDEN_MASK (1 << 5)
        #define REG_RCC_APB2ENR_IOPCEN_MASK (1 << 4)
        #define REG_RCC_APB2ENR_IOPBEN_MASK (1 << 3)
        #define REG_RCC_APB2ENR_IOPAEN_MASK (1 << 2)
        #define REG_RCC_APB2ENR_AFIOEN_MASK (1 << 0)
    #define REG_RCC_CIR_OFFS 0x08
    #define REG_RCC_BDCR_OFFS 0x20
        #define REG_RCC_BDCR_RTCEN_MASK (1 << 15)

// PWR
#define REG_PWR_ADDR 0x40007000
    #define REG_PWR_CR_OFFS 0x00
        #define REG_PWR_CR_DBP_MASK (1 << 8)

// GPIO
#define REG_GPIO_PORTA_ADDR 0x40010800
#define REG_GPIO_PORTB_ADDR 0x40010C00
#define REG_GPIO_PORTC_ADDR 0x40011000
#define REG_GPIO_PORTD_ADDR 0x40011400
#define REG_GPIO_PORTE_ADDR 0x40011800
    #define REG_GPIO_CRL_OFFS 0x00
    #define REG_GPIO_CRH_OFFS 0x04
    #define REG_GPIO_IDR_OFFS 0x08
    #define REG_GPIO_ODR_OFFS 0x0C

// TIM2, TIM3, TIM4
#define REG_TIM2_ADDR 0x40000000
#define REG_TIM3_ADDR 0x40000400
#define REG_TIM4_ADDR 0x40000800
    #define REG_TIM_CR1_OFFS 0x00
        #define REG_TIM_CR1_ARPE_MASK (1 << 7)
        #define REG_TIM_CR1_CEN_MASK (1 << 0)
    #define REG_TIM_CR2_OFFS 0x04
    #define REG_TIM_SMCR_OFFS 0x08
    #define REG_TIM_DIER_OFFS 0x0C
    #define REG_TIM_SR_OFFS 0x10
    #define REG_TIM_EGR_OFFS 0x14
        #define REG_TIM_EGR_UG_MASK (1 << 0)
    #define REG_TIM_CCMR1_OFFS 0x18
        #define REG_TIM_CCMR1_OC2M_MASK (7 << 12)
        #define REG_TIM_CCMR1_OC2M_POS 12
        #define REG_TIM_CCMR1_OC2PE_MASK (1 << 11)
        #define REG_TIM_CCMR1_OC1M_MASK (7 << 4)
        #define REG_TIM_CCMR1_OC1M_POS 4
        #define REG_TIM_CCMR1_OC1PE_MASK (1 << 3)
    #define REG_TIM_CCMR2_OFFS 0x1C
        #define REG_TIM_CCMR2_OC4M_MASK (7 << 12)
        #define REG_TIM_CCMR2_OC4M_POS 12
        #define REG_TIM_CCMR2_OC4PE_MASK (1 << 11)
        #define REG_TIM_CCMR2_OC3M_MASK (7 << 4)
        #define REG_TIM_CCMR2_OC3M_POS 4
        #define REG_TIM_CCMR2_OC3PE_MASK (1 << 3)
    #define REG_TIM_CCER_OFFS 0x20
        #define REG_TIM_CCER_CC4E_MASK (1 << 12)
        #define REG_TIM_CCER_CC3E_MASK (1 << 8)
        #define REG_TIM_CCER_CC2E_MASK (1 << 4)
        #define REG_TIM_CCER_CC1E_MASK (1 << 0)
    #define REG_TIM_CNT_OFFS 0x24
    #define REG_TIM_PSC_OFFS 0x28
    #define REG_TIM_ARR_OFFS 0x2C
    #define REG_TIM_CCR1_OFFS 0x34
    #define REG_TIM_CCR2_OFFS 0x38
    #define REG_TIM_CCR3_OFFS 0x3C
    #define REG_TIM_CCR4_OFFS 0x40
    #define REG_TIM_DCR_OFFS 0x48
    #define REG_TIM_DMAR_OFFS 0x4C

// ADC
#define REG_ADC1_ADDR 0x40012400
    #define REG_ADC_SR_OFFS 0x00
        #define REG_ADC_SR_EOC_MASK (1 << 1)
    #define REG_ADC_CR1_OFFS 0x04
    #define REG_ADC_CR2_OFFS 0x08
        #define REG_ADC_CR2_ADON_MASK (1 << 0)
        #define REG_ADC_CR2_CAL_MASK (1 << 2)
    #define REG_ADC_SMPR1_OFFS 0x0C
    #define REG_ADC_SMPR2_OFFS 0x10
    #define REG_ADC_DR_OFFS 0x4C
    #define REG_ADC_SQR3_OFFS 0x34
        #define REG_ADC_SQR3_SQ1_MASK (15)
        #define REG_ADC_SQR3_SQ1_POS 0

// DAC
#define REG_DAC_ADDR 0x40007400
    #define REG_DAC_CR_OFFS 0x00
        #define REG_DAC_CR_TSEL2_MASK (7 << 19)
        #define REG_DAC_CR_TSEL2_POS 19
        #define REG_DAC_CR_TEN2_MASK (1 << 18)
        #define REG_DAC_CR_BOFF2_MASK (1 << 17)
        #define REG_DAC_CR_EN2_MASK (1 << 16)
        #define REG_DAC_CR_TSEL1_MASK (7 << 3)
        #define REG_DAC_CR_TSEL1_POS 3
        #define REG_DAC_CR_TEN1_MASK (1 << 2)
        #define REG_DAC_CR_BOFF1_MASK (1 << 1)
        #define REG_DAC_CR_EN1_MASK (1 << 0)
    #define REG_DAC_SWTRIGR_OFFS 0x04
        #define REG_DAC_SWTRIGR_SWTRIG1_MASK (1 << 0)
        #define REG_DAC_SWTRIGR_SWTRIG2_MASK (1 << 1)
    #define REG_DAC_DHR12R1_OFFS 0x08
    #define REG_DAC_DHR12R2_OFFS 0x14

// RTC
#define REG_RTC_ADDR 0x40002800
    #define REG_RTC_CRH_OFFS 0x00
    #define REG_RTC_CRL_OFFS 0x04
        #define REG_RTC_CRL_RTOFF_MASK (1 << 5)
        #define REG_RTC_CRL_CNF_MASK (1 << 4)
    #define REG_RTC_PRLH_OFFS 0x08
    #define REG_RTC_PRLL_OFFS 0x0C
    #define REG_RTC_DIVH_OFFS 0x10
    #define REG_RTC_DIVL_OFFS 0x14
    #define REG_RTC_CNTH_OFFS 0x18
    #define REG_RTC_CNTL_OFFS 0x1C
    #define REG_RTC_ALRH_OFFS 0x20
    #define REG_RTC_ALRL_OFFS 0x24

// USART
#define REG_USART1_INTERRUPT_VECTOR_ADDR 0x000000D4
#define REG_USART1_ADDR 0x40013800
    #define REG_USART_SR_OFFS 0x00
        #define REG_USART_SR_TC_MASK (1 << 6)
        #define REG_USART_SR_TXE_MASK (1 << 7)
        #define REG_USART_SR_RXNE_MASK (1 << 5)
    #define REG_USART_DR_OFFS 0x04
    #define REG_USART_BRR_OFFS 0x08
        #define REG_USART_BRR_DIV_FRACTION_MASK 0xF
        #define REG_USART_BRR_DIV_FRACTION_POS 0
        #define REG_USART_BRR_DIV_MANTISSA_MASK 0xFFF0
        #define REG_USART_BRR_DIV_MANTISSA_POS 4
    #define REG_USART_CR1_OFFS 0x0C
        #define REG_USART_CR1_RE_MASK (1 << 2)
        #define REG_USART_CR1_TE_MASK (1 << 3)
        #define REG_USART_CR1_RXNEIE_MASK (1 << 5)
        #define REG_USART_CR1_TXEIE_MASK (1 << 7)
        #define REG_USART_CR1_TCIE_MASK (1 << 6)
        #define REG_USART_CR1_UE_MASK (1 << 13)
    #define REG_USART_CR2_OFFS 0x10
    #define REG_USART_CR3_OFFS 0x14
    #define REG_USART_GTPR_OFFS 0x18

// SPI
#define REG_SPI1_ADDR 0x40013000
    #define REG_SPI_CR1_OFFS 0x00
    #define REG_SPI_CR2_OFFS 0x04
    #define REG_SPI_SR_OFFS 0x08
    #define REG_SPI_DR_OFFS 0x0C
    #define REG_SPI_CRCPR_OFFS 0x10
    #define REG_SPI_RXCRCR_OFFS 0x14
    #define REG_SPI_TXCRCR_OFFS 0x18

// Flash
#define REG_FLASH_KEY1 0x45670123
#define REG_FLASH_KEY2 0xCDEF89AB
#define REG_FLASH_RDPRT_KEY 0x00A5
#define REG_FLASH_ADDR 0x40022000
    #define REG_FLASH_ACR_OFFS 0x00
    #define REG_FLASH_KEYR_OFFS 0x04
    #define REG_FLASH_OPTKEYR_OFFS 0x08
    #define REG_FLASH_SR_OFFS 0x0C
        #define REG_FLASH_SR_BSY_MASK (1 << 0)
    #define REG_FLASH_CR_OFFS 0x10
        #define REG_FLASH_CR_LOCK_MASK (1 << 7)
        #define REG_FLASH_CR_PG_MASK (1 << 0)
        #define REG_FLASH_CR_PER_MASK (1 << 1)
        #define REG_FLASH_CR_STRT_MASK (1 << 6)
        #define REG_FLASH_CR_OPTER_MASK (1 << 5)
    #define REG_FLASH_AR_OFFS 0x14
    #define REG_FLASH_OBR_OFFS 0x1C
    #define REG_FLASH_WRPR_OFFS 0x20

// General
#define FLASH_START_ADDR 0x08000000
#define FLASH_END_ADDR 0x08020000
#define FLASH_PAGE_SIZE 1024
