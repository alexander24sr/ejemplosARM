# ejemplosARM
Ejemplos desarrollados durante el curso de programación de microcontroladores ARM

# Compilación del ultrasonido.c

Para compilar el archivo ultrasonido.c se debe ejecutar el siguiente comando: 
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb --specs=nosys.specs -T stm32f103c8tx_flash.ld startup_stm32f103c8tx.s ultrasonido.c ./serialUart/serialUart.c ./hcsr04/hcsr04.c -o ultrasonido.elf
arm-none-eabi-objcopy -O binary ultrasonido.elf ultrasonido.bin 
st-flash write ultrasonido.bin 0x08000000
