#ifndef BlinkerSlider_H
#define BlinkerSlider_H

#include <Blinker/BlinkerConfig.h>
#include <utility/BlinkerUtility.h>

class BlinkerSlider
{
    public :
        BlinkerSlider(const String & _name, callback_with_int32_arg_t _func = NULL)
            // : sliderName(_name)
        {
            registered = Blinker.attachWidget(_name, _func);

            sliderName = (char*)malloc((_name.length()+1)*sizeof(char));
            strcpy(sliderName, _name.c_str());
        }
        
        void attach(callback_with_int32_arg_t _func)
        {
            if (!registered) {
                return;
            }

            Blinker.freshAttachWidget(sliderName, _func);
        }
        
        void color(const String & _clr) {
            textClr = (char*)malloc((_clr.length()+1)*sizeof(char));
            strcpy(textClr, _clr.c_str());

            _fresh |= 0x01 << 0;
        }
        
        void print(char value)              { _print(STRING_format(value)); }
        void print(unsigned char value)     { _print(STRING_format(value)); }
        void print(int value)               { _print(STRING_format(value)); }
        void print(unsigned int value)      { _print(STRING_format(value)); }       
        void print(long value)              { _print(STRING_format(value)); }        
        void print(unsigned long value)     { _print(STRING_format(value)); }
        void print(double value)            { _print(STRING_format(value)); }
        void print()                        { _print(""); }
    
    private :
        // String sliderName;
        char * sliderName;
        bool registered = false;
        // String textClr = "";
        char * textClr;// = "";
        uint8_t _fresh = 0;

        void _print(const String & n) {
            if (!registered) {
                return;
            }

            String sliderData;

            if (n.length()) {
                sliderData += BLINKER_F("{\""BLINKER_CMD_VALUE"\":");
                sliderData += n;
            }

            // if (textClr.length()) {
            // if (textClr && (_fresh >> 0 & 0x01)) {
            if (_fresh >> 0 & 0x01) {
                if (sliderData.length()) sliderData += BLINKER_F(",");
                else sliderData += BLINKER_F("{");

                sliderData += BLINKER_F("\""BLINKER_CMD_COLOR"\":\"");
                sliderData += (textClr);
                sliderData += BLINKER_F("\"");

                free(textClr);
            }

            sliderData += BLINKER_F("}");

            _fresh = 0;

            Blinker.printArray(sliderName, sliderData);

            // textClr = "";
        }
};

#endif
