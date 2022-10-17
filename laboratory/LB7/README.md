<p align="left">
  <img src="../../.img/teclogo.png">
</p>

# **LB7. GPIO: 16x2 Liquid Crystal Display**

## **OBJECTIVES**
In this laboratory you will write code to drive a two-line, 16 character per line, liquid crystal display. You will start by programming a ready-to-go hex file to test the proper fuctioning of the LCD on your expansion board. Then, you will develop the C driver for your display and display the student numbers of each team member. Finally, you will integrate the LCD driver and the keypad driver you developed in a previous laboratory to create a calculator project. 

* Develop a driver for a 16x2 LCD display 
* Test the LCD on your expansion board by displaying a dummy message
* Develop a calculator firmware using the LCD and the 4x4 matrix keypad

## **INTRODUCTION**
The liquid crystal display incorporates an integrated circuit (HD44780) that processes the information received from the host (in our case, the PIC18F57Q43). The HD44780 processes both commands and characters and the processing mode (between commands or characters) is selected through the __Register Select__, `RS` input of the LCD. While in command mode (i.e., `RS=0`) the HD44780 can execute instructions such as _Clear Display_, _Return Home_, and some others. The full list of commands can be found on page 24 of the [HD44778 datasheet](../../datasheets/HD44780U.pdf). Whereas in character mode (i.e., `RS=1`) the information received should be an ASCII-coded character that is then displayed. The characteres that can be displayed are listed on pages 17 and 18 of the datasheet. Both commands and characters are transfered in parallel through an 8-bit __Data__, `DA[7:0]` port. The __Enable__, `E` signal is used to enable/disable the display to receive/send commands and characters through the Data port. On your expansion board, the 8-bit DATA port of the LCD display is wired to PORT `RD[7:0]` of the microcontroller, the Register Select is connected to `RE0`, and the Enable is connected to `RE1`. An additional line `Read/Write` is available; however, we will only use the `Write` mode, thus the line is hardwired to ground. 

The device has 2 lines and 16 characters per line. The LCD pinout is shown below:

<div align="center">

Pin number | Symbol | Level | I/O | Function
:---: | :---: | :---: | :---: | :---: 
1 | V<sub>SS</sub> | - | - | Power supply (GND)
2 | V<sub>CC</sub> | - | - | Power supply (+5V)
3 | V<sub>EE</sub> | - | - | Contrast adjustment
4 | RS  | 0/1 | I | 0 = Instruction input, 1 = Data input
5 | R/W | 0/1 | I | 0 = Write to LCD, 1 = Read from LCD
6 | E   | 1, 1→0 | I | Enable
7  | D0  | 0/1 | I/O | Databus line 0 (LSB)
8  | D1  | 0/1 | I/O | Databus line 1 
9  | D2  | 0/1 | I/O | Databus line 2
10 | D3  | 0/1 | I/O | Databus line 3
11 | D4  | 0/1 | I/O | Databus line 4
12 | D5  | 0/1 | I/O | Databus line 5
13 | D6  | 0/1 | I/O | Databus line 6
14 | D7  | 0/1 | I/O | Databus line 7
</div>

The LCD can be configured to drive the data bus either in a 4-bit mode or in an 8-bit mode. Either mode must be selected by the user in the initialization chain of the controller. If a 4-bit data bus is used, the LCD will require a total of 7 data lines (3 control lines + 4 data bus lines). Whereas the 8-bit data bus is chosen, the LCD requires 11 lines (3 control lines + 8 data bus lines). The three control lines are referred to as __E__, __RS__ and __R/W__. In this lab we will work with the 8-bit mode only.

The HD44780 controller has two different memories that are used to perform any task on the LCD: the Instruction Register (IR) to store instructions, and the Data Register (DR) to store characters to display. To carry out an operation on the LCD, we first need to switch between these two registers to either send a command that will be interpreted by the controller (through IR), or to display a character on the screen, which is loaded from the data register (DR). To switch between IR and DR we just assign the proper value to Register Select: **RS = 0 for IR, and RS = 1 to for DR**. Once the proper register has been chosen, we can proceed sending information through the DATA port. The control lines are the following: 

1. The __E__ line is the __Enable__. This control line is used to tell the LCD that you are sending data. In this case, your program should first set this line high (_e.g._, `1`) and then set the other two control lines and/or set the data bus. Once the rest of lines are set, `E` must be set low again (`0`). The `1→0` transition tells the 44780 to take input data currently found on the other control lines and the data bus, and to treat it as a command.

2. The __RS__ line is the __Register Select__. When low (`0`), data is treated as a command or special instruction (such as clear screen, position cursor, etc.). However, when high (`1`), data sent is interpreted as text that should be displayed on the screen (_e.g._,, to display the letter `T` on the screen, you would set high __RS__.

3. The `R/W` line is the __Read/Write__ bit. When low, the information on the data bus is being written to the LCD. When high, the program is effectively querying (or reading) from the LCD. Only one instruction (`Get LCD status`) is a _read_ type command. All others are write commands, so `RW` will almost always be low.

### __Handling the *E* control line__

The __E__ line is used to tell the LCD to execute an instruction available on the data bus. It must be set high before an instruction and set low after the instruction. The __E__ line must be manipulated whether the instruction is a read/write or if is text/instruction.

Use this instruction to set `E` high:  
    
    LCD_E = 1;

Or this instruction to set `E` low:   
    
    LCD_E = 0;

__Programming hint:__ The LCD interprets and executes a command at the instant the **E** is set low, thus a negative transition must be programmed to execute an instruction. Moreover, the LCD requires an amount of time to execute an instruction after setting __E__ low. The amount of time required for instruction execution depends on the instruction and the speed of the crystal attached to the 44780’s oscillator input.

### __Moving along the lines and line break__

The 44780 contains a certain amount of memory assigned to the display. All of the written text is stored in this memory, and the 44780 subsequently reads this memory to display the text on the LCD itself. The first character in the upper left-hand corner is at address `00h`. The following character position (character 2 on the first line) has address `01h`, and so on. This addressing continues until reaching the 16th character on the first line, which has address `0Fh`. However, the first character of line 2 has address `40h`. This means that if we write a character to the last position of the first line and then write a character following it, the second character will not appear on the second line. This is because the second character will effectively be written to address `10h`, whereas the second line begins at address `40h`. In such a case, we need to send a command to the LCD that tells it to position the cursor on the second line. The `Set Cursor Position` instruction is `80h`. For this, we must add the address of the location where we wish to position the cursor, `80h + 40h = C0h`. Sending the command `C0h` to the LCD will position the cursor on the second line at the first character position.

### __LCD Initialization__
* As in the simulator, the LCD must be initialized and configured before displaying data. This is accomplished by sending a few initialization instructions to the LCD. The function `LCD_initialize()` sends initialization commands to the LCD and it must be executed before sending any other command or character to display: 

```c
void LCD_initialize(void){
        // LCD Initialization
    COMMAND_MODE;
    LATD = 0x38;        // 8-bit mode
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();    // Enable the data latch

    LATD = 0x02;        // Display home
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();    // Enable the data latch
            
    LATD = 0x0C;        // Display ON
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();    // Enable the data latch        

    LATD = 0x01;        // Clear display
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();    // Enable the data latch

    LATD = 0x80;        // Set display address
    LCD_EN_SetHigh();
    __delay_ms(2);
    LCD_EN_SetLow();    // Enable the data latch
    
    DATA_MODE;
}
```



## **PROCEDURE**
### __EXERCISE 1. PRACTICE WITH THE SIMULATOR__

 To practice to sending commands and displaying characters on an 16 x 2 LCD, use an online [LCD Simulator](https://people.ucalgary.ca/~smithmr/2015webs/encm511_15/15_Labs/SimulationForLab4/djlcdsim1/djlcdsim.html) to simulate data transfer to a virtual LCD screen. To use it, you have to introduce the command you wish to send to the LCD on the ``Logic Lab Station Switches``, either in binary or hexadecimal formats, and then send a pulse on the Enable, ``E(SW8)`` control signal for a few miliseconds (0 → 1 → 0). Below is shown an example for sending command ``0x38`` to the LCD, which sets it up for 8-bit mode, 2 lines and 5 x 8 dots per character (while IR is selected; i.e., `RS=0`). 

<p align="center">
  <img src="img/LCD_sim.gif">
</p>

On the **Tip Box** you can see the command description as well as the executed instruction confirmation once you pulse ``E`` signal. To check that you have sucessfully sent a command to the LCD, you should see a message such as ``On E going LOW, executed instruction was: Function set command : 8 bit mode ON, 2 lines, 5*8 font``, for the case of command ``0x38``, as shown below:

<p align="center">
  <img src="img/command_sent.png">
</p>

However, before you can send characters to display on the LCD, you have to initialize it with a chain of initialization commands (stored in IR). Introduce each command on the initialization chain shown below to the LCD simulator and fill out the description of the table above according to the description given in the Tip Box from the simulator.

| Order | Command (hex) | 8-bit binary code | Execution time | Description of command | 
| :---: | :---: | :---: | :---: | :--- |
| 1 | `` 0x38 `` | ``00111000`` | 37 &mu;s | 8-bit interface data length, 2 lines, 5 x 8 dots per character | 
| 2 | `` 0x02 `` | ``00000010`` | 37 &mu;s |  | 
| 3 | `` 0x0C `` | ``00001100`` | 37 &mu;s |  |
| 4 | `` 0x01 `` | ``00000001`` | 37 &mu;s |  | 
| 5 | `` 0x80 `` | ``10000000`` | 37 &mu;s |  | 
</p>

Once the LCD has been initialized, you can start sending characters to display. For this, it is imperative to switch to the Data Register (DR) where the characters are stored. Switch to DR by setting Register Select control signal (``RS(SW10)``) to 1. 

Type in the ASCII code of the caracter you want to display, either in hexadecimal format into the ``Hex:`` field, or in decimal format into the ``Dec:`` field. You can find the ASCII table available online on a wide variety of websites, such as [RapidTables](https://www.rapidtables.com/code/text/ascii-table.html). Note that to introduce a string of characters, you have to send one character at the time. 

<p align="center">
  <img src="img/LCD_sim_char.gif">
</p>

Use this process to set up the LCD using the commands of the initialization chain seen above, and display the student number of your team members. If you need to move to the second line for completion, use command ``0xC0 - Set DDRAM address to 0x40`` to move the cursor to the first position of the second line (See Figure 6 on the datasheet to see the address of each character).

### __EXERCISE 2: TEST YOUR LCD__
1. Download file [LCD_test.hex](LCD_test.hex) from this repository.  

2. Follow the same procedure that you followed on LB4 to program an `.hex` using MPLAB IPE, but this time choose PIC18F57Q43 instead of the PIC18F45K50. 

3. To to verify the proper functioning of your LCD, you must see the message shown below after a resetting your microcontroller:

<p align="center">
  <img width="300" src="img/msg1.png">
</p>

4. Create a new project in the MPLAB X IDE for the Curiosity Nano board (PIC18F57Q43 &mu;C). and write a program that displays the student number for each of the team members. 

### __EXERCISE 3: 8-BIT CALCULATOR__
1. Create a new project in the MPLAB X IDE for the Curiosity Nano board (PIC18F57Q43 &mu;C).

2. Your keypad configuration will follow the layout shown below:
<div align="center">

<img width="200" src="img/keypad.png">
</div>

3. Create a calculator program that has the following features:
  
  * The program should take an arithmetic operator (__+, -, *, /__) and two operands from the 4x4 matrix keypad to carry out the corresponding calculation. The operator and operands should be shown on the LCD display.

<div align="center">
<img src="img/calc01.png">
</div>

  * When the user presses the __*__ from the keypad, the display executes the operation and writes the result from the calculation on the second line:

<div align="center">
<img src="img/calc02.png">
</div>

4. To carry out a new calculation, the user must press __#__. This action must clear the display an return the cursor home. Then, a new calculation can be entered.

5. The range of the operands is between 0 and 9. Also, the result can only be a positive and integer number.

6. Table below shows the mapping of the keypad symbols with the calculator implementation.

<div align="center">

Kaypad symbol | Arithmetic representation
:---: | :---:
0-9 | 0-9
A  |  +
B  |  -
C  |  *
D  |  /
\# | Clear display
\*  | Calculate
</div>

## __DELIVERABLES__
1. __[60%] Demostrative Video__

    Record a demostrative video (_5 minutes maximum_) showing exercises 1, 2 and 3 of this lab. It is mandatory that each team member explains one of the exercises. 

    **EXERCISE 1**
    1. Show the description of each command of the initialization chain
    2. Show the student numbers of each teammate displayed on the simulator

    **EXERCISE 2**
    1. Show the display on your expansion board with the dummy message to verify the correct functioning of the display. 
    2. Show the display on your expansion board now with the student numbers of the team members. 

    **EXERCISE 3**
    1. Execute three different arithmetic operations with your calculator. Show the complete procedure, from entering operands and operation, displaying the result and clearing the display for a new operation.

    Your video must be uploaded to your favorite video platform (YouTube, TikTok, Instagram, etc.) and you will only have to submitt the link to it the corresponding Canvas activity. __Make sure to set your video as Private, so only people with the link to it can watch it.__

2. __[40%] MPLAB X Projects__ 
 
  * Push your __two MPLAB project folders__ on a GitHub repository, corresponding to exercise 2 and exercise 3, respectively.
  * Your source code must be commented to explain what each line does so it can be easily understood by others.
  * __Do not compress the project folder__. You must directly push the full project folder and files in their original format using Git.
  * Share the link to your LB7 repository on the comments section of your video post page. Consider that on Canvas it will only be allowed one external link entry, thus no other way of reporting your work is possible. Make sure to set your video as Private, so only people with the link to it can watch it.

The due date for LB7 is __Monday, October 17__. Submit your solution:
<div align="center">

[![Generic badge](https://img.shields.io/badge/LB7-Click_here_to_submit-blue.svg?style=flat&logo=appveyor)](https://www.digikey.com.mx/es/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices)

</div>

