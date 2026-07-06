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

For some reason I convinced myself that I needed to use QMK for the firmware because there were mechanical switches involved. I spent a while thinking about how I was going to make an alarm clock using keyboard firmware... only to actually read the BLARE guide properly and notice that it literally tells you to use Arduino IDE from the start xD

Safe to say that saved me from going down a very long compilation hole. After that I started planning out how the firmware should work instead. Since I don't have the hardware yet, I focused on getting a basic firmware structure planned out with Wi-Fi time sync, alarm logic, button handling, and display updates on the screen. Its probably full gibberish and bonkers and would definitely need testing once the kit arrives, but at least I have a solid starting point now :]

Another thing I did today was attend one of the BLARE workshops. I still had a few questions left over from yesterday about the enclosure, wiring, and how everything would actually come together, so the workshop helped clear up a lot of those doubts. Definitely glad I joined instead of trying to guess everything myself.

To finish things off, I made the circuit diagram for the project in... MS Paint yep the GOAT MS Paint lmfao :> It isn't the fanciest tool in the world, but honestly it does the job. Sometimes the simplest tools are enough when you just need to map out where everything connects.

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
