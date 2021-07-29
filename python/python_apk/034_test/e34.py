import kivy

from kivy.app import App
from kivy.uix.anchorlayout import AnchorLayout
from kivy.clock import Clock

class MyW(AnchorLayout):
    pass

class e34App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e34App().run();
