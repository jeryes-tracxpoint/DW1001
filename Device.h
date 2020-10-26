#include "DW1000Time.h"
#include "DW1000Mac.h"

class DeviceClass{

public:
    DeviceClass();
    DeviceClass(byte address[],byte shortAddress[]);
    DeviceClass(byte address[],boolean shortOne = false );
    DeviceClass(byte address[],char x[]);
    ~DeviceClass();

    //seters
    

private:

    uint16_t _replaytime;
    byte      ownaddress[8];

};

extern DeviceClass Device;