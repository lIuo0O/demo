import kivy

from kivy.app import App
from kivy.uix.widget import Widget

class MyW(Widget):
    def b_smash(self):
        self.ids.b1.text='Pudding';

class e7App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e7App().run();
