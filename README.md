# VirtualPilot

This is a project I started using my 3D engine. I wanted to make a simple flight sim and model the Airbus A320.
It is a work in progress, there is much left to do.

## Building

Please see the Building page for instructions and comments.

## Things it does

* Basic flight dynamics (not real aerodynamics but something that looks like it)
* Load procedural terrain (and possibly real world terrain if the tiles are present)
* Load a navaid database (only US navaids for now)
* Load an A320 with 3D cockpit
    * Electrical system
    * FMGC (Flight Management and Guidance Computer)
    * PFD (Primary Flight Display)
    * ND (Navigation Display)
    * SD (System Display)
    * MCDU (Multifunction Control and Display Unit)
    * Basic flight plan (some hard-coded test waypoints)
    * Fly-by-wire

## Things to work on

* Feature fixes in Quick3D (see its own repository for details)
* Airport generation => work in progress
* Navaid database => work in progress
    * Usage of a binary format, plain text XML is way too slow on load
* Concerning the A320
    * Finish the 3D cockpit (and eventually the whole aircraft for outside views)
    * Finish the FMGC and MCDU
    * Create all SD pages
    * Load a flight plan file (why not .fms, the X-Plane format)
    * Finish the ELAC (Elevator and Aileron Computer)
    * Finish the FAC (Flight Augmentation Computer)
    * Finish the normal flight law
    * Create the alternate flight laws
    * Create the hydraulic system
    * Create the pneumatic system
    * Create the CFIDU (Centralized Fault Display Interface Unit)
    * The list never ends...

## Building on Windows, using QtCreator 4.X and Qt 5.X

1. Open the VirtualPilot.pro in QtCreator
2. Go to the projects tab
3. Uncheck Shadow Build (it is always checked by default when opening a new Qt project)
4. In the Build Steps group, click the Details
5. In Make arguments, type -jX where X is a number that depends on the number of cores you want to use for build (usually 6 or 8)
6. Compile the whole project

## Building on Linux, using QtCreator 4.X and Qt 5.X

The procedure here should be the same as above, but has not been tested yet.

## FAQ

**Q**. **Why can't I build using shadow build?**  
**A**. The project has dependencies on submodules, i.e quick3d and qt-plus. When those are finished building, the resulting library (.dll or .so) is copied to the bin folder of VirtualPilot. This copy does not work with shadow build, I did not take the time to understand why and fix it yet. But it is just a matter of using the correct paths...

**Q**. **Why do my changes to some file in qt-plus or Quick3d don't show up at runtime?**  
**A**. The library was probably not copied to the **bin** folder of Virtual Pilot after build.  
The **qt-plus** and **Quick3d** libraries are copied when **Components_Generic** is done building.
Until I fix the project for all dependencies to copy correctly all the time, you may do the following:  
When making a change in **qt-plus** or **Quick3D**, open any .cpp file in **Components_Generic**. Add a space anywhere, remove it, save the file (this forces a build of the module). Compile **Components_Generic**, the **qt-plus** and **Quick3D** libraries will be copied to the **bin** folder.
