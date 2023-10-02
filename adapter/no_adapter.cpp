// Practice exam of the adapter design pattern using a reader example

#include <iostream>

class DataStorage {
public: 
    int data;
};

class USB : DataStorage {
public:

    USB(int num) {
        data = num;
    }

    int USB_Transmit() {
        std::cout << "Transmit data from USB Device" << std::endl;
        return data;
    }
};

class SDCard: DataStorage {
public: 
    SDCard(int num) {
        data = num;
    }

    int SDCard_Transmit() {
        std::cout << "Transmit data from SDCard Device" << std::endl;
        return data;
    }
};

class DataReader{
public:
    void ReadDataFromStorage(USB* usb_device){
        int data = usb_device->USB_Transmit();
        std::cout << "Received data " << data << std::endl;
    }
};

int main() {
    DataReader reader;
    
    USB* usb = new USB(5);
    reader.ReadDataFromStorage(usb);

    SDCard* sdcard = new SDCard(10);
    // reader.ReadDataFromStorage(sdcard); // causes error due to incompatible type

    return 0;
}