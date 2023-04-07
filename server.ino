#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// variable to store all the HTML code (HTML, JS, CSS)

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style type="text/css">
    :root {
  --success: #00b894;
  --progress: #e17055;
}

html {
  box-sizing: border-box;
}
*, *:before, *:after {
  box-sizing: inherit;
}

h1 {
  text-transform: uppercase;
  letter-spacing: 1.1px;
}

.container {
  max-width: 720px;
  margin: 0px auto;
  width: 100%;
}

.text-center { text-align:center; }

.progressbar-wrapper {
  background-color: #dfe6e9;
  color: white;
  border-radius: 15px;
  width: 100%;
}

.progressbar {
  background-color: var(--progress);
  color: white;
  padding: 1rem;
  text-align: right;
  font-size: 20px;
  border-radius: 15px;
}


.progressbar[title="speed"] {
   background-color: var(--success);
}
  
.speed {
  width: 0%;
}


.buttonOn {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.buttonOff {
  background-color: #dd1c1c; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.buttonToggle {
  background-color: #ff6a00;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.button5P {
  background-color: #ff6a00;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.buttonM5P {
  background-color: #ff6a00;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.button100P {
  background-color: #ff6a00;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.button0P {
  background-color: #ff6a00;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
.showPercent{
  background-color: #30982c;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}


datalist {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  writing-mode: vertical-lr;
  width: 520px;
}

option {
  padding: 0;
}

input[type="range"] {
  width: 520px;
  height: 50px;
  margin: 10;
  text-align: center;
}


</style>
<body style="background-color: #87CEFA">
<center>
<div>
<h1>AJAX Based ESP8266 WebServer</h1>
  <button class ="button0P" onclick="sendP(0)">0%</button>
  <button class ="buttonM5P" onclick="sendP(1)">-5%</button>
  <span id="perc_val" class="showPercent">0%</span>
  <button class ="button5P" onclick="sendP(2)">+5%</button>
  <button class ="button100P" onclick="sendP(3)">100%</button><br>
  <input id= "perc_val_slider" class="Slider" type="range" min="0" max="100" value="0" step="1" list="values" onchange=sendP_slider(this.value)></input>
  <datalist id="values">
    <option value="0" label="0%"></option>
    <option value="25" label="25%"></option>
    <option value="50" label="50%"></option>
    <option value="75" label="75%"></option>
    <option value="100" label="100%"></option>
  </datalist>
</div>
 <br>
<div><h2>
</center>

    <div class="container">
        <p>Current Speed : </p>
        <div class="progressbar-wrapper">
         <div title="speed" class="progressbar speed">1090Tr/min</div>
        </div>
   </div>


</h2>
</div>
<script>
function sendP_slider(percentage) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("perc_val_slider").value = this.responseText;
      document.getElementById("perc_val").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "PERCENT_SLIDER?percent="+percentage, true);
  xhttp.send();
}
function sendP(percentage) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("perc_val").innerHTML = this.responseText;
      document.getElementById("perc_val_slider").value = this.responseText;
    }
  };
  xhttp.open("GET", "PERCENT?percent="+percentage, true);
  xhttp.send();
}
function send(led_sts) 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "RELAY?state="+led_sts, true);
  xhttp.send();
}
setInterval(function() 
{
  getData();
}, 250); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        if (this.responseText != document.getElementById("perc_val").innerHTML)
        {
          document.getElementById("perc_val").innerHTML = this.responseText;
          document.getElementById("perc_val_slider").value = this.responseText;
        }
    }
  };
  xhttp.open("GET", "WPERCENT", true);
  xhttp.send();
}
setInterval(function() {
    getSpeed();
    }, 500);
function getSpeed() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.querySelector("body > div > div > div").style.width = `${(this.responseText * 100) / 4200}%`;
            document.querySelector("body > div > div > div").innerHTML = this.responseText + "Tr/min";
        }
    };
    xhttp.open("GET", "WSPEED", true);
    xhttp.send();
}

</script>
</body>
</html>
)=====";

#ifndef STASSID
#define STASSID "tp5&6"   // Network SSID
#define STAPSK "" // Network Password
#endif


const char *ssid = STASSID; // Network SSID
const char *password = STAPSK; // Network Password

const char *server = "http://192.168.0.230"
char *resource = "/relay/0"
const unsigned long HTTP_TIMEOUT = 10000; // Timeout for HTTP requests
const size_t MAX_CONTENT_SIZE = 512; // Maximum size of the file to download

ESP8266WebServer serverWeb(80); // PORT OF WEB SERVER


void handleRoot() // Function that handles the root page of the web server
{
    serverWeb.send(200, "text/html", webpage); // Send the webpage to the client --> constant containing all CSS, HTML and JS code
}

void handleNotFound() // Function that handles the error page of the web server (404)
{
    String message = "<html> Error not found </html>";
    serverWeb.send(404, "text/html", message);
}


bool connect(const char* hostName) {
  Serial.print("Connect to ");
  Serial.println(hostName);

  bool ok = client.connect(hostName, 80);

  Serial.println(ok ? "Connected" : "Connection Failed!");
  return ok;
}

bool sendRequest(const char* host, const char* resource) {
  Serial.print("GET ");
  Serial.println(resource);

  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();

  return true;
}

bool skipResponseHeaders() {
  // HTTP headers end with an empty line
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(HTTP_TIMEOUT);
  bool ok = client.find(endOfHeaders);

  if (!ok) {
    Serial.println("No response or invalid response!");
  }
  return ok;
}

bool readReponseContent(struct clientData* clientData) {
  // Compute optimal size of the JSON buffer according to what we need to parse.
  // See https://bblanchon.github.io/ArduinoJson/assistant/
  const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 
      2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 
      JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 390;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }

  // Here were copy the strings we're interested in using to your struct data
  strcpy(clientData->power, root["power"]);
  strcpy(clientData->voltage, root["voltage"]);
  // It's not mandatory to make a copy, you could just use the pointers
  // Since, they are pointing inside the "content" buffer, so you need to make
  // sure it's still in memory when you read the string

  return true;
}

void disconnect() {
  Serial.println("Disconnect");
  client.stop();
}


void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    serverWeb.on("/", handleRoot);
    serverWeb.onNotFound(handleNotFound);

    serverWeb.begin();
}


void loop() (
    serverWeb.handleClient();               // Handle WEB SERVER connections
    if (connect(server)) {
        if (sendRequest(server, resource) && skipResponseHeaders()) {
            clientData ClientData;
            if (readReponseContent(&clientData)) {
                Serial.print("Power: ");
                Serial.println(clientData.power);
                Serial.print("voltage: ");
                Serial.println(clientData.voltage);
            }
        }
    }

)