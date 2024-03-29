# Hlasovací zařízení pro Hudbu z FEKTu

### Cíle projektu
Cílem projektu je vytvořit zařízení sloužící k počítání hlasů jednotlivých kapel na akci Hudba z FEKTu. Zařízením má být možné hlasovat až pro šest kapel a průběžné hlasy mají být k nahlédnutí na displeji.
<br><br>
![front](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/front.jpg)

## O projektu
Tento projekt se zabývá vytvořením zařízení, které dokáže počítat, zobrazovat a zaznamenávat hlasy. Vytvořené hlasovací zařízení je vytištěné na 3D tiskárně z mnoha dílů a sešroubováno dobromady. Na přední straně je podsvícené logo akce Hudby z FEKTu. Pod magnety připevněným víkem se nachází šest tlačítek s indikací. Zadní panel, rovněž připevněn magnety je součástím víka a dá se spolu s ním složit za zařízení. Tímto složením se odkryje zadní panel na kterém se nachází LCD display, tři spínače, micro USB konektor, krytka s nápisem "328P" a 3D tištěný šroub se symbolem SD karty. Display zobrazuje aktuální počet hlasů jednotlivých kapel. Zařízení je napájeno pouze externě micro USB konektorem. V pravo od něj se nachází hlavní spínač, který zajišťuje zapínání a vypínání zařízení. Spínač s názvem "LCD" zapíná a vypíná podsvícení displeje. Spínač "LOGO" zapíná a vypíná podsvícení loga na předním panelu. Obojí možné vypnout například pro šetření energie při napájení z powerbanky. Šroub se symbolem SD karty po odšroubování umožní přístup k micro SD kartě. Pod krytkou "328P" se nachází programovací piny Arduina (viz sekce Software - Programování).

### Funkce zařízení
Po připojení a zapnutí zařízení je možné začít hlasovat. Stiskem tlačítka vybrané kapely se rozsvítí indikace daného tlačítka. Behem svitu indikace nelze znovu hlasovat, zařízení během této doby aktualizuje informace na displeji a ukládá aktuální počet hlasů na microSD kartu.

## Hardware
![HzF_open](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/HzF_open.jpg)

### Seznam součástek
* 6x [Tlačítko](https://www.gme.cz/tlacitkovy-spinac-pbs-13b-r)
* 1x [klon Arduino Pro mini](https://www.aliexpress.com/item/2031903258.html?spm=a2g0s.9042311.0.0.27424c4dakAzYm)
* 1x Převodník USB/TTL pro programování, [YP-05](https://www.hadex.cz/m435b-prevodnik-usbttl-modul-s-ft232rl/?gclid=CjwKCAjwmeiIBhA6EiwA-uaeFRXA4soPKs384wWb1vIK3xhRTusBXaXjJ_JUQO9WOdVvmTuzFmfkJxoCZpMQAvD_BwE) modul s FT232RL 
* 18x LED z pásku 60/m [Adresovatelný LED pásek WS2812B](https://www.aliexpress.com/item/2036819167.html?spm=a2g0s.9042311.0.0.27424c4diLhTmF)
* 1x [Modul čtečky microSD karet](https://www.gme.cz/modul-ctecky-micro-sd-karet)
* 1x [microSD karta](https://www.alza.cz/verbatim-micro-sdhc-16gb-class-10-sd-adapter-d442132.htm)
* 1x [LCD display 16x2 znaků](https://www.gme.cz/modry-lcd-display-16x2-i2c)
* 1x [Pinout modul s microUSB konektorem](https://www.gme.cz/modul-pinout-s-micro-usb-konektorem)
* 2x Univerzální DPS 5x7cm předvrtaná
* 10x [Šroubovací svorkovnice 2pól](https://www.gme.cz/svorkovnice-sroubovaci-do-dps-ark500-2ex)
* Konektory [JST XH 2.54](https://www.laskarduino.cz/laskakit-sada-jst-xh-konektoru-80ks/?gclid=CjwKCAjwmeiIBhA6EiwA-uaeFTCon_2C3VW73b0MITJvmmYHPBOMC0zGkSmEcFqFK19o3NaiOJ1m8xoC3CAQAvD_BwE)
* 1x [Hlavní spínač](https://www.gme.cz/p-sw101-red)
* 2x [Malý spínač](https://www.gme.cz/p-sm101-1r3)
* Rezistory: 3x 10k; 1x 1k,2k,4k7,6k8
* Filamenty: [Prusament PETG Jet Black](https://shop.prusa3d.com/cs/prusament/802-prusament-petg-jet-black-1kg.html), [Prusament PETG Clear](https://shop.prusa3d.com/cs/prusament/1216-prusament-petg-clear-1kg.html)
* Hliníkový pásek 10mm široký, 2mm tlustý (chlazení LED pásku)
* Neodymové magnety, fastony, dutinky, vodiče, stahovací pásky a bužírky
* Šroubky, matičky a podložky M3x10, imbus, válcová hlava
* Šrouby do plastu 8mm, křížový, půlkulatá hlava

### Schéma zapojení
![HzF_schematic](https://github.com/langrfrantisek/HzF_voting_system/blob/main/HzF_hlasovani_schema.png)
<br><br>
Tlačítka jsou zapojena jednovodičovým připojením přes dělič. Při stisku tlačítka se dělič uzemní v určitém místě (pro každé tlačíko v jiném) a dojde tak ke změně úbytku napětí, který je rozeznáván přes ADC (analog./digital. převodník) na pinu A7. ADC bere jako referenci 3,3V Arduina, proto je napájení "žebříku" děliče právě VCC (3,3V Arduina). Zbylé periferie (včetně samotného Arduina) jsou po zapnutí napájecího spínače napájeny přímo z micro USB napájecího konkektoru (označen jako "5V").\
Adresovatelný RGB LED pásek zajišťující indikaci stisknutých tlačítek a podsvícení loga je připojen na pin 7. Šestice LED pro indikaci stisku tlačítkek jsou zapojeny od tlačítka šest směrem k nižším hodnotám tlačítek. V podsvícení loga je dalších dvanáct LED. Při pohledu na zařízení zepředu jdou LED postupně uplně z prava, dolů a pak dokola. Poslední je pak LED podsvicující blesk.\
LOGO spínač je připojen přes pull-up rezistor k pinu 2.\
LCD display pro 16x2 znaků je připojen přes I2C sběrnici. LCD spínač pak ovládá zapnutí a vypnutí podsvícení LCD.\
Modul pro microSD karty je připojen přes sběrnici SPI. Pro přístup k microSD kartě je potřeba odšroubovat ze zadního panelu plastový šroub se symbolem SD karty.

#### Osazení
Součástky jsou osazeny na pájivé pole a propojeny. Arduino a modul pro micro SD kartu je zasunut v patici. LCD display, spínače a adresovatelný LED pásek jsou připojeny pomocí konketorů. Dělič pro tlačítka má vlastní pájivé pole se šroubovacími konektory pro všechna tlačítka a potřebnými rezistory. Obě desky jsou propojeny třemi vodiči (VCC,DATA,GND)<br><br>
![PCB](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/PCB_solo.jpg)

#### Možnost rozšíření o další tlačítka
V případě potřeby rozšíření o další tlačítka (například pro akci HzF Warm-Up) je u propojovacích vodičů ještě jedna volná šroubovací svorka, která by šla snadno propojit s pinem A6 a vytvořit tak další datový vstup pro další dělič s tlačítky. Po vyvedení GND a VCC ze stávajícího pájivého pole s deličem by mohl vzniknout přídavný modul s dalšími tlačítky.


## Software

### Vývojový diagram
![flowchart](https://github.com/langrfrantisek/HzF_voting_system/blob/main/HzF_flowchart.png)
*verze v PDF [zde](https://github.com/langrfrantisek/HzF_voting_system/blob/main/HzF_flowchart.pdf)*
<br><br>
### Popis programu
Na začátku kódu se provede inicializace knihoven, pinů, proměnných a barevného pole pro animaci loga. Nastaví se také výchozí zobrazení displeje a přerušení časovače 2. Veškerý běh programu probíhá v ISR (Interrupt service routine) časovače 2. Časovač má nastavenou předděličku tak, aby se ISR spustila každých 16ms. V ISR se pomocí počítání kolikrát už smyčka proběhla volí, co se má v programu stát. Pokud nebylo stisknuto tlačítko, vyhledává se každé dva cykly ISR jestli nedošlo k jeho stisku. Vyhledávání zajišťuje funkce button_search() rozpozná, které tlačítko bylo stisknuto a rozsvítí příslušnou indikaci. Zavolá při rozpoznání stisknutého tlačítka funkci display_update() ta aktualizuje displej o nový počet hlasů a zavolá funkci sd_update(), která aktualizuje počet hlasů na microSD kartě (připsáním nového řádku s aktuálním počtem hlasů). Po stisku tlačítka a zavolání potřebných funkcí program přestane na 100 cyklů ISR hledat stisknuté tlačítko. Po tuto dobu svítí indikace, které tlačítko bylo stisknuto a pokračuje animace loga pokud je zapnutá vypínačem LOGO na zadním panelu. Tato animace dělá krok každé 4 ISR. Animace probíhá otáčením definovaného pole barev okolo loga na předním panelu. Po uplynutí 100 cyklů od zmáčknutí tlačítka se indikace, které tlačítko bylo stisknuté zhasne a zařízení je připraveno na další hlasování.

### Programování
Pro přístup k programovacím pinům je potřeba odšroubovat šroubek na krytce s nápisem "328P". **Je li připojen PC přes programátor k Arduinu, nesmí být zařízení napájeno z micro USB konektoru!** Stačí vypnout hlavní vypínač. Programátor a arduino mohou poté být při testování propojeny i při zapnutí zařízení **za předpokladu, že je programátor odpojen od PC/napájení během napájení zařízení z micro USB**. Pokud je programátor připojen k Arduinu (ne k PC) i při testování nového programu je kvůli rušení třeba odpojit svorku na desce programátoru, která projuje napájení programátoru a Arduino (adresovatelný LED pásek jinak blbne).\
Pro programování je nutné použít programátor (např. Převodník [YP-05](https://www.hadex.cz/m435b-prevodnik-usbttl-modul-s-ft232rl/?gclid=CjwKCAjwmeiIBhA6EiwA-uaeFRXA4soPKs384wWb1vIK3xhRTusBXaXjJ_JUQO9WOdVvmTuzFmfkJxoCZpMQAvD_BwE)).\
V Arduino IDE se jedná o desku "Arduino Pro or Pro Mini, ATmega328P (5V, 16MHz)". 

## Reference
Knihovny: 
* [LiquidCrystal_I2C.h](https://github.com/fmalpartida/New-LiquidCrystal/blob/master/LiquidCrystal_I2C.h) 
* [FastLED.h](https://github.com/FastLED/FastLED)

## Fotky
![open](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/open.jpg)
![main](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/main.jpg)
![logo](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/logo.jpg)
![back](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/back.jpg)
![open_back](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/open_back.jpg)
![back_on](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/back_on.jpg)
![panel](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/panel.jpg)
![panel_closer](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/panel_closer.jpg)
![glow](https://github.com/langrfrantisek/HzF_voting_system/blob/main/Photos/glow.jpg)


