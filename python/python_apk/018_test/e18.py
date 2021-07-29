import kivy

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.clock import Clock

class MyW(Widget):

    def my_callback(self, dt):
        self.ids.label1.text = 'My callback is called ' + str(dt);

    def on_touch_down(self, touch):
        if str(touch.button) == 'left':
            Clock.schedule_interval(self.my_callback, 1/30.0)
        if touch.is_double_tap:
            self.ids.label1.text = '';
            Clock.unschedule(self.my_callback);

class e18App(App):
    
    def build(self):
        return MyW();


if __name__ == "__main__":
    e18App().run();
