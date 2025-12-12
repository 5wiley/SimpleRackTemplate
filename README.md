Original project structure by Infrasonic Audio

# Voltages

Eurorack = +/-5v at 0v, 10vpp, 1v/oct
Conversion of 3.6:10 (10 * 0.36) for Eurorack -> Daisy
Daisy = +/- 1.8v at 1.8v, 3.6vpp, 360mv/oct

A voltage divider could take Eurorack -> Daisy. To go Daisy -> Eurorack you'd have to subtract 1.8v then amplify by 2.78 (ish).