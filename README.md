# Prog4_Engine

Engine and game built by: Bjarne Huijs,

With this project we were tasked to rework a very basic(bad) programming/game engine and use that reworked engine to build a small game. This game was QBert.

For my engine I primarily used shared pointers while trying to be careful and consistent with ownership. I intentionally made this choice over unique pointers/raw pointers etc because 
of the self cleaning capabilities of shared pointers, as well as the ease of access to the data you need. This of course as already stated imposes risk on object ownership and cleanup.

We learned multiple programming patters over the semester, such as the SRP principle which states an object only takes care of itself, and doesnt handle logic for other objects 
unless it owns or manages those objects.

I tried to implement these principles where I saw them to be appliccable. the principles I primarily used over this project are: 
Observer,
SRP,
Singleton | Factory | Manager (kept them together as I only used singletons as either a factory, a manager or both),
and OCP (very basic principle to make extension easier)

One of the requirements for the assignment was multi-threading, which to me was quite a challenge as it was my first contact with it. I received help from some others to solve this.
My implementation of multi-threading is located in the SDL-Sound system. A fair amount of the code used here was written with assistance from Rhidian Dewit. 
So I want to give credit where it's due as some pieces of code were copied from his implementation. This was needed to get my version to work properly.

For other smaller bits of code I have placed comments above them when I did not write them myself and credit the person who did in that comment.

The assets, sprites, textures and audio were all sourced from free to use platforms.
audio effects link (not the background music file): https://www.101soundboards.com/boards/10365-qbert-sounds
sprite sheet: https://www.spriters-resource.com/arcade/qbert/sheet/60496/

GitHub Link: https://github.com/BjarneHuijs/Prog4_Engine