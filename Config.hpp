#ifndef Config_hpp
#define Config_hpp

#include "Arduino.h"
#include "Display.hpp"
#include "Led.hpp"
#include "Pilot.hpp"
#include "Player.hpp"
#include "Mate.hpp"
#include "Ultrasonic.hpp"
#include "Utility.hpp"
#include "Input.hpp"
#include "BallTouch.hpp"
#include "Compass.hpp"

#include "EEPROM.h"
#include "Pin.h"

#include <SPI.h>
#include <WSWire.h>
#include <EEPROM.h>
#include <Pixy.h>
#include <RotaryEncoder.h>
#include <PID_v1.h>
#include <Adafruit_NeoPixel.h>

// Implementierung: FAHREN
extern bool start, onLine, isHeadstart, isAvoidMate, isKeeperLeft, wasMotor, wasStart;
extern int rotMulti, drivePower, driveRotation, driveDirection, driveOrientation, lineDir;
extern unsigned long lineTimer, headstartTimer, avoidMateTimer, flatTimer;
extern String driveState;

// Implementierung: BEWERTUNG
extern byte scoreBallWidth, scoreBall, scoreRearward, scoreGoal, score;

// Implementierung: BLUETOOTH, MATE
extern bool wasStartButton;
extern unsigned long startTimer, sendAvoidTimer, bluetoothTimer;

// Implementierung: WICHTUNG DER PID-REGLER
extern double pidSetpoint, pidIn, pidOut;
extern PID myPID;

// Implementierung: BATTERY
extern byte batState;
extern int batVol;

// Implementierung: PIXY
extern bool seeBall, seeGoal, seeEast, seeWest, closeBall, isDrift, driftLeft, ccLeft;
extern byte pixyState, blockCount, blockCountBall, blockCountGoal, blockCountEast, blockCountWest;
extern int ball, ballWidth, ballArea, goal, goalWidth, goalArea, east, eastHeight, west, westHeight;
extern unsigned long seeBallTimer, seeGoalTimer, seeEastTimer, seeWestTimer, closeBallTimer, driftTimer, ballLeftTimer, ballRightTimer, pixyResponseTimer, pixyTimer;
extern Pixy pixy;

// Implementierung: ULTRASCHALL
extern bool isPenaltyFree;
extern unsigned long penaltyFreeTimer, usTimer;

// Implementierung: KICK, LIGHT-BARRIER
extern bool hasBall;
extern unsigned long kickTimer;

// Implementierung: LIFT
extern bool isLifted;

// Implementierung: DISPLAY
extern bool isTypeA;
extern unsigned long lastDisplay;
extern String displayDebug;

// Implementierung: LEDS
extern bool wasLedButton, hasDebugHead, isSetupAnimantion, stateFine;
extern unsigned long ledTimer;

// Implementierung: BUZZER
extern byte silent;
extern unsigned long buzzerStopTimer;

// Implementierung: ROTARY-ENCODER
extern RotaryEncoder rotaryEncoder;
extern int rotaryPositionLast;
extern bool wasMenuButton;

// Fahren
#define ROLE_COOLDOWN 1000      // [0 bis *]~1000 Zeitspanne, in dem kein Rollenwechsel stattfindet
#define ANGLE_SIDEWAY 100       // [0 bis 180]~100
#define ANGLE_GOAL 80           // [0 bis 180]~80 Winkel für Tordrehung
#define ANGLE_GOAL_MAX 45       // [0 bis 180]~45 maximaler Orientierungswinkel zum Tor
#define ANGLE_PASSIVE_MAX 35    // [0 bis 180]~45 maximaler Orientierungswinkel beim Zurückfahren
#define ANGLE_TURN_MAX 90       // [0 bis 180]~90 maximaler Orientierungswinkel zur Ballsuche
#define ANGLE_RETURN_MIN 20     // [0 bis 180]~90 minimaler Orientierungswinkel beim Zurücckdrehen
#define ANGLE_CENTER 15         // [0 bis 180]~15 Toleranz für mittige Objekte
#define ROTATION_SIDEWAY 100    // [0 bis *]~100
#define ROTATION_AWAY 40        // [0 bis *]~40
#define ROTATION_18CM 50        // [0 bis *]~70
#define ROTATION_10CM 70        // [0 bis *]~90
#define ROTATION_TOUCH 40       // [0 bis *]~20
#define SPEED_BACKWARDS 1.4*60      // [0 bis 255]~70  STATUS 0: Nach hinten
#define SPEED_PENALTY 1.4*40        // [0 bis 255]~50  STATUS 0: Nach hinten
#define SPEED_KEEPER 1.4*65         // [0 bis 255]~60  STATUS 1: Torverteidigung
#define SPEED_FREE 1.4*70           // [0 bis 255]~70 STATUS 4: Befreiung
#define SPEED_LOST 1.4*60          // [0 bis 255]~100 STATUS 5: Seitlich verloren
#define SPEED_SIDEWAY 1.4*60       // [0 bis 255]~100  STATUS 6: Ballverfolgung
#define SPEED_BALL 1.4*45          // [0 bis 255]~72  STATUS 6: Ballverfolgung
#define SPEED_BALL_FAR 1.4*50      // [0 bis 255]~72  STATUS 6: Ballverfolgung
#define SPEED_CLOSE 1.4*45         // [0 bis 255]~60 STATUS 7: Torausrichtung
#define SPEED_ATTACK 1.4*60        // [0 bis 255]~100 STATUS 8: Angriff
#define SPEED_AVOID_MATE 1.4*100   // [0 bis 255]~100 STATUS 9: Ausweichen
#define SPEED_DRIFT 1.4*80         // [0 bis 255]~140
#define SPEED_LINE 1.4*90          // [0 bis 255]~90

// TIMES
#define BACKWARD_MAX_DURATION 4000    // wann darf frühestens eingegriffen werden
#define GOAL_STUCK_DURATION 500       // wie lange soll nach vorne gefahren werden?
#define SIDEWARD_MAX_DURATION 1500    // max Zeit für Seitwärtsfahren
#define SIDEWARD_MIN_DURATION 700     // min Zeit für Seitwärtsfahren
#define TURN_MAX_DURATION 1500        // max Zeit für Drehmodus
#define RETURN_MAX_DURATION 1500      // max Zeit für Drehmodus zurück
#define LOST_DURATION 700             // max Zeit für Ausweichmanöver
#define LINE_DURATION 80              // wie lange steuern wir der Linie entgegen?
#define HEADSTART_DURATION 350        // wie lange fahren wir volle Geschwindigkeit?
#define AVOID_MATE_DURATION 200       // wie lange weichen wir aus
#define DRIFT_DURATION 200            // wie lange steuern wir einem Drift entgegen?
#define PIXY_RESPONSE_DURATION 20000  // wie lange soll die Pixy-Led grün nachleuchten?

// Feld
#define COURT_REARWARD_MAX 35           // optimaler Abstand nach hinten
#define COURT_REARWARD_MIN 25           // optimaler Abstand nach hinten
#define COURT_WIDTH 150         // Summe der Abstände nach rechts und links
#define COURT_BORDER_MIN 80     // Abstand nach rechts bzw. links am Torpfosten
#define COURT_WIDTH_FREE 140
#define COURT_POST_TO_BORDER 110 // Abstand nach rechts bzw. links am Torpfosten

// LEDS
#define ANIMATION true          // soll die Animation stattfinden?
#define ANIMATION_SPEED .01     // Geschwindigkeit der Animation
#define ANIMATION_DURATION 2000 // Länge der Animation
#define BOTTOM_LENGTH 40        // [0 bis *] Anzahl der Boden-Leds
#define BOTTOM_BRIGHTNESS 255   // [0 bis 255] Helligkeit der Boden-Leds
#define MATRIX_LENGTH  12       // [0 bis *] Anzahl der Matrix-Leds
#define MATRIX_BRIGHTNESS 50    // [0 bis 255] Helligkeit der Matrix-Leds
#define INFO_LENGTH 12           // [0 bis *] Anzahl der Info-Leds
#define INFO_BRIGHTNESS 10     // [0 bis 255] Helligkeit der Info-Leds

// PID-Regler
#define PID_FILTER_P .27  // [0 bis *]~.27 p:proportional
#define PID_FILTER_I .02  // [0 bis *]~0   i:vorausschauend
#define PID_FILTER_D .03  // [0 bis *]~.03 d:Schwung herausnehmen (nicht zu weit drehen)

// PIYX
#define SIGNATURE_BALL 1      // Pixy-Signature des Balls
#define SIGNATURE_GOAL 2      // Pixy-Signature des Tors
#define SIGNATURE_CC 28       // Pixy-Signature des Tors
#define BALL_WIDTH_TRIGGER 35 // Schwellwert eines großen Balles
#define BALL_ANGLE_TRIGGER 40 // Schwellenwert der Ballrichtung

// DISPLAY
#define SETUP_MESSAGE_RANGE 10 // [0 bis *] Anzahl von Schritten im Setup

// Serielle Kommunikationen
#define DEBUG false                // soll eine Usb-Kommunikation bestehen?
#define DEBUG_STATE false          // soll der Statuswechsel gezeigt werden?
#define DEBUG_FUNCTIONS true     // sollen Methoden gezeigt werden?
#define DEBUG_LOOP true           // soll jeder Schleifendurchlauf gezeigt werden?
#define DEBUG_BLUETOOTH true      // sollen bluetooth nachrichten gezeigt werden?
#define DEBUG_SERIAL Serial       // Serial der Usb-Schnittstelle
#define BLUETOOTH true            // soll eine Bluetooth-Kommunikation bestehen?
#define BLUETOOTH_SERIAL Serial2  // Serial des Bluetooth-Moduls
#define BOTTOM_SERIAL Serial3     // Serial des Bodensensor-Arduinos
#define LOGGER_SERIAL Serial1 // Serial des Ultraschall-Arduinos
#define START_MARKER 254          // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER 255            // Endzeichen einer Bluetooth-Nachricht

// BATTERY_VOLTAGE
#define VOLTAGE_MIN 40          // [0 bis 126]~40  Mindestspannung des Akkus
#define VOLTAGE_MOTOR_CRIT 100  // [0 bis 126]~90  Kritische Akkuspannung beim Fahren
#define VOLTAGE_MOTOR_LOW 108   // [0 bis 126]~108 Geringe Akkuspannung beim Fahren
#define VOLTAGE_CRIT 100        // [0 bis 126]~90  Kritische Akkuspannung
#define VOLTAGE_LOW 110         // [0 bis 126]~110 Geringe Akkuspannung

// BEWERTUNG
#define WEIGHTING_BALL 50
#define WEIGHTING_BALL_WIDTH 100
#define WEIGHTING_REARWARD 30
#define WEIGHTING_SEE_GOAL 10

// Zeitumwandlung
#define MILS_PER_SEC  (1000UL)  // Millisekunden pro Sekunde
#define MILS_PER_MIN  (60000UL) // Millisekunden pro Minute
#define SECS_PER_MIN  (60UL)    // Sekunden pro Minute
#define MINS_PER_HOUR (60UL)   // Minuten pro Stunde

// Makro-Methoden
#define X_CENTER ((PIXY_MAX_X-PIXY_MIN_X)/2)                                  // PIXY: Die Mitte des Bildes der Pixy (in Pixeln)
#define numberOfSeconds(_millis_) ((_millis_ / MILS_PER_SEC) % SECS_PER_MIN)  // TIME: wandle Zeit in Sekundenanzeige um
#define numberOfMinutes(_time_) (_time_ / MILS_PER_MIN) % MINS_PER_HOUR       // TIME: wandle Zeit in Minutenanzeige um

void pinModes();

#endif
