import kivy

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.clock import Clock

class MyW(Widget):

    def my_callback(self, dt):
        self.ids.label1.text = 'My callback is called !' + str(dt);

    def on_touch_down(self, touch):
        Clock.schedule_once(self.my_callback, 1);

class e17App(App):

    def build(self):
        return MyW();


if __name__ == "__main__":
    e17App().run();
