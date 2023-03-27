#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
int main() {
    // communicate via registry 
    //DDRx Data Direction Register for port x
    //PINx Read from Port x
    //PORTx Write to Port x

    /*
    Data Direction Register 
The data direction register (DDR) is most likely the first register that you configure since the DDR register determines if pins on a specific port are inputs or outputs. The DDR register is 8 bits long and each bit corresponds to a pin on that I/O port. 

For example, the first bit (bit 0) of DDRB will determine if PB0 is an input or output, while the last bit (bit 7) will determine if PB7 is an input or output. 

In PIC devices, a value of 1 is used for inputs and a value of 0 is used for outputs, but for AVR devices the reverse is true; 1 refers to an output while 0 refers to an input. So lets say if we want to configure all the pins on PORT B as outputs, we would simply use the following code:

DDRB = 0xFF;
or 
DDRB = 0b11111111;

The first example uses hexadecimal, whereas the second uses binary. While it is common practice to use hexadecimal, the binary version can make it more clear which bits in the port are being used as an input or output. If we wanted to turn all the pins on PORT B into input pins then we could use...

DDRB = 0x00;
or
DDRB = 0b00000000;

How about something more complex? Lets say you want the first two pins to be outputs (PB0 and PB1), and the rest of the pins to be inputs. The following code would do the trick:

DDRB = 0x03;
or
DDRB = 0b00000011;
    */
    DDRB = 0xff;
/*
PINx Register
With our DDR register sorted out, its time to learn how to read digital values into our microcontroller from the real world. This is done using the register PINx where x is the register being read from. Reading from a port is rather easy as shown in the following code example:

dataValue = PINB;

When this is executed, all the pins on PORT B are read into dataValue, and each bit in dataValue will now correspond to the digital levels on each pin at the time the reading was taken. While this is can be useful, we may sometimes want to test individual bits instead of all the bits at the same time. In the PIC, the .bits member could be used to access individual bits, but this is not the case for AVR devices. Instead, accessing individual bits involves a bit of manipulation (pardon the pun), including the use of logical AND, OR, and XOR.

To test if a bit is on (logical 1), the two following statements can be used. These functions perform a logical AND with both the PIN register and the bit (represented as an 8-bit number). If the result is zero, the if statement will not be executed because if statements only execute when the condition is non-zero. The first statement uses a binary value to represent which bit to test, whereas the second statement uses a logical shift instruction to create a bit mask, which represents the bit to be tested. The logical shift version is arguably more readable and thus easier to understand. However, the instruction may take longer to execute than the first (depending on optimization).

if ( PINB & (0b00000001))
or
if ( PINB & (1 << n)) where n = bit under test (0 - 7)

Testing for a logical 0 is easily done by using the negation operator before the main test (!)

if ( !(PINB & (0b00000001)) )
or
if ( !(PINB & (1 << n)) ) where n = bit under test (0 â€“ 7)

PORTx Register
Now that we can read from both entire ports and individual pins, how do we write to ports and individual pins? This is where the PORTx register comes in. Writing to this register (where x represents the port being written to) will result in output pins either being on or off. Remember, the physical output pins will only have digital levels corresponding to the PORTx register IF AND ONLY IF the corresponding DDR bits are set as outputs!

Writing values to ports is very easy:

PORTB = 0xFF;

or
PORTB = 0b11111111;

But what about individual bits? This again is done using bitwise operators and setting/clearing bits is a little more involved. This is because we need to preserve the value of the other bits in the PORT register, otherwise, they may be changed, which could result in unexpected behavior if they are connected to external devices such as LEDs, displays, ICs, etc.

To turn a specific bit on we can use the OR logical operator:

PORTB = PORTB | (0b00000001); Turns on bit 0
or
PORTB = PORTB | (1 << n); Turns on bit n where n = 0 to 7

To turn a specific bit off we use both the AND operator and the NOT operator (~):

PORTB = PORTB & ~(0b00000001); Turns off bit 0
or
PORTB = PORTB & ~(1 << n); Turns off bit n where n = 0 to 7

To toggle a bit (so that it is the opposite to what it used to be) we can use the XOR operator:

PORTB = PORTB ^ (0b00000001); Toggles bit 0
or
PORTB = PORTB ^ (1 << n); Toggles bit n where n = 0 to 7
*/
    PORTB = 0xFF;
    while(1) {
        //toggle pin 1 on B registry
        PORTB |= (1 << 1);               
        _delay_ms(200); 
        PORTB &= ~(1 << 1);     
        _delay_ms(100); 
    }
}