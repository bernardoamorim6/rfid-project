# Automated Object Sorting System

A university team project: a conveyor-belt system that identifies objects
by shape and colour using a computer vision module, tags/reads them via
RFID, and sorts them with a servo-actuated separation mechanism at the
discharge end.

## My contribution

The vision/classification pipeline ran on a separate OpenMV camera module
and was **not** written by me. My part of the project was the
electromechanical and integration layer around it:

- **RFID tag reading** — reading MIFARE cards via an MFRC522 reader over
  SPI, for object identification (`rfid_reader.ino`)
- **Camera integration** — SPI communication with the OpenMV module to
  receive classification results from the vision system (`openmv_spi_receiver.ino`)
- **Status display** — writing system status/output to an LCD
  (`display_output.ino`)

## What's missing

The conveyor motor start/stop control and servo-actuated separation logic
were also part of my contribution to this project, but I wasn't able to
recover the original source files for this repo. If found, they'll be
added here.

## Files

| File | Description |
|---|---|
| `rfid_reader.ino` | Reads MIFARE RFID tags via MFRC522 (SPI) |
| `openmv_spi_receiver.ino` | Receives classification data from an OpenMV camera over SPI |
| `write_to_display.ino` | Drives a 16x2 LCD status display |

## Hardware

- Arduino (or compatible microcontroller)
- MFRC522 RFID reader module
- OpenMV camera module (vision processing, separate codebase)
- 16x2 character LCD
- Conveyor belt with DC motor drive
- Servo-actuated separator arm

---

Team project completed as part of university coursework.