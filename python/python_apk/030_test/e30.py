import kivy

from kivy.app import App
from kivy.uix.floatlayout import FloatLayout

class MyW(FloatLayout):
    pass;

class e30App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e30App().run();
