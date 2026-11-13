# Seven Segment LUT

A lightweight, header-only C library for generating lookup tables (LUTs) for seven-segment displays.

The library provides a convenient way to generate a seven-segment lookup table for different hardware pin configurations. Simply specify the bit position assigned to each segment, and the macros generate the corresponding display patterns.

## Features

- Header-only, with no dependencies
- Configurable bit positions for each segment
- Supports hexadecimal-style characters (`0–9`, `A–F`) and additional characters (`H`, `L`, `P`, `U`)
- Generates an 8-bit display pattern for each character
- Assumes **active-high** segment control

## Segment Mapping

The library uses the following segment naming convention:

```text
  --- A ---
 |         |
 F         B
 |         |
  --- G ---
 |         |
 E         C
 |         |
  --- D ---
```

The decimal point (`DP`) is not included in the lookup table.

## Basic Usage

Include `SevenSegment.h` and define a lookup table using `SEVEN_SEGMENT_LUT()`.

The arguments specify the bit positions assigned to segments `A` through `G`, respectively.

```c
#include <stdint.h>
#include "SevenSegment.h"

// Map segments A-G to bits 0-6.
static const uint8_t segment_lut[SS_COUNT] =
    SEVEN_SEGMENT_LUT(0, 1, 2, 3, 4, 5, 6);

int main(void) {
    // Display the number 5.
    uint8_t pattern = segment_lut[SS_FIVE];

    // Use pattern to drive your display hardware.
    (void)pattern;

    return 0;
}
```

For a different hardware configuration, simply change the bit positions:

```c
// Map segments A-G to bits 1-7.
static const uint8_t segment_lut[SS_COUNT] =
    SEVEN_SEGMENT_LUT(1, 2, 3, 4, 5, 6, 7);
```

The resulting lookup table can be used directly with GPIO, shift registers, SPI peripherals, or other display-driving hardware.

## ATmega328P Bare-Metal SPI Example

The following example demonstrates using the library with an ATmega328P and an SPI-connected 74HC595 shift register.

### Connections

| ATmega328P | 74HC595 |
|---|---|
| PB3 (MOSI) | DS (SER) |
| PB5 (SCK) | SHCP (SRCLK) |
| PB1 | STCP (RCLK) |
| GND | GND |

Connect the 74HC595 outputs to the corresponding seven-segment display pins.

This example assumes:
- A common-cathode, active-high seven-segment display.
- A 74HC595 shift register.
- An external current-limiting resistor for each segment.
- A CPU clock frequency of 16 MHz.

```c
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "SevenSegment.h"

#define LATCH_PIN PB1

// Segment bit positions: A-G -> Q0-Q6.
static const uint8_t segment_lut[SS_COUNT] =
    SEVEN_SEGMENT_LUT(0, 1, 2, 3, 4, 5, 6);

static void spi_init(void) {
    // Configure MOSI, SCK and latch as outputs.
    DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB1);

    // Configure SPI as master, clock = F_CPU / 16.
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

static void spi_transmit(uint8_t data) {
    SPDR = data;

    // Wait for transmission to complete.
    while (!(SPSR & (1 << SPIF)));
}

static void display_write(uint8_t pattern) {
    // Begin latch pulse.
    PORTB &= ~(1 << LATCH_PIN);

    spi_transmit(pattern);

    // Latch the transmitted data.
    PORTB |= (1 << LATCH_PIN);
    PORTB &= ~(1 << LATCH_PIN);
}

int main(void) {
    spi_init();

    uint8_t i = 0;

    while (1) {
        display_write(segment_lut[i]);

        i = (i + 1) % SS_COUNT;

        _delay_ms(500);
    }

    return 0;
}
```

**Note:** If your shift register or display wiring requires inverted logic, invert the lookup-table output before transmitting it:

```c
display_write(~segment_lut[i]);
```

## Character Index

The enum `SevenSegment` defines the lookup-table indices:

| Enum | Character |
|---|---|
| `SS_ZERO` – `SS_NINE` | 0–9 |
| `SS_A` – `SS_F` | A–F |
| `SS_H` | H |
| `SS_L` | L |
| `SS_P` | P |
| `SS_U` | U |
| `SS_COUNT` | Number of entries in the LUT |

Use `SS_COUNT` as the lookup-table length and when iterating through all available characters.

## License

Copyright 2026 Joseph Agrane

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.