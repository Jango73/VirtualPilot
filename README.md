# VirtualPilot

This is a project I started using my 3D engine. I wanted to make a simple flight sim and model the Airbus A320.
It is a work in progress, there is much left to do.

## Building

Open .pro file in Qt Creator and build **without** shadow build option.

## Things it does

* Basic flight dynamics (not real aerodynamics but something that looks like it)
* Load procedural terrain
* Load an A320 with 3D cockpit
    * Electrical system
    * FMGC
    * PFD, ND and MCDU displays
    * Basic flight plan (some test waypoints)
    * Fly-by-wire
