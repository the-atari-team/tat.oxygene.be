# Oxygene Be

Or Oxygene Part #2

A horizontal Shoot'em Up Game which should show, what is possible on good old Atari 8bit.
It needs at least 64kb RAM and will not work longer on Atari 400/800.

The only I've taken from the original game is the graphics of
the spacecraft, the enemies and the font of the big ships.  

The rest of the game is complete rewritten.

1. At first, insert disk and boot without basic.
2. The loader occurs after some sector reads. It takes a while to read 64kb.
3. The main menu occurs, here you can choose the level and mission.
There are some more options. Simply use the cursor keys to walk through this options.
4. Leave main menu by trigger or space key.
Now you see mission overview. It shows what you have to do in the game.
5. The game starts with space key or trigger. Play!
With your small space craft, fly horizontal over a big ship and destroy small jets on
runways all over the big ship. Also destroy the enemies in front.
The enemies shoot simple single shoots, but they get more angry the more you
destroy. The color of the enemies changed.
Are all need jets and enemies destroyed, land your space craft on a empty runway near
the end of the big ships. To do so, fly straightforward over the small arrows from
the left side. 
To make missions not so simple, there exists high buildings on the big ship, see there
shadow. A touch cost lot of energy, most the time the own space craft.
So be careful.
6. At the end you get a status report what is done.
If all is green, mission is successful.
Use the stick up or trigger to get to next mission. If all missions done
it goes to the next level at mission #1.

## technical

* All space craft animations are new, there are more and better animations.
* Also the shoots are animated. Looks nicer.
* There are different enemies. Up to 4 in a vertical manner.
* The Atari display lsits are optimized, take less memory. The oxygene letter is down sized to 32bytes per line.  
* The Atari display list interrupts are all new.
* There are more colors at the same time on the screen.
* The space craft has an energy shield, simple hits of enemies will not kill you but decrease your energy.
* Joy of use is better than in the old game.
* There are no random enemies which shoot at random time.
* The enemies came all the time of the front, change of direction and the enemies came from the other side.
* There are 3 different shoot types in different speed.
* Always the enemy near you will fire.
* There exist a hate-factor, the more jets and enemies you kill the more decrease the factor.
You see it at the color of the enemies. 
* Now there are missions to complete.
* Different count of jets has to destroy on the surface of the big ship.
* Different count of enemies has to kill.
* The time runs out.
* There exist different difficult level. From god-mode up to suicide level.
* There exist an extra option menu so you can play with different options. Simple use the cursor keys.
* A highscore exist.

## Atari technicals
* The game use nearly the whole 64kb RAM.
* The boot disc use LiteDOS by Mr.Atari, which gives us 4 kb more free memory.
* The player missile gfx lies under the OS, also the fonts and the big ship.
* The switch between RAM and OS comes from TurboBasic. Source-code follows if there exist interest.
* The fonts, images and ship graphics are single files, this simplifies the exchange.
* The TAT Sign based on player missile gfx also, saves some memory.
* The Space craft takes 3 player with its shadow and 2 missiles.
* Space craft shoot takes one missile.
* Enemies take on player due to the time limitations on the simple 8 bit computer there are no
more display interrupt tricks to show the enemies.
* Enemy shoot take one missile which is differently animated and differently dangerous. 
* The big ship takes 17 * 512 bytes and will all the time reload from disk.
* To cut down there size, a simple run-length encoder was used from old german happy computer journal.
* There exist a simple editor to create such big ships.
* The energy level line is a simple GTIA-Trick on a graphics 0 line with a simple font and dithering.
* So it looks like you have 11 colors in one line. The small ship on the right is a player.
* Sound is complete new created, near by a simple sound generator from P.Finzel out of
his book "Hexenküche".
* Unfortunately there is no theme song yet.


## technical at development time 

Big things of the game are written in an ALGOL like high language. Due to the fact that Action! was
very expensive in the old days of Atari in the late 80ies I created a simple compiler for my self.
I studied some books about compiler build. 
This compiler has to be make work again, I fixed some bugs, simplify a lot of things.
It supports:
* functions/procedures with more than 3 parameters
* works also recursive until 6502 stack overflows
* Supports relative complex expressions.
* Multiply and divisions in a 2-complement are replaced by binary shift.
* Knows if-then-else
* for- while- repeat-until loops
* Ok there exist an overhead to real assembler, but it makes programming so much easier.
* The compiler also works perfect with other routines in assembler together.
* A goody, the source runs most the time also with Atari-(Turbo)-Basic together, because
it uses only the atari floating point zero page registers.
* The compiler load the source in parts from disk/harddisk and translate it to assembler.
Most assembler code is compatible to MAC/65 but full compatible to atasm.
With the atari800 emulator in turbo mode you can work at high speed.
I've patched the atari800 for my self, so I'm be able to stop it with an illegal instruction and
go back to my bash scripts.
So some bash scripts, an editor like intellij and ready is a simple development environment.
I also use Altirra for debugging. Atasm labels will read via parameter.

It is fun to develop in 8bit for the Atari again.
The only really evil, the constant lack of memory at 64kb.

August 2020, Lars
