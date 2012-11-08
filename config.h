/*
  config.h - compile time configuration
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011-2012 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef config_h
#define config_h

// IMPORTANT: Any changes here requires a full re-compiling of the source code to propagate them.

#define BAUD_RATE 9600

// Define pin-assignments
#define STEPPING_DDR       DDRD
#define STEPPING_PORT      PORTD
#define X_STEP_BIT         2  // Uno Digital Pin 2
#define Y_STEP_BIT         3  // Uno Digital Pin 3
#define Z_STEP_BIT         4  // Uno Digital Pin 4
#define X_DIRECTION_BIT    5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT    6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT    7  // Uno Digital Pin 7
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
#define STEPPING_MASK (STEP_MASK | DIRECTION_MASK) // All stepping-related bits (step/direction)

#define STEPPERS_DISABLE_DDR    DDRB
#define STEPPERS_DISABLE_PORT   PORTB
#define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

#define LIMIT_DDR       DDRB
#define LIMIT_PIN       PINB
#define LIMIT_PORT      PORTB
#define X_LIMIT_BIT     1  // Uno Digital Pin 9
#define Y_LIMIT_BIT     2  // Uno Digital Pin 10
#define Z_LIMIT_BIT     3  // Uno Digital Pin 11
#define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

#define SPINDLE_ENABLE_DDR   DDRB
#define SPINDLE_ENABLE_PORT  PORTB
#define SPINDLE_ENABLE_BIT   4  // Uno Digital Pin 12

#define SPINDLE_DIRECTION_DDR   DDRB
#define SPINDLE_DIRECTION_PORT  PORTB
#define SPINDLE_DIRECTION_BIT   5  // Uno Digital Pin 13

#define COOLANT_FLOOD_DDR   DDRC
#define COOLANT_FLOOD_PORT  PORTC
#define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3

// #define ENABLE_M7  // Mist coolant disabled by default. Uncomment to enable.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#ifdef ENABLE_M7
  #define COOLANT_MIST_DDR   DDRC
  #define COOLANT_MIST_PORT  PORTC
  #define COOLANT_MIST_BIT   4 // Uno Analog Pin 4
#endif  

#define PINOUT_DDR       DDRC
#define PINOUT_PIN       PINC
#define PINOUT_PORT      PORTC
#define PIN_RESET        0  // Uno Analog Pin 0
#define PIN_FEED_HOLD    1  // Uno Analog Pin 1
#define PIN_CYCLE_START  2  // Uno Analog Pin 2
#define PINOUT_INT       PCIE1  // Pin change interrupt enable pin
#define PINOUT_INT_vect  PCINT1_vect
#define PINOUT_PCMSK     PCMSK1 // Pin change interrupt register
#define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))


// Default settings (used when resetting eeprom-settings)
// TODO: Begin to fill these out for various as-built machines, i.e. config_sherline5400.h
#define MICROSTEPS 4
#define DEFAULT_X_STEPS_PER_MM (94.488188976378*MICROSTEPS)
#define DEFAULT_Y_STEPS_PER_MM (94.488188976378*MICROSTEPS)
#define DEFAULT_Z_STEPS_PER_MM (94.488188976378*MICROSTEPS)
#define DEFAULT_STEP_PULSE_MICROSECONDS 10
#define DEFAULT_MM_PER_ARC_SEGMENT 0.1
#define DEFAULT_RAPID_FEEDRATE 500.0 // mm/min
#define DEFAULT_FEEDRATE 250.0
#define DEFAULT_ACCELERATION (DEFAULT_FEEDRATE*60*60/10.0) // mm/min^2
#define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
#define DEFAULT_STEPPING_INVERT_MASK ((1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))
#define DEFAULT_REPORT_INCHES 0 // false
#define DEFAULT_AUTO_START 1 // true
#define DEFAULT_INVERT_ST_ENABLE 0 // false
#define DEFAULT_HARD_LIMIT_ENABLE 0  // false
#define DEFAULT_HOMING_ENABLE 0  // false
#define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
#define DEFAULT_HOMING_RAPID_FEEDRATE 250.0 // mm/min
#define DEFAULT_HOMING_FEEDRATE 25 // mm/min
#define DEFAULT_HOMING_DEBOUNCE_DELAY 100 // msec (0-65k)
#define DEFAULT_HOMING_PULLOFF 1 // mm
#define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-255)
#define DEFAULT_DECIMAL_PLACES 3
#define DEFAULT_N_ARC_CORRECTION 25

// Define runtime command special characters. These characters are 'picked-off' directly from the
// serial read data stream and are not passed to the grbl line execution parser. Select characters
// that do not and must not exist in the streamed g-code program. ASCII control characters may be 
// used, if they are available per user setup. Also, extended ASCII codes (>127), which are never in 
// g-code programs, maybe selected for interface programs.
// TODO: Solidify these default characters. Temporary for now.
#define CMD_STATUS_REPORT '?'
#define CMD_FEED_HOLD '!'
#define CMD_CYCLE_START '~'
#define CMD_RESET 0x18 // ctrl-x

// The temporal resolution of the acceleration management subsystem. Higher number give smoother
// acceleration but may impact performance.
// NOTE: Increasing this parameter will help any resolution related issues, especially with machines 
// requiring very high accelerations and/or very fast feedrates. In general, this will reduce the 
// error between how the planner plans the motions and how the stepper program actually performs them.
// However, at some point, the resolution can be high enough, where the errors related to numerical 
// round-off can be great enough to cause problems and/or it's too fast for the Arduino. The correct
// value for this parameter is machine dependent, so it's advised to set this only as high as needed.
// Approximate successful values can range from 30L to 100L or more.
#define ACCELERATION_TICKS_PER_SECOND 60L

// Minimum planner junction speed. Sets the default minimum speed the planner plans for at the end
// of the buffer and all stops. This should not be much greater than zero and should only be changed
// if unwanted behavior is observed on a user's machine when running at very slow speeds.
#define MINIMUM_PLANNER_SPEED 0.0 // (mm/min)

// Minimum stepper rate. Sets the absolute minimum stepper rate in the stepper program and never runs
// slower than this value, except when sleeping. This parameter overrides the minimum planner speed.
// This is primarily used to guarantee that the end of a movement is always reached and not stop to
// never reach its target. This parameter should always be greater than zero.
#define MINIMUM_STEPS_PER_MINUTE 800 // (steps/min) - Integer value only

// Time delay increments performed during a dwell. The default value is set at 50ms, which provides
// a maximum time delay of roughly 55 minutes, more than enough for most any application. Increasing
// this delay will increase the maximum dwell time linearly, but also reduces the responsiveness of 
// run-time command executions, like status reports, since these are performed between each dwell 
// time step. Also, keep in mind that the Arduino delay timer is not very accurate for long delays.
#define DWELL_TIME_STEP 50 // Integer (1-255) (milliseconds)

// Number of homing cycles performed after when the machine initially jogs to limit switches.
// This help in preventing overshoot and should improve repeatability. This value should be one or 
// greater.
#define N_HOMING_CYCLE 2 // Integer (1-128)

// Number of blocks Grbl executes upon startup. These blocks are stored in EEPROM, where the size
// and addresses are defined in settings.h. With the current settings, up to 5 startup blocks may
// be stored and executed in order. These startup blocks would typically be used to set the g-code
// parser state depending on user preferences.
#define N_STARTUP_LINE 3 // Integer (1-5)

// ---------------------------------------------------------------------------------------
// FOR ADVANCED USERS ONLY: 

// Toggles XON/XOFF software flow control for serial communications. Not officially supported
// due to problems involving the Atmega8U2 USB-to-serial chips on current Arduinos. The firmware
// on these chips do not support XON/XOFF flow control characters and the intermediate buffer 
// in the chips cause latency and overflow problems with standard terminal programs. However, 
// using specifically-programmed UI's to manage this latency problem has been confirmed to work.
// As well as, older FTDI FT232RL-based Arduinos(Duemilanove) are known to work with standard
// terminal programs since their firmware correctly manage these XON/XOFF characters. In any
// case, please report any successes to grbl administrators!
// #define ENABLE_XONXOFF // Default disabled. Uncomment to enable.

// Creates a delay between the direction pin setting and corresponding step pulse by creating
// another interrupt (Timer2 compare) to manage it. The main Grbl interrupt (Timer1 compare) 
// sets the direction pins, and does not immediately set the stepper pins, as it would in 
// normal operation. The Timer2 compare fires next to set the stepper pins after the step 
// pulse delay time, and Timer2 overflow will complete the step pulse, except now delayed 
// by the step pulse time plus the step pulse delay. (Thanks langwadt for the idea!)
//   This is an experimental feature that should only be used if your setup requires a longer
// delay between direction and step pin settings (some opto coupler based drivers), as it may
// adversely effect Grbl's high-end performance (>10kHz). Please notify Grbl administrators 
// of your successes or difficulties, as we will monitor this and possibly integrate this as a 
// standard feature for future releases. However, we suggest to first try our direction delay
// hack/solution posted in the Wiki involving inverting the stepper pin mask.
// NOTE: Uncomment to enable. The recommended delay must be > 3us and the total step pulse
// time, which includes the Grbl settings pulse microseconds, must not exceed 127us. Reported
// successful values for certain setups have ranged from 10 to 20us.
// #define STEP_PULSE_DELAY 10 // Step pulse delay in microseconds. Default disabled.

// ---------------------------------------------------------------------------------------

// TODO: Install compile-time option to send numeric status codes rather than strings.

#endif
