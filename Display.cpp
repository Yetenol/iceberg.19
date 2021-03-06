#include "Display.hpp"

// Implementierung: OBJEKTE
//extern Display d;
extern Player p;
extern Led led;
extern Mate mate;
extern Pilot m;
extern Ultrasonic us;
extern Compass compass;

Display::Display(int resetPin){}

void Display::init() {
  /*begin();  // initialisiere das Displays
  clearDisplay(); // leere den Bildschirm
  if (!silent) drawBitmap(0, 0, LOGO, 114, 64, WHITE); // zeige das Logo
  display();  //wendet Aenderungen an*/
}

void Display::setupMessage(byte pos, String title, String description) {
  
  /*if (!silent) {
    fillRect(47, 0, 81, 31, BLACK); // lösche das Textfeld
    drawRect(0, 29, map(pos, 0, SETUP_MESSAGE_RANGE, 0, 128), 2, WHITE);
    setTextColor(WHITE);

    setTextSize(2);
    setCursor(47, 0);
    print(title.substring(0, 6));

    setTextSize(1);
    setCursor(47, 17);
    print(description.substring(0, 13));

    display();
  }*/
}

// Infos auf dem Bildschirm anzeigen
void Display::update() {
  /*if (set() == false) {
    if (DEBUG_FUNCTIONS) debug(F("reload"));
    set();
  }

  clearDisplay();
  setTextColor(WHITE);

  if (compass.getHeading() < -135) { // zeige einen Punkt, der zum Tor zeigt
    drawRect(map(compass.getHeading(), -180, -134, 63 , 125), 61, 2, 2, WHITE); //unten (rechte Hälfte)
  } else if (compass.getHeading() < -45) {
    drawRect(125, map(compass.getHeading(), -135, -44, 61, 0), 2, 2, WHITE); //rechts
  } else if (compass.getHeading() < 45) {
    drawRect(map(compass.getHeading(), -45, 44, 125, 0), 0, 2, 2, WHITE); //oben
  } else if (compass.getHeading() < 135) {
    drawRect(0, map(compass.getHeading(), 45, 134, 0, 61), 2, 2, WHITE); //links
  } else if (compass.getHeading() < 180) {
    drawRect(map(compass.getHeading(), 135, 179, 0, 62), 61, 2, 2, WHITE); //unten (linke Hälfte)
  }
  if (level == 0) {
    drawLine(map(page, 0, PAGE_RANGE, 3, 123), 11, map(page, -1, PAGE_RANGE - 1, 3, 123), 11, WHITE);
  } else if (level == 1) {
    drawLine(3, 11, map(subpage, 0, subpageRange[page], 3, 123), 11, WHITE);
    drawLine(map(subpage, -1, subpageRange[page] - 1, 3, 123), 11, 123, 11, WHITE);
  }

  // Pixy Boxen
  if (page == 3) {
    for (byte i = 0; i < blockCount; i++) { // geht alle erkannten Bloecke durch
      int width = map(pixy.blocks[i].width, 0, PIXY_MAX_X - PIXY_MIN_X + 1, 0, 121);
      int height = map(pixy.blocks[i].height, 0, PIXY_MAX_Y - PIXY_MIN_Y + 1, 0, 47);
      int x = map(pixy.blocks[i].x - width / 2, PIXY_MIN_X, PIXY_MAX_X, 3, 123);
      int y = map(pixy.blocks[i].y - height / 2, PIXY_MIN_Y, PIXY_MAX_Y, 13, 59);
      int angle = pixy.blocks[i].angle;
      switch (pixy.blocks[i].signature) { // Was sehe ich?
        case SIGNATURE_BALL:
          if (subpage < 2) fillRect(x, y, width, height, WHITE);
          break;
        case SIGNATURE_GOAL:
          if (subpage == 0) drawRect(x, y, width, height, WHITE);
          else if (subpage == 2) fillRect(x, y, width, height, WHITE);
          break;
        case SIGNATURE_CC:
          DEBUG_SERIAL.println(angle);
          if (subpage == 0 || subpage == 3) {
            if (angle < 0) drawLine(x + width, y, x, y + height, WHITE);
            else drawLine(x, y, x + width, y + height, WHITE);
          }
          break;
      }
    }
    if (subpage == 1 && seeBall) drawLine(63, 59, map(ball, -X_CENTER, X_CENTER, 3, 123), 13, WHITE);
    if (subpage == 2 && seeGoal) drawLine(63, 59, map(goal, -X_CENTER, X_CENTER, 3, 123), 13, WHITE);
  }
  setTextSize(1);
  setCursor(3, 3);
  print(title.substring(0, 14) + String("               ").substring(0, max(1, 15 - title.length())) + runtime);

  setTextSize(2);
  setCursor(3, 14);
  print(line0.substring(0, 10));

  setCursor(3, 30);
  print(line1.substring(0, 10));

  setCursor(3, 46);
  print(line2.substring(0, 10));

  invertDisplay(m.getMotEn());
  display();      // aktualisiere Display

  lastDisplay = millis(); // merke Zeitpunkt*/
}

void Display::select() {
  if (level < 1) {
    level++;
    update();
  }
}

void Display::back() {
  if (level == 0) {
    reset();
  } else {
    level--;
    update();
  }
}

void Display::toggle() {
  if (level == 0) select();
  else back();
}

void Display::change(int change) {
  if (level == 0) {
    page += change;
    shift(page, 0, PAGE_RANGE);
    subpage = 0;
  } else if (level == 1) {
    subpage += change;
    shift(subpage, 0, subpageRange[page]);
  }
  update();
}

bool Display::set() {
  runtime = "";
  int min = numberOfMinutes(millis());
  if (min < 10) {
    runtime += "0";
  }
  runtime += String(min) + ":";
  int sec = numberOfSeconds(millis());
  if (sec < 10) {
    runtime += "0";
  }
  runtime += String(sec);

  title = "";
  line0 = "";
  line1 = "";
  line2 = "";
  lineIndex = 0;

  String charBall;
  String charGoal;
  String charEast;
  String charWest;
  String charSum;

  switch (page) {
    case 0:
      if (isTypeA) title = F("IcebergRobotsA");
      else title = F("IcebergRobotsB");

      if (seeBall) {
        if (p.isRusher())      addLine(F("rush"), ball, true);
        else if (p.isKeeper()) addLine(F("keep"), ball, true);
        else                   addLine(F("off"), ball, true);
      } else {
        if (p.isRusher())      addLine(F("rush"), F("blind"));
        else if (p.isKeeper()) addLine(F("keep"), F("blind"));
        else                   addLine(F("off"), F("blind"));
      }
      addLine(driveState.substring(0, 6), driveDirection, true);
      if (batState == 2) addLine(F("lowVoltage"));
      else addLine(displayDebug);
      addLine(F("=========="));
      break;
    case 1:
      title = F("Sensor");
      addLine(F("B.angl"), ball, true);
      addLine("^" + String(us.front()), String(us.right()) + ">");
      addLine("<" + String(us.left()), String(us.back()) + "v");
      
      addLine(F("Barr"), analogRead(LIGHT_BARRIER));
      addLine(F("Volt"), String(batVol / 10) + "." + String(batVol % 10)); // battery voltage
      if (onLine) {
        addLine(F("Line:"), lineDir, true);
      } else {
        addLine(F("Line:"));
      }
      addLine(F("Head"), compass.getHeading(), true);
      addLine(F("Time"), millis() / 1000);
      //addLine("acc.X", accel_event.acceleration.x, true); TODO
      //addLine("acc.Y", accel_event.acceleration.y, true); TODO
      //addLine("acc.Z", accel_event.acceleration.z, true); TODO
      addLine(F("=========="));
      break;
    case 2:
      title = F("Weighting");
      addLine(F("Scr"), score);
      addLine(F("B.widt"), scoreBallWidth);
      addLine(F("B.cent"), scoreBall);
      addLine(F("Back"), scoreRearward);
      addLine(F("Goal"), scoreGoal);
      addLine(F("=========="));
      break;
    case 3:
      if (!blockCountBall && seeBall) charBall = '*';
      else charBall = String(blockCountBall).charAt(0);
      if (!blockCountGoal && seeGoal) charGoal = '*';
      else charGoal = String(blockCountGoal).charAt(0);
      if (!blockCountEast && seeEast) charEast = '*';
      else charEast = String(blockCountEast).charAt(0);
      if (!blockCountWest && seeWest) charWest = '*';
      else charWest = String(blockCountWest).charAt(0);
      charSum = String(blockCount).charAt(0);

      if (subpage == 0) title = "Pixy " + charBall + "+" + charGoal + "+" + charWest + "+" + charEast + "=" + charSum;
      else if (subpage == 1) title = "Ball " + charBall;
      else if (subpage == 2) title = "Goal   " + charGoal;
      else if (subpage == 3) title = "CC       " + charWest + "+" + charEast;
      addLine();
      addLine();
      addLine();
      addLine();
      break;
    case 4:
      title = F("Pixy");
      if (seeBall) addLine(F("B.angl"), ball, true);
      else addLine(F("B.angl"));
      addLine(F("B.widt"), ballWidth);
      addLine(F("B.area"), ballArea);
      addLine(F("#ball"), (millis() - seeBallTimer) / 1000);
      if (seeGoal) addLine(F("G.angl"), goal, true);
      else addLine(F("G.angl"));
      addLine(F("G.widt"), goalWidth);
      addLine(F("G.area"), goalArea);
      addLine(F("#goal"), (millis() - seeGoalTimer) / 1000);
      if (seeEast) addLine(F("E.angl"), east, true);
      else addLine(F("E.angl"));
      if (seeWest) addLine(F("W.angl"), west, true);
      else addLine(F("W.angl"));

      if (seeWest || seeEast) {
        int angle = 0;
        if (seeWest) angle += west;
        else angle += east - 30;
        if (seeEast) angle += east;
        else angle += west + 30;

        angle /= 2;
        if (ccLeft) addLine(F("CC <"), angle, true);
        else addLine(F("CC >"), angle, true);
      } else addLine(F("CC"));
      addLine(F("=========="));
      break;
    case 5:
      title = F("Driving");
      addLine(F("direc"), driveDirection, true);
      addLine(F("power"), drivePower, true);
      addLine(driveState);
      addLine(F("orien"), pidSetpoint, true);
      addLine(F("rotat"), driveRotation, true);
      addLine(F("?line"), onLine);
      addLine(F("?head"), isHeadstart);
      addLine(F("#head"), (millis() - headstartTimer) / 1000);
      addLine(F("#flat"), (millis() - flatTimer) / 1000);
      addLine(F("#role"), p.lastRoleToggle() / 1000);
      addLine(F("#clos"), closeBallTimer / 1000);
      addLine(F("=========="));
      break;
    case 6:
      title = F("Mate");
      if (mate.timeout()) addLine(F("Tout:"), mate.timeout() / 1000);
      else {
        if (!mate.getMotEn()) addLine(F("Role:"), F("off"));
        else if (mate.isKeeper()) addLine(F("Role:"), F("keeper"));
        else if (mate.isRusher()) addLine(F("Role:"), F("rusher"));
        else addLine(F("Role:"), "?");
        addLine(F("State"), mate.getState());
        addLine(F("Score"), mate.getScore());
      }
      addLine(F("=========="));
      break;
  }
  if (batState == 3) {
    if (255 * (millis() % 2000 < 1000)) {
      line2 = F("critVoltag");
    } else {
      line2 = "";
    }
  }
  if (subpageRange[page] != lineIndex) {
    subpageRange[page] = lineIndex;
    return false;
  } else {
    return true;
  }
}

void Display::addLine(String title, String value) {
  if (title.length() + value.length() < 10) title += String("          ").substring(0, 10 - title.length() - value.length());
  title += value;
  title = title.substring(0, 10);
  int line = lineIndex - subpage;
  shift(line, 0, subpageRange[page]);
  if (line == 0) {
    line0 = title;
  } else if (line == 1) {
    line1 = title;
  } else if (line == 2) {
    line2 = title;
  }
  lineIndex++;

}
void Display::addLine(String title, long value, bool showPlus) {
  if (showPlus) {
    addLine(title, intToStr(value));
  } else {
    addLine(title, String(value));
  }
}
void Display::addLine(String title, long value) {
  addLine(title, String(value));
}
void Display::addLine(String title) {
  addLine(title, "");
}
void Display::addLine() {
  addLine("", "");
}

String Display::intToStr(int number) {
  if (number < 0) {
    return String(number);
  } else {
    return "+" + String(number);
  }
}

byte Display::getPage() {
  return page;
}

