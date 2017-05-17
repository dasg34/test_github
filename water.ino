#define WATER A0
#define PIEZO 13
  
#define LDO 2093
#define MI 2637
#define SOL 3136
#define HDO 4186

#define RED 11
#define GREEN 10
#define BLUE 9

void led_3color_on(int red, int green, int blue, int color);
static int moisture_warning_count; 

static int
soil_moisture_get()
{
  //수분 센서로부터 받은 값을 리턴.
  int out = analogRead(WATER);
  Serial.println(out);
  return out;
}

int
enough_water_is()
{
  if (soil_moisture_get() < 200 )
     return 0;
   else
     return 1;
  //수분 센서의 측정값이 일정수준 아래로 떨어지면 0, 아니면 1 리턴.
}

void
dry_warn(int tone_val)
{
  //부저 소리 발생.
  tone(PIEZO, tone_val, 500);
}

void 
water_check()
{
  if (enough_water_is() == 0 )
     moisture_warning_count++;
   else
     moisture_warning_count = 0;

  if (moisture_warning_count >= 10 )

  {
     if ((moisture_warning_count - 10) % 6 == 0)
     { 
      dry_warn(HDO);
      led_3color_on(RED, GREEN, BLUE, RED_COLOR);
     }
  }
  else if (moisture_warning_count >= 7 )
  {
     dry_warn(SOL);
     led_3color_on(RED, GREEN, BLUE, YELLOW_COLOR);
  }
  else if (moisture_warning_count >= 5 )
  {
     dry_warn(MI);
     led_3color_on(RED, GREEN, BLUE, YELLOW_COLOR);
  }
  else if (moisture_warning_count >= 3 )
  {
     dry_warn(LDO);
     led_3color_on(RED, GREEN, BLUE, GREEN_COLOR);
  }
  //비정상이면 카운트 플러스, 일정카운트 이상 쌓이면 0.
  //수준 이상이 되면 카운트 초기화.
}

void
water_setup()
{
  pinMode(WATER, INPUT);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

