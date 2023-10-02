// Practice exam of the adapter design pattern using a reader example

#include <iostream>

class DataStorage {
public: 
    int data;
    int GetData() {return data;}
    void SetData(const int& n) {data = n;} 
};

class USB : public DataStorage {
public:
    USB(int num) {
        data = num;
    }

    virtual int USB_Transmit() {
        std::cout << "Transmit data from USB Device" << std::endl;
        return data;
    }
};

class SDCard: public DataStorage {
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

// Key steps:
// 1. Create an adapter class that inherits the Client Interface (USB)
// 2. Include an instance of the adaptee 
// 3. Override the client interface function with a call to the service function
class SDCard_USB_Adapter : public USB {
private:
    SDCard* sdcard;
public:
    SDCard_USB_Adapter(SDCard* sdcard) : USB(-1) {
        this->sdcard = sdcard;
    }
    int USB_Transmit() override {
        return sdcard->SDCard_Transmit();
    };
};

int main() {
    DataReader reader;
    USB* usb = new USB(5);
    reader.ReadDataFromStorage(usb);

    SDCard* sdcard = new SDCard(10);
    USB* usb2 = new SDCard_USB_Adapter(sdcard);
    reader.ReadDataFromStorage(usb2); 
    sdcard->SetData(20);
    reader.ReadDataFromStorage(usb2); 


    return 0;
}