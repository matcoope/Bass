<p align="center">
    <b>BASS</b><br/>
	Pure Swift module to access <a href="http://un4seen.com/bass.html">libbass</a> from Swift code as a dynamic framework.
	<br/><br/>
	<a href="https://github.com/Carthage/Carthage"><img src="https://img.shields.io/badge/carthage-compatible-brightgreen.svg"/></a>
	<img src="https://img.shields.io/badge/swift-3.0.x-blue.svg"/>
	<a href="https://github.com/Starling-Inc/Bass/releases"><img src="https://img.shields.io/github/release/Starling-Inc/Bass.svg"/></a>
	<img src="https://img.shields.io/badge/platform-iOS-lightgrey.svg"/>
</p>

#### Motivation
Original library is written in C and available for Apple platforms: iOS, tvOS, macOS. Swift is compatible with C language and 
provides direct access to C code.
Therefore you're able to use [libbass](http://un4seen.com/bass.html) in your Swift code out-of-the-box, but not exactly. 

There is [official instruction](http://www.un4seen.com/forum/?topic=10910.msg76056#msg76056) how 
[libbass](http://un4seen.com/bass.html) should be linked and used within your `iOS / tvOS` project, so this module does it for 
you.
The only thing you need to use [libbass](http://un4seen.com/bass.html) in your Swift project from now is connect this 
framework as dependency — currently only [Carthage](#carthage) is supported.

#### Carthage
To add the dependency, simply add Bass to your `Cartfile`:

```
github "Starling-Inc/Bass" ~> 2.0
```

If you doesn't know what [Carthage](https://github.com/Carthage/Carthage) is, follow the [link](https://github.com/Carthage/Carthage).

#### Usage
When you're set up, you can use the module directly:

```swift
func initialize() {
	// this is not a part of original library, just convenient method to use it through dynamic module
    BASS_LoadPlugins() 
    
	// direct calls of library's API
	BASS_Init(-1, 44100, 0, nil, nil)
	BASS_SetConfig(DWORD(BASS_CONFIG_IOS_NOCATEGORY), 1)
}

func free() {
	BASS_Free()
}
```

This module does not provide anny additional functionality, so you have to process errors by yourself.
