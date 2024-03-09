#include <Servo.h>

#define pBas 3
#define pFroBac 5
#define pTopDow 6
#define pClo 9

#define pBtn 1

//--------------------------------- CLASS ROBOTICARM ---------------------------------------------//
class RoboticArm {
public:
  RoboticArm(int pA1, int pA2, int pA3, int pA4)
    : pBase(pA1), pFrontBack(pA2), pTopDown(pA3), pClow(pA4) {
  }

  void attachServos(int pA1, int pA2, int pA3, int pA4) {
    s1.attach(pA1);
    s2.attach(pA2);
    s3.attach(pA3);
    s4.attach(pA4);
  }

  void dettachServos() {
    s1.detach();
    s2.detach();
    s3.detach();
    s4.detach();
  }

  void startsPositions() {
    starting = checksStartingPosition(s1, 1);
    setUpStartingPosition(s1, starting, 1);

    starting = checksStartingPosition(s2, 2);
    setUpStartingPosition(s2, starting, 2);

    starting = checksStartingPosition(s3, 3);
    setUpStartingPosition(s3, starting, 3);

    starting = checksStartingPosition(s4, 4);
    setUpStartingPosition(s4, starting, 4);
  }

  void selfEmployment() {


    //TO DO: Configurar as posições dos servos para realizar o
    //trabalho autônomo.
  }

private:
  int pBase, pFrontBack, pTopDown, pClow, he;
  bool starting;
  Servo s1, s2, s3, s4;

  bool checksStartingPosition(Servo servo, int he) {
    if (he == 1) {
      if (servo.read() >= 93 - 5 and servo.read() <= 93 + 5) {
        return true;
      } else {
        return false;
      }
    } else if (he == 2) {
      if (servo.read() >= 70 - 5 and servo.read() <= 70 + 5) {
        return true;
      } else {
        return false;
      }
    } else if (he == 3) {
      if (servo.read() >= 150 - 5 and servo.read() <= 150 + 5) {
        return true;
      } else {
        return false;
      }
    } else {
      if (servo.read() >= 170 - 5 and servo.read() <= 170 + 5) {
        return true;
      } else {
        return false;
      }
    }
  }

  void setUpStartingPosition(Servo servo, bool starting, int he) {
    if (starting == false) {
      if (he == 1) {
        servo.write(93);
        servo.detach();
      }
      if (he == 2) {
        servo.write(70);
        servo.detach();
      }
      if (he == 3) {
        servo.write(150);
        servo.detach();
      }
      if (he == 4) {
        servo.write(170);
        servo.detach();
      }
    }
  }
};

//------------------------------------ CLASS BUTTON ---------------------------------------------//
class Button {
public:
  Button(int pB)
    : pButton(pB) {
    setupButton(pButton);
    btnClicado = btnLiberado = 0;
  }

  int checkButton() {
    if (btnClicado == 1 and btnLiberado == 1) {
      count++;
      btnClicado = 0;
      btnLiberado = 0;
      return count;

      if (count > 2) {
        count = 0;
      }
    }
  }

private:
  int pButton, btnClicado, btnLiberado, count;

  void setupButton(int pB) {
    pinMode(pB, INPUT);
  }
};


//--------------------------------------INICIO DO PROGRAMA-------------------------------------------------------//
RoboticArm robArm(pBas, pFroBac, pTopDow, pClo);
Button btt(pBtn);

void setup() {
  // Serial.begin(9600);
  // robArm.startsPositions();
}

void loop() {
  if (btt.checkButton() == 1) {
    robArm.attachServos(pBas, pFroBac, pTopDow, pClo);
    // robArm.selfEmployment();
  }else if (btt.checkButton() == 2){
    robArm.dettachServos();
  }
}
