/* 2014
 *
 * Breakout game by Ilya Titov. Find building instructions on
 * http://webboggles.com/ The code that does not fall under the licenses of
 * sources listed below can be used non commercially with attribution.
 *
 * If you have problems uploading this sketch, this is probably due to sketch
 * size - you need to update ld.exe in arduino\hardware\tools\avr\avr\bin
 * https://github.com/TCWORLD/ATTinyCore/tree/master/PCREL%20Patch%20for%20GCC
 *
 * This sketch is using the screen control and font functions written by Neven
 * Boyanov for the http://tinusaur.wordpress.com/ project Source code and font
 * files available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 * Sleep code is based on this blog post by Matthew Little:
 * http://www.re-innovation.co.uk/web12/index.php/en/blog-75/306-sleep-modes-on-attiny85
 *
 */
/* 2016
 *
 * Updated by pakozm (Paco Zamora Martinez):
 *
 *   - code refactoring
 *
 *   Attiny85 PINS
 *             ____
 *   RESET   -|_|  |- 3V
 *   SCL (3) -|    |- (2) RIGHT
 *   SDA (4) -|    |- (1) BUZZER
 *   GND     -|____|- (0) LEFT
 */
/* 2016
 * Modified by Alexey Dynda.
 * New SSD1306 library is linked.
 */
#include <avr/eeprom.h>
#include "font6x8.h"
#include "ssd1306.h"
#include "nano_gfx.h"
#include <avr/sleep.h>
#include <avr/interrupt.h> // needed for the additional interrupt

//#define min(a,b) ((a)<(b)) ? (a) : (b)
//#define max(a,b) ((a)>(b)) ? (a) : (b)

uint16_t *EEPROM_ADDR = (uint16_t*)0;

#define LEFT_BTN    0
#define BUZZER      1
#define RIGHT_BTN   2

const int SCREEN_WIDTH   = 128;
const int SCREEN_HEIGHT  = 64;
const int BALL_INITIAL_X = SCREEN_WIDTH/2;
const int BALL_INITIAL_Y = 50;
const int PLATFORM_HEIGHT = 10;
const int INITIAL_PLATFORM_WIDTH = 16;
const int INITIAL_HDIR = -1;
const int INITIAL_VDIR = -1;

const int NUM_ROWS       = 8;
const int BLOCKS_PER_ROW = 16;
const int BLOCK_NUM_ROWS = 3;
const int PLAYER_ROW     = NUM_ROWS - 1;
const int TOTAL_BLOCKS   = BLOCK_NUM_ROWS * BLOCKS_PER_ROW;

volatile byte player = 0; //0 to SCREEN_WIDTH-platformWidth  - this is the position of the bounce platform
byte platformWidth = INITIAL_PLATFORM_WIDTH;
byte ballx = BALL_INITIAL_X; // coordinate of the ball
byte bally = BALL_INITIAL_Y; // coordinate of the ball
int vdir = -1; // vertical direction and step  distance
int hdir = -1; // horizontal direction and step distance
unsigned long lastFrame = 0; // time since the screen was updated last
boolean rows[BLOCK_NUM_ROWS][BLOCKS_PER_ROW]; // on-off array of blocks
uint16_t score = 0; // score - counts the number of blocks hit and resets the array
               // above when devisible by TOTAL_BLOCKS

void resetGame();
void drawPlatform();
void beep(int bCount,int bDelay);
void platformStep();
void drawBall();
void ballStep();
void frameStep();
void clearAreaBelowBlocks();
void drawBlocks();
void system_sleep();
void resetBlocks();

ISR(PCINT0_vect)
{
    if (player >0) 
    {
        player--;
    }
    return;
}

void playerInc(){ // PB2 pin button interrupt
  if (player<SCREEN_WIDTH-platformWidth){player++;}
}

void setup()
{
  DDRB |= 0b00011010;  	// set PB1 as output (for the speaker)
#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__)
  PCMSK = 0b00000001;	// pin change mask: listen to portb bit 1
  GIMSK |= 0b00100000;	// enable PCINT interrupt
  sei();		// enable all interrupts
  attachInterrupt(0,playerInc,CHANGE);
#else
#endif
  resetGame();
}

void loop() {
  // frame actions and screen update
  if (lastFrame+10 < millis()) {
    // continue moving after the interrupt
    platformStep();
    
    // bounce off the sides of the screen
    ballStep();

    // frame actions
    frameStep();

    // update whats on the screen
    noInterrupts();
    drawBlocks();
    clearAreaBelowBlocks();
    drawBall();
    drawPlatform();
    interrupts();

    lastFrame = millis();
    
  }
}

uint8_t canvas_buffer[30 * 24/8];
NanoCanvas canvas(30, 24, canvas_buffer);

#include "sova.h"

void resetGame(){
  lastFrame = millis();
  delay(40);
  noInterrupts();
  ssd1306_init();
  ssd1306_fillScreen(0x00);
  canvas.char_f6x8(0,4, "BREAK");
  canvas.char_f6x8(6,12, "OUT" );
  ssd1306_drawBitmap(0, 0, 128, 64, Sova);
  ssd1306_drawCanvas(0, 0, canvas.width(), canvas.height(), canvas.buffer());
  
  beep(200,600);
  beep(300,200);
  beep(400,300);
  interrupts();
  delay(3000);
  noInterrupts();
  resetBlocks();
  platformWidth = INITIAL_PLATFORM_WIDTH;
  ballx = BALL_INITIAL_X;
  bally = BALL_INITIAL_Y;
  hdir = INITIAL_HDIR;
  vdir = INITIAL_VDIR;
  score = 0;
  player = random(0,SCREEN_WIDTH-platformWidth);
  ballx = player+(platformWidth>>1);
  interrupts();
}

// the collsision check is actually done before this is called, this code works
// out where the ball will bounce
void collision(){
  if ((bally+vdir)%8==7&&(ballx+hdir)%8==7){ // bottom right corner
    if (vdir==1){hdir=1;}else if(vdir==-1&&hdir==1){vdir=1;}else {hdir=1;vdir=1;}
  }else if ((bally+vdir)%8==7&&(ballx+hdir)%8==0){ // bottom left corner
    if (vdir==1){hdir=-1;}else if(vdir==-1&&hdir==-1){vdir=1;}else {hdir=-1;vdir=1;}
  }else if ((bally+vdir)%8==0&&(ballx+hdir)%8==0){ // top left corner
    if (vdir==-1){hdir=-1;}else if(vdir==1&&hdir==-1){vdir=-1;}else {hdir=-1;vdir=-1;}
  }else if ((bally+vdir)%8==0&&(ballx+hdir)%8==7){ // top right corner
    if (vdir==-1){hdir=1;}else if(vdir==1&&hdir==1){vdir=-1;}else {hdir=1;vdir=-1;}
  }else if ((bally+vdir)%8==7){ // bottom side
    vdir = 1;
  }else if ((bally+vdir)%8==0){ // top side
    vdir = -1;
  }else if ((ballx+hdir)%8==7){ // right side
    hdir = 1;
  }else if ((ballx+hdir)%8==0){ // left side
    hdir = -1;
  }else {
    hdir = hdir*-1; vdir = vdir*-1;
  }

  beep(30,300);

}

void drawPlatform(){
  noInterrupts();
  ssd1306_setPos(player,PLAYER_ROW);
  ssd1306_i2cDataStart();
  for (byte pw = 1; pw <platformWidth; pw++) {
    ssd1306_i2cSendByte(B00000011);
  }
  ssd1306_i2cStop();
  interrupts();
}

void sendBlock(boolean fill){
  if (fill==1){
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B01111110);
    ssd1306_i2cSendByte(B00000000);
  }else {
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
    ssd1306_i2cSendByte(B00000000);
  }
}

void resetBlocks() {
  for (byte i =0; i<BLOCKS_PER_ROW;i++){
    for (int j=0; j<BLOCK_NUM_ROWS; ++j) {
      rows[j][i] = 1;
    }
  }
}

void drawBlocks() {
  for (int r=0; r<BLOCK_NUM_ROWS; ++r) {
    ssd1306_setPos(0,r);
    ssd1306_i2cDataStart();
    for (int bl = 0; bl <BLOCKS_PER_ROW; bl++) {
      if(rows[r][bl]==1){
        sendBlock(1);
      }else {
        sendBlock(0);
      }
    }
    ssd1306_i2cStop();
  }
}

void clearAreaBelowBlocks() {
  for (int r=BLOCK_NUM_ROWS; r<NUM_ROWS; ++r) {
    ssd1306_setPos(0,r);
    ssd1306_i2cDataStart();
    for (byte i =0; i<SCREEN_WIDTH; i++){
      ssd1306_i2cSendByte(B00000000);
    }
    ssd1306_i2cStop();
  }
}

void drawBall() {
  ssd1306_setPos(ballx,bally>>3);
  uint8_t temp = B00000001;
  ssd1306_i2cDataStart();
  temp = temp << ((bally&0x07)+1);
  ssd1306_i2cSendByte(temp);
  ssd1306_i2cStop();
}

// continues moving after interrupt
void platformStep() {
  if (digitalRead(RIGHT_BTN)==1) {
    player = min(SCREEN_WIDTH-platformWidth, player+3);
  }
  if (digitalRead(LEFT_BTN)==1) {
    player = max(0, player-3);
  }
}

// move and bounce the ball when reaches the screen limits
void ballStep() {
  if ((bally+vdir<SCREEN_HEIGHT-PLATFORM_HEIGHT && vdir==1) ||
      (bally-vdir>1 && vdir==-1)) {
    bally+=vdir;
  }
  else {
    vdir = vdir*-1;
  }
  if (((ballx+hdir<SCREEN_WIDTH-1) && (hdir==1)) ||
      ((ballx-hdir>1) && (hdir==-1))) {
    ballx+=hdir;
  }
  else {
    hdir = hdir*-1;
  }
}

void frameStep() {
  if (bally+vdir>=SCREEN_HEIGHT-PLATFORM_HEIGHT) {
    if(bally>10 &&
       (ballx<player || ballx>player+platformWidth)) {
      // game over if the ball misses the platform
      uint16_t topScore = eeprom_read_word(EEPROM_ADDR);
      if (topScore == 0xFFFF) {
        eeprom_write_word(EEPROM_ADDR, 0);
        topScore = 0;
      }
      if (score>topScore){
        topScore = score;
        eeprom_write_word(EEPROM_ADDR, topScore);
      }
      ssd1306_fillScreen(0x00);
      ssd1306_charF6x8(32, 3, "Game Over");
      ssd1306_charF6x8(32, 5, "score ");
      char temp[6] = {0,0,0,0,0,0};
      utoa(score,temp,10);
      ssd1306_charF6x8(70, 5, temp);
      ssd1306_charF6x8(32, 6, "top score ");
      utoa(topScore,temp,10);
      ssd1306_charF6x8(90, 6, temp);
      for (int i = 0; i<1000; i++){
        beep(1,random(0,i*2));
      }
      delay(1000);
      system_sleep();
      resetGame();
    }else if (ballx<player+(platformWidth>>1) && bally>10) {
      // if the ball hits left of the platform bounce left
      hdir=-1;
      beep(20,600);
    }else if (ballx>player+(platformWidth>>1) && bally>10) {
      // if the ball hits right of the platform bounce right
      hdir=1;
      beep(20,600);
    }else {
      // bounce right by default
      hdir=1;
      beep(20,600);
    }
  }

  int ball_row;
 collisionCheck: // go back to here if a collision was detected to prevent flying through a rigid
  ball_row = (bally+vdir)>>3;
  if (ball_row <= 2){
    if (rows[ball_row][ballx>>3]==1) {
      rows[ball_row][ballx>>3]=0;
      score++;
      collision();
      // reset blocks if all have been hit
      if (score%TOTAL_BLOCKS==0){
        resetBlocks();
      }
      // check collision for the new direction to prevent flying through a rigid
      goto collisionCheck;
    }
  }
}

void beep(int bCount,int bDelay){
  for (int i = 0; i<=bCount*2; i++){
    digitalWrite(BUZZER,i&1);
    for(int i2=0; i2<bDelay; i2++){__asm__("nop\n\t");}
  }
    digitalWrite(BUZZER,LOW);
}

// Routines to set and clear bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void system_sleep()
{
  ssd1306_fillScreen(0x00);
  ssd1306_i2cSendCommand(0xAE);
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
  ssd1306_i2cSendCommand(0xAF);
}
