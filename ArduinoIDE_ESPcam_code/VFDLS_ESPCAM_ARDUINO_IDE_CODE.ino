#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
#include "FS.h"
#include "SD_MMC.h"
#include "EEPROM.h"

const char* ssid = "Hazem_Vehicle_System";
const char* password = "1234567890";

WebServer server(80);

// متغيرات القراءات اللايف
String live_temp = "--";
String live_dist = "SAFE";
String live_w1 = "--";
String live_w2 = "--";
int pictureCount = 0;

// بنّات الكاميرا (AI-Thinker)
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

String getHTML() {
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial; text-align:center; background:#f4f4f4;} .card{background:white; padding:20px; margin:20px; border-radius:10px; box-shadow:0 4px 8px 0 rgba(0,0,0,0.2);}";
  html += ".btn{background:#4CAF50; color:white; padding:15px 25px; border:none; border-radius:5px; cursor:pointer; font-size:18px; font-weight:bold; margin:5px;} .btn:active{background:#3e8e41;}</style>";
  
  html += "<script>";
  html += "setInterval(function() {";
  html += "  fetch('/data').then(response => response.json()).then(data => {";
  html += "    document.getElementById('temp').innerText = data.t;";
  html += "    document.getElementById('dist').innerText = data.d;";
  html += "    document.getElementById('w1').innerText = data.w1;";
  html += "    document.getElementById('w2').innerText = data.w2;";
  html += "  });";
  html += "}, 1000);"; 
  html += "</script>";
  
  html += "</head><body><h1>Vehicle IoT Dashboard</h1>";
  html += "<div class='card'><h2>Live Sensors Data</h2>";
  html += "<p>Temperature: <b><span id='temp'>" + live_temp + "</span> &deg;C</b></p>";
  html += "<p>Distance: <b><span id='dist'>" + live_dist + "</span></b></p>";
  html += "<p>Window 1: <b><span id='w1'>" + live_w1 + "</span></b></p>";
  html += "<p>Window 2: <b><span id='w2'>" + live_w2 + "</span></b></p>";
  html += "</div>";

  html += "<div class='card'><h2>Control Panel</h2>";
  html += "<button class='btn' onclick=\"fetch('/start')\">START SYSTEM</button> ";
  html += "<button class='btn' style='background:#f44336;' onclick=\"fetch('/stop')\">STOP SYSTEM</button>";
  html += "</div>";

  html += "<div class='card'><h2>Last Accident Log</h2><p>Saved on SD as: /accident_X.jpg</p></div>";
  html += "</body></html>";
  return html;
}

void takePhoto() {
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) return;
  
  pictureCount = EEPROM.read(0) + 1;
  if(pictureCount > 250 || pictureCount == 0) pictureCount = 1;
  
  String path = "/accident_" + String(pictureCount) + ".jpg";
  fs::FS &fs = SD_MMC; 
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(file){
    file.write(fb->buf, fb->len);
    EEPROM.write(0, pictureCount); 
    EEPROM.commit();
  }
  file.close();
  esp_camera_fb_return(fb); 
}

void setup() {
  Serial.begin(9600); // سرعة موحدة مع Tiva C
  EEPROM.begin(512);
  WiFi.softAP(ssid, password);
  SD_MMC.begin();
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0; config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM; config.pin_d1 = Y3_GPIO_NUM; config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM; config.pin_d4 = Y6_GPIO_NUM; config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM; config.pin_d7 = Y9_GPIO_NUM; config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM; config.pin_vsync = VSYNC_GPIO_NUM; config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM; config.pin_sccb_scl = SIOC_GPIO_NUM; config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM; config.xclk_freq_hz = 20000000; config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA; config.jpeg_quality = 10; config.fb_count = 1;
  esp_camera_init(&config);
  
  sensor_t * s = esp_camera_sensor_get();
  s->set_vflip(s, 1); s->set_hmirror(s, 1);

  server.on("/", []() { server.send(200, "text/html", getHTML()); });
  
  server.on("/data", []() {
    String json = "{\"t\":\"" + live_temp + "\",\"d\":\"" + live_dist + "\",\"w1\":\"" + live_w1 + "\",\"w2\":\"" + live_w2 + "\"}";
    server.send(200, "application/json", json);
  });

  server.on("/start", []() { Serial.print('1'); server.send(200, "text/plain", "OK"); });
  server.on("/stop", []() { Serial.print('3'); server.send(200, "text/plain", "OK"); });

  server.begin();
}

void loop() {
  server.handleClient();

  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil('\n');
    msg.trim(); 
    
    if(msg.startsWith("T:")) live_temp = msg.substring(2);
    else if(msg.startsWith("D:")) live_dist = msg.substring(2) + " cm";
    else if(msg.startsWith("S:")) live_dist = "SAFE";
    else if(msg.startsWith("W1:")) live_w1 = msg.substring(3);
    else if(msg.startsWith("W2:")) live_w2 = msg.substring(3);
    else if(msg == "ALERT:P001") takePhoto(); // 🚨 تم التعديل لتطابق الـ Tiva C
  }
}