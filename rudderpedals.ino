/*
 *  @author     James Radko
 *  @license    MIT - Copyright (c) 2021 James Radko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *  Sketch:      FlightPedals
 *  Description:  Using XInput, reads a potentiometer and converts a 10 bit ADC reading
 *                to a 16 bit joystick value, which is then sent via XInput to
 *                Microsoft Flight Simulator 2020, for use as rudder pedals
 */

// libraries
#include <XInput.h>
/*
 * 
   _____ ____  _   _ ______ _____ _____ 
  / ____/ __ \| \ | |  ____|_   _/ ____|
 | |   | |  | |  \| | |__    | || |  __ 
 | |   | |  | | . ` |  __|   | || | |_ |
 | |___| |__| | |\  | |     _| || |__| |
  \_____\____/|_| \_|_|    |_____\_____|

 */

// define pin for potentiometer - A3 is a wildass guess and if it's not wrong I'm angy
int potPin = A3;
// define minimum voltage
float minVolt = 1.71;
// define maximum voltage
float maxVolt = 2.35;
// define voltage in, or reference voltage
float voltIn = 5.05;
// Do some math to determine 10 bit values expected from potentiometer
int minPot = (minVolt / voltIn) * 1023;
int maxPot = (maxVolt / voltIn) * 1023;


/*
 *  
 __ _             _    __  __ _____                   _   
/ _\ |_ __ _ _ __| |_  \ \/ / \_   \_ __  _ __  _   _| |_ 
\ \| __/ _` | '__| __|  \  /   / /\/ '_ \| '_ \| | | | __|
_\ \ || (_| | |  | |_   /  \/\/ /_ | | | | |_) | |_| | |_ 
\__/\__\__,_|_|   \__| /_/\_\____/ |_| |_| .__/ \__,_|\__|
                                         |_|              
 */

void setup() {
	XInput.begin();

}

/*
|\  /|    '       |            
| \/ |/~~|||/~\   |  /~\/~\|~~\
|    |\__|||   |  |__\_/\_/|__/
                           |   
 */

void loop() {
  // Read the potentiometer value
  int rawPot = analogRead(potPin);
  // Convert this 10 bit reading to a 16 bit value, on the range calculated from voltages
  int pot = map(rawPot, minPot, maxPot, -32767, 32767);
  /* prevent the code from trying to send a value that is impossible.
     No margin of error is needed since we're using this, it will make
     sure that if the value is lower than the minimum, it sends the minimum
     and likewise over max will send max. It's a super helpful function.
  */
  pot = constrain(pot, -32767, 32767);
  // Set the value on the left joystick, x axis. This can be altered obviously.
  XInput.setJoystick(JOY_LEFT, pot, 0);
  // Send the updated position to the computer.
  XInput.send();
  // delay for 10 milliseconds because idk, it felt proper.
  delay(10);
  // loop again!! :D
  
  
}
/*
 __   __        ___ 
|  \ /  \ |\ | |__  
|__/ \__/ | \| |___ 

`                                                                                                             ``
                                                                                                                
                                                                                                                
`                                                                                                             ``
                                                                                                              ``
                                                                                                                
                                                                                                                
`                                                                                                             ``
                                                                                                                
                                                                                                                
                                           .:;;;,`                                                            ``
                                        `;#zzzzzzz*,               `..`                                       ``
                                       ,#zzzzzzzzzzz+,         .;+zzzzzz#i,                                     
                                     `;zzzzzzzzzzzzzzz+.    `:+zzzzzzzzzzzz+,                                 ``
                                     *zzzzzzzzzzzzzzzzzz:  :#zzzzzzzzzzzzzzzz:                                ``
                                    *zzzzzzzzzzzzzzzzzzzz;izzzzzzzzzzzzzzzzzzz.                                 
                                   izzzzzzzzzzzzznnzzzzzzz:zzzzzzzzzzzzzzzzzzz*                               ``
                                  :zzzzzzzzzznxxxnnnxxnzzz#;zzzzzzzzzzzzzzzzzzz.                              ``
                                 .zzzzzzzzznxzzzzzzzzznxnzz:zzzzzzzzzzzzzzzzzzzi                                
                                 +zzzzzzznnzzzzzzzzzzzzznxz**zzzzzzzzz+++*++++##                              ``
                                :zzzzzznnzzzzzzzzzzzzzzzzzx#izz+*;:.`.,:i*+++*i;`                             ``
                                +zzzzznnzzzzzzzzzzzzzzzzzznn;z#*#zzzzz#+**i;;;;;.                               
`                              .zzzzzzzzzzzzzzzzzzzzzzzzzzzn;zzzzzzzzzzzzzzzzzzz#i,                           ``
                               izzzzzzzzzzzzzzzzzzzzz#*i;i;i;zzzzzzzzzzzzzzzzzzzzzz*.                         ``
                               #zzzzzzzzzzzzzzzzzz#i;i+#zzz#,+zzzzzzzzzzzzzzzzzzz*;ii:`                         
`                             .zzzzzzzzzzzzzzzzz#;*zzzzzzzzzz:zzzzzzzzzzzzzzzz#i;+zzzz#.                      ``
                            `:izzzzzzzzzzzzzzzziizzz+i;iii;;**izzzzzzzzzzzzz#;iz+;;;;;;,                      ``
                          ,*z*#zzzzzzzzzzzzzz+;+z#i;*zzzzzzz+;.zzzzzzzzzzz+;iz*;*zzzzzzzi`                      
`                        izzz;zzzzzzzzzzzzz*;*z*;;i;;i;;;*#zzz#;*zzzzzzz+;*z*;+zzzz#i,..:;`                   ``
                        izzzzizzzzzzzzz#iii+#i;*;i+*;:,,,.`.:i#z*;zzz#i;+z*;+zzzz+:`                          ``
                       ,zzzz#*zzzzzzzzzzzz+;i#;;i,          `,;iz**+i*zz*;#zzz#i.                               
`                      #zzzz*#zzzzzzzzz#ii+z#:;`              .*;*zzzz*;#zz#i,        .,                      ``
                      ,zzzzz+zzzzzzzzzzzzzz#,.                  :*;z*;+z#i,          ;@@*                     ``
                      +zzzzzzzzzzzzzzzzzzzz,             `#z.    .i;*i:`             z#++                       
`                    .zzzzzzzzzzzzzzzzzzzzi              z#nn     `.                 ;@W:                     ``
                     *zzzzzzzzzzzzzzzzzzzz+`             x#zM                              .                  ``
                    .zzzzzzzzzzzzzzzzzzzzzz#:`           ,xx:   `i#..                 `,;*#*                    
`                   izzzzzzzzzzzzzzzzzzzzzzzz#:.             `,*zz*izz+*i::,....,,:i*#zzz*.                   ``
                   `zzzznznzzzzzzzzzzzzzzzzzzzzz#*;,.`   `,;+zzzz;;nnzzzzzzzzzzzzzzzzzzz:                     ``
                   :zzzznnnzzzzzzzzzzzzzzzzz+i#zzzzzzzz##zzzzzz#:*nnzzzzzzzzzzzzzzzzzz*.                        
`                  #zzznzzxnzzzzzzzzzzzzzzzzz#i:;i+zzzzzzzzzz+;:#nzzzzzzzzzzzzzzzzzz+,                        ``
                  ,zzzzxzznzzzzzzzzzzzzzzzzzzzzzz+*;;;i***i;:i#nzzzzzi;*#zzzzzzz#+i,                            
                  *zzzxznxnnzzzzzzzzzzzzzzzzzzzzzzzzzz#+++#zznnznnzzzzz+i:;;;;;;i+z;                            
`                `zzzxzxzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzznnnnznnzzzzzzzzzz;+zzzzzzzz,                         ``
                 ,zznzznzzzzzzzzzzzzzz#i;;;;;i*#zzznnnxxxnzznnzzzzzzzzzzzzzzzzzzzzz+:,                          
                 izzzzzzzzzzzzzzzzzz*:;+z#zz#+*;::i+#zzzzzzznzzzzzzzzzzzzzzzzzzz#i:i##`                         
`                +zzzzzzzzzzzzzzzzz:i#############+*;;;;*#znzzzzzzzzzzzzzzzzz+i:;+####:                       ``
                 #zzzzzzzzzzzzzzz+:###################z#*i;;;;*+#######+*i;;;*########,                         
                `zzzzzzzzzzzzzzz+:########+++###############z#*iiiiiiii**+z##########:    ;.                    
`               .zzzzzzzzzzzzzz+:######;.`    `,;*#################################+.     .                   ``
                ,zzzzzzzzzzzzzz:####+,             `,;*#z#####################z#*i,                             
                :zzzzzzzzzzzzz;+###*`                   .:;*+##zzz###+++**i;:.`                                 
`               ;zzzzzzzzzzzz+;###+`                          `````                                           ``
                izzzzzzzzzzzz:####.                                                           .i,               
                izzzzzzzzzzz#i###i                                                  `:;;,`    ..`               
`               izzzzzzzzzzz;####`                                                .i#####+;.                  ``
                ;zzzzzzznznz;###i                   `.:;;;:.                     :##########;                   
                :zzzzzznnnz+*##z,                 `:+#######+;.                .*####**######`                  
`               .zzzzznnnzni####`                .*############*:`           .;+##+;. `.i###*                 ``
                `zzzzzzznnz;###*                :######++########+*;,`  `.,;*###+:`      `,.`                   
                 +zzzzzzzzz;###;               ,####+;`   .:i+#########+######+;`                               
`                izzzzzzzzz;###,              `+###+.        `,i+###########+:`                               ``
                 ,zzzzzzzzz;###,              :####,             .:*#####+;.                                    
                 `zzzzzzzz#;###.              +###*                 `,,,.        ,:                             
`                 +zzzzzzz#;###,             .####;                              `.                           ``
                  ;zzzzzzzz;###:             ,####,                                                             
                  .zzzzzzzz;###*             :####.                                                             
`                  +zzzzzzz;####.            ,i*+#,                                                           ``
                   ,zzzzzzz*+###+`       `,;*+++*i,                                                             
                    +zzzzzzz;###z+,`  .:*#########z#i,`                                                         
`                   .#zzzzzzi+#########################+i:.`         ``..,,::;;,                              ``
                  :##,+zzzzzz:+#############+***+#########z##+++++#####zz#######,                               
                `*zzzz;;zzzzzz;i########+i::i***;,:*###########################i`                               
`              `zzzzzzz+;;#zzzz+:;i*i;;;i+zzzzzznz#*::i+###########z###+*ii;:,`                               ``
               `nzzzzzzzz#i;*zzzz##++#zzzzzzzzzxnzzzzz#;:;;;:;;;;;;;;;;i+*,                                     
               `zzzzzzzzzzzz#i;i+zzzzzzzzzzzzznzxzznxxxzzzzzznnnzzzzzzzi,               :`                      
               `zzzzzzzzzzzzzzzz+**#zzzzzzzzznnznnxnzxzzzzzzzzzzzzz#i,`                .z`  ,*                ``
               `zzzzzzzzzzzzzzzzzzzzzzzzzzzznnzzxnzznnzzzzzzzz#*;;;`                  `#z`,*z;                 `
               `zzzzzzzzzzzzzzzzzzzzzzzzzzzxnzzzzzzzxzzzzz*i;:;*#z*                  .#zz#zz#                   
               `zzzzzzzzzzzzzzzzzzzzzzzzznxzzzzzzzzxnzzzzzzzzzzzzzz:                :zzzzzzz:                 ``
               `zzzzzzzzzzzzzzzzzzzzzzzzxnzzzzzzzzznnzzzzzzzzzzzzzzz*.            .+zzzzzzzz+.                 `
               `zzzzzzzzzzzzzzzzzzzzznxnzzzzzzzzzzzzzxnzzzzzzzzzzzzzzz:         .izzzzzzzzzzzz*`                
               `zzzzzzzzzzzzzzzzzzzznnzzzzzzzzzzzzzzznnzzzzzzzzzzzzzzzz+`     .*zzzzzzzzzzzzzz+,              ``
               `zzzzzzzzzzzzzzzzznnnzzzzzzzzzzzzzxnxxzzzzzzzzzzzzzzzzzzz#` `:+zzzzzzzzzzzz*:.`                 `
               `zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzxxzzzzzzzzzzzzzzzzzzzzzzzz*:zzzzzzzzzzzzzi.                      
               `zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzxzzzzzzzzzzzzzzzzzzzzzzzzzzz;#zzzzzzzzzzz*                      ``
               `nzzzzzzzzzzzzzzzzzzzzzzzzzzzznnzzzzzzzzzzzzzzzzzzzzzzzzzzzz;zzzzzzzzzzz.                       `
               `*****************************+*****************************,**********:                         
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                     ,++++**i:    *+++++++``+++++++i :+++++++: i+++++++.`+++++++* ,+++++++:                     
                     *########M.  W#######.,#######M *#######+ x#######:.#######W *########                   ``
                     *#########n  W#######.,#######M *#######+ x#######:.#######W *########                    `
                     *####MW####` W#######.,#######M *#######+ x#######:.#######W *########                     
                     *####i:####: W###W,,, ,####n,,. *####*,,. x###@:,,`.####n,,, *####+,,.                   ``
                     *####i,####: W###W    ,####z    *####;    x###@`   .####z    *####i                       `
                     *####i,####: W###W    ,####z    *####;    x###@`   .####z    *####i                        
                     *####+#####. W###@::: ,####n::, *####+::. x###@;:: .####x::, *#####::.                   ``
                     *#########z  W######W ,######## *#######; x######@`.#######z *#######i                    `
                     *#######@+`  W######W ,######## *#######; x######@`.#######z *#######i                     
                     *####xW###n  W######W ,######## *#######; x######@`.#######z *#######i                   ``
                     *####i:####. W###W::, ,####n::. *####*::` x###@::: .####x::, *####+::`                    `
                     *####i,####: W###W    ,####z    *####;    x###@`   .####z    *####i                        
                     *####i,####: W###W    ,####z    *####;    x###@`   .####z    *####i                      ``
                     *####i,####: W###W    ,####z    *####;    x###@`   .####z    *####i                       `
                     *####i,####: W###@nnn;,####Wnnn.*####xnn# x####nnni.####Wnnn.*####Mnnz                     
                     *####i,####: W#######*,########.*#######M x#######+.########,*#######W                   ``
                     *####i,####: W#######*,########.*#######M x#######+.########,*#######W                    `
                     *####i,####: M#######*,########.*#######M x#######+.########,i#######W                     
                      ````  ````  ````````` ```````` ````````` ````````` ```````` `````````                   ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `
                                                                                                                
                                                                                                              ``
                                                                                                               `


                    
 */
