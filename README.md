# BART
The Pørch's Bar of Light (BART) is an audio-visual sign that was designed, built, and programmed by Trenton Rhodes and Kwadwo Tenkorang. See the story of how BART came to be and how it works [here](https://wordpress.its.virginia.edu/TLP_TLC/2020/12/01/bart/).

# Usage
The working version of BART is in `BART_v1.2`. Simply plug in BART to turn it on. It will start in Wahoo mode. Clicking the button under BART will cycle through the following modes:
1. Wahoo - Solid navy blue and orange GO HOOS!
2. Wahoo Party - Wahoo colors that react to music. Brightness will match music loudness. Top lights up to treble, bottom to bass.
3. Rainbow Road - Rainbow colors with a sparkle, reminiscent of the countless hours of Mario Kart we played
4. Off - All lights turn off 


# Installation
This project was built in the arduino library. Install the following libraries through the arduino IDE `Tools > Manage Libraries...`
- arduinoFFT
- FastLED

# Electronic Hardware
- Microcontroller: [Arduino UNO](https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_3?dchild=1&keywords=arduino+uno&qid=1626229232&sr=8-3)
- Microphone: [Comidox 3Pcs](https://www.amazon.com/gp/product/B07J6N734S/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1)
- LEDs: [BTF-LIGHTING WS2812B RGB](https://www.amazon.com/BTF-LIGHTING-60pixels-Individually-Addressable-Non-waterproof/dp/B01CDTED80/ref=sr_1_19?dchild=1&keywords=ws2812b&qid=1601686283&refinements=p_85%3A2470955011&rnid=2470954011&rps=1&sr=8-19)
- Arduino Programming Cable: USB 2.0 CABLE TYPE A/B (same as most printer cables)
- 5V Adapter 
- Button

# Connections


| Component | Arduino Pin |
| --- | ----------- |
| Button | D2 |
| Top LED Data Line | D3 |
| Bottom LED Data Line | D4 |
| Microphone | A0 |




# Resources

### Arduino LED Overview
<https://www.youtube.com/watch?v=5M24QUVE0iU>

<https://www.youtube.com/watch?v=WS6FI_NyRzs>

<https://www.youtube.com/watch?v=YgII4UYW5hU>


### FastLED
<https://github.com/FastLED/FastLED/wiki/Pixel-reference>

<https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples#managing-your-own-output>

<http://fastled.io/docs/3.1/struct_c_r_g_b.html>

### Fast Fourier Transform (FFT)
<https://create.arduino.cc/projecthub/shajeeb/32-band-audio-spectrum-visualizer-analyzer-902f51>

<https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/>

<https://blog.yavilevich.com/2016/08/arduino-sound-level-meter-and-spectrum-analyzer/>

<https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover>


### Microphones
<https://blog.yavilevich.com/2016/08/arduino-sound-level-meter-and-spectrum-analyzer/>

### Sample Projects
<https://create.arduino.cc/projecthub/buzzandy/music-reactive-led-strip-5645ed>
<https://www.youtube.com/watch?v=bZZby3jp4KY>


