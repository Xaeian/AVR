# AVR

Kompilacja i wgranie _(erase)_ projektu z pojedyńczym plikiem `main.c`

```bash
avr-gcc -Os -DF_CPU=16000000UL -D__AVR_ATmega328P__ -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main.elf
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -F -V -c arduino -P COM8 -b 115200 -p ATMEGA328P -U flash:w:main.hex # arduino
avrdude avrdude -c usbasp -p ATMEGA328P -U flash:w:main.hex # usbasp
```