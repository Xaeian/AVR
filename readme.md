# 🎓 AVR

Kurs programowania procesorów **AVR** na przykładzie mikrokontrolera **Atmega328P**.

## 🤔 Dlaczego AVR?

Mikrokontrolery wydane przez firmę Atmel nie są już aż tak popularne jak kiedyś i są powolutku wypierane. Jednak w mojej opinii taka Atmega jest lepszym procesorem na początek samodzielnej nauki niż zaawansowany STM32.

- Mamy ją w obudowie **DIP28** THT, więc możemy sobie na płytce stykowej wszystko sami poogarniać
- W sieci i literaturze można znaleźć masę przykładów i materiałów dotyczących tych mikrokontrolerów, z których zdecydowana większość dotyczy scalaków Atmega8A, Atmega32A oraz Atmega328P
- Mała różnorodność wykorzystywanych układów oraz niewielka ilość peryferiów i ich prostota, która w rozwiązaniach rynkowych jest dużym ograniczeniem, tutaj przekłada się na spójność przykładów. Jeden UART, niewielkie możliwości konfiguracji - wystarczy podłączyć i działa.

## 📦 Co potrzebujemy?

- Płytkę ze wbudowanym bootloaderem, na przykład Arduino, lub bez ale wówczas potrzebujemy zewnętrzny programator USBasp.
- Kopilator języka C przygotowany specjalnie pod mikrokontrolery AVR jakim jest **WinAVR**. Po [pobraniu](https://sqrt.pl/WinAVR.zip)/[instalacji](https://winavr.sourceforge.net/download.html) najlepiej umieścić go w lokalizacjai `C:\WinAVR`.
- [Klient **GIT**](https://git-scm.com/download/win), który rozwiąże kwestie tworzenia nowego/czystego projektu z szablonu, który stanowi zawartość tego repozytorium.
- Edytor kodu **IDE**, tak jak **VSCode**. Chociaż formalnie można obejść się bez niego, to narzędzie bywa niezmiernie pomocne. Wyłapuje większość błędów, koloruje składnię oraz podpowiada podczas tworzenia kodu.
- Narzędzia do zarządzania procesem kompilacji programów, jakim jest [**Make**](https://www.gnu.org/software/make/) Aby zainstalować **Make**, można skorzystać z menedżera pakietów [**Chocolatey**](https://chocolatey.org/), który umożliwia prostą instalację wymaganych komponentów. Wystarczy otworzyć **PowerShell** jako 🛡️administrator i wywołać komendy:

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
choco install make
```

Instalacja **Make** automatycznie utworzy zmienną systemową, jednak w przypadku pozostałych programów konieczne będzie ręczne ich utworzenie.

🪟 `Win` + `R` » `sysdm.cpl` » Advanced » **Environment Variables**

- Path » `C:\WinAVR\bin`

Na zakończenie należy otworzyć konsolę i zweryfikować, czy wszystkie pakiety zostały zainstalowane poprawnie. Można to zrobić przy użyciu komendy `--version`.

```sh
avr-gcc --version
avr-objcopy --version
avrdude -v
make --version
```

## 🔥 Compile and burn

Aby sklonować repozytorium, a tym samym utworzyć nowy projekt AVR, wystarczy _(o ile mamy zainstalowanego [klienta Git](https://git-scm.com/download/win))_ wykonać następującą komendę `clone`:

```sh
git clone https://github.com/Xaeian/AVR
```

Pierwszym etapem uruchamiania programu jest przekształcenie naszego projektu w języku **C**, czyli w tym przypadku pliku `main.c`, w plik wsadowy _(program)_ dla mikrokontrolera w formacie `.hex` _(lub `.bin`)_. Proces ten nazywamy **kompilacją**:

```sh
avr-gcc -Os -DF_CPU=16000000UL -D__AVR_ATmega328P__ -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main.elf
avr-objcopy -O ihex -R .eeprom main.elf main.hex
```

Następnie należy zaprogramować mikrokontroler, czyli wgrać plik wsadowy do jego pamięci. Dokładniej mówiąc, musimy wgrać nasz plik `.hex` do dedykowanego sektoru pamięci FLASH mikrokontrolera. Komenda ta będzie różniła się w zależności od programatora. Pracując z **Arduino** lub inną płytką z bootloaderem _(gdzie należy zwrócić uwagę na **port COM**, który system przydzielił naszemu urządzeniu)_, komenda `avrdude` będzie wyglądać następująco:

```sh
avrdude -F -V -c arduino -P COM8 -b 115200 -p ATMEGA328P -U flash:w:main.hex
```

W przypadku **USBasp** komenta `avrdude` będzie wyglądać tak:

```sh
avrdude -c usbasp -p ATMEGA328P -U flash:w:main.hex
```

Proces ten już wydaje się skomplikowany, a stanie się jeszcze bardziej uciążliwy, gdy nasz projekt będzie się rozrastał. Aby go zautomatyzować, użyjemy narzędzia `make`, które dzięki konfiguracji zawartej w pliku `makefile` zrobi wszystko automatycznie. Wystarczy wpisać w konsoli:

```sh
make
```

Jednorazowo trzeba umieścić listę plików `.c` w zmiennej `SRC` oraz listę folderów z plikami nagłówkowymi `.h` w zmiennej `INC`, ale to niewielka cena za automatyzację kompilacji i wgrywania programu 🙂
