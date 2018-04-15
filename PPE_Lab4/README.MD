# Windows Programming Laboratory Work #4
## Subject
_Windows Timer. Animation._

## Bonus Objectives

- [x] Increase and decrease animation speed using mouse wheel (2 pt)
- [x] Solve flickering problem (2 pt) please describe in your readme/report how you did it
- [x] Add animated objects which interact with each other (2-6 pt), ex.:
    - Few balls which have different velocity and moving angles. In order to get max points, add balls with mouse, make balls to change color on interaction and any other things that will show your engineering spirit
    - Any other interesting and reach in animation application
- [x] Animate a Nyan Cat that leaves a rainbow tail (Math.floor(+35% for task with interacting objects))

## Result
Implemented in C#
* On click - balls of different colors and with different velocities appear.
* When balls interacts with the window boundaries they change their movement direction and color(2-6p)
* Balls velocity can be changed with mouse wheel (2pt)
* When you press space the nyan cat appears  and she is moving to the right
* Using arrows you can move up and down the nyan cat
* When nyan cat and balls collide, the balls dissapear.
* Flickering problem was solved by using double - buffer.(2pt)

```C#
this.SetStyle(
                System.Windows.Forms.ControlStyles.UserPaint |
                System.Windows.Forms.ControlStyles.AllPaintingInWmPaint |
                System.Windows.Forms.ControlStyles.OptimizedDoubleBuffer,
                true);
```
or 
```C#
this.DoubleBuffered = true;
```

  ## Conclusion
In this laboratory work, we learned to make some animation using timer and a little bit of our creativity. So, I noticed that animations
are created, by redrawing the window every timer tick, so in order to make the balls move , we have to redraw them every time in a
different position or if we use sprites, every tick we have to put in the picture box another sprite.
At the beginning of the work, I met the flickering problem, in this case you should use double buffering, because when you use two buffers
while an image /frame is shown a separate frame is buffered to be shown next. 
![night](Results/screen2.bmp)
