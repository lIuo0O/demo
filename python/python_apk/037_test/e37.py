import kivy

from kivy.app import App
from kivy.uix.widget import Widget

class MyW(Widget):
    pass

class e37App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e37App().run();
