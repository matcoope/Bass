<p align="center">
    <b>BASS</b><br />
	Pure Swift module to access <a href="http://un4seen.com/bass.html">libbass</a> from Swift code as a dynamic framework.
</p>

[![Carthage Compatible](https://img.shields.io/badge/Carthage-compatible-brightgreen.svg)](https://github.com/Carthage/Carthage)
![Swift 3.0.x](https://img.shields.io/badge/Swift-3.0.x-blue.svg)
[![GitHub Release](https://img.shields.io/github/release/Starling-Inc/Bass.svg)](https://github.com/Starling-Inc/Bass/releases)
![platforms](https://img.shields.io/badge/platform-iOS-lightgrey.svg)

####Motivation
Original library is written in C and available for Apple platforms: iOS, tvOS, macOS. Swift is compatible with C language and 
provides direct access to C code.
Therefore you're able to use [libbass](http://un4seen.com/bass.html) in your Swift code out-of-the-box, but not exactly. 

There is [official instruction](http://www.un4seen.com/forum/?topic=10910.msg76056#msg76056) how 
[libbass](http://un4seen.com/bass.html) should be linked and used within your `iOS / tvOS` project, so this module does it for 
you.
The only thing you need to use [libbass](http://un4seen.com/bass.html) in your Swift project from now is connect this 
framework as dependency — currently only [Carthage](#carthage) is supported.

#### Carthage
To add thr dependency, simply add Bass to your `Cartfile`:

```
github "Starling-Inc/Bass" ~> 2.0
```

If you doesn't know what [Carthage](https://github.com/Carthage/Carthage) is, follow the [link](https://github.com/Carthage/Carthage).
