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

	/* Declare PA5 as alternate function mode */
	GPIOA->MODER |= (1 << 11);

	/* Set PA5 as alternative function AF1 */
	GPIOA->AFR[0] |= (0b0001 << 20);

	/* Declare the digital output PA5 as push-pull */
	GPIOA->OTYPER &= ~(0 << 5);

	/* Enable counter and set it as internal clock */
	TIM2->CR1 |= 1;

	/* Set prescaler for TIM2 - 10000 updates per second */
	TIM2->PSC = 49;

	/* Set auto-reload for TIM2 */
	TIM2->ARR = 100;

	/* Set PWM mode 1 */
	TIM2->CCMR1 |= (0b110 << 4);

	/* Enable the PWM mode */
	TIM2->CCER |= 1;

	/* Fade */
	int i = 0;
	while(1){
		/* Duty call 50% */
		TIM2->CCR1 = i;
		i++;
		for(int j = 0; j < 10000; j++){}
		if(i > 100){
			i = 0;
		}

	}
}
