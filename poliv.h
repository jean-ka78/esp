long startsecondswd;            // день недели время начала в секундах
long stopsecondswd;             // день недели время остановки в секундах
long nowseconds;                // время в секундах


int manual = 0;                 // статус режима Ручной
int oldstatus;                  // статус последнего выбраного режима в Автоматическом режиме
int Morning;                    // статус Button V288886 режим Утро  (то есть учитывать TimeInput V288884)
int Evening;                    // статус Button V288887 режим Вечер (то есть учитывать TimeInput V288885)
int Morningstatus = 0;          // статус TimeInput Утро (на выходе функции 0 или 1) ON/OFF реле (нужно для функции resetRelay)
int Eveningstatus = 0;          // статус TimeInput Утро (на выходе функции 0 или 1) ON/OFF реле (нужно для функции resetRelay)
//#define relay 29 // Реле подключаем 

void activetoday() {       // проверяем, если график должен работать сегодня
  if (year() != 1970) {
    
    if (Morning == 1) {
      Blynk.syncVirtual(V24); // синхронизируем виджет timeinput 
    }
    if (Evening == 1) {
      Blynk.syncVirtual(V25); // синхронизируем виджет timeinput
    }
  }
}


 /* Здесь мы сохраняем в переменную oldstatus, порядковый номер, 
    включенного Автоматического состояния в последний раз */
void checklastbuttonpressed () {
  if ((Morning == 1) && (Evening == 0)) {
    oldstatus = 1;
  }
  if ((Morning == 0) && (Evening == 1)) {
    oldstatus = 2;
  }
  if ((Morning == 1) && (Evening == 1)) {
    oldstatus = 3;
  }
  if ((Morning == 0) && (Evening == 0)) {
    oldstatus = 4;
  }
}

/* Здесь мы соответственно возращаем включенное Автоматическое 
   состояние используя значение сохраненное в переменной oldstatus*/
void restorelastbuttonpressed () {
  if (oldstatus == 1) {
    Morning = 1;
    Blynk.virtualWrite(V26, 1);
  }
  if (oldstatus == 2) {     
    Evening = 1 ;
    Blynk.virtualWrite(V27, 1);
  }
  if (oldstatus == 3) {
    Evening = 1;
    Morning = 1;
    Blynk.virtualWrite(V26, 1);
    Blynk.virtualWrite(V27, 1);
  }
  if (oldstatus == 4) {
    Morning = 0;
    Evening = 0;
    Blynk.virtualWrite(V26, 0);
    Blynk.virtualWrite(V27, 0);
  }
}

BLYNK_WRITE(V29)  // Manual/Auto selection
{
  if (param.asInt() == 1) {
    manual = 1;             // Ручной режим включить

    checklastbuttonpressed ();

    Morning = 0;
    Evening = 0;
    Blynk.virtualWrite(V26, 0);
    Blynk.virtualWrite(V27, 0);

  } else {
    restorelastbuttonpressed ();
    manual = 0;           // Ручной режим выключить, включить автоматический режим
  }
}

/*
 * Эту функцию мы вызываем когда включаем один из таймеров
 * Переключаем кнопку Auto/Manual в режим Auto
 * Переключаем кнопку On/Off в режим Auto
 * Выключаем реле
 */
void resetManual()
{
  Blynk.virtualWrite(V29, 0);   //Отключить ручной режим
  Blynk.virtualWrite(V28, 0);   //Выключить устройство
  manual = 0;
  relay = LOW; // Off реле
}

/*
  Здесь мы проверяем в каком режиме находится система, в момент нажатия кнопки ON - OFF,
  в Автоматическом или Ручном режиме.
  И автоматически переводим в ручной режим и запоминаем состаяние Автоматического режима.
  Или просто включаем и выключаем выходное устройство
*/
BLYNK_WRITE(V28)  // ON-OFF Manual
{
  if (param.asInt() == 1) { // кнопка изменила состояние на 1

    if (manual == 0) { //Система была в Автоматическом режиме
      checklastbuttonpressed ();
      manual = 1;
      Morning = 0;
      Evening = 0;
      Blynk.virtualWrite(V29, 1);
      Blynk.virtualWrite(V26, 0);
      Blynk.virtualWrite(V27, 0);
      relay = HIGH; // ON реле
      Blynk.virtualWrite(V28, 1);   //Включение кнопки виджета Ручное управление

    } else {             //Система была в Ручном режиме
      Morning = 0;
      Evening = 0;
      Blynk.virtualWrite(V29, 1);
      Blynk.virtualWrite(V26, 0);
      Blynk.virtualWrite(V27, 0);
      relay = HIGH; // ON реле
      Blynk.virtualWrite(V28, 1);   //Включение кнопки виджета Ручное управление
    }
  } else { // кнопка изменила состояние на 0

    if (manual == 0) {  //Система была в Автоматическом режиме
      checklastbuttonpressed ();
      manual = 1;
      Morning = 0;
      Evening = 0;
      Blynk.virtualWrite(V29, 1);
      Blynk.virtualWrite(V26, 0);
      Blynk.virtualWrite(V27, 0);
      relay = LOW; // OFF реле
      Blynk.virtualWrite(V28, 0);   //Выключение кнопки виджета Ручное управление

    } else {            //Система была в Ручном режиме
      Morning = 0;
      Evening = 0;
      Blynk.virtualWrite(V29, 1);
      Blynk.virtualWrite(V26, 0);
      Blynk.virtualWrite(V27, 0);
      relay = LOW; // OFF реле
      Blynk.virtualWrite(V28, 0);   //Выключение кнопки виджета Ручное управление
    }
  }
}


BLYNK_WRITE(V24)//Morning Time Input
{
  if (Morning == 1) {
  
    TimeInputParam t(param);

    int dayadjustment = -1;
    if (weekday() == 1) {
      dayadjustment =  6; // Это нужно для определения воскресенья. Воскресенье в RTC это 1, а в Blynk 7
    }
    // В библиотеке RTC неделя начинается в воскресенье, а в Blynk в понедельник
    // Эта конструкция проверяет выбран ли сегодня день номер такой то
    if (t.isWeekdaySelected(weekday() + dayadjustment)) { 

      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
      //Serial.println(startsecondswd);  // used for debugging
      if (nowseconds >= startsecondswd) {

        if (nowseconds <= startsecondswd + 90) {  //код для того что бы точно отправить сигнал на реле (90s on 60s timer ensures 1 trigger command is sent)
          Morningstatus = 1; // код что бы переключить реле в ON          
        }
      }

      stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
      //Serial.println(stopsecondswd);  // used for debugging
      if (nowseconds >= stopsecondswd) {
        Morningstatus = 0; // OFF реле        

        if (nowseconds <= stopsecondswd + 90) { //код для того что бы точно отправить сигнал на реле (90s on 60s timer ensures 1 trigger command is sent)
          Morningstatus = 0; // код что бы переключить реле в OFF
        }
      }
      else {
        if (nowseconds >= startsecondswd) {
          Morningstatus = 1; // ON реле          
        }
      }
    } else {Morningstatus = 0;}
  } else {Morningstatus = 0;}
}

BLYNK_WRITE(V25)//Evening Time Input
{
  if (Evening == 1) {
   
    TimeInputParam t(param);

    int dayadjustment = -1;
    if (weekday() == 1) {
      dayadjustment =  6; // Это нужно для определения воскресенья. Воскресенье в RTC это 1, а в Blynk 7
    }
     // В библиотеке RTC неделя начинается в воскресенье, а в Blynk в понедельник
    // Эта конструкция проверяет выбран ли сегодня день номер такой то
    if (t.isWeekdaySelected(weekday() + dayadjustment)) { 

      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
      //Serial.println(startsecondswd);  // used for debugging
      if (nowseconds >= startsecondswd) {

        if (nowseconds <= startsecondswd + 90) {  //код для того что бы точно отправить сигнал на реле (90s on 60s timer ensures 1 trigger command is sent)
          Eveningstatus = 1; // код что бы переключить реле в ON
        }
      }

      stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
      //Serial.println(stopsecondswd);  // used for debugging
      if (nowseconds >= stopsecondswd) {
        Eveningstatus = 0; // OFF реле        

        if (nowseconds <= stopsecondswd + 90) { //код для того что бы точно отправить сигнал на реле (90s on 60s timer ensures 1 trigger command is sent)
          Eveningstatus = 0; // код что бы переключить реле в OFF
        }
      }
      else {
        if (nowseconds >= startsecondswd) {
          Eveningstatus = 1; // ON реле          
        }
      }
    } else {Eveningstatus = 0;}
  } else {Eveningstatus = 0;}
}



BLYNK_WRITE(V26)  // Утро выбрано Button Morning selected
{
  if (param.asInt() == 1) { //&& (V29 == 1)
    timer.setTimeout(50, resetManual);    
    timer.setTimeout(50, checklastbuttonpressed);
    Morning = 1;
  } else {    
    Morning = 0;
    // синхронизируемся с виджетом, благодаря этому
    // обнавляется информация что на выходе Morning Time Input
    Blynk.syncVirtual(V24); 
  }
}


BLYNK_WRITE(V27)  // Вечер выбран Button Evening selected
{
  if (param.asInt() == 1) { //&& V29 == 1
    timer.setTimeout(50, resetManual);
    timer.setTimeout(50, checklastbuttonpressed);
    Evening = 1;
  } else {      
    Evening = 0;
    // синхронизируемся с виджетом, благодаря этому
    // обнавляется информация что на выходе Evening Time Input
    Blynk.syncVirtual(V25); 
  }
}
void resetRelay()
{     
  if (Blynk.connected()){ // проверяем есть ли связь с сервером если есть, то работаем если нет то отключаем реле
    if (manual == 0) // проверяем включен ли Автоматический режим
      {
        if (Evening == 1 || Morning == 1) // проверяем активен или нет хоть один таймер        
        {
              // проверяем что на выходе Morning или Evening Time Input
              if    (Morningstatus == 1 || Eveningstatus == 1){ 
                    // код что бы переключить реле в ON
                    relay = HIGH; // ON реле
                    new_rellay_poliv = 1;
                   // Blynk.notify("Полив включен");
                    Blynk.virtualWrite(V28, 1); // Button ON в приложении (обратная связь)
         }    else  {// код что бы переключить реле в OFF
                    relay = LOW; // OFF реле
                    new_rellay_poliv = 0;
                   // Blynk.notify("Полив выключен");
                    Blynk.virtualWrite(V28, 0); } //Button OFF в приложении (обратная связь)     
        } else {// код что бы переключить реле в OFF
          relay = LOW; // OFF реле
          new_rellay_poliv = 0;
        //  Blynk.notify("Полив выключен");
          Blynk.virtualWrite(V28, 0); } //Button OFF в приложении (обратная связь)
      }
  } else {// код что бы переключить реле в OFF
          relay = LOW; // OFF реле
          new_rellay_poliv = 0;
       //   Blynk.notify("Полив выключен");
          Blynk.virtualWrite(V28, 0); } //Button OFF в приложении (обратная связь)       
 
 if (relay != relay_poliv)
  {
   relay_poliv=relay;
  DATA_Send();
   terminal.println("Полив:"+ String(relay));
   terminal.flush(); 
  }

}
