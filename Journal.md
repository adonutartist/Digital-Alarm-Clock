# Devlog #1

**Date & Time:** 5 July, 10:00 PM to 6 July, 3:20 AM *(breaks included)*  

Today I spent almost 5 hours in Autodesk Fusion 360 working on the enclosure for my digital alarm clock. It was my first proper attempt at making an electronics enclosure from scratch (only made a hackpad before yes I got skill issues ;-;) so there was quite a bit of trial and error :<

The case consists of two parts:
- Main shell
- Removable back plate

The back plate is designed to be attached using M3x8mm screws, so I can easily open it later for wiring, debugging, or making changes without destroying the whole case :]
I followed the tutorial available on the BLARE website for a lot of the basic enclosure design, but I also made several changes to make it fit my own project better:
- Added 4 mechanical keys.
- Changed the position of the ESP32.
- Changed the position of the buzzer.
- Rearranged the internal layout.

I also found a font called Digital 7 that looks like digital clock text and it fits so well with the emboss I added on the case :>
One thing I am still confused about... why does the tutorial add a hole underneath the buzzer like on the bottom plate... ;-;
My guess is that its there so the sound can escape the enclosure instead of getting trapped inside. Makes sense... I think :p but wouldn't that lead to the buzzer falling through the hole ;-; man I am so dumb

## Progress Pictures

<table>
<tr>
<td width="50%">
<img width="100%" alt="Screenshot (96)" src="https://github.com/user-attachments/assets/2699964e-956b-4430-b104-35fb85a8dc7f" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (97)" src="https://github.com/user-attachments/assets/ff8592b6-2ccb-40ec-a24a-2c3034fa9cd9" />
</td>
</tr>

<tr>
<td width="50%">
<img width="100%" alt="Screenshot (98)" src="https://github.com/user-attachments/assets/d53408c4-b8d6-4ce7-ad4b-56d43ee947f3" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (99)" src="https://github.com/user-attachments/assets/ff23283a-6d91-472f-88e8-755ad8089629" />
</td>
</tr>

<tr>
<td width="50%">
<img width="100%" alt="Screenshot (101)" src="https://github.com/user-attachments/assets/4a2b8933-b26a-4e34-8a9f-2f10bd86d73c" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (100)" src="https://github.com/user-attachments/assets/41ed30f7-b4f0-40e3-a860-a1cb78f2af0b" />
</td>
</tr>
</table>

Pretty happy with how it's turning out so far :D There's still a lot left to do, but at least now I have a solid enclosure to build everything around. Next up is finishing the design and making the wiring diagram and oh also the firmware ;-;

---

# Devlog #2

**Date & Time:** 6 July, 10:00 PM to 7 July, 1:51 AM *(Mostly easy stuff today xD)*

Today was a mix of figuring things out, redesigning stuff, and realizing I should probably read the documentation before assuming things ;-;

Firstly I added a key on top to set/stop alarm. I also wanted the enclosure to have a bit more personality instead of just being a plain rectangular box, so I added a Kintsugi design similar to my macropad to the front of the case. I thought it would make it look a little more unique while still keeping it fairly minimal. After finishing that, I spent some time making a few nice renders because seeing the finished design from different angles is always satisfying :D and also made cool exploded view of it :>

Then I made the circuit diagram for the project in MS Paint yep the GOAT MS Paint lmfao :> It isn't the fanciest tool in the world, but honestly it does the job really well. I thought of using kicad schematic to do this but MS Paint just felt way more easier like I didn't want to go find all sym libraries and stuff ;-; I am definetly becoming more lazy ngl xd

For some reason I convinced myself that I needed to use QMK for the firmware because there were mechanical switches involved. I spent a while thinking about how I was going to make an alarm clock using keyboard firmware... only to actually read the BLARE guide properly and notice that it literally tells you to use Arduino IDE from the start xD literally I am just so dumb xd
Safe to say this saved me from going down a very long compilation doom... I frikin hate how much time it takes QMK to compile even the simplest stuff ;-; After that I started reading some tutorials for Arduino IDE and seeing other alarm clock codes instead. Since I don't have the hardware yet, I focused on getting a basic firmware structure planned out with Wi-Fi time sync, alarm logic, key handling, and display updates on the screen. Its probably full gibberish and bonkers and would definitely need testing once the kit arrives, but at least I have something to ship right now :]

Another thing I did today was attend one of the BLARE workshops. I still had a few questions left over from yesterday about the enclosure, wiring, and how everything would actually come together, so the workshop helped clear up those doubts. Definitely glad I joined instead of trying to guess everything myself.

## Progress Pictures

<table>
<tr>
<td width="50%">
<img width="1645" height="806" alt="circuitv3" src="https://github.com/user-attachments/assets/6f9a762e-4ff5-40f3-acd5-b95797f9cfc1" />
</td>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo5" src="https://github.com/user-attachments/assets/8194add8-cf10-4dcc-ba36-2dcbc9ed5a76" />
</td>
</tr>

<tr>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo3" src="https://github.com/user-attachments/assets/bd260514-c78a-43fc-a41e-eb73c3469e3f" />
</td>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo" src="https://github.com/user-attachments/assets/593648d6-539c-4395-9a22-56ef74e29eb5" />
</td>
</tr>
</table>

Overall, today was less about making huge visible progress and more about getting everything ready to ship. The project feels a lot more planned out now, and I don't feel nearly as lost as I did yesterday xD. Next up is Waiting for the kit, and then finally seeing if everything actually works outside of my imagination ;-;

---

# Devlog #3

**Date & Time:** 7 July 10:00 PM to 8 July 1 AM *(no breaks :p)*

Today was mostly about improving the enclosure after getting feedback on my CAD model. Turns out designing something that looks nice and designing something that's actually 3D printable are two very different things xD
I got a DM from the reviewer who reviewed my enclosure and pointed out a few things that would cause problems during printing. I'm really glad I got the feedback before sending it off because I definitely would've run into issues otherwise :<

Here are the changes I made after the review:

- Rotated the chamfers so they point towards the build plate instead of away from it, reducing unnecessary overhangs.
- Changed the embossed text so it's more printer friendly.
- Added the missing screw holes to the back plate apparently the version I shared was an older file without them ;-;
- Went through the whole model once more to make sure everything should print a lot more reliably.

One thing I also learned today is that the printer won't magically print multiple colours just because I designed them that way xD. The enclosure will be printed entirely in black, so if I still want the gold Kintsugi lines later I'll have to paint them myself or maybe use vinyl or stickers. Honestly, I think hand painting them could end up looking even cooler :]
The mentor also shared a really useful guide about designing parts specifically for 3D printing. I didn't realize how much orientation, overhangs, and support material affect a print until now. Definitely learned something new today instead of just randomly adding chamfers because they looked nice xD
Overall this wasn't the most exciting day in terms of adding new features so not much visual changes, but I feel like the enclosure is much closer to something that can actually be manufactured now instead of just looking good on my screen :D

---

# Devlog #4

**Date & Time:** 31 August 4 PM to 31 August 11 PM *(with breaks :p)*

Yesterday my kit arrived was pretty excited to take a look and sadly there were no stickers but all the components were present nothing broken all gud! Then I watched a video on how to solder it looked pretty easy and irl too it was mildly easy ngl! First time soldering btw lol xDDD well anyways i soldered the pins to tht tft display and the esp32c3 mcu, then i soldered a MM and a FM wire to each of the keycaps and also the buzzer. Then i got confused on how to assemble these cuz all have common gnd wire so how do i achieve tht with only jumper wires so then I pinged EMT and Liam in blare to help me understand how to do this all and they told me first my circuit is kinda wrong i gotta have the TFT's BL pin connected to the GND cuz this display acts kinda weird, and they also told me i gotta use a breadboard for the easy or else i would have to solder them all gnd wires kinda confusing so i js found a breadboard my cousin brother had gave me like 3 years ago so i js used tht and the thing worked YEWW IT FRIKIN WORKED MY FIRST SOLDERING PROJECT WORKED WITHOUT ANY MISTKES EXCEPT ONE! I had soldered the buzzer wrong i thought it was passive but it was actually an active so i had connected gnd wire to plus yeh i am dumb so i had to try to like remove the solder and in the process i plucked the minus pin out of its hole the buzzer looked beyong saving sir liam said i am cooked but i denied to give up! I took a jumper wire and stuck its male end into tht hole of the pin and soldered it yehhhh i am the GOAT this is 100000 IQ move ikr ikr and guess wht it worked! IT WORKEDDDDDD!!! now the question was how to fit this all mess into the case which turned out is rly small like frikin hilariously ssmall the mcu didnt fit in its pocket, the breadboard didnt fit either just the buzzer and keys and display was fitting quite well so yeh gotta push it scram it all in somehow so i first remove the connections from the bread then somehow fixed the mcu in tht pocket too small for it hd to melt the hole for usb a lil to make it bigger cuz it was way too small and then i used tape to fix the screen and buzzer and mcu in place and for the keys i js forced it down its hole and it fit fabulously! now i scrammed its back plate somehow fitting all the wires or force fitting idk how to but still the back plate wouldnt fit cuz of the breadboard so again i did a 100000 IQ move i broke the breadboard like it was already in part i js removed its gnd part so it was js a thin strip of gnd and it easily went in cuz of how thin it is and how i fixed the backplate and holy i am done!!!!!!!!!!!!!!!!!!!!!!!!!! Wrote the firmware too for alarm and wifi time sync and it all works i am so glad! 

## Lapse Link

https://lapse.hackclub.com/timelapse/eQyfPEJTRa2B

## Estimated time spent

6 houishh

## Progress Pictures

<img width="3264" height="1840" alt="IMG_20260901_162159" src="https://github.com/user-attachments/assets/4764849b-d89a-4846-a47e-a623f6af454e" />

