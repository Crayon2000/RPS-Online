# RPS Online

## Help Contents

* Overview
  * [What is RPS Online](#rps-online)
  * [How do I play Rock Paper Scissors](#how-do-i-play-rock-paper-scissors-the-rules)
* Network Play
  * [Network Play Concepts](#network-play-concepts)
  * [Playing over a LAN](#playing-over-a-lan)
  * [Playing over Internet](#playing-over-internet)
* Commands
  * [Game Menu Commands](#game-menu)
  * [Options Menu Commands](#options-menu)
  * [Network Menu Commands](#network-menu)
  * [Help Menu Commands](#help-menu)
* FAQ
  * [Where can I find my IP address](#how-to-get-my-ip-address)

For more info about this program, contact me by e-mail at:
[crayon1@rocketmail.com](crayon1@rocketmail.com)

Copyright © 2001-2023 Crayon Application

## RPS Online

### Description

RPS Online is game for Windows that let you play Rock Paper Scissors over the Internet or LAN and versus the computer.

### Installation

All the files must be in the same directory.

The AutoInstall program usually but them in `C:\Program Files\RPS Online`

### How to Play

There are two modes:

1. VS the Computer
2. VS a Real opponent

#### VS the Computer

Simply click one of the three choices (rock, paper, scissors) and the game start automatically.

#### VS a Real opponent

You must connect to opponent first, go in the **Network** menu and click on **Connect to opponent...** in the text box enter the IP address of your opponent. For more information on IP address go to see the FAQ section. Once you are connected click one of the three choices (rock, paper, scissors) and the game start automatically. In two players mode you have to wait for your opponent to play between each throw. You could also use the chat to talk with your opponent.

For more information, see the Menu Commands:

* [Game Menu Commands](#game-menu)
* [Options Menu Commands](#options-menu)
* [Network Menu Commands](#network-menu)
* [Help Menu Commands](#help-menu)

### Disclaimer

This program is shareware and as such it may be freely distributed and copied, as long as it is not modified in any way, and no fee is charged.

This program is provided with no warranties expressed or implied. The author will not be held responsible by the use of this program.

Have fun!!!

![RPS Online](RPS.png?raw=true)

## How do I play Rock paper scissors (The Rules)

Rock Paper Scissors is a game for two players typically played using the players' hands. The two players each make a fist with one hand and hold the other open, palm upward. Together, they tap their fists in their open palms once, twice, and on the third time form one of three items: a rock (by keeping the hand in a fist), a sheet of paper (by holding the hand flat, palm down), or a pair of scissors (by extending the first two fingers and holding them apart).

The winner of that round depends on the items formed. If the same item is formed, it's a tie. If a rock and scissors are formed, the rock wins, because a rock can smash scissors. If scissors and paper are formed, the scissors win, because scissors can cut paper. If paper and a rock are formed, the paper wins, because a sheet of paper can cover a rock. After one round is completed, another is begun. Play continues until one player reaches a predetermined score, or whenever the players' boredom is alleviated. (Often this game is played to pass the time while waiting in line for something, or while on a long road trip.)

## Game menu

**New**: Start a new game.

**Exit**: Quits the program.

## Options menu

**Sound**: Toggle sound on/off.

**Music**: Toggle music on/off.

## Network menu

**Connect to Opponent**: Connect to Internet or LAN to play versus another player.

**Disconnect**: Close the connection.

## Help menu

**Online Help**: Opens the RPS Online Help (but you’ve already figured out that much). Select a topic from the Contents list.

**About...**: This item brings up a dialog which gives information about RPS Online.

## Network Play Concepts

Instead of playing against the computer, RPS Online allows you to play against another person. This way, every move you do is sent to the computer of your opponent and vice versa. The location of your opponent does not matter: (s)he can be your neighbor or someone halfway across the world.

### Chat

A chat is available when a connection is established. Now you can type messages to your opponent to compliment him/her with a victory, or to protest.

There are two ways to play with another person: [over a LAN](#playing-over-a-lan), or [over the Internet](#playing-over-internet).

### TCP/IP

RPS Online uses the TCP/IP protocol. This protocol lets your computer talk to the computer of your opponent. It is used for the Internet, but you can also use it in a LAN.

[Learn where to get your IP address](#how-to-get-my-ip-address)

## Playing over a LAN

### What you need to play

In order to play RPS Online over a LAN the following conditions must be fulfilled:

* Your computer has a network card
* You have correctly installed TCP/IP support for this network card
* Both computers are connected to the same Local Area Network (LAN)

### IP Numbers

Please note that not all IP numbers will work in a LAN.
The following standard IP number ranges should be used for LAN play:

* 192.168.0.x, with x between 0 and 255 (e.g. 192.168.0.0 and 192.168.0.1), and subnet mask 255.255.255.0.
* 172.16.x.x thru 172.31.x.x
* 10.x.x.x.

Only addresses in these ranges will be recognized as LAN addresses, all other IP addresses are seen as Internet addresses.

You need to know the IP number of your opponent in order to connect to him/her. Your opponent can tell you that by opening the **Network** / **Connect to Opponent** window. His IP number is shown there.

### Steps to follow

Follow these steps to start a network game:

1. On the **Network** menu, select **Connect to Opponent...**
2. Type the IP Number of your opponent in the edit box.
3. Click Connect.
4. Note: your opponent has to execute these steps as well.

A connection should now be established within a few seconds.

## Playing over Internet

### What you need to play

In order to play RPS Online over the Internet the following conditions must be fulfilled:

* Your computer has a modem, ISDN line or cable modem
* You have TCP/IP support installed for this device
* You have an Internet account with an Internet Service Provider

You need to know the IP number of your opponent in order to connect to him/her.

### Steps to follow

Follow these steps to start a network game:

1. Connect to the Internet
2. On the **Network** menu, select **Connect to Opponent...**
3. Type the IP number of your opponent in the edit box.
4. Click Connect.
5. Note: your opponent has to execute these steps as well.

A connection will now be established; this may take a few seconds.

## How to get my IP address

**If you don't know the IP address** that your ISP temporarily assigns to you, you can find it with the **winipcfg** command in Windows 95/98.

1. Click the Start button, and then click Run.
2. Type the following line in the Open box, and then click OK: winipcfg
3. A new window should open

![IP Configuration](WinIPCfg_Flou.png?raw=true)

Your current TCP/IP settings are displayed.

NOTE: The Winipcfg display is not updated dynamically.
To view changes, quit Winipcfg and then run it again.

If you are using Windows NT, use the **ipconfig** command.
