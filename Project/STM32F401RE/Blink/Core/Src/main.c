#include <main.h>

int main(){
	/* Start the HSE clock */
	RCC->CR |= (1 << 16);

	/* Check if the HSE clock is ready */
	while(!(RCC->CR & (1 << 17)));

	/* Now is the HSE clock ready - Time to select it as system clock */
	RCC->CFGR |= 0b01;

	/* Check if the HSE clock is selected */
	while(!(RCC->CFGR & 0b0100));

	/* Prescaler AHB from 8 MHz to 4 MHz */
	RCC->CFGR |= (0b1000 << 4);

	/* Prescaler APB1 from 4 MHz to 500 kHz (16 division) times 2 if prescaler is > 1 */
	RCC->CFGR |= (0b111 << 10);

	/* Enable for GPIOA */
	RCC->AHB1ENR |= 1;

	/* Enable TIM2 */
	RCC->APB1ENR |= 1;

	/* Enable counter and set it as internal clock */
	TIM2->CR1 |= 1;

	/* Set prescaler for TIM2 - 1000 updates per second */
	TIM2->PSC = 499;

	/* Set auto-reload for TIM2 */
	TIM2->ARR = 0xFFFF;

	/* Declare PA5 as digital output */
	GPIOA->MODER |= 0b10000000000;

	/* Declare the digital output PA5 as push-pull */
	GPIOA->OTYPER |= (0 << 5);

	/* Blink in one second */
	const uint32_t wait = 1000;
	while(1){
		/* Set */
		GPIOA->BSRR |= (1 << 5);

		/* Delay 1 second */
		uint32_t tickstart = TIM2->CNT;
		while((TIM2->CNT - tickstart) < wait){}

		/* Reset the set */
		GPIOA->BSRR |= (1 << 21);
		tickstart = TIM2->CNT;
		while((TIM2->CNT - tickstart) < wait){}
	}
}
