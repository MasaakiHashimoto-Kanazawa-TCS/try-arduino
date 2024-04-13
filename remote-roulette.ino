//7セグメントLEDを0から9まで1秒ごとに自動カウント

#include <IRremote.h>

const int IR_RECEIVE_PIN = 12;  // IRセンサのピン番号を定義する
bool LoopStop = true;
decode_results results;

//数字を配列で定義
const boolean Seg_Array[11][8] = {
  {1,1,1,0,0,1,1,1}, //0
  {1,0,0,0,0,1,0,0}, //1
  {1,1,0,1,0,0,1,1}, //2
  {1,1,0,1,0,1,1,0}, //3
  {1,0,1,1,0,1,0,0}, //4
  {0,1,1,1,0,1,1,0}, //5
  {0,0,1,1,0,1,1,1}, //6
  {1,1,1,0,0,1,0,0}, //7
  {1,1,1,1,0,1,1,1}, //8
  {1,1,1,1,0,1,0,0}, //9
  {0,0,0,0,1,0,0,0}  //.
};

void setup(){
  //IR remote
  irrecv.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the IR receiver // Start the receiver
  Serial.println("REMOTE CONTROL START");

  int i = 0;
  for(i=1;i<=8;i++){
//pinModeで1から8ピンを出力に定義（面倒なのでforで8回繰り返し）
    pinMode(i,HIGH);
  }
}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    String key = decodeKeyValue(irrecv.decodedIRData.command);
    if (key != "ERROR") {
      Serial.println(key);

      if (key == "2") {
        LoopStop = false;
      } else if (key == "1") {
        LoopStop = true;
      }
    }

    irrecv.resume();  // Enable receiving of the next value
  }

  if (LoopStop) {
    int i = 0;
    for(i=0;i<11;i++){
      //0から9、DPを表示する
      SegPrint(i);
      delay(1000);
    }
  }


}

//数字を表示させる関数
void SegPrint(int num){
  int i = 0;
  for(i=1;i<=8;i++){
//各セグメントにHIGHかLOW(0か1)を出力
    digitalWrite(i-1,Seg_Array[num][i-1]);
   }
}