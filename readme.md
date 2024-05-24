# AVR

Kurs programowania procesorów **AVR** na przykładzie mikrokontrolera **Atmega328P**.

## Dlaczego AVR?

Mikrokontrolery wydane przez firmę Atmel nie są już aż tak popularne jak kiedyś i są powolutku wypierane. Jednak w mojej opinii taka Atmega jest lepszym procesorem na początek samodzielnej nauki niż zaawansowany STM32.

- Mamy ją w obudowie **DIP28** THT, więc możemy sobie na płytce stykowej wszystko sami poogarniać
- W sieci i literaturze można znaleźć masę przykładów i materiałów dotyczących tych mikrokontrolerów, z których zdecydowana większość dotyczy scalaków Atmega8A, Atmega32A oraz Atmega328P
- Mała różnorodność wykorzystywanych układów oraz niewielka ilość peryferiów i ich prostota, która w rozwiązaniach rynkowych jest dużym ograniczeniem, tutaj przekłada się na spójność przykładów. Jeden UART, niewielkie możliwości konfiguracji - wystarczy podłączyć i działa.

## Co potrzebujemy?

- Płytkę ze wbudowanym bootloaderem, na przykład Arduino, lub bez ale wówczas potrzebujemy zewnętrzny programator USBasp.
- Kopilator języka C przygotowany specjalnie pod mikrokontrolery AVR jakim jest **WinAVR**. Po pobraniu/instalacji najlepiej umieścić go w lokalizacjai `C:\WinAVR`. 
- Klient **GIT**, który uprości nam kwetie pobierania projektów startowych.
- Edytor kodu IDE jakim jest **VSCode**. Formalnie się bez niego da obejść, jednak tanie narzędzie bywa niezmiernie pomocne. Wyłapuje więksozśc błędów, koloruje składnie oraz podpowiad podczas tworzenia kodu.
- Narzędzia do zarządzania procesem kompilacji programów, jakim jest [**Make**](https://www.gnu.org/software/make/) Aby zainstalować **Make**, można skorzystać z menedżera pakietów [**Chocolatey**](https://chocolatey.org/), który umożliwia prostą instalację wymaganych komponentów. Wystarczy otworzyć **PowerShell** jako 🛡️administrator i wywołać komendy:

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
choco install make
```

Instalacja **Make** automatycznie utworzy zmienną systemową, jednak w przypadku pozostałych programów konieczne będzie ręczne ich utworzenie.

🪟 Run » `sysdm.cpl` » Advanced » **Environment Variables**

- Path » `C:\WinAVR\bin`

Na zakończenie należy otworzyć konsolę i zweryfikować, czy wszystkie pakiety zostały zainstalowane poprawnie. Można to zrobić przy użyciu komendy `--version`.

```bash
avr-gcc --version
avr-objcopy --version
make --version
```

## Pierwszy program

...


Kompilacja i wgranie _(erase)_ projektu z pojedyńczym plikiem `main.c`

```bash
avr-gcc -Os -DF_CPU=16000000UL -D__AVR_ATmega328P__ -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main.elf
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -F -V -c arduino -P COM8 -b 115200 -p ATMEGA328P -U flash:w:main.hex # arduino
avrdude avrdude -c usbasp -p ATMEGA328P -U flash:w:main.hex # usbasp
```




