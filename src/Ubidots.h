/*
Copyright (c) 2013-2017 Ubidots.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Original maker Mateo Velez - Metavix for Ubidots Inc
Modified by Jose Garcia for Ubidots Inc
Modified by Rob Cermak <rob.cermak@gmail.com>

*/

#ifndef _Ubidots_H_
#define _Ubidots_H_
#endif

#include "application.h"
#include <JsonStreamingParser.h>
#include <TlsTcpClient.h>
//#include "spark_wiring_string.h"
//#include "spark_wiring_tcpclient.h"
//#include "spark_wiring_usbserial.h"

//
// This example connect to the Let's Encrypt HTTPS server.
// Let's Encrypt ROOT Ca PEM file is here ( https://letsencrypt.org/certificates/ )
// If you want to use other Root CA, check your server administrator or own Root CA pem.
//
#define LET_ENCRYPT_CA_PEM                                              \
"-----BEGIN CERTIFICATE----- \r\n"                                      \
"MIIFjTCCA3WgAwIBAgIRANOxciY0IzLc9AUoUSrsnGowDQYJKoZIhvcNAQELBQAw\r\n"  \
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\r\n"  \
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTYxMDA2MTU0MzU1\r\n"  \
"WhcNMjExMDA2MTU0MzU1WjBKMQswCQYDVQQGEwJVUzEWMBQGA1UEChMNTGV0J3Mg\r\n"  \
"RW5jcnlwdDEjMCEGA1UEAxMaTGV0J3MgRW5jcnlwdCBBdXRob3JpdHkgWDMwggEi\r\n"  \
"MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCc0wzwWuUuR7dyXTeDs2hjMOrX\r\n"  \
"NSYZJeG9vjXxcJIvt7hLQQWrqZ41CFjssSrEaIcLo+N15Obzp2JxunmBYB/XkZqf\r\n"  \
"89B4Z3HIaQ6Vkc/+5pnpYDxIzH7KTXcSJJ1HG1rrueweNwAcnKx7pwXqzkrrvUHl\r\n"  \
"Npi5y/1tPJZo3yMqQpAMhnRnyH+lmrhSYRQTP2XpgofL2/oOVvaGifOFP5eGr7Dc\r\n"  \
"Gu9rDZUWfcQroGWymQQ2dYBrrErzG5BJeC+ilk8qICUpBMZ0wNAxzY8xOJUWuqgz\r\n"  \
"uEPxsR/DMH+ieTETPS02+OP88jNquTkxxa/EjQ0dZBYzqvqEKbbUC8DYfcOTAgMB\r\n"  \
"AAGjggFnMIIBYzAOBgNVHQ8BAf8EBAMCAYYwEgYDVR0TAQH/BAgwBgEB/wIBADBU\r\n"  \
"BgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEEAYLfEwEBATAwMC4GCCsGAQUFBwIB\r\n"  \
"FiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2VuY3J5cHQub3JnMB0GA1UdDgQWBBSo\r\n"  \
"SmpjBH3duubRObemRWXv86jsoTAzBgNVHR8ELDAqMCigJqAkhiJodHRwOi8vY3Js\r\n"  \
"LnJvb3QteDEubGV0c2VuY3J5cHQub3JnMHIGCCsGAQUFBwEBBGYwZDAwBggrBgEF\r\n"  \
"BQcwAYYkaHR0cDovL29jc3Aucm9vdC14MS5sZXRzZW5jcnlwdC5vcmcvMDAGCCsG\r\n"  \
"AQUFBzAChiRodHRwOi8vY2VydC5yb290LXgxLmxldHNlbmNyeXB0Lm9yZy8wHwYD\r\n"  \
"VR0jBBgwFoAUebRZ5nu25eQBc4AIiMgaWPbpm24wDQYJKoZIhvcNAQELBQADggIB\r\n"  \
"ABnPdSA0LTqmRf/Q1eaM2jLonG4bQdEnqOJQ8nCqxOeTRrToEKtwT++36gTSlBGx\r\n"  \
"A/5dut82jJQ2jxN8RI8L9QFXrWi4xXnA2EqA10yjHiR6H9cj6MFiOnb5In1eWsRM\r\n"  \
"UM2v3e9tNsCAgBukPHAg1lQh07rvFKm/Bz9BCjaxorALINUfZ9DD64j2igLIxle2\r\n"  \
"DPxW8dI/F2loHMjXZjqG8RkqZUdoxtID5+90FgsGIfkMpqgRS05f4zPbCEHqCXl1\r\n"  \
"eO5HyELTgcVlLXXQDgAWnRzut1hFJeczY1tjQQno6f6s+nMydLN26WuU4s3UYvOu\r\n"  \
"OsUxRlJu7TSRHqDC3lSE5XggVkzdaPkuKGQbGpny+01/47hfXXNB7HntWNZ6N2Vw\r\n"  \
"p7G6OfY+YQrZwIaQmhrIqJZuigsrbe3W+gdn5ykE9+Ky0VgVUsfxo52mwFYs1JKY\r\n"  \
"2PGDuWx8M6DlS6qQkvHaRUo0FMd8TsSlbF0/v965qGFKhSDeQoMpYnwcmQilRh/0\r\n"  \
"ayLThlHLN81gSkJjVrPI0Y8xCVPB4twb1PFUd2fPM3sA1tJ83sZ5v8vgFv2yofKR\r\n"  \
"PB0t6JzUA81mSqM3kxl5e+IZwhYAyO0OTg3/fs8HqGTNKd9BqoUwSRBzp06JMg5b\r\n"  \
"rUCGwbCUDI0mxadJ3Bz4WxR6fyNpBK2yAinWEsikxqEt\r\n"  \
"-----END CERTIFICATE----- "
const char letencryptCaPem[] = LET_ENCRYPT_CA_PEM;

#ifndef SERVER
#define SERVER "translate.ubidots.com"
#endif
#ifndef TIME_SERVER
#define TIME_SERVER "pool.ntp.org"
#endif
#ifndef USER_AGENT
#define USER_AGENT "Particle"
#endif
#ifndef VERSION
#define VERSION "3.0.0"
#endif
#ifndef PORT
#define PORT 9012
#endif
#ifndef MAX_VALUES
#define MAX_VALUES 10
#endif
#ifndef MAX_DEVICES
#define MAX_DEVICES 10
#endif
#ifndef TYPE_TCP
#define TYPE_TCP 1
#endif
#ifndef TYPE_UDP
#define TYPE_UDP 2
#endif
#ifndef TIMEOUT
#define TIMEOUT 10000
#endif
#ifndef SERVERNAME
#define SERVERNAME "things.ubidots.com"
#endif
#ifndef SERVERHTTP
#define SERVERHTTP "things.ubidots.com"
#endif
#ifndef SERVERTYPE
#define SERVERTYPE "api"
#endif
#ifndef SERVERVERSION
#define SERVERVERSION "v1.6"
#endif
#ifndef PORTHTTP
#define PORTHTTP 80
#endif
#ifndef PORTHTTPS
#define PORTHTTPS 443
#endif
#ifndef MODE_HTTP
#define MODE_HTTP 1
#endif
#ifndef MODE_HTTPS
#define MODE_HTTPS 2
#endif

const float ERROR_VALUE = -3.4028235E+8;

// Define a data point (a Ubidot)
typedef struct Value {
    char  *idName;
    char  *contextOne;
    float idValue;
    unsigned long timestamp_val;
} Value;

// Define a device 
typedef struct Device {
  char *label;
  char *description;
  char *context;
  int numVars;
  char *id;
} Device;

class Ubidots {
 public:
    explicit Ubidots(const char* token);
    explicit Ubidots(const char* token, const char* server); // Deprecate
    explicit Ubidots(const char* token, uint8_t serverMode);
    explicit Ubidots(const char* token, uint8_t serverMode, uint16_t serverPort);
    void add(char *variable_id, double value);
    void add(char *variable_id, double value, char *ctext);
    void add(char *variable_id, double value, char *ctext, unsigned long timestamp);
    bool getDevices();
    float getValue(char* id);
    float getValueWithDatasource(char* device, char* variable);
    float getValueHTTP(char* id);
    char* getVarContext(char* id);
    unsigned long now();
    unsigned long ntpUnixTime();
    int numDevices();
    bool queryServer(char *query);
    bool sendAll();
    bool sendAll(unsigned long timestamp_global);
    void setDeviceName(char* deviceName);
    void setDeviceLabel(char* deviceLabel);
    bool setDatasourceName(char* dsName); //Deprecated
    bool setDatasourceTag(char* dsTag); //Deprecated
    void setDebug(bool debug);
    void setMethod(uint8_t method); // Default UDP
    void setParser(JsonStreamingParser* parser);
    void setPort(uint16_t serverPort); // Default use specified or 0 (use default mode)
    void setServerMode(uint8_t serverMode); // Default HTTPS

 private:
    // Define value array
    Value * val;
    uint8_t _currentValue;
    // Define device array
    Device * devices;
    uint8_t _currentDevice;

    JsonStreamingParser* _parser;
    TCPClient _client;
    TlsTcpClient _tlsclient;
    UDP _clientUDP;
    UDP _clientTMP;
    const char* _dsName;
    bool _debug = false;
    uint8_t _method;
    uint8_t _serverMode;
    char* _pId;
    const char* _server;
    const char* _token;
    uint16_t _port;
    bool sendAllUDP(char* buffer);
    bool sendAllTCP(char* buffer);
    void init(const char* token, uint8_t serverMode, uint16_t serverPort);
};
