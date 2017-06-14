# Changes since 2.1.13

# 2017-06-13

* Not much documentation on the translate.ubidots.com API, so
we will begin to phase that out.   
* Allow switching between http and https modes and allow selecting of
a different port number.
* Fix some typos
* Spark.process() -> Particle.process();
* Eliminate all compile warnings

These warnings can not be fixed with simple updates.   These will be
rewritten and we will just bump the version to 3.X.X.

'''
Ubidots.cpp: In member function 'bool Ubidots::sendAll()':
Ubidots.cpp:573:24: warning: passing NULL to non-pointer argument 1 of 'bool Ubidots::sendAll(long unsigned int)' [-Wconversion-null]
     return sendAll(NULL);
                        ^
Ubidots.cpp: In member function 'bool Ubidots::sendAll(long unsigned int)':
Ubidots.cpp:579:30: warning: NULL used in arithmetic [-Wpointer-arith]
     if ( timestamp_global != NULL) {
                              ^
Ubidots.cpp:594:41: warning: NULL used in arithmetic [-Wpointer-arith]
         if ((val + i)->timestamp_val != NULL) {
'''

# TODO

* See if we can add to a dummy variable the old way
* See if we can add to a dummy variable the new way
* See if we can retrieve data in a date range
* Compare to data we have and send un-sent data
