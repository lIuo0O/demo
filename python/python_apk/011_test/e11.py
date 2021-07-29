from kivy.app import App
from kivy.properties import ObjectProperty
from kivy.uix.widget import Widget
from kivy.clock import Clock
from plyer import accelerometer

class Accel(Widget):
    
    def __init__(self):
        super(Accel, self).__init__();
        self.sensorEnabled = False;

    def get_acceleration(self, dt):
        val = accelerometer.acceleration;

        self.ids.label1.text = "x: " + str(val[0]);
        self.ids.label2.text = "y: " + str(val[1]);
        self.ids.label3.text = "z: " + str(val[2]);

    def pressed(self):
        try:
            if not self.sensorEnabled:
                accelerometer.enable();
                Clock.schedule_interval(self.get_acceleration, 1/20.);
                self.sensorEnabled = True;
                self.ids.button1.text = "Stop";
            else:
                accelerometer.disable();
                Clock.unschedule(self.get_acceleration);
                self.sensorEnabled = False;
                self.ids.button1.text = 'Start';
        except NotImplementedError:
            import traceback;
            traceback.print_exc();
            self.ids.status.text = 'Accelerometer is not supported for your platform';

class e11App(App):

    def build(self):
        return Accel();

if __name__ == "__main__":
    e11App().run();
