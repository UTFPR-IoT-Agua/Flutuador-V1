void setupSensors() 
{
  #ifdef PH_DEF   
    #if PH_DEF == 1
      if (gravityPH.begin()) {     
        DEBUG_PORT.println(F(" - For pH, use commands \"PH,CAL,7\", \"PH,CAL,4\", and \"PH,CAL,10\" to calibrate the circuit to those respective values"));
        DEBUG_PORT.println(F("   Use command \"PH,CAL,CLEAR\" to clear the calibration"));                           
        DEBUG_PORT.println("Loaded pH EEPROM");
      }
    #endif
  #endif

  #ifdef ORP_DEF
    #if ORP_DEF == 1
      if(gravityORP.begin()){
        DEBUG_PORT.println(F(" - For ORP, use command \"ORP,CAL,xxx\" to calibrate the circuit to the value xxx \n   \"ORP,CAL,CLEAR\" clears the calibration"));
        DEBUG_PORT.println("Loaded ORP EEPROM");
      }
    #endif
  #endif

  #ifdef DO_DEF
    #if DO_DEF == 1
      if(gravityDO.begin()){
        DEBUG_PORT.println(F(" - For DO, use command \"CAL\" to calibrate the circuit to 100% saturation in air\n   \"DO,CAL,CLEAR\" clears the calibration"));
        DEBUG_PORT.println("Loaded DO EEPROM");
      }
    #endif
  #endif

}

void parse_cmd(char* string) {
  strupr(string);
  String cmd = String(string);

#ifdef PH_DEF   
  #if ORP_DEF == 1
    if(cmd.startsWith("ORP,CAL")){
      int index = cmd.indexOf(',');
      if(index != -1){
        String param = cmd.substring(index+1, cmd.length());
        int index = param.indexOf(',');
        if(index != -1){
          String param2 = param.substring(index+1, param.length());
          if(param2.equals("CLEAR")){
            gravityORP.cal_clear();
            Serial.println("CALIBRATION CLEARED");
          }
          else{
            int cal_param = param2.toInt();
            gravityORP.cal(cal_param);
            Serial.println("ORP CALIBRATED");
          }
        }
      }
    }
  #endif
#endif


#ifdef PH_DEF
  #if PH_DEF == 1
    
    if (strcmp(string, "PH,CAL,7") == 0) {       
      gravityPH.cal_mid();                                
      Serial.println("MID CALIBRATED");
    }
    else if (strcmp(string, "PH,CAL,4") == 0) {            
      gravityPH.cal_low();                                
      Serial.println("LOW CALIBRATED");
    }
    else if (strcmp(string, "PH,CAL,10") == 0) {      
      gravityPH.cal_high();                               
      Serial.println("HIGH CALIBRATED");
    }
    else if (strcmp(string, "PH,CAL,CLEAR") == 0) { 
      gravityPH.cal_clear();                              
      Serial.println("CALIBRATION CLEARED");
    }
  
  #endif
#endif

#ifdef DO_DEF
  #if DO_DEF == 1
    
    if(cmd.startsWith("DO,CAL,CLEAR")){
      gravityDO.cal_clear();
      Serial.println("CALIBRATION CLEARED");
    }
    else if(cmd.startsWith("DO,CAL")){
      gravityDO.cal();
      Serial.println("DO CALIBRATED");
    
    }
  #endif
#endif
}



float getPH(){
  float value = 0;

  #ifdef PH_DEF
    #if PH_DEF == 1
      value = gravityPH.read_ph();
    #endif
  #endif

  return value;
}

float getORP(){
  float value = 0;
  #ifdef ORP_DEF
    #if ORP_DEF == 1
        value = gravityORP.read_orp();
    #endif
  #endif
  
  return value;
}


float getDO(){
  float value = 0;
  #ifdef DO_DEF
    #if DO_DEF == 1
        value = gravityDO.read_do_percentage();
    #endif
  #endif

  return value;
}


float getConductivity(){
  float value = 0;

  #ifdef CONDUCTIVITY_DEF 
    #if CONDUCTIVITY_DEF == 1
      value = 1;
    #endif
  #endif

  return value;
}


float getTurbidity(){
  float value = 0;

  #ifdef TURBIDITY_DEF 
    #if TURBIDITY_DEF == 1
      value = 1;
    #endif
  #endif

  return value;
}


float getTemperature(){
  float value = 0;

  #ifdef TEMPERATURE_DEF 
    #if TEMPERATURE_DEF == 1
      value = 1;
    #endif
  #endif

  return value;
}


float getFlow(){
  float value = 0;

  #ifdef FLOW_DEF 
    #if FLOW_DEF == 1
      value = 1;
    #endif
  #endif

  return value;
}




void updateSensors(){
  sensors param;

  #ifdef PH_DEF 
    param.ph = getPH(); 
  #endif
  
  #ifdef ORP_DEF 
    param.orp = getORP();  
  #endif
  
  #ifdef DO_DEF 
    param.dissolvedOxygen = getDO();  
  #endif
  
  #ifdef CONDUCTIVITY_DEF 
    param.conductivity = getConductivity();  
  #endif
  
  #ifdef TURBIDITY_DEF 
    param.turbidity = getTurbidity();
  #endif
  
  #ifdef TEMPERATURE_DEF 
    param.temperature = getTemperature();  
  #endif
  
  #ifdef FLOW_DEF 
    param.flow = getFlow();  
  #endif 

  logSDCard(&param);
}
