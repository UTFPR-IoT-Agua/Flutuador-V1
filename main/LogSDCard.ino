// Initialize SD card

void setupSD(){

  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    DEBUG_PORT.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    DEBUG_PORT.println("No SD card attached");
    return;
  }
  DEBUG_PORT.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    DEBUG_PORT.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }

  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if(!file) {
    DEBUG_PORT.println("File doens't exist");
    DEBUG_PORT.println("Creating file...");
    String dataMessage;
    dataMessage = "Reading ID,";
  
    #ifdef PH_DEF 
      dataMessage += " pH,"; 
    #endif
    #ifdef ORP_DEF 
      dataMessage += " ROP,"; 
    #endif
    #ifdef DO_DEF 
      dataMessage += " DO,"; 
    #endif
    #ifdef CONDUCTIVITY_DEF 
      dataMessage += "Conductivity,"; 
    #endif
    #ifdef TURBIDITY_DEF 
      dataMessage += "Turbidity,"; 
    #endif
    #ifdef TEMPERATURE_DEF 
      dataMessage += "Temperature,"; 
    #endif
    #ifdef FLOW_DEF 
      dataMessage += "Flow,"; 
    #endif
    
    dataMessage += "\r\n";
           
    writeFile(SD, "/data.txt", dataMessage.c_str());
  }
  else {
    DEBUG_PORT.println("File already exists");  
  }
  file.close();
}



// Write the sensor readings on the SD card
void logSDCard(sensors *param) {
  String dataMessage;
 // dataMessage = String(readingID) + "," + String(dayStamp) + "," + String(timeStamp) + "," + 
  //              String(temperature) + "\r\n";



  
  dataMessage = String(millis()) + ",";
  
  #ifdef PH_DEF 
    dataMessage += String((*param).ph) + ","; 
  #endif
  #ifdef ORP_DEF 
    dataMessage += String((*param).orp) + ","; 
  #endif
  #ifdef DISS_OXY_DEF 
    dataMessage += String((*param).dissolvedOxygen) + ","; 
  #endif
  #ifdef CONDUCTIVITY_DEF 
    dataMessage += String((*param).conductivity) + ","; 
  #endif
  #ifdef TURBIDITY_DEF 
    dataMessage += String((*param).turbidity) + ","; 
  #endif
  #ifdef TEMPERATURE_DEF 
    dataMessage += String((*param).temperature) + ","; 
  #endif
  #ifdef FLOW_DEF 
    dataMessage += String((*param).flow) + ","; 
  #endif
  
  dataMessage += "\r\n";
           
  DEBUG_PORT.print("Save data: ");
  DEBUG_PORT.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}

// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  DEBUG_PORT.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    DEBUG_PORT.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    DEBUG_PORT.println("File written");
  } else {
    DEBUG_PORT.println("Write failed");
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  DEBUG_PORT.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    DEBUG_PORT.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    DEBUG_PORT.println("Message appended");
  } else {
    DEBUG_PORT.println("Append failed");
  }
  file.close();
}
