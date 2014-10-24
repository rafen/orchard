#ifndef _Commands_h
#define _Commands_h

// how much serial data we expect before a newline
#define MAX_INPUT 50

#define COMMANDS_DEBUG_LEVEL 0


// here to process incoming serial data after a terminator received
void process_data (const char * data){
    // Due to low memory jus make a simple comparison and do not use Strings :-(
    if(strcmp(data, "manual") == 0){
        manual = true;
        Serial.println("Manual");
    }else if(strcmp(data, "automatic") == 0){
        manual = false;
        Serial.println("Automatic");
    }else if(strcmp(data, "ONvalve0") == 0){
        if(manual){
            digitalWrite(valves[0], LOW);
        }
    }else if(strcmp(data, "OFFvalve0") == 0){
        if(manual){
            digitalWrite(valves[0], HIGH);
        }
    }else if(strcmp(data, "ONvalve1") == 0){
        if(manual){
            digitalWrite(valves[1], LOW);
        }
    }else if(strcmp(data, "OFFvalve1") == 0){
        if(manual){
            digitalWrite(valves[1], HIGH);
        }
    }else{
        #if COMMANDS_DEBUG_LEVEL >= 1
            Serial.println("Command not found");
        #endif
    }
}

void processIncomingByte (const char inByte){
    static char input_line[MAX_INPUT];
    static unsigned int input_pos = 0;

    switch (inByte){

        case ';':     // end of textx
            input_line [input_pos] = 0;    // terminating null byte

            // terminator reached! process input_line here ...
            process_data (input_line);

            // reset buffer for next time
            input_pos = 0;
            break;

        case '\n':     // discard newline
            break;
        case '\r':     // discard carriage return
            break;

        default:
            // keep adding if not full ... allow for terminating null byte
            if (input_pos < (MAX_INPUT - 1))
                input_line [input_pos++] = inByte;
            break;
    }
}

#endif
