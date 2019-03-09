# Candy Crush

This repository is a project in NCKU course "Program Design 2".

---
## Abstract

This repository is going to implement a level of the classic game "Candy Crush" in C++ with Qt. Qt is a cross-platform application development framework written in C++ for desktop, embedded and mobile. Supported Platforms include Linux, OS X, Windows, VxWorks, QNX, Android, iOS, BlackBerry, Sailfish OS and others.

> More information about [Qt](https://wiki.qt.io/About_Qt)

* The resource of [pictures (`img`)]() and [sounds (`sound`)]() are originated from [here](https://candycrush.fandom.com/wiki/Candy_Crush_Saga_Wiki).
* [How to install Qt IDE?](https://www.qt.io/qt-5-12?utm_campaign=Qt%205.12&utm_source=homepage-hero-banner)

---
## Execution

1. Compilation
    ```bash
    $ make
    # OR
    $ qmake
    ```
2. Execute the file `CandyCrush.pro` in Qt IDE.
    * If succeed, you will see the picture as follow
        ![](https://i.imgur.com/EGpsKPf.png)
3. How to play this game?
    * The target is get at least 10000 points in 1:30
        ![](https://i.imgur.com/EGpsKPf.png)
    * The rule is follow the gam "Candy Crush" we know
        ![](https://i.imgur.com/i1ZAc0k.png)
        ![](https://i.imgur.com/Xyuhv2e.png)
    * If you win, you will see the picture as follow
        ![](https://i.imgur.com/tyS0fJi.png)
    * If you loss, you will see the picture as follow
        ![](https://i.imgur.com/68Mlcj0.png)

---
## Dependency

> **NOTICE:** Make sure you have already installed the following packages if you are using Ubuntu Linux 14.04 LTS.

* [Ubuntu Linux 14.04 LTS](http://releases.ubuntu.com/14.04/)
    * [Package: libpulse-dev (1:4.0-0ubuntu11)](https://packages.ubuntu.com/trusty/libpulse-dev)
    * [Package: gstreamer1.0-plugins-good (1.2.4-1~ubuntu1.4 and others)](https://packages.ubuntu.com/trusty/gstreamer1.0-plugins-good)
    * [Package: gstreamer1.0-plugins-bad (1.2.4-1~ubuntu1.1 and others)](https://packages.ubuntu.com/trusty/gstreamer1.0-plugins-bad)
    * [Package: gstreamer1.0-plugins-ugly (1.2.3-2build1)](https://packages.ubuntu.com/zh-tw/trusty/gstreamer1.0-plugins-ugly)
    * [Package: gstreamer1.0-libav (1.2.3-1)](https://packages.ubuntu.com/trusty/gstreamer1.0-libav)
* [Qt Creator 4.8.2](http://download.qt.io/official_releases/qt/5.12/5.12.1/qt-opensource-linux-x64-5.12.1.run.mirrorlist) - Based on Qt 5.12.1 (GCC 5.3.1 20160406 (Red Hat 5.3.1-6), 64 bit)

---
## Logs

* MAR 09, 2019 - Build and test on [Qt Creator 4.8.2](http://download.qt.io/official_releases/qt/5.12/5.12.1/qt-opensource-linux-x64-5.12.1.run.mirrorlist)

---
## Author

* [David Lu](https://github.com/yungshenglu)

---
## License

[GNU GENERAL PUBLIC LICENSE Version 3](LICENSE)
