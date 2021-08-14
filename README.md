# Hlasovací zařízení pro Hudbu z FEKTu

### Cíle projektu
Cílem projektu je vytvořit zařízení sloužící k počítání hlasů jednotlivých kapel na akci Hudba z FEKTu. Zařízením má být možné hlasovat až pro šest kapel a průběžné hlasy mají být k nahlédnutí na displeji.

## O projektu
Tento projekt se zabývá vytvořením zařízení, které by dokázalo počítat, zobrazovat a zaznamenávat hlasy. Vytvořené hlasovací zařízení je vytištěné na 3D tiskárně z mnoha dílů a sešroubováno dobromady. Na přední straně je podsvícené logo akce Hudby z FEKTu. Pod magnety připevněným víkem se nachází šest tlačítek s indikací. Zadní panel, rovněž připevněn magnety je součástím víka a dá se spolu s ním složit za zařízení. Tímto složením se odkryje zadní panel na kterém se nachází LCD display, tři přepínače, micro USB konektor, krytka s nápisem "328P" a 3D tištěný šroub se symbolem SD karty. Display zobrazuje aktuální počet hlasů jednotlivých kapel. Zařízení je napájeno pouze externě micro USB konektorem. V pravo od něj se nachází hlavní přepínač, který zajišťuje zapínání a vypínání zařízení. Přepínač s názvem "LCD" zapíná a vypíná podsvícení displeje. Přepínač "LOGO" zapíná a vypíná podsvícení loga na předním panelu. Obojí možné vypnout například pro šetření energie při napájení z powerbanky. Šroub se symbolem SD karty po odšroubování umožní přístup k micro SD kartě. Pod krytkou "328P" se nachází programovací piny Arduina (viz sekce Software - Programování).

### Funkce zařízení
Po připojení a zapnutí zařízení je možné začít hlasovat. Stiskem tlačítka vybrané kapely se rozsvítí indikace daného tlačítka. Behem svitu indikace nelze znovu hlasovat, zařízení během této doby aktualizuje informace na displeji a ukládá aktuální počet hlasů na microSD kartu.

## Harware
Tlačítka jsou zapojena jednovodičovým připojením přes dělič. Při stisku tlačítka se dělič uzemní v určitém místě (pro každé tlačíko v jiném) a dojde tak ke změně úbytku napětí, který je rozeznáván přes ADC (analog./digital. převodník) na pinu A7. ADC bere jako referenci 3,3V Arduina, proto je napájení "žebříku" děliče právě VCC (3,3V Arduina). Zbylé periferie (včetně samotného Arduina) jsou po zapnutí napájecího přepínače napájeny přímo z micro USB napájecího konkektoru (označen jako "5V").\
Adresovatelný RGB LED pásek zajišťující indikaci stisknutých tlačítek a podsvícení loga je připojen na pin 7. Šestice LED pro indikaci stisku tlačítkek jsou zapojeny od tlačítka šest směrem k nižším hodnotám tlačítek. V podsvícení loga je dalších dvanáct LED. Při pohledu na zařízení zepředu jdou LED postupně uplně z prava, dolů a pak dokola. Poslední je pak LED podsvicující blesk.\
LOGO přepínač je připojen přes pull-up rezistor k pinu 2.\
LCD display pro 16x2 znaků je připojen přes I2C sběrnici. LCD přepínač pak ovládá zapnutí a vypnutí podsvícení LCD.\
Modul pro microSD karty je připojen přes sběrnici SPI. Pro přístup k microSD kartě je potřeba odšroubovat ze zadního panelu plastový šroub se symbolem SD karty.

### Schéma zapojení
![HzF_schematic](https://github.com/langrfrantisek/HzF_voting_system/blob/main/HzF_hlasovani_schema.png)

#### Osazení
Součástky jsou osazeny na pájivé pole a propojeny. Arduino a modul pro micro SD kartu je zasunut v patici. LCD display, přepínače a adresovatelný LED pásek jsou připojeny pomocí konketorů. Dělič pro tlačítka má vlastní pájivé pole se šroubovacími konektory pro všechna tlačítka a potřebnými rezistory. Obě desky jsou propojeny třemi vodiči (VCC,DATA,GND).

#### Možnost rozšíření o další tlačítka
V případě potřeby rozšíření o další tlačítka (například pro akci HzF Warm Up) je u propojovacích vodičů ještě jedna volná šroubovací svorka, která by šla snadno propojit s pinem A6 a vytvořit tak další datový vstup pro další dělič s tlačítky. Po vyvedení GND a VCC ze stávajícího pájivého pole s deličem by mohl vzniknout přídavný modul s dalšími tlačítky.

### Seznam součástek

## Software
### Vývojový diagram

### Programování
Pro přístup k programovacím pinům je potřeba odsroubovat šroubek na krytce s nápisem "328P". **Je li připojen PC přes programátor k Arduinu, nesmí být zařízení napájeno z micro USB konektoru!** Stačí vypnout hlavní vypínač. Programátor a arduino mohou poté být při testování propojeny i při zapnutí zařízení **za předpokladu, že je programátor odpojen od PC/napájení během napájení zařízení z micro USB**, kvůli rušení (adresovatelný LED pásek jinak blbne) je třeba odpojit svorku která projuje napájení programátoru a Arduino.

## Reference


