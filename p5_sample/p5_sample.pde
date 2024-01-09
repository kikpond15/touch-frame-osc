import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;
int touchsLenght = 0;
ArrayList<PVector> touchs = new ArrayList<PVector>();

void setup() {
  size(1500, 1000);
  frameRate(25);
  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);
}

void draw() {
  background(0);
  for (int i=0; i<touchs.size(); i++) {
    ellipse(touchs.get(i).x, touchs.get(i).y, 10, 10);
  }
}

void oscEvent(OscMessage msg) {
  //msg.print();
  if (msg.checkAddrPattern("/touchesLenght")) {
    touchsLenght = msg.get(0).intValue();
    if (touchsLenght == 0) touchs.clear();
  }
  if (msg.checkAddrPattern("/touches/position")) {
    touchs.clear();
    for (int i=0; i<touchsLenght; i++) {
      PVector p = new PVector(msg.get(i*3).intValue(), msg.get((i*3)+1).intValue(), msg.get((i*3)+2).intValue());
      touchs.add(p);
    }
  }
}
