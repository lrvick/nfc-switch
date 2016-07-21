# NFC Switch #

<http://github.com/lrvick/nfc-switch>

[![TravisCI][travis-badge]][travis-status]
[![License][license-badge]][license]

[travis-badge]: https://travis-ci.org/lrvick/nfc-switch.svg?branch=master
[travis-status]: https://travis-ci.org/lrvick/nfc-switch
[license-badge]: https://img.shields.io/github/license/lrvick/nfc-switch.svg
[license]: https://github.com/lrvick/nfc-switch/blob/master/LICENSE.md

## About ##

This project provides control code for an Arduino/PN532 based switch system,
intended to control simple 5v pulse controlled latching relay boards.

This could be suitable for lock/unlocking doors, turning AC devices on
or off, or togging power on vehicles with simple keyswitch lines such as
motorcycles or ATVs.

## Requirements ##

  * [Arduino Pro Mini 328 - 3.3V/8 MHz][1]
  * [PN532 NFC/RFID controller breakout board - v1.6][2]
  * 3V pulse controlled latching relay kit such as:
    * [Adafruit Latching Mini Relay FeatherWing][3]
    * [3v to 5v Bistable Latching Relay Kit][4]
  * PN532 breakout should be connected to the Arduino Pro Mini directly via I2C
  * Relay on/off lines to pins 2/3 respectively

[1]: https://www.adafruit.com/products/2377
[2]: https://www.adafruit.com/products/364
[3]: https://www.adafruit.com/products/2923
[4]: https://www.wirelessthings.net/3v-to-5v-bistable-latching-relay-kit


## Usage ##

1. Create authorized tag header file

    ```bash
    cp authorized_ids.h.sample authorized_ids.h
    vim authorized_ids.h
    ```

2. Build

    ```bash
    make build
    ```

3. Upload to board

    ```bash
    make upload
    ```

4. Test tags

    ```bash
    make monitor
    ```

    Begin scanning tags and verify lock/unlock/fail states and latch positions
    are as you expect.


## Notes ##

  Use at your own risk. You may be eaten by a grue.

  Questions/Comments?

  You can find me on the web via:

  [Email](mailto://lance@lrvick.net) |
  [Blog](http://lrvick.net) |
  [Twitter](http://twitter.com/lrvick) |
  [Facebook](http://facebook.com/lrvick) |
  [Google+](http://plus.google.com/109278148620470841006) |
  [YouTube](http://youtube.com/lrvick) |
  [Last.fm](http://last.fm/user/lrvick) |
  [LinkedIn](http://linkedin.com/in/lrvick) |
  [Github](http://github.com/lrvick/)
