# STM32-Registers-Only

![a](https://github.com/DanielMartensson/STM32-Registers-Only/blob/main/logo.png?raw=true)

This is a repository where I uploading projects that are made with registers only. 
That means I don't use `HAL` or `CubeMX`. I only access the registers and set the `bit` values.
The reason why I'm creating this repository is to documnenting for future use.

There are three reasons to use registers compared to `HAL` or `CubeMX`.

* Learn how a typical microcontroller works
* Accessing the registers creates a much faster operation
* It's fun to dive into the registers, even if the learning curve is quite high

The uploaded projects contains support for

* STM32F401RE - Blink an LED with a timer as delay