#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;
bool dmpPret = false;
uint8_t Etat_mpuInt;
uint8_t etat_capteur;
uint16_t Taille_paquet;
uint16_t nb_octets;
uint8_t  memoire[64];
const float RADIANS_EN_DEGRES =57.2958;
Quaternion q;
VectorFloat g;
float ypr[3];
volatile bool mpuInterrupt=false;

void dmpDonneesPretes() {mpuInterrupt=true;}

void setup() {Wire.begin();Serial.begin(9600);
mpu.initialize();if (mpu.testConnection())
Serial.println("connexion avec MPU6050 établie");
else
Serial.println("erreur de connexion avec MPU6050 ");
delay(1000);etat_capteur=mpu.dmpInitialize();
if (etat_capteur==0){
Serial.println("unité DMP disponible...");
mpu.setDMPEnabled(true);
attachInterrupt(0,dmpDonneesPretes,RISING);
Etat_mpuInt=mpu.getIntStatus();dmpPret=true;
Taille_paquet=mpu.dmpGetFIFOPacketSize();}
else {
Serial.println("Erreur d'initialisation de l'unité DMP");
Serial.println(etat_capteur);}}

void loop() { if (!dmpPret) return;
mpuInterrupt=false;Etat_mpuInt=mpu.getIntStatus();
nb_octets=mpu.getFIFOCount();
if ((Etat_mpuInt & 0x10)||(nb_octets==1024)) {
mpu.resetFIFO();
Serial.println("débordement de mémoire ....!");}
else if (Etat_mpuInt & 0x02) {
while (nb_octets<Taille_paquet)
nb_octets=mpu.getFIFOCount();
mpu.getFIFOBytes(memoire,Taille_paquet);
mpu.resetFIFO();nb_octets-=Taille_paquet;
mpu.dmpGetQuaternion(&q,memoire);
mpu.dmpGetGravity(&g,&q);
mpu.dmpGetYawPitchRoll(ypr,&q,&g);
Serial.println(ypr[0]*RADIANS_EN_DEGRES,2);
delay(100);}}
