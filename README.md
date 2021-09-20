# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## Reflection

#### PID Controller

PID Controller, standing for Proportional, Integral and Derivative is a controller that takes the current value and the cross-track error to generate steering inputs that allow the car to follow the desired path.

The full formula for PID controller output is the following (code from `src/pid.cpp`):

```
steer(cte): -Kp * cte - Kd * (cte - PrevCte) - Ki * TotalCte;
```

where `Kp`, `Kd` and `Ki` are the proportional, derivative and integral part of the controller equation.

The proportional part `Kp` is responsible for the sensitivity of the controllers' response, i.e. the higher it is, the quicker will be the response to error. However, a highly sensitive controller will quickly start to oscilate and eventually overshoot.

The derivative part `Kd` is responsible for managing that overshooting. It means, that the higher the slope of the current trajectory of the car towards the ideal track, the less agressive next steering signal will be. `Kd` effectively prevents the controller from oscilating after a strong response.

The integral part `Ki` can compensate for any constant bias the controlled object might have by adjusting the output to a sum of all cte's observed in the lifecycle of the controller (an integral).

#### Tuning PID parameters

My approach to tuning PID hyperparameters was as found in one of the [forum discussions](https://discussions.udacity.com/t/how-to-tune-parameters/303845/4?u=jgrodowski). I started with `Ki` and `Kd` set to 0, which makes the controller a simple P-controller and tried to tune `Kp` so that the error and oscilations remain small for the longest possible distance travelled until the car overshoots.

Then I started increasing `Kd` to compensate overshooting and observed how the car became more stable in several small steps, from `0.1` up to `3.5`.

Finally, I introduced a really small `Ki` which subjectively made the car drive back to the center of the lane a bit quicker. I also revisited `Kp` and increased by `0.02` at the end to make steering responses a bit snappier.

Final parameters: `Kp = 0.09; Kd = 3.5, Ki = 0.001`

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
