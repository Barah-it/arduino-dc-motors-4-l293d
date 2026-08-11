/*
  مهمة: التحكم في 4 محركات DC باستخدام شريحة L293D (الجزء الأول فقط)

  التتابع الحركي:
  1. للأمام: 30 ثانية
  2. للخلف: 60 ثانية (دقيقة كاملة)
  3. لليمين ولليسار بالتناوب (محاكاة الانعطاف): دقيقة كاملة

  ملاحظة: نستخدم شريحتين L293D للتحكم بـ 4 محركات
  (كل شريحة L293D تتحكم بمحركين DC)

  التوصيل المقترح على Tinkercad:
  L293D #1 (يتحكم بالمحركين الأيمن الأمامي RF و الأيمن الخلفي RB):
  - IN1 -> Pin 2   (اتجاه محرك RF)
  - IN2 -> Pin 3   (اتجاه محرك RF)
  - IN3 -> Pin 4   (اتجاه محرك RB)
  - IN4 -> Pin 5   (اتجاه محرك RB)
  - EN1, EN2 -> 5V مباشرة (تشغيل دائم بأقصى سرعة) أو PWM لو أردت تحكم بالسرعة

  L293D #2 (يتحكم بالمحركين الأيسر الأمامي LF و الأيسر الخلفي LB):
  - IN1 -> Pin 6   (اتجاه محرك LF)
  - IN2 -> Pin 7   (اتجاه محرك LF)
  - IN3 -> Pin 8   (اتجاه محرك LB)
  - IN4 -> Pin 9   (اتجاه محرك LB)
  - EN1, EN2 -> 5V مباشرة

  فكرة التحكم:
  - IN1=HIGH, IN2=LOW  => المحرك يدور للأمام
  - IN1=LOW,  IN2=HIGH => المحرك يدور للخلف
  - IN1=LOW,  IN2=LOW  => المحرك متوقف
*/

// محركات الجهة اليمنى (L293D الأول)
const int RF_IN1 = 2;
const int RF_IN2 = 3;
const int RB_IN3 = 4;
const int RB_IN4 = 5;

// محركات الجهة اليسرى (L293D الثاني)
const int LF_IN1 = 6;
const int LF_IN2 = 7;
const int LB_IN3 = 8;
const int LB_IN4 = 9;

void setup() {
  pinMode(RF_IN1, OUTPUT);
  pinMode(RF_IN2, OUTPUT);
  pinMode(RB_IN3, OUTPUT);
  pinMode(RB_IN4, OUTPUT);

  pinMode(LF_IN1, OUTPUT);
  pinMode(LF_IN2, OUTPUT);
  pinMode(LB_IN3, OUTPUT);
  pinMode(LB_IN4, OUTPUT);

  stopAllMotors();

  // 1) للأمام لمدة 30 ثانية
  moveForward();
  delay(30000);

  // 2) للخلف لمدة 60 ثانية
  moveBackward();
  delay(60000);

  // 3) لليمين ولليسار بالتناوب لمدة 60 ثانية
  unsigned long turnStart = millis();
  while (millis() - turnStart < 60000) {
    turnRight();
    delay(2000); // ثانيتين يمين
    turnLeft();
    delay(2000); // ثانيتين يسار
  }

  // إيقاف كل المحركات بعد انتهاء التتابع
  stopAllMotors();
}

void loop() {
  // فارغ، لأن كامل التتابع تم تنفيذه مرة واحدة داخل setup()
  // إذا أردت تكرار الدورة، انقل الكود من setup() إلى هنا
}

// ---------- دوال الحركة ----------

void moveForward() {
  // كل المحركات تدور بنفس الاتجاه للأمام
  digitalWrite(RF_IN1, HIGH); digitalWrite(RF_IN2, LOW);
  digitalWrite(RB_IN3, HIGH); digitalWrite(RB_IN4, LOW);
  digitalWrite(LF_IN1, HIGH); digitalWrite(LF_IN2, LOW);
  digitalWrite(LB_IN3, HIGH); digitalWrite(LB_IN4, LOW);
}

void moveBackward() {
  // عكس اتجاه دوران كل المحركات
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, HIGH);
  digitalWrite(RB_IN3, LOW); digitalWrite(RB_IN4, HIGH);
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, HIGH);
  digitalWrite(LB_IN3, LOW); digitalWrite(LB_IN4, HIGH);
}

void turnRight() {
  // محاكاة الانعطاف لليمين: الجهة اليسرى للأمام، الجهة اليمنى للخلف (أو متوقفة)
  digitalWrite(RF_IN1, LOW);  digitalWrite(RF_IN2, HIGH); // يمين للخلف
  digitalWrite(RB_IN3, LOW);  digitalWrite(RB_IN4, HIGH);
  digitalWrite(LF_IN1, HIGH); digitalWrite(LF_IN2, LOW);  // يسار للأمام
  digitalWrite(LB_IN3, HIGH); digitalWrite(LB_IN4, LOW);
}

void turnLeft() {
  // محاكاة الانعطاف لليسار: الجهة اليمنى للأمام، الجهة اليسرى للخلف (أو متوقفة)
  digitalWrite(RF_IN1, HIGH); digitalWrite(RF_IN2, LOW);  // يمين للأمام
  digitalWrite(RB_IN3, HIGH); digitalWrite(RB_IN4, LOW);
  digitalWrite(LF_IN1, LOW);  digitalWrite(LF_IN2, HIGH); // يسار للخلف
  digitalWrite(LB_IN3, LOW);  digitalWrite(LB_IN4, HIGH);
}

void stopAllMotors() {
  digitalWrite(RF_IN1, LOW); digitalWrite(RF_IN2, LOW);
  digitalWrite(RB_IN3, LOW); digitalWrite(RB_IN4, LOW);
  digitalWrite(LF_IN1, LOW); digitalWrite(LF_IN2, LOW);
  digitalWrite(LB_IN3, LOW); digitalWrite(LB_IN4, LOW);
}
