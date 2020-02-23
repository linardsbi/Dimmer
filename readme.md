# LED strip dimming

## Small LED dimming project.

This was supposed to run on an ESP8266, but I didn't have any 3.3v MOSFETs lying around.
Going to port it in the future and add an API; for now using serial input to change LED brightness.

## Serial syntax

Send values over in either this: "<red value>,<green value>,<blue value>," (all values are optional), or this: "<color name>:<color value>," format.
