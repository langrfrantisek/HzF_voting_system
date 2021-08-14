# Hlasovací zařízení pro Hudbu z FEKTu

### Cíle projektu
Cílem projektu je vytvořit zařízení sloužící k počítání hlasů jednotlivých kapel na akci Hudba z FEKTu. Zařízením má být možné hlasovat až pro šest kapel a průběžné hlasy mají být k nahlédnutí na displeji.

## Harware
Tlačítka jsou zapojena jednovodičovým připojením přes dělič. Při stisku tlačítka se dělič uzemní v určitém místě (pro každé tlačíko v jiném) a dojde tak ke změně úbytku napětí, který je rozeznáván přes ADC (analog./digital. převodník) na pinu A7. ADC bere jako referenci 3,3V Arduina, proto je napájení "žebříku" děliče právě VCC (3,3V Arduina). Zbylé periferie (včetně samotného Arduina) jsou po zapnutí napájecího přepínače napájeny přímo z micro USB napájecího konkektoru (označen jako "5V").\
Adresovatelný LED pásek zajišťující indikaci stisknutých tlačítek a podsvícení loga je připojen na pin 7. Šestice LED pro indikaci stisku tlačítkek jsou zapojeny od tlačítka šest směrem k nižším hodnotám tlačítek. V podsvícení loga je dalších dvanáct LED. Při pohledu na zařízení zepředu jdou LED postupně uplně z prava, dolů a pak dokola. Poslední je pak LED podsvicující blesk.\
LOGO přepínač je připojen přes pull-up rezistor k pinu 2.\
LCD display pro 16x2 znaků je připojen přes I2C sběrnici. LCD přepínač pak ovládá zapnutí a vypnutí podsvícení LCD.
Modul pro microSD karty je připojen přes sběrnici SPI. Pro přístup k microSD kartě je potřeba odšroubovat ze zadního panelu plastový šroub se symbolem SD karty.
### Programování
Pro přístup k programovacím pinům je potřeba odsroubovat šroubek na krytce s nápisem "328P". **Je li připojen PC přes programátor k Arduinu, nesmí být zařízení napájeno z micro USB konektoru!** Stačí vypnout hlavní vypínač. Programátor a arduino mohou poté být při testování propojeny i při zapnutí zařízení **za předpokladu, že je programátor odpojen od PC/napájení během napájení zařízení z micro USB**, kvůli rušení (adresovatelný LED pásek jinak blbne) je třeba odpojit svorku která projuje napájení programátoru a Arduino.
### Schéma zapojení
![HzF_schematic](https://github.com/langrfrantisek/HzF_voting_system/blob/main/HzF_hlasovani_schema.png)

### Seznam součástek

## Software
### Vývojový diagram

## Reference


