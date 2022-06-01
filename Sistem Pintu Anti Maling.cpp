#include <LiquidCrystal.h>	// Include LiquidCrystal library
#include <Keypad.h>    		// Include Keypad library
#include <Servo.h>			// Include Servo library
#define Password_Length 8	// Panjang kata sandi + 1 untuk karakter null

LiquidCrystal lcd(A5,A4,A3,A2,A1,A0);											// Menjadikan pin A5,A4,A3,A2,A1,A0 sebagai input dari LCD
Servo myservo;																	// Inisialisasi servo

char Data[Password_Length];     
char Master[Password_Length] = "1A2B3C4";	// Mengatur password secara default 
char customKey;  
int electric_motor = 10;	// Menjadikan pin 10 sebagai output dari DC motor
int buzzer = 11;			// Menjadikan pin 11 sebagai output dari buzzer
int indicator_led = 12;		// Menjadikan pin 12 sebagai output dari LED
int k ;
int i = 0;
int s = 0;
int g = 0;
int a = 0;
int wait = 300; 			// Memberi jeda LED selama 0,3 detik
byte data_count = 0; 		// Menghitung untuk karakter yang dimasukkan
const byte ROWS = 4; 		// Kaypad memiliki 4 baris yang konstan
const byte COLS = 4; 		// Kaypad memiliki 4 kolom yang konstan

char hexaKeys[ROWS][COLS] = {	// Karakter baris dan kolom pada kaypad
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};  // Menjadikan pin 9, 8, 7, dan 6 sebagai output baris dari keypad
byte colPins[COLS] = {5, 4, 3, 2};	// Menjadikan pin 5, 4, 3, dan 2 sebagai output kolom dari keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);// Membuat objek keypad


void setup() {

  pinMode(electric_motor, OUTPUT);  // Menjadikan pin DC motor sebagai pin output
  pinMode(buzzer, OUTPUT); 			// Menjadikan pin buzzer sebagai pin output
  pinMode(indicator_led, OUTPUT);	// Menjadikan pin LED sebagai pin output
  Serial.begin(9600);    			
  lcd.begin(16,2);  				// Inisialisasi tampilan LCD
  Serial.print("Enter Password:");
  lcd.print("Enter Password:");		// Menampilkan "Enter Password:" di LCD
  delay(1500);						// Memberi jeda selama 1,5 detik
  lcd.clear();						// Menghapus karakter pada LCD

}
void loop() {


for(k=0;k<7 && g<1;k++)          	// Perulangan "For loop" untuk menginputkan < 7 karakter dari keypad 
{
 lcd.setCursor(0,0);				// Menampilkan karakter pada baris pertama (0,0) LCD
 lcd.print("Enter Password:");		// Menampilkan karakter di LCD
 delay(100);						// Memberi jeda selama 0,1 detik

 customKey = customKeypad.getKey();	// Penekanan tombol di keypad


if (customKey) {					// Masukkan penekanan tombol ke dalam array
 Data[data_count] = customKey;
   Serial.print(Data[data_count]);
   
   lcd.setCursor(s,1);				// Perintah LCD untuk mengubah kolom baris kedua
   lcd.print(Data[data_count]);
  
   digitalWrite(indicator_led,HIGH);// LED biru akan menyala ketika setiap input berhasil
   delay(wait);						// LED menunda untuk menyala
   digitalWrite(indicator_led,LOW);	// LED biru akan mati ketika setiap input tidak berhasil
   delay(wait);

   data_count++;
   s++;
}
}


if (data_count == Password_Length - 1) {	// Fungsi perulangan if untuk memerikasa apakah jumlah input telah mencapai panjang kata sandi
 while(i<1)                                
{
 Serial.println("");						// Mengirim kursor monitor serial di baris berikutnya
 lcd.print("");
 i++;
}

 if (!strcmp(Data, Master)) {				// Fungsi perulangan if jika kondisi kata sandi benar
  
   digitalWrite(electric_motor, HIGH);		// DC motor akan bergerak ketika kata sandi benar
   digitalWrite(buzzer, LOW);				// Buzzer tidak berbunyi ketika kata sandi benar
   Serial.println("correct");				// Menampilkan "correct" pada LCD
   lcd.clear();								// Menghapus karakter pada LCD
   myservo.attach(5);						// Deklarasi servo pada output pin 5
   myservo.write(90);						// Mengontrol motor servo agar berputar ke sudut 90°
   
   lcd.setCursor(0,0);						// Mengatur tampilan posisi karakter di baris pertama pada LCD 
   lcd.print("Password is");				// Menampilkan "Password is" pada LCD				
   lcd.setCursor(0,1);						// Mengatur tampilan posisi karakter di baris kedua pada LCD
   lcd.print("correct");					// Menampilkan "correct" pada LCD
   delay(3000);								// Memberi jeda selama 3 detik
   
   lcd.setCursor(0,0);
   lcd.print("Please come in");
   lcd.setCursor(0,1);
   lcd.print("and welcome :)");
   delay(5000);								// Memberi jeda selama 5 detik
   lcd.clear();								// Menghapus karakter pada LCD
   g=1;
}

else {										// Fungsi perulangan if jika kondisi kata sandi salah

   digitalWrite(electric_motor, LOW);		// DC motor tidak bergerak ketika kata sandi salah
   digitalWrite(buzzer,HIGH);				// Buzzer akan berbunyi ketika kata sandi salah
   Serial.println("incorrect");				// Menampilkan "incorrect" pada LCD
   lcd.clear();								// Menghapus karakter pada LCD
   
   lcd.setCursor(0,0);						// Mengatur tampilan posisi karakter di baris pertama pada LCD
   lcd.print("Password is");				// Menampilkan "Password is" pada LCD
   lcd.setCursor(0,1);						// Mengatur tampilan posisi karakter di baris kedua pada LCD
   lcd.print("incorrect");					// Menampilkan "incorrect" pada LCD
   delay(3000);								// Memberi jeda selama 3 detik
   
   lcd.setCursor(0,0);
   lcd.print("Please  try");
   lcd.setCursor(0,1);
   lcd.print("again  :(");
   delay(3000);								// Memberi jeda selama 3 detik
   lcd.clear();								// Menghapus karakter pada LCD
   g=1;
}
}
   a=1;
}

void clearData() {			// Kondisi menghapus data            
while (data_count != 0) {
Data[data_count--] = 0;
}
return;
}