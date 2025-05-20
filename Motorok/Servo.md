Szervómotorok használata Arduino-val
Amikor egy projektben precíz mozgásvezérlésre van szükség, a szervómotor az egyik legjobb választás. Legyen szó robotkarokról, szenzor irányításról vagy egyszerű ajtómozgatásról – a szervómotorok gyorsak, pontosak és könnyen vezérelhetők Arduino-val.

🎯 Mi az a szervómotor?
A hobbiszintű szervómotor egy kis műanyag vagy fém doboz, amely precízen forgatható 0–180° között (egyes modellek akár 270°-ig is). Az alábbi főbb részekből áll:

DC motor – a forgómozgást végzi

Fogaskerék áttétel – lassítja a motor sebességét, növelve a nyomatékot

Kimeneti tengely (kar) – ide csatlakozik a mozgó elem (pl. kar)

Potméter – méri a tengely aktuális pozícióját

Vezérlő elektronika – összehasonlítja a kívánt és aktuális szöget

📷 Belső felépítés:
https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Internal-Structure-Illustration.png
Figure 1.1 – Szervómotor belső szerkezete

🔄 Hogyan működik?
A szervó egy zárt hurkú visszacsatolásos rendszer része. Az Arduino PWM jelet küld, a szervó ezt fogadja, és a beépített vezérlő beállítja a tengely pozícióját.

📷 Zárt hurkú rendszer blokkvázlata:
https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Servo-Motor-Closed-Loop-System-Block-Diagram.png
Figure 1.2 – A zárt visszacsatolásos rendszer vázlata

Ha a tényleges pozíció eltér a kívánttól, a vezérlő kiszámítja az eltérést (hibát), és a DC motort annak megfelelően vezérli.

⏱ PWM alapú vezérlés
A szervómotorok vezérlése PWM (Pulse Width Modulation) segítségével történik. A jel időtartama határozza meg a kívánt pozíciót:

kb. 1 ms – 0° (bal szél)

kb. 1.5 ms – 90° (középállás)

kb. 2 ms – 180° (jobb szél)

📷 Időzítési diagram:
https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Working-Timing-Diagram.png
Figure 1.3 – PWM időzítés szervómotorhoz

🔌 Szervómotor lábkiosztás
A legtöbb hobbiszintű szervó három vezetékes:

Szín	Funkció	Csatlakozás Arduino-n
Piros	Tápfeszültség	5V
Barna/fekete	Földelés	GND
Narancs/sárga	Jel (PWM)	pl. D9

📷 Lábkiosztás ábra:
https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Pinout.png
Figure 1.4 – Szervómotor lábkiosztása

🔧 Bekötés Arduino UNO-val
Példa az SG90 mikro szervómotor bekötésére:

📷 Bekötési ábra:
https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Connecting-Servo-Motor-to-Arduino-Uno-Sweep-Code.png
Figure 1.5 – Szervómotor csatlakoztatása Arduino UNO-hoz

Szervómotor	Arduino
Piros	5V
Barna	GND
Narancs	D9



When it comes to choosing the right motor for a project, the options can be overwhelming—stepper motors, DC motors, brushless motors, and more. Each type has its own strengths. But if you need precise control over movement, there’s one clear choice: the servo motor. Tell a servo motor where to point, and it will go there exactly! It’s as simple as that!

Servo motors first became popular in the Remote Control (RC) world, where they were used to control the steering of RC cars or the flaps on RC planes. Over time, they found their way into robotics, automation, and of course, the Arduino world.

In this guide, you’ll learn how a servo works, how to connect it to an Arduino, and how to control its position using simple Arduino code. Whether you’re building a robotic arm, an automated door, or just experimenting with motion control, this tutorial will help you get started.

Let’s dive in and get that servo moving!

## What is a Servo and what makes it precise?

Inside a typical hobby servo motor, you’ll find five main components working together: a DC motor, a gearbox, a servo horn, a potentiometer, and a control unit.

![Servo Motor Internal Structure Illustration](https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Internal-Structure-Illustration.png)**DC Motor**: This is the core component providing the rotational force. It’s similar to the hobby motors found in toys, but how it’s controlled makes all the difference. The DC motor connects to the output shaft through a series of gears.

**Gearbox**: The gearbox (a system of gears) plays a crucial role in increasing the motor’s torque and improving the precision of its movements. It reduces the speed of the motor but increases its strength.

**Servo Horn**: This is a plastic arm (or wheel) attached to the output shaft (the part that actually rotates). The servo horn gives you a place to attach whatever you want the servo to move – like the arm of a robot or the rudder on a model airplane.

**Potentiometer**: This is a variable resistor that acts as a position sensor. It’s connected directly to the output shaft. As the output shaft rotates, the potentiometer’s resistance changes. This tells the control unit exactly where the motor is positioned.

**Control Unit**: This is the “brain” of the servo motor. It receives signals from an external controller (like an Arduino), checks the potentiometer’s position, and controls the DC motor.

### Here’s how these parts work together:

The servo motor works using what’s called a “**closed-loop feedback system**“.

![servo motor closed loop system block diagram](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Servo-Motor-Closed-Loop-System-Block-Diagram.png)When you send a signal to the servo telling it to move to a specific position, the control unit receives this command.

The potentiometer is physically connected to the output shaft, so it always knows the current position of the servo. When the motor rotates, the output shaft turns, and so does the potentiometer. This rotation changes the potentiometer’s resistance, creating a voltage that directly corresponds to the current position of the output shaft (and thus the motor). This voltage serves as feedback to the control unit.

The control unit constantly compares this feedback voltage (representing the motor’s current position) with the desired position signal from the microcontroller.

If there’s a difference (an “error” signal) between the desired position and the current position, the control unit adjusts the power and direction of the DC motor to fix this difference.

As the motor moves, the potentiometer’s feedback voltage changes, continuously updating the control unit about the motor’s current position.

Once the motor reaches the desired position you wanted, the error signal becomes zero, and the control unit stops the motor.

This whole process happens very quickly and repeatedly. The servo is always checking its position and making tiny adjustments to stay exactly where it should be. This is why servos are so good at holding their position, even when external forces try to move them.

This entire system is called a “**servomechanism**” or simply a “**servo**.” It works as a closed-loop control system, using negative feedback to precisely control the motor’s speed and direction, allowing it to reach and maintain a specific position.

## How Do Servo Motors Work?

Hobby servo motors are controlled using a clever technique called **Pulse Width Modulation (PWM)**.

PWM works by sending a series of electrical pulses to the servo at regular intervals. For most hobby servos, these pulses are sent about 50 times per second (50 Hz). This means a new pulse arrives every 20 ms (1/50th of a second).

What really matters for controlling the servo’s position isn’t how often we send pulses, but how long each pulse lasts. This duration is called the “**pulse width**” (or “**duty cycle**” of the PWM signal, if you prefer the technical term).

![Servo Motor Working Timing Diagram](https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Working-Timing-Diagram.png)* A short pulse around 1 ms or less tells the servo to move to 0 degrees (all the way to one side)
* A medium pulse of about 1.5 ms positions the servo at 90 degrees (right in the middle)
* A longer pulse of around 2 ms moves the servo to 180 degrees (all the way to the other side)
* For positions in between, we use pulse widths that fall between these values. For example, if we want the servo at the 45-degree position (halfway between 0 and 90 degrees), we would use a pulse that’s about 1.25 ms long.

This means we can precisely control exactly where the servo points by carefully controlling how long each pulse lasts. The servo’s control unit receives these pulses, measures their width, and moves the motor to the corresponding position.

The animation below can help you visualize how changes in pulse width correspond to different servo positions.

![Servo Motor Working Animation](https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Working-Animation.gif)**Not All Servos Are Exactly the Same**

It’s important to note that the exact pulse width range can vary slightly between different servo motor models. Some servos might use a range such as 0.5 ms for 0 degrees and 2.5 ms for 180 degrees.

This is why it’s always a good idea to check the datasheet that comes with your specific servo motor. The datasheet will tell you exactly what pulse widths to use for different positions with your particular servo.

## Servo Motor Pinout

Almost all hobby servos come with a standard three-pin, 0.1″-spaced connector. While the color coding of the wires may vary between brands, the pins are generally arranged in the same order.

Here’s a breakdown of the pinout:

![Servo Motor Pinout](https://lastminuteengineers.com/wp-content/uploads/arduino/Servo-Motor-Pinout.png) is the ground pin.

 pin supplies power to the servo motor. Most hobby servos need between 4.8V and 6V to operate properly. Providing the right voltage is important – too little and the servo won’t have enough strength, too much and you might damage it.

 receives the PWM (Pulse Width Modulation) signal from a microcontroller, which determines the servo’s position.

The color coding of the wires can vary between brands, but the power wire is almost always Red, making it easy to identify. The ground wire is typically black or brown, and the control wire is usually orange, yellow, or white.

## Wiring Servo Motor to Arduino UNO

Alright! Let’s connect a servo motor to an Arduino UNO and see how it works.

For this experiment, we’ll use an SG90 Micro Servo Motor. This small but powerful motor runs on 5V (can work between 4.8V to 6V DC) and can rotate up to 180 degrees—90 degrees in each direction.

It’s important to note that when the servo is sitting still, it only needs about 10mA of current. But when it’s moving, it needs much more—between 100mA and 250mA. This means that for most simple projects, we can power the servo directly from the Arduino’s 5V pin. But if your servo needs more than 250mA, you should use a separate power supply to avoid damaging your Arduino.

To connect the SG90 servo motor to the Arduino:

* Connect the red wire to the 5V pin on the Arduino.
* Connect the black or brown wire to the GND (ground) pin.
* Connect the orange or yellow wire to pin #9 on the Arduino. This pin is PWM-enabled, meaning it can send the Pulse Width Modulation (PWM) signal needed to control the servo’s movement.

Here’s a quick reference table for the pin connections:



| Servo Motor |  | Arduino |
| 5V |  | 5V |
| GND |  | GND |
| Control |  | 9 |

Please refer to the image below to see the proper wiring setup.

![connecting servo motor to arduino uno sweep code](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Connecting-Servo-Motor-to-Arduino-Uno-Sweep-Code.png)Once everything is connected, you’re ready to control the servo motor using Arduino code!

## Arduino Example 1 – Sweep

Let’s start by using one of the built-in examples from the Arduino IDE. Open the Examples menu, navigate to Servo, and select the Sweep sketch.

![servo sweep example](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Servo-sweep-example.png)Once the code is loaded, upload it to your Arduino board. If everything is set up correctly, you’ll see the servo motor’s shaft sweeping back and forth across 180 degrees.


```
#include 

 servoPin = ;
Servo servo;
 angle = ;  

 () {
  servo.(servoPin);
}

 () {

  
   (angle = ; angle < ; angle++) {
    servo.(angle);
    ();
  }

  
   (angle = ; angle > ; angle--) {
    servo.(angle);
    ();
  }
}
```
### Code Explanation:

Controlling a servo motor is actually pretty simple, thanks to the [Servo library](https://www.arduino.cc/en/reference/servo) that comes with Arduino. This library gives us easy commands to tell the servo exactly where we want it to move.

The first thing we do in our sketch is include this Servo library.


```
#include 
```
Next, we need to tell Arduino which pin our servo is connected to.


```
 servoPin = ;
```
Then, we create a servo object that we’ll use to control our motor.


```
Servo servo;
```
You can control up to eight servos this way. If you had two servos, for example, you would write:


```
Servo servo1;
Servo servo2;
```
We also need a variable called `angle` to keep track of where our servo is pointing.


```
 angle = ;
```
In the setup() function, we connect our servo object to the pin we chose earlier. This tells Arduino which pin should send signals to the servo.


```
servo.(servoPin);
```
Now, in the loop() function, we first move the servo from 0 degrees to 180 degrees. We use a `for` loop that increases the angle by one degree at a time. Each time through the loop, the command `servo.write(angle);` moves the servo to its new position. To keep things smooth, we add a small 15-millisecond pause after each movement.


```

 (angle = ; angle < ; angle++) {
  servo.(angle);
  ();
}
```
Once the servo reaches 180 degrees, we make it move back to 0 degrees. We do this with another `for` loop that decreases the angle one degree at a time until we get back to 0.


```

 (angle = ; angle > ; angle--) {
  servo.(angle);
  ();
}
```
After reaching 0 degrees, the whole process starts over again. This makes the servo continuously sweep back and forth between 0 and 180 degrees.

This example is a great way to see how we can control a servo with simple commands. Once you understand this, you can start changing the code to make your servo do different things, like stopping at certain angles or moving at different speeds.

## Arduino Example 2 – Controlling a Servo with a Potentiometer

Now that we’ve seen how to make a servo motor sweep back and forth automatically, let’s take it a step further by adding a potentiometer. This will allow us to manually control the position of the servo by simply turning a knob. This kind of setup is useful in many real-world applications, such as adjusting the direction of a sensor or controlling the movement of a robotic arm.

### Wiring

We’ll keep most of the connections from the previous example, but now we’re adding a 10KΩ potentiometer. The potentiometer has three pins. One pin should be connected to GND (ground), the other to 5V, and the middle pin (also called the wiper) should be connected to analog input A0 on the Arduino. This setup allows the Arduino to read how much the knob is turned and adjust the servo accordingly.

![connecting servo motor to arduino uno for potentiometer control](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Connecting-Servo-Motor-to-Arduino-Uno-For-Potentiometer-Control.png)### Arduino Code

This code is actually simpler than the Sweep example we worked on earlier.


```
#include 

 potPin = ;
 servoPin = ;
Servo servo;

 () {
  servo.(servoPin);
}

 () {
   reading = (potPin);
   angle = (reading, , , , );
  servo.(angle);
}
```
### Code Explanation

First, we create a new variable called `potPin`, which represents the analog pin (A0) where the potentiometer is connected. This allows us to read the position of the knob.


```
 potPin = ;
```
Now, inside the loop() function, the first thing we do is read the potentiometer’s current position using the `analogRead()` function. This function gives us a value between 0 and 1023, depending on how much the potentiometer is turned. When the knob is all the way to the left, the value will be 0. When it’s all the way to the right, the value will be 1023.


```
 reading = (potPin);
```
Since our servo can only move between 0 and 180 degrees, we need to convert the potentiometer’s reading into an appropriate servo angle. This is where the [map()](https://www.arduino.cc/reference/en/language/functions/math/map/) function comes in handy. The `map()` function takes a number from one range and converts it to another range. In this case, we convert the range 0-1023 into 0-180 so that the servo moves across its full range as we turn the potentiometer.


```
 angle = (reading, , , , );
```
After mapping the value, we use the `servo.write()` function to tell the servo to move to the calculated angle. This means that as you turn the potentiometer, the servo will follow along, rotating smoothly to match the knob’s position.


```
servo.(angle);
```
## Troubleshooting

Have you ever noticed your servo motor behaving weirdly when connected to your Arduino? Sometimes it might twitch, move incorrectly, or even cause your Arduino to restart. Don’t worry! This is actually a very common problem that many people face, and there are simple ways to fix it.

The main reason this happens is because servo motors are power-hungry devices. When a servo first starts moving, it can suddenly need up to 800 mA of electricity. This is a lot of power – much more than your Arduino can provide all at once. When the servo tries to draw this much power, it can cause the voltage to drop temporarily, which makes everything behave strangely.

There are two good ways to solve this problem.

### Solution 1: Add a Decoupling Capacitor

The first solution is to add a “decoupling capacitor” to your circuit. You’ll want to use an electrolytic capacitor with a value between 470µF and 1000µF. When you connect it, make sure to attach the longer lead to the 5V power and the shorter lead to GND.

![connecting servo motor with capacitor to arduino uno sweep code](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Connecting-Servo-Motor-with-Capacitor-to-Arduino-Uno-Sweep-Code.png)The capacitor works by storing extra electricity when it’s not needed and then releasing it quickly when the servo suddenly demands more power. Think of it like a small backup power bank that helps out during those moments when your servo needs an extra boost. This helps prevent those voltage drops that cause problems.

### Solution 2: Use a Separate Power Supply

If adding a capacitor doesn’t completely solve your problem, you can try the second solution, which is to use a separate power supply just for your servo motor. This is especially helpful if your servo needs more power than your Arduino can give, or if you’re using multiple servos at the same time.

For this separate power supply, you could use a pack of 4 AA batteries, a regulated 5V power adapter that plugs into the wall, or even a USB power bank that provides 5V output. The important thing is that this power source should handle the servo’s high power needs.

To connect everything properly, you’ll need to attach the servo’s red wire (the power wire) to the positive side of your external power source. Then connect the servo’s black or brown wire (the ground wire) to the negative or ground side of your power source. The servo’s yellow or orange wire (the signal wire) should still connect to one of the digital PWM pins on your Arduino, like pin 9, because the Arduino needs to send control signals to tell the servo how to move.

There’s one very important step you can’t forget: you must connect the ground (GND) of your external power supply to the ground (GND) of your Arduino. This creates a “common reference point” between the two circuits, which is necessary for everything to work together properly.

![powering servo motor with external power supply](https://lastminuteengineers.com/wp-content/uploads/arduino/v2/Powering-Servo-Motor-with-External-Power-Supply.png)With this setup, your Arduino still controls the servo by sending signals through the signal pin, but it no longer has to supply the power that makes the servo move. The external power source handles all the high power demands, allowing your servo to operate smoothly without causing problems for your Arduino.

