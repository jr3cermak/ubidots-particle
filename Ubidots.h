#ifndef __Ubidots_H_
#define __Ubidots_H_
#define DEBUG_UBIDOTS

#include "application.h"
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"
#include <stdarg.h>

#define USER_AGENT  "Ubidots/v1 Particle/1.0"
#define BASE_URL  "things.ubidots.com"
#define ATTEMPS  6

typedef struct UbidotsCollection {
  int n;
  int i;
  char  **variable_ids;
  float *values;
  char  *_ids;
} UbidotsCollection;

class ubidots {
    private:
        void assemble(char* chain, char* method, char* endpoint);
        void assemble_with_data(char* chain, char* method, char* endpoint, char* data);

    public:
        ubidots(char* token);
        char* get_or_create_datasource();
        char* get_or_create_variable(char* ID, char* variableName);
        bool send(char* chain, char* status, char* body);
        char* parser_id(char* status, char* body);
        bool send_with_reconect(char* chain, char* status, char* body);
        
        UbidotsCollection* ubidots_collection_init(int n);
        void ubidots_collection_add(UbidotsCollection *coll, char *name, double value);
        int ubidots_collection_save(UbidotsCollection *coll);
        void ubidots_collection_cleanup(UbidotsCollection *coll);
        
        bool send_ubidots(int number, ... );
        
        char* _token;   
};
#endif
