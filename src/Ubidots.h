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
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"

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
#define VERSION "2.1.13"
#endif
#ifndef PORT
#define PORT 9012
#endif
#ifndef MAX_VALUES
#define MAX_VALUES 10
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

typedef struct Value {
    char  *idName;
    char  *contextOne;
    float idValue;
    unsigned long timestamp_val;
} Value;

class Ubidots {
 public:
    explicit Ubidots(const char* token);
    explicit Ubidots(const char* token, const char* server); // Deprecate
    explicit Ubidots(const char* token, uint8_t serverMode);
    explicit Ubidots(const char* token, uint8_t serverMode, uint16_t serverPort);
    void add(char *variable_id, double value);
    void add(char *variable_id, double value, char *ctext);
    void add(char *variable_id, double value, char *ctext, unsigned long timestamp);
    float getValue(char* id);
    float getValueWithDatasource(char* device, char* variable);
    float getValueHTTP(char* id);
    char* getVarContext(char* id);
    unsigned long now();
    unsigned long ntpUnixTime();
    bool sendAll();
    bool sendAll(unsigned long timestamp_global);
    void setDeviceName(char* deviceName);
    void setDeviceLabel(char* deviceLabel);
    bool setDatasourceName(char* dsName); //Deprecated
    bool setDatasourceTag(char* dsTag); //Deprecated
    void setDebug(bool debug);
    void setMethod(uint8_t method); // Default UDP
    void setPort(uint16_t serverPort); // Default use specified or 0 (use default mode)
    void setServerMode(uint8_t serverMode); // Default HTTPS

 private:
    TCPClient _client;
    UDP _clientUDP;
    UDP _clientTMP;
    Value * val;
    uint8_t _currentValue;
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
