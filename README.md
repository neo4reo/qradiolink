QRadioLink
==========

[![Build Status](https://travis-ci.org/kantooon/qradiolink.svg?branch=master)](https://travis-ci.org/kantooon/qradiolink)

About
-----

*QRadioLink* is a Linux software defined radio transceiver application using VOIP for inter-communication, built on top of [GNU radio](https://www.gnuradio.org/), 
which allows experimenting with software defined radio hardware using different digital and analog radio signals and a friendly user interface.

Its primary purpose is educational, but it can also be customized for low power data communications
on various frequency bands.
It can also be used as an amateur radio SDR transceiver for demonstrating radio communications to students.

The application was originally inspired from the [Codec2 GMSK modem](https://github.com/on1arf/gmsk) project by Kristoff Bonne.

[![Screenshot](http://qradiolink.org/images/qradiolink26.png)](http://qradiolink.org)

Features
---

- VOIP connection between two or more stations operating in simplex or semi-duplex mode
- Direct VOIP talk-around (requires internet connection)
- VOX mode
- Transmit and receive analog FM, SSB, AM, digital voice, text messages, digital video, IP protocol.
- Full duplex 250 kbit/s IP data modem with configurable TX/RX offsets
- Analog and digital mode repeater - full duplex mode, no mixed mode support 
- Radio forwarding over VOIP - forward voice to the VOIP connection and viceversa
- Mixed operation mode (receive one mode and transmit another)
- Audio codecs: Codec2 700 bit/s, Codec2 1400 bit/s, Opus 9600 bit/s
- Narrow band digital voice mode with the [Codec2](http://rowetel.com/codec2.html) audio codec
- Wideband digital voice mode with the [Opus](https://xiph.org) audio codec
- Digital modulation:  **BPSK**, **DQPSK**, **2FSK**, **4FSK**
- Analog modulation: narrow FM (5 kHz), FM (10 kHz), Wide FM (broadcast, receive-only), AM, SSB
- CTCSS encoder and decoder for analog FM
- Supported hardware: [**Ettus USRP**](https://ettus.com), [**RTL-SDR**](https://osmocom.org/projects/sdr/wiki/rtl-sdr), [**LimeSDR-mini**](https://www.crowdsupply.com/lime-micro/limesdr-mini) (through SoapySDR), BladeRF, other devices supported by [**gr-osmosdr**](https://osmocom.org/projects/sdr/wiki/GrOsmoSDR)
 

Requirements
----
- Build dependencies on Debian Stretch: 

<pre>libasound2 (>= 1.0.16), libboost-program-options1.62.0, libboost-system1.62.0, 
libboost-thread1.62.0, libc6 (>= 2.15), libcodec2-0.4, libconfig++9v5, libgcc1 (>= 1:3.0), 
libgnuradio-analog3.7.10, libgnuradio-audio3.7.10, libgnuradio-blocks3.7.10, 
libgnuradio-digital3.7.10, libgnuradio-fec3.7.10, libgnuradio-filter3.7.10, 
libgnuradio-osmosdr0.1.4, libgnuradio-pmt3.7.10, libgnuradio-qtgui3.7.10, 
libgnuradio-runtime3.7.10, libgsm1 (>= 1.0.13), libjpeg62-turbo (>= 1.3.1), 
libopus0 (>= 1.1), libspeexdsp1, libprotobuf10, libpulse0 (>= 0.99.1), libqt4-network (>= 4:4.5.3), 
libqt4-sql (>= 4:4.5.3), libqtcore4 (>= 4:4.8.0), libqtgui4 (>= 4:4.6.1),
 libstdc++6 (>= 5.2), gnuradio-dev, gr-osmosdr, libgsm1-dev, libprotobuf-dev,
 libopus-dev, libspeexdsp-dev, libpulse-dev, libcodec2-dev, libasound2-dev, libjpeg62-turbo-dev,
 libconfig++-dev, qt4-qmake, libqt4-dev, libqwt5-qt4-dev, libqt4-sql-sqlite, qt4-dev-tools
</pre>

- Please make sure you have all the development packages installed before building QRadioLink
- Depending on whether GNU radio was built with Qt4 or Qt5, you will need the corresponding development packages
- QT >= 4.8 (QT 5 only works on Debian testing with GNUradio 3.7.11 packages )
- qmake (either qmake-qt4 or qmake-qt5)
- Pulseaudio (native Alsa support is not fully implemented) 
- Gnuradio >= 3.7.10 built with OsmoSDR and UHD support
- Boost 
- libgnuradio-osmosdr built with UHD, RTL-SDR, SoapySDR or HackRF support
- libgsm, libprotobuf, libopus, libspeexdsp, libpulse-simple, libpulse, libasound, libcodec2, libsqlite3, libjpeg, libconfig++
- protoc compiler (libprotoc 2.6.1 or greater)

In order to build on Ubuntu 17.10 you have to install the following packages, assuming a full GNU Radio development environment is already installed.

<pre>
$ sudo apt install libconfig++-dev libgsm1-dev libprotobuf-dev libopus-dev libpulse-dev libasound2-dev libcodec2-dev libsqlite3-dev libjpeg-dev libprotoc-dev protobuf-compiler libqwt5-qt4-dev
</pre>

[Downloads](https://github.com/kantooon/qradiolink/releases "Downloads")
----

Debian Stretch (stable) x86_64 packages are provided via Travis CI automated builds
Please see the [Github releases page](https://github.com/kantooon/qradiolink/releases) for binary downloads.

Opensuse packages are available from [Opensuse build server](https://build.opensuse.org/package/show/hardware:sdr/qradiolink)
thanks to Martin Hauke.

Building the software from source
-----

The guide assumes you are using Debian Stetch.
- Clone the Github repository into a directory of your choice
- Compile the protobuf sources for your system
- Run qmake to generate the Makefile
- Run make (with the optional -j flag)

<pre>
cd qradiolink
mkdir build
cd ext/
protoc --cpp_out=. Mumble.proto
protoc --cpp_out=. QRadioLink.proto
cd ..
cd build/
qmake-qt4 ..
make
./qradiolink
</pre>

Known issues:
- Digital reception sometimes stops working after switching modes. Workaround: select RX mode before starting RX.
- FFT display has incorrect size (too small)
Workaround: switch to waterfall and back
- Segmentation fault when starting TX or RX modes. 
Check that that device settings are correct and you have clicked save in the configuration page.
- In low light, the automatic adjustment of ISO in the video camera can cause very long times to capture a frame.
Solution: use plenty of lighting for video.
- On Gnome desktop environments, the Qt color scheme is not displayed correctly



Running
-------
- It is recommended to start the application using the command line and check for errors.
- At first run, see the Setup tab first and configure the application, then click Save before starting TX or RX from the main page, otherwise you may get a segmentation fault.
- VOIP uses [umurmur](https://github.com/umurmur/umurmur) as a server. The available channels and the logged in stations are also listed on the page once you have connected to the server. The server IP/hostname will be saved on application exit. You can use QRadioLink as a pure VOIP client without using the radio by selecting "Use PTT for VOIP". You can also forward the digital or analog radio voice to the VOIP reflector. Any voice packets coming from the reflector will be transmitted directly after transcoding in this case. Currently full duplex audio from more than two VOIP clients at the same time is not supported.
- The configuration file is located in $HOME/.config/qradiolink.cfg
- The select inputs in the lower right corner toggle between different operating modes. Repeater mode requires both RX and TX to use the same mode.
- The Tune page allows fine tuning 5-5000 kHz around the center frequency (depending on operating mode), and monitoring the 
signal strength.
- Video page will display received video stream (experimental feature). A limited number of cameras are supported.


Credits and License
-------------------
- QRadioLink is designed by Adrian Musceac YO8RZZ, and is released under an Open Source License,
 the GNU General Public License version 3.
- It makes use of other code under compatible licenses, and the authors are credited in the source files.
- The CFreqCtrl widget is Copyright 2010 Moe Wheatley with modifications by Alexandru Csete.
- [Codec2](http://rowetel.com/codec2.html) is developed by David Rowe
- [Opus](https://xiph.org) is developed by the Xiph foundation
- [GNU radio](https://www.gnuradio.org/)  is a free software development toolkit that provides signal processing
blocks to implement software-defined radios and signal-processing systems.

